/*******************************************************************************
* File Name: SPI0_SPI_UART.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
*******************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPI0_PVT.h"
#include "SPI0_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(SPI0_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint32 SPI0_rxBufferHead;
    volatile uint32 SPI0_rxBufferTail;
    volatile uint8  SPI0_rxBufferOverflow;
#endif /* (SPI0_INTERNAL_RX_SW_BUFFER_CONST) */

#if(SPI0_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint32 SPI0_txBufferHead;
    volatile uint32 SPI0_txBufferTail;
#endif /* (SPI0_INTERNAL_TX_SW_BUFFER_CONST) */

#if(SPI0_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 SPI0_rxBufferInternal[SPI0_RX_BUFFER_SIZE];
#endif /* (SPI0_INTERNAL_RX_SW_BUFFER) */

#if(SPI0_INTERNAL_TX_SW_BUFFER)
    volatile uint8 SPI0_txBufferInternal[SPI0_TX_BUFFER_SIZE];
#endif /* (SPI0_INTERNAL_TX_SW_BUFFER) */


#if(SPI0_RX_DIRECTION)

    /*******************************************************************************
    * Function Name: SPI0_SpiUartReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Retrieves the next data element from the receive buffer. Undefined data will
    *  be returned if the RX buffer is empty.
    *  Call SPI0_SpiUartGetRxBufferSize() to return buffer size.
    *   - RX software buffer disabled: Returns data element retrieved from RX FIFO.
    *   - RX software buffer enabled: Returns data element from the software
    *     receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Next data element from the receive buffer.
    *
    * Global Variables:
    *  Look into SPI0_SpiInit for description.
    *
    *******************************************************************************/
    uint32 SPI0_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

        #if(SPI0_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 locTail;
        #endif /* (SPI0_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(SPI0_CHECK_RX_SW_BUFFER)
        {
            if(SPI0_rxBufferHead != SPI0_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (SPI0_rxBufferTail + 1u);

                if(SPI0_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data fron RX software buffer */
                rxData = SPI0_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                SPI0_rxBufferTail = locTail;
            }
        }
        #else
        {
            rxData = SPI0_RX_FIFO_RD_REG; /* Read data from RX FIFO */
        }
        #endif

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: SPI0_SpiUartGetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in receive buffer.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of received data elements
    *
    *******************************************************************************/
    uint32 SPI0_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
        #if(SPI0_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 locHead;
        #endif /* (SPI0_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(SPI0_CHECK_RX_SW_BUFFER)
        {
            locHead = SPI0_rxBufferHead;

            if(locHead >= SPI0_rxBufferTail)
            {
                size = (locHead - SPI0_rxBufferTail);
            }
            else
            {
                size = (locHead + (SPI0_RX_BUFFER_SIZE - SPI0_rxBufferTail));
            }
        }
        #else
        {
            size = SPI0_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return(size);
    }


    /*******************************************************************************
    * Function Name: SPI0_SpiUartClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clear the receive buffer and RX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI0_SpiUartClearRxBuffer(void)
    {
        #if(SPI0_INTERNAL_RX_SW_BUFFER_CONST)
            uint32 intSourceMask;
        #endif /* (SPI0_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(SPI0_CHECK_RX_SW_BUFFER)
        {
            intSourceMask = SPI0_SpiUartDisableIntRx();

            SPI0_CLEAR_RX_FIFO;

            /* Flush RX software buffer */
            SPI0_rxBufferHead     = SPI0_rxBufferTail;
            SPI0_rxBufferOverflow = 0u;

            /* End RX transfer */
            SPI0_ClearRxInterruptSource(SPI0_INTR_RX_ALL);

            SPI0_SpiUartEnableIntRx(intSourceMask);
        }
        #else
        {
            SPI0_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (SPI0_RX_DIRECTION) */


#if(SPI0_TX_DIRECTION)

    /*******************************************************************************
    * Function Name: SPI0_SpiUartWriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    * Parameters:
    *  txDataByte: the data to be transmitted.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI0_SpiUartWriteTxData(uint32 txDataByte)
    {
        #if(SPI0_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 locHead;
            uint32 intSourceMask;
        #endif /* (SPI0_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(SPI0_CHECK_TX_SW_BUFFER)
        {
            /* Head index to put data */
            locHead = (SPI0_txBufferHead + 1u);

            /* Adjust TX software buffer index */
            if(SPI0_TX_BUFFER_SIZE == locHead)
            {
                locHead = 0u;
            }

            while(locHead == SPI0_txBufferTail)
            {
                /* Wait for space in the TX software buffer */
            }

            /* The TX software buffer has at least one room */

            if((SPI0_txBufferHead == SPI0_txBufferTail) &&
               (SPI0_FIFO_SIZE != SPI0_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                SPI0_TX_FIFO_WR_REG = txDataByte;
            }
            /* Put data in the TX software buffer */
            else
            {
                /* Clear old status of INTR_TX_EMPTY. It sets at the end of transfer: TX FIFO empty. */
                SPI0_ClearTxInterruptSource(SPI0_INTR_TX_NOT_FULL);

                SPI0_PutWordInTxBuffer(locHead, txDataByte);

                SPI0_txBufferHead = locHead;

                /* Enable interrupt to transmit */
                intSourceMask  = SPI0_INTR_TX_NOT_FULL;
                intSourceMask |= SPI0_GetTxInterruptMode();
                SPI0_SpiUartEnableIntTx(intSourceMask);
            }
        }
        #else
        {
            while(SPI0_FIFO_SIZE == SPI0_GET_TX_FIFO_ENTRIES)
            {
                /* Block while TX FIFO is FULL */
            }

            SPI0_TX_FIFO_WR_REG = txDataByte;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: SPI0_SpiUartPutArray
    ********************************************************************************
    *
    * Summary:
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * Parameters:
    *  wrBuf:  pointer to an array with data to be placed in transmit buffer.
    *  count:  number of data elements to be placed in the transmit buffer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI0_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for(i=0u; i < count; i++)
        {
            SPI0_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: SPI0_SpiUartGetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of elements currently in the transmit buffer.
    *  TX software buffer disabled: returns the number of used entries in TX FIFO.
    *  TX software buffer enabled: returns the number of elements currently used
    *  in the transmit buffer. This number does not include used entries in the
    *  TX FIFO. The transmit buffer size is zero until the TX FIFO is full.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Number of data elements ready to transmit.
    *
    *******************************************************************************/
    uint32 SPI0_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
        #if(SPI0_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 locTail;
        #endif /* (SPI0_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(SPI0_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = SPI0_txBufferTail;

            if(SPI0_txBufferHead >= locTail)
            {
                size = (SPI0_txBufferHead - locTail);
            }
            else
            {
                size = (SPI0_txBufferHead + (SPI0_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = SPI0_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return(size);
    }


    /*******************************************************************************
    * Function Name: SPI0_SpiUartClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the transmit buffer and TX FIFO.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI0_SpiUartClearTxBuffer(void)
    {
        #if(SPI0_INTERNAL_TX_SW_BUFFER_CONST)
            uint32 intSourceMask;
        #endif /* (SPI0_INTERNAL_TX_SW_BUFFER_CONST) */

        #if(SPI0_CHECK_TX_SW_BUFFER)
        {
            intSourceMask = SPI0_SpiUartDisableIntTx();

            SPI0_CLEAR_TX_FIFO;

            /* Flush TX software buffer */
            SPI0_txBufferHead = SPI0_txBufferTail;

            /* End TX transfer if it is in progress */
            intSourceMask &= (uint32) ~SPI0_INTR_TX_NOT_FULL;

            SPI0_SpiUartEnableIntTx(intSourceMask);
        }
        #else
        {
            SPI0_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (SPI0_TX_DIRECTION) */


/*******************************************************************************
* Function Name: SPI0_SpiUartDisableIntRx
********************************************************************************
*
* Summary:
*  Disables RX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns RX interrupt soureces enabled before function call.
*
*******************************************************************************/
uint32 SPI0_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = SPI0_GetRxInterruptMode();

    SPI0_SetRxInterruptMode(SPI0_NO_INTR_SOURCES);

    return(intSource);
}


/*******************************************************************************
* Function Name: SPI0_SpiUartDisableIntTx
********************************************************************************
*
* Summary:
*  Disables TX interrupt sources.
*
* Parameters:
*  None
*
* Return:
*  Returns TX interrupt soureces enabled before function call.
*
*******************************************************************************/
uint32 SPI0_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = SPI0_GetTxInterruptMode();

    SPI0_SetTxInterruptMode(SPI0_NO_INTR_SOURCES);

    return(intSourceMask);
}


#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)

    /*******************************************************************************
    * Function Name: SPI0_PutWordInRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the RX buffer.
    *  Only available in Unconfigured operation mode.
    *
    * Parameters:
    *  index:      index to store data byte/word in the RX buffer.
    *  rxDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI0_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in the buffer */
        if(SPI0_ONE_BYTE_WIDTH == SPI0_rxDataBits)
        {
            SPI0_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            SPI0_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            SPI0_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: SPI0_GetWordFromRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from RX buffer.
    *  Only available in Unconfigured operation mode.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 SPI0_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if(SPI0_ONE_BYTE_WIDTH == SPI0_rxDataBits)
        {
            value = SPI0_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) SPI0_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)SPI0_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return(value);
    }


    /*******************************************************************************
    * Function Name: SPI0_PutWordInTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Stores byte/word into the TX buffer.
    * Only available in Unconfigured operation mode.
    *
    * Parameters:
    *  idx:        index to store data byte/word in the TX buffer.
    *  txDataByte: byte/word to store.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI0_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in the buffer */
        if(SPI0_ONE_BYTE_WIDTH == SPI0_txDataBits)
        {
            SPI0_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            SPI0_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            SPI0_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: SPI0_GetWordFromTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Reads byte/word from TX buffer.
    *  Only available in Unconfigured operation mode.
    *
    * Parameters:
    *  idx: index to get data byte/word from the TX buffer.
    *
    * Return:
    *  Returns byte/word read from TX buffer.
    *
    *******************************************************************************/
    uint32 SPI0_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if(SPI0_ONE_BYTE_WIDTH == SPI0_txDataBits)
        {
            value = (uint32) SPI0_txBuffer[idx];
        }
        else
        {
            value  = (uint32) SPI0_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) SPI0_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return(value);
    }

#endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
