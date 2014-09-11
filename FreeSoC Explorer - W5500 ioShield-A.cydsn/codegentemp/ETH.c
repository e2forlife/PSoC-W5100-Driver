/**
 * \addtogroup w5x00
 * @{
 */

/**
 * \file Driver implementation for interfacing with the W5x00 device
 * \author Chuck Erhardt (chuck@e2forlife.com)
 *
 * This file contains the main driver implementation for control
 * of the W5x00 device.
*/

/*
 * Change Log:
 * 
 * V1.1
 * - Modified the SPI access function to remove hard wait for READ_WRITE_DELAY  <CE>
 * - Removed READ_WRITE_DELAY Parameter <CE>
 * - Added validator to SS_NUM parameter to ensure that the value is the range 0-3 <CE>
 * - Removed "inline" keywords from interal register access function to promote
 *   compatibility with Keil PSoC3 compilers that don't support them. <CE>
 * - Fixed bug in _ProcessRxData() that caused the read pointer not to be updated without
 *   the lookahead flag being set. <CE>
 * V1.2
 * - Added _STS_SPI_IDLE flag to _SpiDone conditions to prevent deadlocking that
 *   was occuring during the first read or write using the SPI device (SPIM moded) <CE>
 * - Removed the check for SOCKET_ESTABLISHED at the start of the TcpReceive
 *   function to allow for reading received socket data after the socket was dropped
 *   by the remote server.  It was brought to my attention that this occurs when
 *   operating with client connection to HTTP servers. <CE>
 * - Added a MAC address parser and MAC to String Converter. <CE>
 */

/* Cypress library includes */
#include <cytypes.h>
#include <cylib.h>

/*  include functions and types for the driver */
#include "ETH.h"
/* Include register address constants */
#include "ETH_reg55.h"

/* include the serial interface functions */
#include <SPI.h>
#include <CSN.h>

extern uint8 SPI_initVar;

typedef struct
{
	uint8  Protocol;
	uint8  SocketFlags;
	uint16 SourcePort;
	uint8  ServerFlag;
	uint8  TxBufferSize;
	uint8  RxBufferSize;
} ETH_SOCKET;

#if (5 == 1) // W5100 Specific
const uint32 ETH_SOCKET_TX_BASE[4] = { 0x4000, 0x4800, 0x5000, 0x5800 };
const uint32 ETH_SOCKET_RX_BASE[4] = { 0x6000, 0x6800, 0x7000, 0x7800 };

#define ETH_MAX_SOCKET   ( 4 )
#define ETH_BURST_MAX    ( 1 )

/**
 * \def ETH_SOCKET REG(s,r)
 * \brief Convert the socket number to a base address within the W5100
 */
#define ETH_SOCKET_REG(s,r)           ( (((uint32)s<<8)+0x0400) + r )

#elif (5 == 2) // W5200 Specific
	
const uint32 ETH_SOCKET_TX_BASE[8] = { 0x8000, 0x8800, 0x9000, 0x9800, 0xA000, 0xA800, 0xB000, 0xB800 };
const uint32 ETH_SOCKET_RX_BASE[8] = { 0xC000, 0xC800, 0xD000, 0xD800, 0xE000, 0xE800, 0xF000, 0xF800 };

#define ETH_MAX_SOCKET   ( 8 )
#define ETH_BURST_MAX    ( 0x7FFF )

/**
 * \def ETH_SOCKET REG(s,r)
 * \brief Convert the socket number and register to a base address within the W5200
 */
#define ETH_SOCKET_REG(s,r)           ( ((uint32)s<<8) + r )
#elif (5 == 5) // W5500 Specific

	const uint32 ETH_SOCKET_TX_BASE[8] = { 0x00020000, 0x00060000, 0x000A0000, 0x000E0000, 0x00120000, 0x00160000, 0x001A0000, 0x001E0000 };
	const uint32 ETH_SOCKET_RX_BASE[8] = { 0x00030000, 0x00070000, 0x000B0000, 0x000F0000, 0x00130000, 0x00170000, 0x001B0000, 0x001F0000 };

	#define ETH_MAX_SOCKET   ( 8 )
	#define ETH_BURST_MAX    ( 0xFFFF )

	const uint32 ETH_W5500_BSB[8] = { 0x00010000, 0x00050000, 0x00090000, 0x000D0000, 0x00110000, 0x00150000, 0x00190000, 0x001E0000 };
	/**
	 * \def ETH_SOCKET REG(s,r)
	 * \brief Convert the socket number and register to a base address within the W5500
	 */
	#define ETH_SOCKET_REG(s,r)           ( ETH_W5500_BSB[s] + r )

#else
	#error "W5x00 components other than W5100, W5200 and W5500 are not currently supported"
#endif

ETH_SOCKET ETH_SocketConfig[ETH_MAX_SOCKET];
uint32 ETH_SubnetMask;

uint8 ETH_MAC[6]; /* V1.2: removed = {00-de-ad-be-ef-00}; */

/* ------------------------------------------------------------------------ */
/* V1.2 HEX digit conversion tools for MAC Address parsing */
#define ETH_ISXDIGIT(x) \
( ((x>='0')&&(x<='9'))||((x>='a')&&(x<='f'))||((x>='A')&&(x<='F')) )
/* ------------------------------------------------------------------------ */
#define ETH_HEX2BIN(x) \
( ((x>='0')&&(x<='9'))? (x-'0') : \
  ((x>='a')&&(x<='f'))? ((x-'a')+10) : \
  ((x>='A')&&(x<='F'))? ((x-'A')+10) : 0 )
/* ------------------------------------------------------------------------ */
#define ETH_BIN2HEX(x) \
( (x>9)? ((x-10)+'A') : (x + '0'))
/* END V1.2 defines */
/* ------------------------------------------------------------------------ */
#if !defined(CY_SCB_SPI_H)
	/* SPIM Code */
/* ------------------------------------------------------------------------ */	
/* V1.1 : Macro definition for the SpiDone flag. */
/*  
	V1.2 : Added SPI_IDLE flag to the condition for done to eliminate
	deadlocking when IDLE but not done.  This seems to occur during the
	initial write/read to/from the SPI port.
*/
/**
 * \brief Macro to determine the state of the spi done
 * This macro reads the status register of the transmitter and masks off the doen bit.
 */
#define ETH_SpiDone     (SPI_ReadTxStatus() & (SPI_STS_SPI_DONE | SPI_STS_SPI_IDLE))
#else
/* include SPI function header for the SCB */
#include <SPI_SPI_UART.h>

/* V1.1 : Include the header for the select pin used. */
#define ETH_SpiDone    ((SPI_SpiUartGetTxBufferSize()==0)?1:0)
#endif

/* ------------------------------------------------------------------------ */
/**
 * \brief Select the active SCB chip select connected to the W51
 *
 * this fucntion will set the active SS line within the SCB to select and
 * communicate with the W5100 device.
 * \note this functions requires that the device chip select is originating
 *  from the SPI device.
 */
void
ETH_ChipSelect( void )
{
	/*
	 * User code for setting the chip select enable.  This is called once
	 * at the beginning of each tranfer to/from the W5100, so we recommend
	 * either doing nothing (SPIM SS straight out), or to switch the demux
	 * component to select the correct output for the SS routing.  This
	 * should probably not drive a pin directly since there is no return
	 * call from the driver that would allow an enable/disable type of
	 * implementation for CSN control.
	 */
	CSN_Write( ~(1<<0) );
	/* `#START CHIP_SELECT_GENERATION` */

	/* `#END` */
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Called at the end of a transfer to deselect the device
 *
 * This function is called by the chip access functions from the core
 * interface code to de-select the device after the read/write operation
 * has been completed. This was changed from the "old way" of doing things
 * using the hardware SS pin because the FIFO will empty too quickly
 * causing interruptions in the transfer during burst writes at high
 * speed. This allows bursting without having to have a huge software
 * FIFO and using DMA to keep the buffer loaded.
 */
void
ETH_ChipDeSelect( void )
{
	/* V1.1: Wait for SPI operation to complete */
	while( ETH_SpiDone == 0) {
		CyDelayUs(1);
	}
	CSN_Write(0xFF);
}

/* ======================================================================== */
/* Generic SPI Functions */
/*
 * NOTE: when using the SPIM, there must be a buffer length of at least 4
 * bytes to allow the transfer/receive cycle for each read/write operation
 * to be contained within the FIFO buffer.
 */
#if !defined(CY_SCB_SPI_H)
	/* SPIM Code */
/* ------------------------------------------------------------------------ */
/**
 * \brief write Data to the W5100 at the specified address
 * \param addr Address of register or memory buffer
 * \param dat Data to write to the device
 *
 * This function will send the WRITE opcode, address and data to the W5100
 * in order to write the data to the specified register.
 */
void 
ETH_ChipWrite(uint32 addr, uint8 *dat, uint16 length)
{
	uint16 txLen;
	uint16 txCount;
	uint16 adr;
	uint8 crit;
	/* V2.0 W5500 block select bits, stripped from the upper 16 bits of the address */
	uint8 bsb;
	
	/* V1.1: Wait for SPI operation to complete */
	while( ETH_SpiDone == 0) {
		CyDelayUs(1);
	}
	/* V1.1: End change */
	
	crit = CyEnterCriticalSection();
	
	adr = (addr&0x0000FFFF);
	bsb = (addr>>16)&0x001F; /* remove the block-select bits from the address */
	
	txLen = 0;
	txCount = 0;
	do {
		/* Using internal device SS generation */
		ETH_ChipSelect();
		/*
		 * The first thing to do is to clear the Rx Buffer of any lingering
		 * data left from other transfers.  Then send the data per the W5100
		 * datasheet p.62
		 */
		SPI_ClearRxBuffer();
		/* Begin transfer of data to device */
#if (5 == 1)
		/*
	     * The W5100 uses an opcode followed by the register/buffer
	     * address for each data element transfered.
	     */
		txLen = 1;
		SPI_WriteTxData(ETH_WRITE_OP);
		SPI_WriteTxData((adr>>8)&0x00FF);
		SPI_WriteTxData(adr&0x00FF);
#elif (5 == 2)
	    /*
	     * The Header block for the W5200 uses the address, plus
	     * a length word which contains a read/write bit.  Setting
	     * the bit to a 1 (0x80) will enable write mode
	     */
		txLen = (length > ETH_BURST_MAX)? ETH_BURST_MAX : length;
		SPI_WriteTxData( (adr>>8) & 0x00FF);
		SPI_WriteTxData( adr & 0x00FF );
		SPI_WriteTxData( 0x80 | ((txLen>>8)&0x007F) );
		SPI_WriteTxData( txLen & 0x00FF );
#elif (5 == 5)
		/*
	 	 * Build the header block for the W5500, using the length to
	     * added the command length (1, 2, 4 or n) to the set.
		 */
		txLen = length; /* default to the length, since there is N-length data */
		/* 
	     * configure the BSB byte to contain the write bit set.
	     * note/todo : enable SPi-less usage and fixed mode transfer data for
	     * the use without having SPI.
	     */
		bsb = (bsb << 3) | 4;
		
		SPI_WriteTxData( (adr>>8) & 0x00FF);
		SPI_WriteTxData( adr & 0x00FF );
		SPI_WriteTxData( bsb );
		
#endif
		/*
         * send the sequence of bytes to the device following the 
         * header data transfer.  This will wait for the FIFO to  have
         * available memory prior to writing the data to the part.
         * at the end of the block the loop exits and ends the operation
         * by setting the chip select high.
         */
		// Transmit data block
		do {
			while ( (SPI_ReadTxStatus() & SPI_STS_TX_FIFO_NOT_FULL) == 0);
			SPI_WriteTxData(dat[txCount++]);
			--length;
			--txLen;
			++adr;
		} while ( txLen > 0 );

		while( ETH_SpiDone == 0) {
			CyDelayUs(1);
		}
		// End operation
		ETH_ChipDeSelect();
	} while (length > 0);
	
	CyExitCriticalSection( crit );
}

/* ------------------------------------------------------------------------ */
/**
 * \brief Read data from the W5100 at the spsecified address
 * \param addr Address from which to read
 * \returns the data read from the address
 *
 * this fucntion will access a W5100 memory location and read the contents
 * using the serial protocol specified on P.61 of the datasheet.
 */
void
ETH_ChipRead(uint32 addr, uint8 *dat, uint16 length)
{
	uint16 rxIndex; /* the data index in to the receive buffer */
	uint16 address; /* the current chip address */
	uint16 rxLen;   /* the number of bytes to read durning the burst */
	uint16 txBytes; /* the number of dummy bytes send during th read */
	uint8 dump;     /* the number of bytes to ignore from the data stream readback */
	uint16 rxCount; /* the number of bytes read from the chip */
	uint8 rxb;      /* the byte within the SPI buffer read from the chip */
	/* V2.0 W5500 block select bits, stripped from the upper 16 bits of the address */
	uint8 bsb;
	
	/* V1.1: Wait for SPI operation to complete */
	while( ETH_SpiDone == 0) {
		CyDelayUs(1);
	}
	/* V1.1: End change */

	address = (addr & 0x0000FFFF); // assign base pointer address
	bsb = (addr>>16)&0x001F; /* remove the block-select bits from the address */
	rxIndex = 0;    // default the starting index for the receive to zero
	
	do {
		/* Write the chip select instance to select the device */
		ETH_ChipSelect();
		/*
		 * First, clear the Rx Buffer of any waiting data.  Then begin the
		 * read operation by sending the op code, followed byte the address
		 * from which the read will be executed, then send a dummy byte
		 * of zeros to read the data from the device.
		 */
		SPI_ClearRxBuffer();
		/* Send the device header */
		rxCount = 0; // initialize the bytes received to none
#if (5 == 1 )
		/*
		 * W1100 interface code
		 * --------------------
		 * The W5100 only supports 1 byte transfers (no burst mode), so
		 * peg the receive length as 1 byte, and issue a number of commands
		 * in sequence to simulate a burst read.
		 */
		rxLen = 1;  // The W5100 is limited to 1 byte of data transmitted
		dump = 3;   // The W5100 has a 3-byte packet header
		txBytes = 0; // Send only one byte afte rthe header then end the transfer
		SPI_WriteTxData(ETH_READ_OP);
		SPI_WriteTxData(address>>8);
		SPI_WriteTxData(address&0x00FF);
		
#elif (5 == 2)
		/*
		 * W5200 Interface Header
		 * ----------------------
		 * The W5200 protocol expects an address followed by a read
		 * byte count for the header of the protocol, so, this will
		 * issue reads up to the max burst length
		 */
		dump = 4; /*  The W5200 has a definded data length and a header of 4 bytes */
		rxLen = (length < ETH_BURST_MAX) ? length : ETH_BURST_MAX;
		/* 
		 * Set the number of bytes to transmit before
		 * ending the packet to the calculated value
		 */
		txBytes = 0; 
		/* Send the packet header */
		SPI_WriteTxData( address>>8);
		SPI_WriteTxData( address & 0x00FF );
		SPI_WriteTxData( 0x7F & (rxLen>>8) );
		SPI_WriteTxData( rxLen&0x00FF );
#elif (5 == 5)
		/*
	     * W5500 Interface Header
	     * -----------------------
	     * the W5500 header uses an address, fllowed by a command byte
		 * that included a block select (bank) for selecting the registers
	     * using the address as an offset.  following the BSB byte is
	     * the data read/write phase.  This section generates the custom
	     * W5500 header for reading data from the device.
	     */
		dump = 3; /*  The W5500 has a definded data length and a header of 3 bytes */
		rxLen = length;
		/* 
		 * Set the number of bytes to transmit before
		 * ending the packet to the calculated value
		 */
		txBytes = 0; 
		/* Send the packet header */
		SPI_WriteTxData( address>>8);
		SPI_WriteTxData( address & 0x00FF );
		SPI_WriteTxData( bsb << 3);
#endif

		while (rxCount < rxLen) {
			/*
			 * Since the header is clogging the buffer (and it is inefficient
			 * to just clear the header before executing the reads), this loop
			 * will transmit the data completely the header size before
			 * the data has been read, so, send the data when the rxLength
			 * is not zero.
			 */
			if (txBytes < rxLen ) {
				SPI_WriteTxData( 0 );
				address ++;
				length --;
				txBytes ++;
			}
			/*
			 * Read the data from the buffer.  The header data responses
			 * are going to be sitting in the buffer, so dump them
			 * and just receive the data bock
			 */
			while ( ( SPI_ReadRxStatus()&SPI_STS_RX_FIFO_NOT_EMPTY) == 0);
			rxb = SPI_ReadRxData();
			dat[rxIndex] = rxb;
			if (dump > 0) {
				--dump;
			}
			else {
				rxCount++;
				rxIndex++;
			}
		}
		/* Turn off chip select, and set the buffer */
		ETH_ChipDeSelect();
	}
	while ( length > 0);
}
/* ======================================================================== */
/* SCB Specific Functions */
#else
/* ------------------------------------------------------------------------ */
/**
 * \brief write Data to the W5100 at the specified address
 * \param addr Address of register or memory buffer
 * \param dat Data to write to the device
 *
 * This function will send the WRITE opcode, address and data to the W5100
 * in order to write the data to the specified register.
 */
void
ETH_ChipWrite(uint32 addr, uint8 *dat, uint16 length)
{
	/* TBD */
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Read data from the W5100 at the spsecified address
 * \param addr Address from which to read
 * \returns the data read from the address
 *
 * this fucntion will access a W5100 memory location and read the contents
 * using the serial protocol specified on P.61 of the datasheet.
 */
void
ETH_ChipRead(uint32 addr, uint8 *dat, uint16 length)
{
	/* TBD */
}

#endif

/* ======================================================================== */
/* W5x00 Access Primitaves */
#if (1)
/* ------------------------------------------------------------------------ */
/**
 * \brief Write a 16-bit word to the device
 * \param addr the starting address to which the data will be written
 * \param val the 16-bit value to write
 */
void ETH_ChipWrite16( uint32 addr, uint16 val )
{
	uint16 bigVal;
	
#if !( CY_PSOC3 ) 
	bigVal = CYSWAP_ENDIAN16( val );
#else
	bigValu = val;
#endif
	ETH_ChipWrite( addr, (uint8*)&bigVal, 2 );
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Read a 16-bit value from the device
 * \param addr The starting address from which data will be read
 * \returns the 16-bit value read from the memory.
 */
uint16 ETH_ChipRead16( uint32 addr )
{
	uint16 val;
	
	ETH_ChipRead(addr, (uint8*)&val, 2);
#if !( CY_PSOC3 )
	val = CYSWAP_ENDIAN16( val );
#endif
	
	return( val );
}
/* ======================================================================== */
/* END SECTION */
#endif
/* ======================================================================== */
/* Chip Register access */
#if (1)
// Common Registers
/* ------------------------------------------------------------------------ */
/**
 * \brief Set teh chip mac address to teh specified address
 * \param *mac pointer to the array holding the MAC address
 */
void ETH_SetSourceMAC( uint8 *mac )
{
	ETH_ChipWrite(ETH_REG_SHAR, mac,6 );
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Read the chip source MAC address from the MAC registers
 * \param *mac pointer to the address of the buffer to hold the read MAC address
 */
void ETH_GetSourceMAC( uint8 *mac )
{
	ETH_ChipRead(ETH_REG_SHAR,mac,6);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Set the IPv4 address of the network gateway
 * \param ip IP address of the gateway
 */
void ETH_SetGatewayAddress(uint32 ip)
{
	ETH_ChipWrite(ETH_REG_GAR, (uint8*)&(ip),4);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Read the gateway address from the device
 * \returns the IP address of the gateway
 */
uint32 ETH_GetGatewayAddress( void )
{
	uint32 ip = 0xFFFFFFFF;
	
	ETH_ChipRead( ETH_REG_GAR, (uint8*)(ip), 4);
	
	return ip;
}
/* ------------------------------------------------------------------------ */
/**
 * \brief set the subnet mask of the ethernet device
 * \param the subnet mask (IPv4)
 */
void ETH_SetSubnetMask( uint32 ip )
{
	ETH_ChipWrite(ETH_REG_SUBR, (uint8*)&(ip), 4);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Read the subnet mask from the device
 * \returns the subnet mask that was read from the device.
 */
uint32 ETH_GetSubnetMask( void )
{
	uint32 ip = 0xFFFFFFFF;
	ETH_ChipRead(ETH_REG_SUBR, (uint8*)(ip), 4);
	return ip;
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Write the device source IPv4 address
 * \param ip the ip address to set as the chip IP address
 */
void ETH_SetSourceIP(uint32 ip )
{
	ETH_ChipWrite( ETH_REG_SIPR, (uint8*)&(ip), 4 );
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Read the device's programmed IP address
 * \returns The IPv4 address to which the device is set.
 */
uint32 ETH_GetSourceIP( void )
{
	uint32 ip = 0xFFFFFFFF;
	ETH_ChipRead( ETH_REG_SIPR, (uint8*)(ip), 4 );
	return ip;
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Write a value to the device internal MODE register
 * \param mode the value to be written to the mode register.
 */
void ETH_SetMode( uint8 mode )
{
	ETH_ChipWrite(ETH_REG_MODE, (uint8*)&(mode), 1);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Read the present contents of the device internal mode register
 * \returns the value of the mode register
 */
uint8 ETH_GetMode( void )
{
	uint8 mode;
	ETH_ChipRead(ETH_REG_MODE, (uint8*)&(mode),1);
	return mode;
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Write the value of the interrupt register
 * \param ir the value to be written to the interrupt register
 */
void ETH_SetIR(uint8 ir )
{
	ETH_ChipWrite(ETH_REG_IR,(uint8*)&(ir), 1);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief write a value to the Rx mem size register
 * \param size the value to be written to the register
 */
void ETH_SetSocketRxMemSize( uint8 socket, uint8 size ) 
{
	
#if (5 == 1)
	uint8 sz;
	/*
	 * The W5100 uses memory allocations within one register for all sockets.
	 * the options are set by a 2 bit code for 1, 2, 4, or 8 K
	 */
		ETH_ChipRead( ETH_REG_RMSR, &sz, 1);
		sz = sz & (~(3<<(socket<<1)));
		sz = sz | (size<<(socket<<1));
		ETH_ChipWrite( ETH_REG_RMSR, &sz, 1);
#elif ((5 == 2) || (5 == 5))
	/*
	 * The W5200/W5500 interface uses memory size registers located within the socket
	 * register memory maps.
	 */
	ETH_ChipWrite( ETH_SOCKET_REG(socket,ETH_SOCK_RXMEM), &size, 1);
#endif
}

/* ------------------------------------------------------------------------ */
/**
 * \brief Read the contents of hte rx mem size register
 * \returns the value read from teh register
 */
uint8 ETH_GetSocketRxMemSize( uint8 socket )
{
	uint8 sz;
	
	sz = 0xFF;
#if (5 == 1)
	ETH_ChipRead(ETH_REG_RMSR, &sz, 1);
	sz = (sz >> (socket<<1)) & 0x03;
#elif ((5 == 2)||(5 == 5))
	ETH_ChipRead( ETH_SOCKET_REG(socket,ETH_SOCK_RXMEM), &sz, 1);
#endif
	return sz;
}
/* ------------------------------------------------------------------------ */
/**
 * \brief write a value to the tx mem size register
 * \param size The value to be written to the register
 */
void ETH_SetSocketTxMemSize( uint8 socket, uint8 size )
{
	
#if (5 == 1)
	uint8 sz;
	/*
	 * The W5100 uses memory allocations within one register for all sockets.
	 * the options are set by a 2 bit code for 1, 2, 4, or 8 K
	 */
		ETH_ChipRead( ETH_REG_TXSR, &sz, 1);
		sz = sz & (~(3<<(socket<<1)));
		sz = sz | (size<<(socket<<1));
		ETH_ChipWrite( ETH_REG_TXSR, &sz, 1);
#elif ((5 == 2)||(5 == 5))
	/*
	 * The W5200/W5500 interface uses memory size registers located within the socket
	 * register memory maps.
	 */
	ETH_ChipWrite( ETH_SOCKET_REG(socket,ETH_SOCK_TXMEM), &size, 1);
#endif
}
/* ------------------------------------------------------------------------ */
/**
 * \brief read the contents of the tx mem size register
 * \returns the value read from the register
 */
uint8 ETH_GetSocketTxMemSize( uint8 socket )
{
	uint8 sz;
	
	sz = 0xFF;
#if (5 == 1)
	ETH_ChipRead(ETH_REG_TXSR, &sz, 1);
	sz = (sz >> (socket<<1)) & 0x03;
#elif ((5 == 2)||(5 == 5))
	ETH_ChipRead( ETH_SOCKET_REG(socket,ETH_SOCK_TXMEM), &sz, 1);
#endif
	return sz;
}

/* ======================================================================== */
/* End Section */
#endif
/* ======================================================================== */
/* Socket Registers */
#if (1)
/* ------------------------------------------------------------------------ */
/**
 * \brief Write a value to the socket mode register
 * \param socket the socket number for the addressed register
 * \param mode the value to be written to the register
 */
void ETH_SetSocketMode(uint8 socket, uint8 mode)
{
	ETH_ChipWrite((ETH_SOCKET_REG(socket, ETH_SOCK_MR)),(uint8*)&(mode), 1);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Write a value to the socket command register
 * \param socket the socket number for the addressed register
 * \param cmd the value to be written to the register
 */
void ETH_SetSocketCommand(uint8 socket, uint8 cmd)
{
	ETH_ChipWrite( (ETH_SOCKET_REG(socket, ETH_SOCK_CR)),(uint8*)&(cmd),1);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Read a value from the socket command register
 * \param socket the socket number for the addressed register
 * \returns the value read from the register
 */
uint8 ETH_GetSocketCommand(uint8 socket )
{
	uint8 cmd = 0xFF;
	ETH_ChipRead( (ETH_SOCKET_REG(socket, ETH_SOCK_CR)),(uint8*)(&cmd),1);
	return cmd;
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Write a value to the socket interrupt register
 * \param socket the socket number for the addressed register
 * \param ir the value to be written to the register
 */
void ETH_SetSocketIR(uint8 socket, uint8 ir)
{
	ETH_ChipWrite( (ETH_SOCKET_REG(socket, ETH_SOCK_IR)), (uint8*)&(ir), 1);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Read a value from the socket interrupt register
 * \param socket the socket number for the addressed register
 * \returns the value read from the register
 */
uint8 ETH_GetSocketIR(uint8 socket)
{	
	uint8 ir = 0xFF;
	ETH_ChipRead((ETH_SOCKET_REG(socket, ETH_SOCK_IR)), (uint8*)&(ir), 1);
	return ir;
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Read a value from the socket status register
 * \param socket the socket number for the addressed register
 * \returns the value read from the register
 */
uint8 ETH_GetSocketStatus(uint8 socket)
{ 
	uint8 status = 0xFF;
	ETH_ChipRead(ETH_SOCKET_REG(socket, ETH_SOCK_SR), &status, 1);
	return status;
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Write a value to the socket source port register
 * \param socket the socket number for the addressed register
 * \param port the value to be written to the register
 */
void ETH_SetSocketSourcePort(uint8 socket, uint16 port)
{
	ETH_ChipWrite16(ETH_SOCKET_REG(socket, ETH_SOCK_PORT),port);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Write a value to the socket Destination hardware address register
 * \param socket the socket number for the addressed register
 * \param *mac poitner to the array holding the values to be written to the register
 */
void ETH_SetSocketDestMAC(uint8 socket, uint8* mac)
{ 
	ETH_ChipWrite( ETH_SOCKET_REG(socket, ETH_SOCK_DHAR), &mac[0], 6);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Write a value to the socket Destination IP address register
 * \param socket the socket number for the addressed register
 * \param ip the value to be written to the register
 */
void ETH_SetSocketDestIP(uint8 socket, uint32 ip)
{ 
	ETH_ChipWrite(ETH_SOCKET_REG(socket, ETH_SOCK_DIPR), (uint8*)&ip, 4);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Write a value to the socket destination port register
 * \param socket the socket number for the addressed register
 * \param port the value to be written to the register
 */
void ETH_SetSocketDestPort(uint8 socket, uint16 port)
{ 
	ETH_ChipWrite16( ETH_SOCKET_REG(socket, ETH_SOCK_DPORT), port);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Read a value from the socket Tx free size register
 * \param socket the socket number for the addressed register
 * \returns the value read from the register
 */
uint16 ETH_GetSocketTxFree(uint8 socket)
{ 
	return ETH_ChipRead16(ETH_SOCKET_REG(socket, ETH_SOCK_TXFSR));
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Write a value to the socket tx write pointer register
 * \param socket the socket number for the addressed register
 * \param ptr the value to be written to the register
 */
void ETH_SetSocketTxWritePtr(uint8 socket, uint16 ptr)
{ 
	ETH_ChipWrite16(ETH_SOCKET_REG(socket, ETH_SOCK_TXWR),ptr);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Read a value from the socket tx buffer write pointer register
 * \param socket the socket number for the addressed register
 * \returns the value read from the register
 */
uint16 ETH_GetSocketTxWritePtr(uint8 socket)
{ 
	return ETH_ChipRead16(ETH_SOCKET_REG(socket, ETH_SOCK_TXWR));
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Read a value from the socket rx received data size register
 * \param socket the socket number for the addressed register
 * \returns the value read from the register
 */
uint16 ETH_GetSocketRxSize(uint8 socket)
{
	return ETH_ChipRead16(ETH_SOCKET_REG(socket, ETH_SOCK_RXRSR));
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Write a value to the socket rx read pointer register
 * \param socket the socket number for the addressed register
 * \param ptr the value to be written to the register
 */
void ETH_SetSocketRxReadPtr(uint8 socket, uint16 ptr)
{ 
	ETH_ChipWrite16(ETH_SOCKET_REG(socket, ETH_SOCK_RXRD),ptr);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Read a value from the socket rx buffer read pointer register
 * \param socket the socket number for the addressed register
 * \returns the value read from the register
 */
uint16 ETH_GetSocketRxReadPtr(uint8 socket)
{ 
	return ETH_ChipRead16(ETH_SOCKET_REG(socket, ETH_SOCK_RXRD));
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Set the write poitner starting address for a socket
 * \param socket the socket number to modify
 * \param ptr the address value to write in to the pointer register
 */
void ETH_SetSocketRxWritePtr( uint8 socket, uint16 ptr)
{
	/*
	 * This function is not used on the W5100, since there is no register
	 * defined in the memor map to provide this capability
	 */
#if (5 == 2)
	/*
	 * for the W5200 device, write the pointer value to the register
	 */
	ETH_ChipWrite16( ETH_SOCKET_REG(socket, ETH_SOCK_RXWR), ptr);
#endif
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Initialize the Tx buffer Read pointer register
 * \param socket the sockt to be modified
 * \param ptr the address to store in to the pointer register
*/
void ETH_SetSocketTxReadPtr(uint8 socket, uint16 ptr )
{
	ETH_ChipWrite16( ETH_SOCKET_REG(socket, ETH_SOCK_TXRD), ptr);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Write a command to the socket command register and wait for completion
 * \param socket the addressed socket for the command
 * \param cmd the command to execute
 */
uint32 ETH_ExecuteSocketCommand( uint8 socket, int cmd)
{
	uint32 timeout;
	timeout = 0;
	
	ETH_SetSocketCommand(socket,cmd);
	while ( ( ETH_GetSocketCommand(socket) ) && (timeout < 125))
	{
		++timeout;
		CyDelay(1);
	}
	return( timeout );
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Execute a safe read fo the Tx buffer free size register
 * \param socket the addressed socket to read the available tx buffer
 * \returns the number of bytes available in the transmit buffer for the socket
 */
uint16 ETH_GetTxFreeSize( uint8 socket )
{
	uint16 first, second;
	
	first = 0;
	second = 0;
	do {
		first = ETH_GetSocketTxFree( socket );
		if (first != 0) {
			second = ETH_GetSocketTxFree( socket );
		}
	}
	while (first != second );
	
	return( second );
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Execute a safe read of the received data size
 * \param socket the addressed socketfrom which the data will be read
 * \returns the number of bytes waiting in the recieve buffer of the socket
 */
uint16 ETH_GetRxSize( uint8 socket )
{
	uint16 first, second;
	
	first = 0;
	second = 0;
	do {
		first = ETH_GetSocketRxSize( socket );
		if (first != 0) {
			second = ETH_GetSocketRxSize( socket );
		}
	}
	while (first != second );
	
	return second;
}
/* ------------------------------------------------------------------------ */

// END Socket Register access section
#endif
/* ======================================================================== */
/* W5x00 Data Buffer Memory access primitives */
#if (1)
/* ------------------------------------------------------------------------ */
/**
 * \brief Transfer data from a local data buffer to the chip Tx fifo
 * \param socket the socket buffer to which the data will be written
 * \param offset The offest in to the socket buffer
 * \param *buffer pointer to the local buffer to copy to the transmit fifo
 * \param length the number of bytes to be copied to the transmit fifo
 */
void ETH_ProcessTxData(uint8 socket, uint16 offset, uint8* buffer, uint16 length)
{
	uint16 addr;
	uint16 base;
	uint16 PointerOffset;
	uint16 size;
	
	/*
	 * Read the offset pointer, and calculate the base address for the start of write
	 * in to the chip buffers.  Written data will be offset by the offset byte count
	 * specified in the parameters.
	 */
	base = ETH_GetSocketTxWritePtr(socket) + offset;
	PointerOffset = (base & 0x07FF);
	addr = PointerOffset + ETH_SOCKET_TX_BASE[socket];
	/* calculate the number of bytes from the pointer to the end of the buffer */
	size = 0x0800 - PointerOffset;
	
	/*
	 * is there enough space to write the complete packet
	 * or, shoudl the data be split in to two writes.
	 */
	if ( length > size) {
		/*
		 * There is more data to send than will fit from the pointer to the end
		 * of the memory, so we will write the data in two chunks.  First, write the
		 * data from the pointer to the end of the buffer, then write the portion
		 * remaining to the start (base ptr) of the socket buffer
		 */
		ETH_ChipWrite(addr, buffer, size);
		ETH_ChipWrite(ETH_SOCKET_TX_BASE[socket], &buffer[size], length - size);
	}
	else {
		/* 
		 * there is enough available space from the write point to the end of buffer
		 * to hold the whole packe of information, so just write it to the memory
		 */
		ETH_ChipWrite(addr,buffer,length);
	}
	/* move the write pointer */
	base += length;
	/* 
	 * Store the new write pointer so that the device knows that there is data waiting
	 * to be transmitted over the link.
	 */
	ETH_SetSocketTxWritePtr(socket, base);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Transfer data from the chip receive buffer to a local buffer
 * \param socket the socket buffer from which the data will be read
 * \param offset The offest in to the socket buffer
 * \param *buffer pointer to the local buffer to hold the receive fifo data
 * \param length the max number of bytes to be copied to the local buffer
 * \param flags Flag settings to control read fifo options (lookahead)
 */
void ETH_ProcessRxData(uint8 socket, uint16 offset, uint8* buffer, uint16 length, uint8 flags)
{
	uint16 addr;
	uint16 base;
	uint16 PointerOffset;
	uint16 size;
	
	/*
	 * Read the offset pointer, and calculate the base address for the start of read
	 * in to the chip buffers.  The data read will be offset by the offset byte count
	 * specified in the parameters.
	 */
	base = ETH_GetSocketRxReadPtr(socket) + offset;
	PointerOffset = (base & 0x07FF);
	addr = PointerOffset + ETH_SOCKET_RX_BASE[socket];
	/* calculate the number of bytes from the pointer to the end of the buffer */
	size = 0x0800 - PointerOffset;
	/*
	 * is there enough space to read the complete packet
	 * or, should the data be split in to two reads.
	 */
	if ( length > size) {
		/*
		 * There is more data to send than will fit from the pointer to the end
		 * of the memory, so we will write the data in two chunks.  First, write the
		 * data from the pointer to the end of the buffer, then write the portion
		 * remaining to the start (base ptr) of the socket buffer
		 */
		ETH_ChipRead(addr, buffer, size);
		ETH_ChipRead(ETH_SOCKET_RX_BASE[socket], &buffer[size], length - size);
	}
	else {
		/* 
		 * there is enough available space from the write point to the end of buffer
		 * to hold the whole packe of information, so just write it to the memory
		 */
		ETH_ChipRead(addr,buffer,length);
	}
	if ( (flags & 0x01) == 0 ) { /* V1.1: Added ==0 condition to lookahead flag check */
		/* move the write pointer */
		base += length;
		/* 
		 * Store the new write pointer so that the device knows that there is data waiting
		 * to be transmitted over the link.
		 */
		ETH_SetSocketRxReadPtr(socket, base);
	}
}
#endif
/* ======================================================================== */
/* Driver Initialization */
#if (1)
/* ------------------------------------------------------------------------ */
void
ETH_Init(uint8* mac, uint32 ip, uint32 subnet, uint32 gateway)
{
	/*
	 * Initialize the device and the address configuration, then
	 * execute socket memory initialization for the local allocation
	 * table.
	 */
	int index;
	
	CyDelay( 250 ); /* Fixed Boot Delay or chip inintialization will fail */
	
	/* Reset the device */
	ETH_SetMode(0x80); /* Send Reset Command */
	/* Wait for the chip initialization delay */
	CyDelay( 10 );
	
	/* Close all of the socket, and clear the memory to make them available. */
	for(index=0;index<ETH_MAX_SOCKET;++index) {
		ETH_SocketClose( index );
		/* Set the socket memory size */
		ETH_SetSocketTxMemSize(index, ETH_MEM_2K); /* 2K each */
		ETH_SetSocketRxMemSize(index, ETH_MEM_2K); /* 2K Each */
		// initialize memory buffer pointers
		ETH_SetSocketRxReadPtr( index, ETH_SOCKET_RX_BASE[index] );
		ETH_SetSocketRxWritePtr( index, ETH_SOCKET_RX_BASE[index] );
		ETH_SetSocketTxReadPtr( index, ETH_SOCKET_TX_BASE[index] );
		ETH_SetSocketTxWritePtr( index, ETH_SOCKET_TX_BASE[index] );
	}
	/* Set device gateway address */
	ETH_SetGatewayAddress(gateway);
	ETH_SetSubnetMask( subnet );
	/* Store the subnet mask for later use, for ERRATA fix */
	ETH_SubnetMask = subnet;
	/* store the device mac */
	ETH_SetSourceMAC( mac );
	/* store the IP address */
	ETH_SetSourceIP( ip );
	/* clear pending interrupts */
	ETH_SetIR(0xFF);
	/* clear the subnet mask register (W5100 Errata Fix) */
	ETH_SetSubnetMask( 0 );
}
/* ------------------------------------------------------------------------ */
void
ETH_Start( void )
{
	uint32 ip;
	uint32 gateway;
	uint32 sub;
	
	/* Check for SPI initialization */
	if (SPI_initVar == 0) {
		/*
		 * the hardware has not yet been initialized.  Before anything can be
		 * initialized within the driver, the external hardware must be started
		 */
		SPI_Start();
	}
		
	/* wait for power on PLL Lock */
	CyDelay( 10 );
	/* V1.2 new -- Parse MAC Address string */
	if ( ETH_ParseMAC("00-de-ad-be-ef-00", &ETH_MAC[0]) == CYRET_BAD_DATA) {
		ETH_MAC[0] = 0;
		ETH_MAC[1] = 0xDE;
		ETH_MAC[2] = 0xAD;
		ETH_MAC[3] = 0xC0;
		ETH_MAC[4] = 0xDE;
		ETH_MAC[5] = 0;
	}
	/* END of V1.2 Update ------ */
	ip = ETH_ParseIP("192.168.0.101");
	sub = ETH_ParseIP("255.255.255.0");
	gateway = ETH_ParseIP("192.168.0.1");
	/* Initialize the device with the default data */
	ETH_Init( &ETH_MAC[0], ip, sub, gateway  );
}
/* ------------------------------------------------------------------------ */
uint32
ETH_ParseIP( const char* ipString )
{
	/*
	 * Parse a human readable string in to a IP address usable by the hardare
	 */
	int index;
	char digit[5];
	uint8 ip[4];
	int counter;
	int dindex;
	
	index = 0;
	dindex = 0;
	counter = 0;
	
	while ( (counter < 4) && ((unsigned int)index < strlen(ipString) ) ) {
		if ( (ipString[index] >= '0' ) && (ipString[index] <= '9') ) {
			if (dindex > 3) return( 0xFFFFFFFF );
			digit[dindex++] = ipString[index];
			
		}
		
		if ( (ipString[index] == '.') || (ipString[index+1] == 0) ) {
			digit[dindex] = 0;
			dindex = 0;
			/* convert the value and store in the buffer */
			ip[counter] = 0;
			while (digit[dindex] != 0) {
				ip[counter] = (ip[counter]*10) + (digit[dindex]-'0');
				++dindex;
				// ip[counter] = ...
			}
			/* reset the digit index to start accumulating digits again*/
			dindex = 0;
			/* move to the next address byte */
			++counter;
		}
		++index;
	}
	
	if (counter != 4) {
		return( 0xFFFFFFFF );
	}
	else {
		return( ETH_IPADDRESS(ip[0], ip[1], ip[2], ip[3]) );
	}
}
/* ------------------------------------------------------------------------ */
/**
 * /brief Parse a MAC Address string in to a 6-byte mac address
 * /param *macString Pointer to the ASCII-Z String containing the MAC address
 * /param *mac Pointer to the 6-byte array to hold the output mac addres
 */
cystatus ETH_ParseMAC(const char *macString, uint8 *mac)
{
	/* 
	 * a mac address is specified as a string of 6 hex bytes with
	 * dashes ('-') seperating the bytes.  An invalidly formed
	 * address will only process the values up the error and return BAD_DATA
	 * otherwise, SUCESS is returned.
	 */
	int digit;
	int index;
	cystatus result;
	
	result = CYRET_SUCCESS;
	index = 0;
	for(digit = 0;(digit<6) && (result == CYRET_SUCCESS)&&(macString[index] != 0);++digit) {
		// process the first nibble
		if (ETH_ISXDIGIT(macString[index]) ) {
			mac[digit] = ETH_HEX2BIN(macString[index]);
			++index;
			mac[digit] <<= 4;
			if (ETH_ISXDIGIT(macString[index])) {
				mac[digit] += ETH_HEX2BIN(macString[index]);
				++index;
				/*
				 * now for digits other than digit 5 (the last one) look for
				 * the dash seperator.  If there is no dash, return bad data
				 */
				if (digit<5) {
					if( (macString[index]!='-') && (macString[index]!= ':') ){
						result = CYRET_BAD_DATA;
					}
					++index; // move conversion pointer to the next value
				}
			}
			else {
				result = CYRET_BAD_DATA;
			}
		}
		else {
			result = CYRET_BAD_DATA;
		}
	}
	return( result );
}
/* ------------------------------------------------------------------------ */
void ETH_StringMAC(uint8 *mac, char *macString)
{
	int digit;
	int index;
	
	/*
	 * Convert the MAC address specified in to a string
	 */
	index = 0;
	for(digit=0;digit<6;++digit) {
		// convert the first nibble
		macString[index++] = ETH_BIN2HEX(((mac[digit]>>4)&0x0F));
		macString[index++] = ETH_BIN2HEX((mac[digit]&0x0F));
		if (digit<5) {
			macString[index++] = '-';
		}
		else {
			macString[index] = 0;
		}
	}
}
/* ------------------------------------------------------------------------ */
void ETH_StringIP( uint32 ip, char *ipString )
{
	uint8 *ipBytes;
	int index;
	int digit;
	int work, temp;
	
	ipBytes = (uint8*)&ip;
	index = 0;
	for(digit=0;digit<4;++digit) {
		work = ipBytes[digit];
		if (work >= 100) {
			temp = work/100;
			work -= (temp*100);
			ipString[index++] = '0' + temp;
		}
		if (work >= 10) {
			temp = work /10;
			work -= (temp*10);
			ipString[index++] = '0'+temp;
		}
		ipString[index++] = '0'+work;
		if (digit <3) {
			ipString[index++] = '.';
		}
		else {
			ipString[index] = 0;
		}
	}
}

/* ------------------------------------------------------------------------ */
uint8
ETH_SetIP( uint32 ip )
{
	uint8 ok = 0;
	
	if ( ( ip != 0) && (ip != 0xFFFFFFFF) ) {
		ETH_SetSourceIP( ip );
		ok = 0xFF;
	}
	
	return ok;
}
/* ------------------------------------------------------------------------ */
uint32
ETH_GetIP( void )
{
	return ETH_GetSourceIP();
}
/* ------------------------------------------------------------------------ */
void
ETH_SetMAC( uint8* mac )
{
	ETH_SetSourceMAC( mac );
}
/* ------------------------------------------------------------------------ */
void
ETH_GetMAC( uint8* mac )
{
	ETH_GetSourceMAC( mac );
}
#endif
/* ======================================================================== */
/* Socket Controls */
#if (1)
/* ------------------------------------------------------------------------ */
uint8
ETH_SocketOpen( uint8 Protocol, uint16 port, uint8 flags )
{
	uint8 socket;
	int index;
	
	/*
	 * This function will look for the first available socket for allocation
	 * using the defined protocol.  The socket configuration will then be
	 * initialized and saved in the allocation table. If the requested socket
	 * can not be initialized, 0xFF is returned
	 */
	socket = 0xFF;
	/* find the first available socket to open, and how much memory is available */
	for( index = 0;index<ETH_MAX_SOCKET;++index) {
		if ( (socket == 0xFF) && (ETH_SocketConfig[index].Protocol == 0) ) {
			/*
			 * Since the W5100 does not support MAC mode commucications, check to see
			 * if the socket that is free was socket 0.  If the mac protocol was
			 * selected, ignore socket 0
			 */
			if ( (Protocol != ETH_PROTO_MAC) || (index != 0) ) {
				/* store this socket number for allocation */
				socket = index;
			}
		}
	}
	if (socket != 0xFF ) {
		/* Store the socket information in the allocation table */
		ETH_SocketConfig[socket].Protocol = Protocol;
		ETH_SocketConfig[socket].SocketFlags = flags;
		ETH_SocketConfig[socket].SourcePort = port;
		ETH_SocketConfig[socket].ServerFlag = 0;

		/* Set the socket memory size */
		ETH_SetSocketTxMemSize(socket, ETH_MEM_2K); /* 2K each */
		ETH_SetSocketRxMemSize(socket, ETH_MEM_2K); /* 2K Each */
		/* Initialize the socket memeory pointers */
		ETH_SetSocketRxReadPtr( socket, ETH_SOCKET_RX_BASE[index] );
		ETH_SetSocketRxWritePtr( socket, ETH_SOCKET_RX_BASE[index] );
		ETH_SetSocketTxReadPtr( socket, ETH_SOCKET_TX_BASE[index] );
		ETH_SetSocketTxWritePtr( socket, ETH_SOCKET_TX_BASE[index] );

		/* Send the socket open with the correct protocol information */
		ETH_SetSocketSourcePort( socket, port );
		ETH_SetSocketMode( socket, Protocol | flags );
		ETH_ExecuteSocketCommand( socket, 1 );
		
	}
	return socket;
}
/* ------------------------------------------------------------------------ */
void
ETH_SocketClose( uint8 socket )
{
	/*
	 * Set the socket allocation to empty, and issue the close command
	 * to the socket
	 */
	if (socket < ETH_MAX_SOCKET) {
		/* clear the socket memory allocations */
		ETH_SocketConfig[socket].Protocol = 0;
		ETH_SocketConfig[socket].SocketFlags = 0;
		/* close the socket */
		ETH_ExecuteSocketCommand( socket, 0x10 );
		/* Clear pending Interrupts */
		ETH_SetSocketIR( socket, 0xFF);
	}
}
/* ------------------------------------------------------------------------ */
uint8
ETH_SocketProcessConnections( uint8 socket )
{
	uint8 status;
	
	status = ETH_GetSocketStatus(socket);
	/* has a connection termination been requested by remote system */
	if (status == 0x1C) {
		/* Close the socket on this end */
		ETH_SocketClose(socket);
	}
	return (ETH_GetSocketStatus(socket) == 0x00);
}
/* ------------------------------------------------------------------------ */
uint8
ETH_SocketEstablished( uint8 socket )
{
	uint8 result;
	
	result = 0;
	if (socket < ETH_MAX_SOCKET) {
		result = ETH_GetSocketStatus( socket );
	}
	return( result == 0x17);
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Transmit a SEND operation over a socket
 * \param socket the socket to which the send command will be sent
 */
void
ETH_SocketSend(uint8 socket )
{
	uint8 ir;
	
	if (socket < ETH_MAX_SOCKET) {
		/* initialize the subnet mask register : ERRATA FIX */
		ETH_SetSubnetMask( ETH_SubnetMask );
		/* Issue the SEND command */
		ETH_ExecuteSocketCommand( socket, 0x20 );
		/* wait for the SEND to complete, or for a timeout */
		ir = ETH_GetSocketIR( socket );
		/* while SEND is not done, and the socket hasnot timed out or been dsconnected */
		while ( ((ir & 0x10) == 0) && (!(ir&0x0A)) ) {
			CyDelay(1);
			ir = ETH_GetSocketIR( socket );
			
		}
		/* clear the SEND_OK flag from the register */
		ETH_SetSocketIR( socket, 0x10 );
		/* reset the subnet mask : ERRATA FIX */
		ETH_SetSubnetMask( 0 );
	}
}
/* ------------------------------------------------------------------------ */
/**
 * \brief Execute a SEND without an ARP.
 * \param socket the socket to which the SEND will be executed.
 */
void
ETH_SocketSendMac(uint8 socket )
{
	uint8 ir;
	
	/* initialize the subnet mask register : ERRATA FIX */
	ETH_SetSubnetMask( ETH_SubnetMask );
	/* Issue the SEND command */
	ETH_ExecuteSocketCommand( socket, 0x21 );
	/* wait for the SEND to complete, or for a timeout */
	ir = ETH_GetSocketIR( socket );
	/* while SEND is not done, and the socket hasnot timed out or been dsconnected */
	while ( ((ir & 0x10) == 0) && (!(ir&0x0A)) ) {
		CyDelay(1);
		ir = ETH_GetSocketIR( socket );
		
	}
	/* clear the SEND_OK flag from the register */
	ETH_SetSocketIR( socket, 0x10 );
	/* reset the subnet mask : ERRATA FIX */
	ETH_SetSubnetMask( 0 );
}
/* ------------------------------------------------------------------------ */
uint16
ETH_SocketRxDataWaiting( uint8 socket )
{
	return ETH_GetRxSize( socket );
}
#endif
/* ======================================================================== */
/* TCP/IP */
#if (1)
/* ------------------------------------------------------------------------ */
uint8
ETH_TcpOpen(uint16 port)
{
	return ETH_SocketOpen(ETH_PROTO_TCP, port, 0);
}
/* ------------------------------------------------------------------------ */
void
ETH_TcpStartServer( uint8 socket )
{
	/*
	 * Start a open socket listening for a connection
	 */
	/* was this a valid socket? */
	if (socket < ETH_MAX_SOCKET) {
		/* Execute the listen command */
		ETH_ExecuteSocketCommand( socket, 0x02 );
	}
}
/* ------------------------------------------------------------------------ */
void
ETH_TcpStartServerWait( uint8 socket )
{
	uint8 status;
	
	/*
	 * Bug Patch: Exit Waiting for server when an invalid socket is passed
	 */
	if (socket >= ETH_MAX_SOCKET) return;
	ETH_TcpStartServer(socket);
	/* wait for socket establishment */
	/* Update Patch: Loop calls process connections to exit on a closed socket */
	status = ETH_GetSocketStatus(socket);
	while ( (status != 0x17 ) && (status != 0 ) ) {
		CyDelay(1);
		ETH_SocketProcessConnections( socket );
		status = ETH_GetSocketStatus( socket );
	}
}
/* ------------------------------------------------------------------------ */
void
ETH_TcpConnect( uint8 socket, uint32 ip, uint16 port )
{
	uint32 timeout;
	uint8 ir;
	
	/* Exit when passed a closed or invalid socket */
	if ( socket >= ETH_MAX_SOCKET) return;
	/* Check for a valid IP address */
	if ( (ip != 0xFFFFFFFF) && (ip != 0) ) {
		ETH_SetSocketDestIP( socket, ip );
		ETH_SetSocketDestPort( socket, port );
		/* set socket subnet mask */
		ETH_SetSubnetMask( ETH_SubnetMask );
		ETH_ExecuteSocketCommand( socket, 0x04);
		/* wait for the socket connection to the remote host is established */
		while ( (!ETH_SocketEstablished(socket))  && (timeout < 3000) ) {
			CyDelay(1);
			++timeout;
			ir = ETH_GetSocketIR( socket );
			if ( (ir & 0x08) != 0 ) {
				/* internal chip timeout occured */
				timeout = 3000;
			}
		}
		/* clear the Subnet mask register */
		ETH_SetSubnetMask(0);
	}
}
/* ------------------------------------------------------------------------ */
uint8
ETH_TcpConnected( uint8 socket )
{ return ETH_SocketEstablished(socket); }
/* ------------------------------------------------------------------------ */
void
ETH_TcpDisconnect( uint8 socket )
{
	ETH_ExecuteSocketCommand(socket, 0x08);
}
/* ------------------------------------------------------------------------ */
uint16
ETH_TcpSend(uint8 socket, uint8* buffer, uint16 len)
{
	uint16 TxSize;
	uint16 FreeSpace;
	uint8 status;
	
	/* Update Patch: Exit immediately with 0 data tx on bad socket */
	if (socket >= ETH_MAX_SOCKET) return 0;
	TxSize =  (len > 0x0800) ? 0x0800 : len;
	/* check the connection status, and protocol of the socket */
	status = ETH_GetSocketStatus(socket);
	if ( ( status == 0x17) && (ETH_SocketConfig[socket].Protocol == ETH_PROTO_TCP) ) {
		/* 
		 * The socket was open with the correct protocol and is connected to
		 * a valid remote system. In order to send the requested packet data,
		 * first, we must wait for the available buffer memory to be free
		 * in the transmit buffer fifo.
		 */
		FreeSpace = 0;
		status = 0x17;
		while ( (FreeSpace < TxSize) && ( (status == 0x17) && (status != 0x1C) ) ) {
			FreeSpace = ETH_GetTxFreeSize( socket );
			status = ETH_GetSocketStatus( socket );
		}
		/*
		 * Write the data buffer to the chip Tx Buffer, then issue
		 * the chip SEND command
		 */
		ETH_ProcessTxData(socket, 0, buffer, TxSize);
		ETH_SocketSend( socket );
	}
	else {
		/*
		 * the socket was not establised, or there was an error, so clear
		 * the TxSize to signal that no data has bee sent
		 */
		TxSize = 0;
	}
	return TxSize;
}
/* ------------------------------------------------------------------------ */
uint16
ETH_TcpReceive( uint8 socket, uint8* buffer, uint16 length )
{
	uint16 RxSize;

	/*
	 * Revision Update:
	 * Removed dead code, added exit when there is an invlaid socket specified
	 */
	if (socket >= ETH_MAX_SOCKET) return 0;
	/*
	 * read the number of waiting bytes in the buffer memory
	 * but, clip the length of data read to the requested
	 * length of data.
	 */
	RxSize = ETH_GetRxSize( socket );
	RxSize = (RxSize > length) ? length : RxSize;
	/* If there was waiting data, read it from the buffer */
	if (RxSize > 0) {
		ETH_ProcessRxData( socket, 0, buffer, RxSize, 0);
		/* 
		 * after reading the buffer data, send the receive command
		 * to the socket so that the W5100 completes the read
		 */
		ETH_ExecuteSocketCommand(socket, 0x40);
	}
	
	/* return the number of read bytes from the buffer memory */
	return RxSize;
}
/* ------------------------------------------------------------------------ */
void
ETH_TcpPrint( uint8 socket, const char* str )
{
	ETH_TcpSend(socket, (uint8*)str, strlen(str));
}
#endif
/* ======================================================================== */
/* UDP */
#if (1)
/* ------------------------------------------------------------------------ */
uint8
ETH_UdpOpen(uint16 port)
{
	return ETH_SocketOpen(ETH_PROTO_UDP, port, 0);
}
/* ------------------------------------------------------------------------ */	
uint16
ETH_UdpSend(uint8 socket, uint32 ip, uint16 port, uint8* buffer, uint16 length)
{
	uint16 TxSize;
	
	/*
	 * 2.0 Patch: retun immediately upon the detection of a socket that is not open
	 */
	if (socket >= ETH_MAX_SOCKET) return 0;
	/*
	 * Transmit a buffer of data to a specified remote system using UDP.
	 */
	if (ETH_GetSocketStatus(socket) == 0x17) {
		/*
		 * The socket has been established, so wait for available
		 * room in the transmit buffer of the socket, but, trim the
		 * transmitted data length to no more than the available
		 * buffer size in the device. (2K)
		 */
		TxSize = (length > 0x0800) ? 0x0800 : length;
		if ( (ip != 0) && (ip != 0xFFFFFFFF) ) {
			/*
			 * Store the destination IP and port in the chip
			 * socket registers.
			 */
			ETH_SetSocketDestIP( socket, ip );
			ETH_SetSocketDestPort( socket, port );
			/*
			 * process the transmission buffer, and write it in to
			 * the chip buffer memory.
			 */
			ETH_ProcessTxData(socket,0,buffer,TxSize);
			/*
			 * Issue the send command to transmit the buffer.
			 */
			ETH_SocketSend( socket ); 
		}
		else {
			/* an invalid IP address was issued, so return that no data was sent. */
			TxSize = 0;
		}
	}
	return TxSize;
}
/* ------------------------------------------------------------------------ */
uint16
ETH_UdpReceive(uint8 socket, uint32 *ip, uint16 *port, uint8* buffer, uint16 length)
{
	uint16 RxSize;
	uint16 PacketSize;
	uint8  PacketHeader[8];
	
	/*
	 * 2.0 Patch: retun immediately upon the detection of a socket that is not open
	 */
	if (socket >= ETH_MAX_SOCKET) return 0;
	/*
	 * read the number of waiting bytes in the buffer memory
	 * but, clip the length of data read to the requested
	 * length of data.
	 */
	RxSize = ETH_GetRxSize( socket );
	RxSize = (RxSize > length+8) ? length : RxSize;
	/* If there was waiting data, read it from the buffer */
	if (RxSize > 0) {
		/*
		 * the UDP packet is stored in the buffer memory as an 8-byte
		 * packet header followed by the packet data.
		*/
		ETH_ProcessRxData( socket, 0, &PacketHeader[0], 8, 0);
		/*
		 * The packet header contains the 4-byte IP address followed by the
		 * 2-byte port number and the 2-byte packet data length
		 */
		*ip = ETH_IPADDRESS(PacketHeader[0], PacketHeader[1], PacketHeader[2], PacketHeader[3]);
		*port = (uint16)((PacketHeader[4]<<8)&0xFF00) | (PacketHeader[5]&0x00FF);
		PacketSize = (uint16)((PacketHeader[6]<<8)&0xFF00) | (PacketHeader[7]&0x00FF);
		/*
		 * Check to make sure that the packet data has been received completely
		 */
		if (RxSize >= (PacketSize+8) ) {
		
			ETH_ProcessRxData( socket, 8, buffer, PacketSize, 0);
			/* 
			 * after reading the buffer data, send the receive command
			 * to the socket so that the W5100 completes the read
			 */
			ETH_ExecuteSocketCommand(socket, 0x40);
			RxSize = PacketSize;
		}
		else {
			RxSize = 8;
		}
	}
	
	/* return the number of read bytes from the buffer memory */
	return RxSize;
}
#endif
/* ======================================================================== */
/* IGMP */

/* ======================================================================== */
/* DHCP */

/* ======================================================================== */
/* HTTP - Web Server */

/* [] END OF FILE */
/** @} */
