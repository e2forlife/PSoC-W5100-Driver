/*******************************************************************************
* File Name: SPI0.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the SCB Component.
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

#if(SPI0_SCB_MODE_I2C_INC)
    #include "SPI0_I2C_PVT.h"
#endif /* (SPI0_SCB_MODE_I2C_INC) */

#if(SPI0_SCB_MODE_EZI2C_INC)
    #include "SPI0_EZI2C_PVT.h"
#endif /* (SPI0_SCB_MODE_EZI2C_INC) */

#if(SPI0_SCB_MODE_SPI_INC || SPI0_SCB_MODE_UART_INC)
    #include "SPI0_SPI_UART_PVT.h"
#endif /* (SPI0_SCB_MODE_SPI_INC || SPI0_SCB_MODE_UART_INC) */


/**********************************
*    Run Time Configuration Vars
**********************************/

/* Stores internal component configuration for unconfigured mode */
#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common config vars */
    uint8 SPI0_scbMode = SPI0_SCB_MODE_UNCONFIG;
    uint8 SPI0_scbEnableWake;
    uint8 SPI0_scbEnableIntr;

    /* I2C config vars */
    uint8 SPI0_mode;
    uint8 SPI0_acceptAddr;

    /* SPI/UART config vars */
    volatile uint8 * SPI0_rxBuffer;
    uint8  SPI0_rxDataBits;
    uint32 SPI0_rxBufferSize;

    volatile uint8 * SPI0_txBuffer;
    uint8  SPI0_txDataBits;
    uint32 SPI0_txBufferSize;

    /* EZI2C config vars */
    uint8 SPI0_numberOfAddr;
    uint8 SPI0_subAddrSize;
#endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */


/**********************************
*     Common SCB Vars
**********************************/

uint8 SPI0_initVar = 0u;
cyisraddress SPI0_customIntrHandler = NULL;


/***************************************
*    Private Function Prototypes
***************************************/

static void SPI0_ScbEnableIntr(void);
static void SPI0_ScbModeStop(void);


/*******************************************************************************
* Function Name: SPI0_Init
********************************************************************************
*
* Summary:
*  Initializes SCB component to operate in one of selected configurations:
*  I2C, SPI, UART, EZI2C or EZSPI.
*  This function does not do any initialization when configuration is set to
*  Unconfigured SCB.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPI0_Init(void)
{
#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
    if(SPI0_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        SPI0_initVar = 0u; /* Clear init var */
    }
    else
    {
        /* Initialization was done before call */
    }

#elif(SPI0_SCB_MODE_I2C_CONST_CFG)
    SPI0_I2CInit();

#elif(SPI0_SCB_MODE_SPI_CONST_CFG)
    SPI0_SpiInit();

#elif(SPI0_SCB_MODE_UART_CONST_CFG)
    SPI0_UartInit();

#elif(SPI0_SCB_MODE_EZI2C_CONST_CFG)
    SPI0_EzI2CInit();

#endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPI0_Enable
********************************************************************************
*
* Summary:
*  Enables SCB component operation.
*  The SCB configuration should be not changed when the component is enabled.
*  Any configuration changes should be made after disabling the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPI0_Enable(void)
{
#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
    if(!SPI0_SCB_MODE_UNCONFIG_RUNTM_CFG)
    {
        /* Enable SCB block, only if already configured */
        SPI0_CTRL_REG |= SPI0_CTRL_ENABLED;
        
        /* Enable interrupt */
        SPI0_ScbEnableIntr();
    }
#else
    SPI0_CTRL_REG |= SPI0_CTRL_ENABLED; /* Enable SCB block */
    
    SPI0_ScbEnableIntr();
#endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPI0_Start
********************************************************************************
*
* Summary:
*  Invokes SCB_Init() and SCB_Enable().
*  After this function call the component is enabled and ready for operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  SPI0_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void SPI0_Start(void)
{
    if(0u == SPI0_initVar)
    {
        SPI0_initVar = 1u; /* Component was initialized */
        SPI0_Init();       /* Initialize component      */
    }

    SPI0_Enable();
}


/*******************************************************************************
* Function Name: SPI0_Stop
********************************************************************************
*
* Summary:
*  Disables the SCB component.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPI0_Stop(void)
{
#if(SPI0_SCB_IRQ_INTERNAL)
    SPI0_SCB_IRQ_Disable();     /* Disable interrupt before block */
#endif /* (SPI0_SCB_IRQ_INTERNAL) */

    SPI0_CTRL_REG &= (uint32) ~SPI0_CTRL_ENABLED;  /* Disable SCB block */

#if(SPI0_SCB_IRQ_INTERNAL)
    SPI0_SCB_IRQ_ClearPending(); /* Clear pending interrupt */
#endif /* (SPI0_SCB_IRQ_INTERNAL) */
    
    SPI0_ScbModeStop(); /* Calls scbMode specific Stop function */
}


/*******************************************************************************
* Function Name: SPI0_SetCustomInterruptHandler
********************************************************************************
*
* Summary:
*  Registers a function to be called by the internal interrupt handler.
*  First the function that is registered is called, then the internal interrupt
*  handler performs any operations such as software buffer management functions
*  before the interrupt returns.  It is user's responsibility to not break the
*  software buffer operations. Only one custom handler is supported, which is
*  the function provided by the most recent call.
*  At initialization time no custom handler is registered.
*
* Parameters:
*  func: Pointer to the function to register.
*        The value NULL indicates to remove the current custom interrupt
*        handler.
*
* Return:
*  None
*
*******************************************************************************/
void SPI0_SetCustomInterruptHandler(cyisraddress func)
{
    SPI0_customIntrHandler = func; /* Register interrupt handler */
}


/*******************************************************************************
* Function Name: SPI0_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Enables interrupt for specific mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void SPI0_ScbEnableIntr(void)
{
#if(SPI0_SCB_IRQ_INTERNAL)
    #if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Enable interrupt source */
        if(0u != SPI0_scbEnableIntr)
        {
            SPI0_SCB_IRQ_Enable();
        }
    #else
        SPI0_SCB_IRQ_Enable();
        
    #endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */
#endif /* (SPI0_SCB_IRQ_INTERNAL) */
}


/*******************************************************************************
* Function Name: SPI0_ScbModeEnableIntr
********************************************************************************
*
* Summary:
*  Calls Stop function for specific operation mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
static void SPI0_ScbModeStop(void)
{
#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
    if(SPI0_SCB_MODE_I2C_RUNTM_CFG)
    {
        SPI0_I2CStop();
    }
    else if(SPI0_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        SPI0_EzI2CStop();
    }
    else
    {
        /* None of modes above */
    }
#elif(SPI0_SCB_MODE_I2C_CONST_CFG)
    SPI0_I2CStop();

#elif(SPI0_SCB_MODE_EZI2C_CONST_CFG)
    SPI0_EzI2CStop();

#endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: SPI0_SetPins
    ********************************************************************************
    *
    * Summary:
    *  Sets pins settings accordingly to selected operation mode.
    *  Only available in Unconfigured operation mode. The mode specific
    *  initialization function calls it.
    *  Pins configuration is set by PSoC Creator when specific mode of operation
    *  selected in design time.
    *
    * Parameters:
    *  mode:      Mode of SCB operation.
    *  subMode:   Submode of SCB operation. It is only required for SPI and UART
    *             modes.
    *  uartTxRx:  Direction for UART.
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void SPI0_SetPins(uint32 mode, uint32 subMode, uint32 uartTxRx)
    {
        uint32 hsiomSel[SPI0_SCB_PINS_NUMBER];
        uint32 pinsDm  [SPI0_SCB_PINS_NUMBER];
        uint32 i;

        /* Make all unused */
        for(i = 0u; i < SPI0_SCB_PINS_NUMBER; i++)
        {
            hsiomSel[i] = SPI0_HSIOM_DEF_SEL;
            pinsDm[i]   = SPI0_PIN_DM_ALG_HIZ;
        }

        /* Choice the Dm and HSIOM */
        if((SPI0_SCB_MODE_I2C   == mode) ||
           (SPI0_SCB_MODE_EZI2C == mode))
        {
            hsiomSel[SPI0_MOSI_SCL_RX_PIN_INDEX] = SPI0_HSIOM_I2C_SEL;
            hsiomSel[SPI0_MISO_SDA_TX_PIN_INDEX] = SPI0_HSIOM_I2C_SEL;

            pinsDm[SPI0_MOSI_SCL_RX_PIN_INDEX] = SPI0_PIN_DM_OD_LO;
            pinsDm[SPI0_MISO_SDA_TX_PIN_INDEX] = SPI0_PIN_DM_OD_LO;
        }
        else if(SPI0_SCB_MODE_SPI == mode)
        {
            hsiomSel[SPI0_MOSI_SCL_RX_PIN_INDEX] = SPI0_HSIOM_SPI_SEL;
            hsiomSel[SPI0_MISO_SDA_TX_PIN_INDEX] = SPI0_HSIOM_SPI_SEL;
            hsiomSel[SPI0_SCLK_PIN_INDEX]        = SPI0_HSIOM_SPI_SEL;

            if(SPI0_SPI_SLAVE == subMode)
            {
                /* Slave */
                pinsDm[SPI0_MOSI_SCL_RX_PIN_INDEX] = SPI0_PIN_DM_DIG_HIZ;
                pinsDm[SPI0_MISO_SDA_TX_PIN_INDEX] = SPI0_PIN_DM_STRONG;
                pinsDm[SPI0_SCLK_PIN_INDEX]        = SPI0_PIN_DM_DIG_HIZ;

            #if(SPI0_SS0_PIN)
                /* Only SS0 is valid choice for Slave */
                hsiomSel[SPI0_SS0_PIN_INDEX] = SPI0_HSIOM_SPI_SEL;
                pinsDm  [SPI0_SS0_PIN_INDEX] = SPI0_PIN_DM_DIG_HIZ;
            #endif /* (SPI0_SS1_PIN) */
            }
            else /* (Master) */
            {
                pinsDm[SPI0_MOSI_SCL_RX_PIN_INDEX] = SPI0_PIN_DM_STRONG;
                pinsDm[SPI0_MISO_SDA_TX_PIN_INDEX] = SPI0_PIN_DM_DIG_HIZ;
                pinsDm[SPI0_SCLK_PIN_INDEX]        = SPI0_PIN_DM_STRONG;

            #if(SPI0_SS0_PIN)
                hsiomSel[SPI0_SS0_PIN_INDEX] = SPI0_HSIOM_SPI_SEL;
                pinsDm  [SPI0_SS0_PIN_INDEX] = SPI0_PIN_DM_STRONG;
            #endif /* (SPI0_SS0_PIN) */

            #if(SPI0_SS1_PIN)
                hsiomSel[SPI0_SS1_PIN_INDEX] = SPI0_HSIOM_SPI_SEL;
                pinsDm  [SPI0_SS1_PIN_INDEX] = SPI0_PIN_DM_STRONG;
            #endif /* (SPI0_SS1_PIN) */

            #if(SPI0_SS2_PIN)
                hsiomSel[SPI0_SS2_PIN_INDEX] = SPI0_HSIOM_SPI_SEL;
                pinsDm  [SPI0_SS2_PIN_INDEX] = SPI0_PIN_DM_STRONG;
            #endif /* (SPI0_SS2_PIN) */

            #if(SPI0_SS3_PIN)
                hsiomSel[SPI0_SS3_PIN_INDEX] = SPI0_HSIOM_SPI_SEL;
                pinsDm  [SPI0_SS3_PIN_INDEX] = SPI0_PIN_DM_STRONG;
            #endif /* (SPI0_SS2_PIN) */
            }
        }
        else /* UART */
        {
            if(SPI0_UART_MODE_SMARTCARD == subMode)
            {
                /* SmartCard */
                hsiomSel[SPI0_MISO_SDA_TX_PIN_INDEX] = SPI0_HSIOM_UART_SEL;
                pinsDm  [SPI0_MISO_SDA_TX_PIN_INDEX] = SPI0_PIN_DM_OD_LO;
            }
            else /* Standard or IrDA */
            {
                if(0u != (SPI0_UART_RX & uartTxRx))
                {
                    hsiomSel[SPI0_MOSI_SCL_RX_PIN_INDEX] = SPI0_HSIOM_UART_SEL;
                    pinsDm  [SPI0_MOSI_SCL_RX_PIN_INDEX] = SPI0_PIN_DM_DIG_HIZ;
                }

                if(0u != (SPI0_UART_TX & uartTxRx))
                {
                    hsiomSel[SPI0_MISO_SDA_TX_PIN_INDEX] = SPI0_HSIOM_UART_SEL;
                    pinsDm  [SPI0_MISO_SDA_TX_PIN_INDEX] = SPI0_PIN_DM_STRONG;
                }
            }
        }

        /* Condfigure pins: set HSIOM and DM */
        /* Condfigure pins: DR registers configuration remains unchanged for cyfitter_cfg() */

    #if(SPI0_MOSI_SCL_RX_PIN)
        SPI0_SET_HSIOM_SEL(SPI0_MOSI_SCL_RX_HSIOM_REG,
                                       SPI0_MOSI_SCL_RX_HSIOM_MASK,
                                       SPI0_MOSI_SCL_RX_HSIOM_POS,
                                       hsiomSel[SPI0_MOSI_SCL_RX_PIN_INDEX]);
    #endif /* (SPI0_MOSI_SCL_RX_PIN) */

    #if(SPI0_MOSI_SCL_RX_WAKE_PIN)
        SPI0_SET_HSIOM_SEL(SPI0_MOSI_SCL_RX_WAKE_HSIOM_REG,
                                       SPI0_MOSI_SCL_RX_WAKE_HSIOM_MASK,
                                       SPI0_MOSI_SCL_RX_WAKE_HSIOM_POS,
                                       hsiomSel[SPI0_MOSI_SCL_RX_WAKE_PIN_INDEX]);
    #endif /* (SPI0_MOSI_SCL_RX_WAKE_PIN) */

    #if(SPI0_MISO_SDA_TX_PIN)
        SPI0_SET_HSIOM_SEL(SPI0_MISO_SDA_TX_HSIOM_REG,
                                       SPI0_MISO_SDA_TX_HSIOM_MASK,
                                       SPI0_MISO_SDA_TX_HSIOM_POS,
                                       hsiomSel[SPI0_MISO_SDA_TX_PIN_INDEX]);
    #endif /* (SPI0_MOSI_SCL_RX_PIN) */

    #if(SPI0_SCLK_PIN)
        SPI0_SET_HSIOM_SEL(SPI0_SCLK_HSIOM_REG, SPI0_SCLK_HSIOM_MASK,
                                       SPI0_SCLK_HSIOM_POS, hsiomSel[SPI0_SCLK_PIN_INDEX]);
    #endif /* (SPI0_SCLK_PIN) */

    #if(SPI0_SS0_PIN)
        SPI0_SET_HSIOM_SEL(SPI0_SS0_HSIOM_REG, SPI0_SS0_HSIOM_MASK,
                                       SPI0_SS0_HSIOM_POS, hsiomSel[SPI0_SS0_PIN_INDEX]);
    #endif /* (SPI0_SS1_PIN) */

    #if(SPI0_SS1_PIN)
        SPI0_SET_HSIOM_SEL(SPI0_SS1_HSIOM_REG, SPI0_SS1_HSIOM_MASK,
                                       SPI0_SS1_HSIOM_POS, hsiomSel[SPI0_SS1_PIN_INDEX]);
    #endif /* (SPI0_SS1_PIN) */

    #if(SPI0_SS2_PIN)
        SPI0_SET_HSIOM_SEL(SPI0_SS2_HSIOM_REG, SPI0_SS2_HSIOM_MASK,
                                       SPI0_SS2_HSIOM_POS, hsiomSel[SPI0_SS2_PIN_INDEX]);
    #endif /* (SPI0_SS2_PIN) */

    #if(SPI0_SS3_PIN)
        SPI0_SET_HSIOM_SEL(SPI0_SS3_HSIOM_REG,  SPI0_SS3_HSIOM_MASK,
                                       SPI0_SS3_HSIOM_POS, hsiomSel[SPI0_SS3_PIN_INDEX]);
    #endif /* (SPI0_SS3_PIN) */



    #if(SPI0_MOSI_SCL_RX_PIN)
        SPI0_spi_mosi_i2c_scl_uart_rx_SetDriveMode((uint8)
                                                               pinsDm[SPI0_MOSI_SCL_RX_PIN_INDEX]);
    #endif /* (SPI0_MOSI_SCL_RX_PIN) */

    #if(SPI0_MOSI_SCL_RX_WAKE_PIN)
    SPI0_spi_mosi_i2c_scl_uart_rx_wake_SetDriveMode((uint8)
                                                               pinsDm[SPI0_MOSI_SCL_RX_WAKE_PIN_INDEX]);

    /* Set interrupt on rising edge */
    SPI0_SET_INCFG_TYPE(SPI0_MOSI_SCL_RX_WAKE_INTCFG_REG,
                                    SPI0_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK,
                                    SPI0_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS,
                                    SPI0_INTCFG_TYPE_FALLING_EDGE);

    #endif /* (SPI0_MOSI_SCL_RX_WAKE_PIN) */

    #if(SPI0_MISO_SDA_TX_PIN)
        SPI0_spi_miso_i2c_sda_uart_tx_SetDriveMode((uint8)
                                                                    pinsDm[SPI0_MISO_SDA_TX_PIN_INDEX]);
    #endif /* (SPI0_MOSI_SCL_RX_PIN) */

    #if(SPI0_SCLK_PIN)
        SPI0_spi_sclk_SetDriveMode((uint8) pinsDm[SPI0_SCLK_PIN_INDEX]);
    #endif /* (SPI0_SCLK_PIN) */

    #if(SPI0_SS0_PIN)
        SPI0_spi_ss0_SetDriveMode((uint8) pinsDm[SPI0_SS0_PIN_INDEX]);
    #endif /* (SPI0_SS0_PIN) */

    #if(SPI0_SS1_PIN)
        SPI0_spi_ss1_SetDriveMode((uint8) pinsDm[SPI0_SS1_PIN_INDEX]);
    #endif /* (SPI0_SS1_PIN) */

    #if(SPI0_SS2_PIN)
        SPI0_spi_ss2_SetDriveMode((uint8) pinsDm[SPI0_SS2_PIN_INDEX]);
    #endif /* (SPI0_SS2_PIN) */

    #if(SPI0_SS3_PIN)
        SPI0_spi_ss3_SetDriveMode((uint8) pinsDm[SPI0_SS3_PIN_INDEX]);
    #endif /* (SPI0_SS3_PIN) */
    }

#endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
