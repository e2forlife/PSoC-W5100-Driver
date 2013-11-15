/**
 * \addtogroup iethernet
 * @{
 */
/**
 * \file Bootloader support for the iEthernet interface
 * \author Chuck Erhardt <chuck@e2forlife.com>
 * \version 1.0
 *
 * this file contains the implementation of the code to support the PSoC
 * bootloader interfaces to allow for bootloading over the Ethernet interface
 */

#include <cytypes.h>
#include "ETH0.h"
 
 /* Bootload code guard to prevent conflicts */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_ETH0)

static uint8 ETH0_BootBuffer[128];

/* Boot loader code to be included */

void CyBtldrCommStart( void )
{
    /* start the component using the defaults */
    ETH0_Start(0);
    ETH0_Socket_Start(0, ETH0_Sn_MR_TCP, 23, 0);
    ETH0_TCP_Listen( 0 );
}

void CyBtldrCommStop( void )
/* single channel implementation */
{
    ETH0_Socket_Close( 0 );
}

void CyBtldrCommReset( void )
/* single channel implementation */
{
    /*
     * since the buffers are locally located within the TCP chip,
     * read the buffer until there is no data returned from the buffer
     * to clear data.
     */
    while ( ETH0_TCP_Receive(0,&ETH0_BootBuffer[0]) != 0) {
        CyDelay(1);
    }
}

cystatus CyBtldrCommWrite( uint8 *dat, uint16 size, uint16 *count, uint8 timeOut )
/* single channel implementation */
{
    /* call driver to write data to the connection */
    if (ETH0_TCP_Established(0) != 0) {
        /* does the length of data fit within the Ethernet packet buffer? */
        if (size < ETH0_BUFFER_SIZE) {
            ETH0_TCP_Send(0, dat, size );
            *count = size;
        }
        /* otherwise, this was a real big packet, so send only a half-buffer full */
        else {
            ETH0_TCP_Send(0, &(dat[packetPos]), ETH0_BUFFER_SIZE>>1);
        }
        *count = ETH0_BUFFER_SIZE>>1;
        return CYRET_SUCCESS;
    }
    else {
    /* socket connection is not yet established, so fail on timeout */
        return CYRET_TIMEOUT;
    }
}

cystatus CyBtldrCommRead( uint8 *dat, uint16 size, uint16 *count, uint8 timeOut)
/* single channel implementation */
{
    uint8 to;
    uint16 RxLen;
    
    to = 0;
    /* call driver to write data to the connection */
    if (ETH0_TCP_Established(0) != 0) {
        do {
            RxLen = ETH0_TCP_Receive(0,dat);
            ++to;
            CyDelay(1);
        }
        while ( (RxLen == 0) && (to < timeOut) );
        return (RxLen > 0)? CYRET_SUCCESS : CYRET_TIMEOUT;
    }
    else {
        return CYRET_TIMEOUT;
    }
}

#endif
/* [] END OF FILE */
