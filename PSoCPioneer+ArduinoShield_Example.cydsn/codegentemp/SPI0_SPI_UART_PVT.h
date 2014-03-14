/*******************************************************************************
* File Name: SPI0_SPI_UART_PVT.h
* Version 1.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_SPI0_H)
#define CY_SCB_SPI_UART_PVT_SPI0_H

#include "SPI0_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if(SPI0_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  SPI0_rxBufferHead;
    extern volatile uint32  SPI0_rxBufferTail;
    extern volatile uint8   SPI0_rxBufferOverflow;
#endif /* (SPI0_INTERNAL_RX_SW_BUFFER_CONST) */

#if(SPI0_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  SPI0_txBufferHead;
    extern volatile uint32  SPI0_txBufferTail;
#endif /* (SPI0_INTERNAL_TX_SW_BUFFER_CONST) */

#if(SPI0_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 SPI0_rxBufferInternal[SPI0_RX_BUFFER_SIZE];
#endif /* (SPI0_INTERNAL_RX_SW_BUFFER) */

#if(SPI0_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 SPI0_txBufferInternal[SPI0_TX_BUFFER_SIZE];
#endif /* (SPI0_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

#if(SPI0_SCB_MODE_SPI_CONST_CFG)
    void SPI0_SpiInit(void);
#endif /* (SPI0_SCB_MODE_SPI_CONST_CFG) */

#if(SPI0_SPI_WAKE_ENABLE_CONST)
    void SPI0_SpiSaveConfig(void);
    void SPI0_SpiRestoreConfig(void);
#endif /* (SPI0_SPI_WAKE_ENABLE_CONST) */

#if(SPI0_SCB_MODE_UART_CONST_CFG)
    void SPI0_UartInit(void);
#endif /* (SPI0_SCB_MODE_UART_CONST_CFG) */

#if(SPI0_UART_WAKE_ENABLE_CONST)
    void SPI0_UartSaveConfig(void);
    void SPI0_UartRestoreConfig(void);
#endif /* (SPI0_UART_WAKE_ENABLE_CONST) */

/* Interrupt processing */
#define SPI0_SpiUartEnableIntRx(intSourceMask)  SPI0_SetRxInterruptMode(intSourceMask)
#define SPI0_SpiUartEnableIntTx(intSourceMask)  SPI0_SetTxInterruptMode(intSourceMask)
uint32 SPI0_SpiUartDisableIntRx(void);
uint32 SPI0_SpiUartDisableIntTx(void);

#endif /* (CY_SCB_SPI_UART_PVT_SPI0_H) */


/* [] END OF FILE */
