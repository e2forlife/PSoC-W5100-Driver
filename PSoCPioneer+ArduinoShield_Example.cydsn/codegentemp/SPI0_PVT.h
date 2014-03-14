/*******************************************************************************
* File Name: .h
* Version 1.10
*
* Description:
*  This private file provides constants and parameter values for the
*  SCB Component in I2C mode.
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

#if !defined(CY_SCB_PVT_SPI0_H)
#define CY_SCB_PVT_SPI0_H

#include "SPI0.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define SPI0_SetI2CExtClkInterruptMode(interruptMask) SPI0_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define SPI0_ClearI2CExtClkInterruptSource(interruptMask) SPI0_CLEAR_INTR_I2C_EC(interruptMask)
#define SPI0_GetI2CExtClkInterruptSource()                (SPI0_INTR_I2C_EC_REG)
#define SPI0_GetI2CExtClkInterruptMode()                  (SPI0_INTR_I2C_EC_MASK_REG)
#define SPI0_GetI2CExtClkInterruptSourceMasked()          (SPI0_INTR_I2C_EC_MASKED_REG)

/* APIs to service INTR_SPI_EC register */
#define SPI0_SetSpiExtClkInterruptMode(interruptMask) SPI0_WRITE_INTR_SPI_EC_MASK(interruptMask)
#define SPI0_ClearSpiExtClkInterruptSource(interruptMask) SPI0_CLEAR_INTR_SPI_EC(interruptMask)
#define SPI0_GetExtSpiClkInterruptSource()                 (SPI0_INTR_SPI_EC_REG)
#define SPI0_GetExtSpiClkInterruptMode()                   (SPI0_INTR_SPI_EC_MASK_REG)
#define SPI0_GetExtSpiClkInterruptSourceMasked()           (SPI0_INTR_SPI_EC_MASKED_REG)

#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void SPI0_SetPins(uint32 mode, uint32 subMode, uint32 uartTxRx);
#endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */

void SPI0_DisableTxPinsInputBuffer(void);
void SPI0_EnableTxPinsInputBuffer(void);


/**********************************
*     Vars with External Linkage
**********************************/

extern cyisraddress SPI0_customIntrHandler;
extern SPI0_BACKUP_STRUCT SPI0_backup;

#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common config vars */
    extern uint8 SPI0_scbMode;
    extern uint8 SPI0_scbEnableWake;
    extern uint8 SPI0_scbEnableIntr;

    /* I2C config vars */
    extern uint8 SPI0_mode;
    extern uint8 SPI0_acceptAddr;

    /* SPI/UART config vars */
    extern volatile uint8 * SPI0_rxBuffer;
    extern uint8   SPI0_rxDataBits;
    extern uint32  SPI0_rxBufferSize;

    extern volatile uint8 * SPI0_txBuffer;
    extern uint8   SPI0_txDataBits;
    extern uint32  SPI0_txBufferSize;

    /* EZI2C config vars */
    extern uint8 SPI0_numberOfAddr;
    extern uint8 SPI0_subAddrSize;
#endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */

#endif /* (CY_SCB_PVT_SPI0_H) */


/* [] END OF FILE */
