/**
 * \addtogroup w5100
 * @{
 */

/**
 * \file PSoC4 Specific hardware controls
 * \author Chuck Erhardt (chuck@e2forlife.com)
 *
 * This file contains the implementation of hardware
 * access functions used to control the SPI read/write
 * using the SCB of the PSoC4 device family.  This
 * file also implements hardware generic functions for
 * the use of features required by the driver.
 */

/* Include cypress library data */
#include <cytypes.h>
#include <cylib.h>

/* include the function definitions for the driver */
#include <ETH0.h>

/* include the definitions for the Cypress SPI API */
#include <SPI0.h>

/* ------------------------------------------------------------------------ */
/**
 * \brief Select the active SCB chip select connected to the W51
 *
 * this fucntion will set the active SS line within the SCB to select and
 * communicate with the W5100 device.
 */
static void
ETH0_W51_Select( void )
{
	if (1 < 4) {
		SPI0_SpiSetActiveSlaveSelect(1);
	}
	else {
		SPI0_SpiSetActiveSlaveSelect(0);
	}			
}
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
ETH0_W51_Write(uint16 addr, uint8 dat)
{
	/* Using internal device SS generation */
	ETH0_W51_Select();
	/*
	 * The first thing to do is to clear the Rx Buffer of any lingering
	 * data left from other transfers.  Then send the data per the W5100
	 * datasheet p.62
	 */
	SPI0_SpiUartClearRxBuffer();
	/* Begin transfer of data to device */
	SPI0_SpiUartWriteTxData(ETH0_WRITE_OP);
	SPI0_SpiUartWriteTxData((addr>>8)&0x00FF);
	SPI0_SpiUartWriteTxData(addr&0x00FF);
	SPI0_SpiUartWriteTxData(dat);
	/* Wait for operation to end */
	CyDelayUs(5); /* At 6 MBPS it will take approx 6 uS to send the data */
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
uint8
ETH0_W51_Read(uint16 addr)
{
	uint32 dat;
	uint32 count;
	
	/* Using internal device SS generation */
	ETH0_W51_Select();
	/*
	 * First, clear the Rx Buffer of any waiting data.  Then begin the
	 * read operation by sending the op code, followed byte the address
	 * from which the read will be executed, then send a dummy byte
	 * of zeros to read the data from the device.
	 */
	SPI0_SpiUartClearRxBuffer();
	/* Begin data read */
	SPI0_SpiUartWriteTxData(ETH0_READ_OP);
	SPI0_SpiUartWriteTxData(addr>>8);
	SPI0_SpiUartWriteTxData(addr&0x00FF);
	SPI0_SpiUartWriteTxData( 0 );
	/* Wait for operations to complete. */
	CyDelayUs( 5 );
	count = SPI0_SpiUartGetRxBufferSize();
	while( count > 0 )
	{
		dat = SPI0_SpiUartReadRxData(); 
		count = SPI0_SpiUartGetRxBufferSize();
	}
	
	return( dat&0xFF );
}
/* [] END OF FILE */
