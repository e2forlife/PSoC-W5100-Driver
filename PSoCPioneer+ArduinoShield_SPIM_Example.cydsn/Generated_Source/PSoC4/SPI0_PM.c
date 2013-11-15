/*******************************************************************************
* File Name: SPI0_PM.c
* Version 2.40
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPI0_PVT.h"

static SPI0_BACKUP_STRUCT SPI0_backup =
{
    SPI0_DISABLED,
    SPI0_BITCTR_INIT,
    #if(CY_UDB_V0)
        SPI0_TX_INIT_INTERRUPTS_MASK,
        SPI0_RX_INIT_INTERRUPTS_MASK
    #endif /* CY_UDB_V0 */
};


/*******************************************************************************
* Function Name: SPI0_SaveConfig
********************************************************************************
*
* Summary:
*  Saves SPIM configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPI0_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPI0_SaveConfig(void) 
{
    /* Store Status Mask registers */
    #if(CY_UDB_V0)
       SPI0_backup.cntrPeriod      = SPI0_COUNTER_PERIOD_REG;
       SPI0_backup.saveSrTxIntMask = SPI0_TX_STATUS_MASK_REG;
       SPI0_backup.saveSrRxIntMask = SPI0_RX_STATUS_MASK_REG;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: SPI0_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores SPIM configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPI0_backup - used when non-retention registers are restored.
*
* Side Effects:
*  If this API is called without first calling SaveConfig then in the following
*  registers will be default values from Customizer:
*  SPI0_STATUS_MASK_REG and SPI0_COUNTER_PERIOD_REG.
*
*******************************************************************************/
void SPI0_RestoreConfig(void) 
{
    /* Restore the data, saved by SaveConfig() function */
    #if(CY_UDB_V0)
        SPI0_COUNTER_PERIOD_REG = SPI0_backup.cntrPeriod;
        SPI0_TX_STATUS_MASK_REG = ((uint8) SPI0_backup.saveSrTxIntMask);
        SPI0_RX_STATUS_MASK_REG = ((uint8) SPI0_backup.saveSrRxIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: SPI0_Sleep
********************************************************************************
*
* Summary:
*  Prepare SPIM Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPI0_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPI0_Sleep(void) 
{
    /* Save components enable state */
    SPI0_backup.enableState = ((uint8) SPI0_IS_ENABLED);

    SPI0_Stop();
    SPI0_SaveConfig();
}


/*******************************************************************************
* Function Name: SPI0_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  SPI0_backup - used when non-retention registers are restored.
*  SPI0_txBufferWrite - modified every function call - resets to
*  zero.
*  SPI0_txBufferRead - modified every function call - resets to
*  zero.
*  SPI0_rxBufferWrite - modified every function call - resets to
*  zero.
*  SPI0_rxBufferRead - modified every function call - resets to
*  zero.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SPI0_Wakeup(void) 
{
    SPI0_RestoreConfig();

    #if(SPI0_RX_SOFTWARE_BUF_ENABLED)
        SPI0_rxBufferFull  = 0u;
        SPI0_rxBufferRead  = 0u;
        SPI0_rxBufferWrite = 0u;
    #endif /* (SPI0_RX_SOFTWARE_BUF_ENABLED) */

    #if(SPI0_TX_SOFTWARE_BUF_ENABLED)
        SPI0_txBufferFull  = 0u;
        SPI0_txBufferRead  = 0u;
        SPI0_txBufferWrite = 0u;
    #endif /* (SPI0_TX_SOFTWARE_BUF_ENABLED) */

    /* Clear any data from the RX and TX FIFO */
    SPI0_ClearFIFO();

    /* Restore components block enable state */
    if(0u != SPI0_backup.enableState)
    {
        SPI0_Enable();
    }
}


/* [] END OF FILE */
