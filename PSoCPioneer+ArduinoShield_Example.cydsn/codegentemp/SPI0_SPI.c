/*******************************************************************************
* File Name: SPI0_SPI.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the SCB Component in
*  SPI mode.
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

#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Config Structure Initialization
    ***************************************/

    const SPI0_SPI_INIT_STRUCT SPI0_configSpi =
    {
        SPI0_SPI_MODE,
        SPI0_SPI_SUB_MODE,
        SPI0_SPI_CLOCK_MODE,
        SPI0_SPI_OVS_FACTOR,
        SPI0_SPI_MEDIAN_FILTER_ENABLE,
        SPI0_SPI_LATE_MISO_SAMPLE_ENABLE,
        SPI0_SPI_WAKE_ENABLE,
        SPI0_SPI_RX_DATA_BITS_NUM,
        SPI0_SPI_TX_DATA_BITS_NUM,
        SPI0_SPI_BITS_ORDER,
        SPI0_SPI_TRANSFER_SEPARATION,
        0u,
        NULL,
        0u,
        NULL,
        SPI0_SCB_IRQ_INTERNAL,
        SPI0_SPI_INTR_RX_MASK,
        SPI0_SPI_RX_TRIGGER_LEVEL,
        SPI0_SPI_INTR_TX_MASK,
        SPI0_SPI_TX_TRIGGER_LEVEL
    };


    /*******************************************************************************
    * Function Name: SPI0_SpiInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for SPI operation.
    *
    * Parameters:
    *  config:  Pointer to a structure that contains the following ordered list of
    *           fields. These fields match the selections available in the
    *           customizer.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI0_SpiInit(const SPI0_SPI_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due bad fucntion parameter */
        }
        else
        {
            /* Configure pins */
            SPI0_SetPins(SPI0_SCB_MODE_SPI, config->mode, SPI0_DUMMY_PARAM);

            /* Store internal configuration */
            SPI0_scbMode       = (uint8) SPI0_SCB_MODE_SPI;
            SPI0_scbEnableWake = (uint8) config->enableWake;
            SPI0_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            SPI0_rxBuffer      =         config->rxBuffer;
            SPI0_rxDataBits    = (uint8) config->rxDataBits;
            SPI0_rxBufferSize  = (uint8) config->rxBufferSize;

            /* Set TX direction internal variables */
            SPI0_txBuffer      =         config->txBuffer;
            SPI0_txDataBits    = (uint8) config->txDataBits;
            SPI0_txBufferSize  = (uint8) config->txBufferSize;


            /* Configure SPI interface */
            SPI0_CTRL_REG     = SPI0_GET_CTRL_OVS(config->oversample)        |
                                            SPI0_GET_CTRL_EC_AM_MODE(config->enableWake) |
                                            SPI0_CTRL_SPI;

            SPI0_SPI_CTRL_REG = SPI0_GET_SPI_CTRL_CONTINUOUS    (config->transferSeperation)  |
                                            SPI0_GET_SPI_CTRL_SELECT_PRECEDE(config->submode &
                                                                          SPI0_SPI_MODE_TI_PRECEDES_MASK) |
                                            SPI0_GET_SPI_CTRL_SCLK_MODE     (config->sclkMode)            |
                                            SPI0_GET_SPI_CTRL_LATE_MISO_SAMPLE(config->enableLateSampling)|
                                            SPI0_GET_SPI_CTRL_SUB_MODE      (config->submode)             |
                                            SPI0_GET_SPI_CTRL_MASTER_MODE   (config->mode);

            /* Configure RX direction */
            SPI0_RX_CTRL_REG     =  SPI0_GET_RX_CTRL_DATA_WIDTH(config->rxDataBits)         |
                                                SPI0_GET_RX_CTRL_BIT_ORDER (config->bitOrder)           |
                                                SPI0_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter) |
                                                SPI0_SPI_RX_CTRL;

            SPI0_RX_FIFO_CTRL_REG = SPI0_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure TX direction */
            SPI0_TX_CTRL_REG      = SPI0_GET_TX_CTRL_DATA_WIDTH(config->txDataBits) |
                                                SPI0_GET_TX_CTRL_BIT_ORDER (config->bitOrder)   |
                                                SPI0_SPI_TX_CTRL;

            SPI0_TX_FIFO_CTRL_REG = SPI0_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

            /* Configure interrupt with SPI handler */
            SPI0_SCB_IRQ_Disable();
            SPI0_SCB_IRQ_SetVector(&SPI0_SPI_UART_ISR);
            SPI0_SCB_IRQ_SetPriority((uint8)SPI0_SCB_IRQ_INTC_PRIOR_NUMBER);

            /* Configure interrupt sources */
            SPI0_INTR_I2C_EC_MASK_REG = SPI0_NO_INTR_SOURCES;
            SPI0_INTR_SPI_EC_MASK_REG = SPI0_NO_INTR_SOURCES;
            SPI0_INTR_SLAVE_MASK_REG  = SPI0_GET_SPI_INTR_SLAVE_MASK(config->rxInterruptMask);
            SPI0_INTR_MASTER_MASK_REG = SPI0_GET_SPI_INTR_MASTER_MASK(config->txInterruptMask);
            SPI0_INTR_RX_MASK_REG     = SPI0_GET_SPI_INTR_RX_MASK(config->rxInterruptMask);
            SPI0_INTR_TX_MASK_REG     = SPI0_GET_SPI_INTR_TX_MASK(config->txInterruptMask);


            /* Clear RX buffer indexes */
            SPI0_rxBufferHead     = 0u;
            SPI0_rxBufferTail     = 0u;
            SPI0_rxBufferOverflow = 0u;

            /* Clrea TX buffer indexes */
            SPI0_txBufferHead = 0u;
            SPI0_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: SPI0_SpiInit
    ********************************************************************************
    *
    * Summary:
    *  Configures the SCB for SPI operation.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI0_SpiInit(void)
    {
        /* Configure SPI interface */
        SPI0_CTRL_REG     = SPI0_SPI_DEFAULT_CTRL;
        SPI0_SPI_CTRL_REG = SPI0_SPI_DEFAULT_SPI_CTRL;

        /* Configure TX and RX direction */
        SPI0_RX_CTRL_REG      = SPI0_SPI_DEFAULT_RX_CTRL;
        SPI0_RX_FIFO_CTRL_REG = SPI0_SPI_DEFAULT_RX_FIFO_CTRL;

        /* Configure TX and RX direction */
        SPI0_TX_CTRL_REG      = SPI0_SPI_DEFAULT_TX_CTRL;
        SPI0_TX_FIFO_CTRL_REG = SPI0_SPI_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with SPI handler */
        #if(SPI0_SCB_IRQ_INTERNAL)
            SPI0_SCB_IRQ_Disable();
            SPI0_SCB_IRQ_SetVector(&SPI0_SPI_UART_ISR);
            SPI0_SCB_IRQ_SetPriority((uint8)SPI0_SCB_IRQ_INTC_PRIOR_NUMBER);
        #endif /* (SPI0_SCB_IRQ_INTERNAL) */
        
        /* Configure interrupt sources */
        SPI0_INTR_I2C_EC_MASK_REG = SPI0_SPI_DEFAULT_INTR_I2C_EC_MASK;
        SPI0_INTR_SPI_EC_MASK_REG = SPI0_SPI_DEFAULT_INTR_SPI_EC_MASK;
        SPI0_INTR_SLAVE_MASK_REG  = SPI0_SPI_DEFAULT_INTR_SLAVE_MASK;
        SPI0_INTR_MASTER_MASK_REG = SPI0_SPI_DEFAULT_INTR_MASTER_MASK;
        SPI0_INTR_RX_MASK_REG     = SPI0_SPI_DEFAULT_INTR_RX_MASK;
        SPI0_INTR_TX_MASK_REG     = SPI0_SPI_DEFAULT_INTR_TX_MASK;

        #if(SPI0_INTERNAL_RX_SW_BUFFER_CONST)
            SPI0_rxBufferHead     = 0u;
            SPI0_rxBufferTail     = 0u;
            SPI0_rxBufferOverflow = 0u;
        #endif /* (SPI0_INTERNAL_RX_SW_BUFFER_CONST) */

        #if(SPI0_INTERNAL_TX_SW_BUFFER_CONST)
            SPI0_txBufferHead = 0u;
            SPI0_txBufferTail = 0u;
        #endif /* (SPI0_INTERNAL_TX_SW_BUFFER_CONST) */
    }

#endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: SPI0_SetActiveSlaveSelect
********************************************************************************
*
* Summary:
*  Selects one of the four SPI slave select signals.
*  The component should be in one of the following states to change the active
*  slave select signal source correctly:
*   - the component is disabled
*   - the component has completed all transactions (TX FIFO is empty and the
*     SpiDone flag is set)
*  This function does not check that these conditions are met.
*  At initialization time the active slave select line is slave select 0.
*
* Parameters:
*  activeSelect: The four lines available to utilize Slave Select function.
*
* Return:
*  None
*
*******************************************************************************/
void SPI0_SpiSetActiveSlaveSelect(uint32 activeSelect)
{
    uint32 spiCtrl;

    spiCtrl = SPI0_SPI_CTRL_REG;

    spiCtrl &= (uint32) ~SPI0_SPI_CTRL_SLAVE_SELECT_MASK; /* Clear SS bits */
    spiCtrl |= (uint32)  SPI0_GET_SPI_CTRL_SS(activeSelect);

    SPI0_SPI_CTRL_REG = spiCtrl;
}


#if(SPI0_SPI_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: SPI0_SpiSaveConfig
    ********************************************************************************
    *
    * Summary:
    *  Wakeup disabled: does nothing.
    *  Wakeup  enabled: clears SCB_backup.enableState to keep component enabled
    *  while DeepSleep. The SCB_INTR_SPI_EC_WAKE_UP enabled while initialization
    *  and tracks in active mode therefore it does not require to be cleared.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Global variables:
    *  None
    *
    *******************************************************************************/
    void SPI0_SpiSaveConfig(void)
    {
        /* Clear wake-up before enable */
        SPI0_ClearSpiExtClkInterruptSource(SPI0_INTR_SPI_EC_WAKE_UP);

        /* Enable interrupt to wakeup the device */
        SPI0_SetSpiExtClkInterruptMode(SPI0_INTR_SPI_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: SPI0_SpiRestoreConfig
    ********************************************************************************
    *
    * Summary:
    *  Does nothing.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Global variables:
    *  None
    *
    *******************************************************************************/
    void SPI0_SpiRestoreConfig(void)
    {
        /* Disable interrupt to wakeup the device */
        SPI0_SetSpiExtClkInterruptMode(SPI0_NO_INTR_SOURCES);
    }
#endif /* (SPI0_SPI_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
