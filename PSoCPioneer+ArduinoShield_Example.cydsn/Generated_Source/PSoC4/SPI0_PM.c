/*******************************************************************************
* File Name: SPI0_PM.c
* Version 1.10
*
* Description:
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPI0.h"
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


/***************************************
*   Backup Structure declaration
***************************************/

SPI0_BACKUP_STRUCT SPI0_backup =
{
    0u, /* enableState */
};


/*******************************************************************************
* Function Name: SPI0_Sleep
********************************************************************************
*
* Summary:
*  Calls SaveConfig function fucntion for selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPI0_Sleep(void)
{
#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)

    if(0u != SPI0_scbEnableWake)
    {
        if(SPI0_SCB_MODE_I2C_RUNTM_CFG)
        {
            SPI0_I2CSaveConfig();
        }
        else if(SPI0_SCB_MODE_SPI_RUNTM_CFG)
        {
            SPI0_SpiSaveConfig();
        }
        else if(SPI0_SCB_MODE_UART_RUNTM_CFG)
        {
            SPI0_UartSaveConfig();
        }
        else if(SPI0_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SPI0_EzI2CSaveConfig();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    }
    else
    {
        SPI0_backup.enableState = (uint8) SPI0_GET_CTRL_ENABLED;
        
        if(0u != SPI0_backup.enableState)
        {
            SPI0_Stop();
        }
    }
    
    SPI0_DisableTxPinsInputBuffer();
    
#else
    
    #if defined (SPI0_I2C_WAKE_ENABLE_CONST) && (SPI0_I2C_WAKE_ENABLE_CONST)
        SPI0_I2CSaveConfig();
        
    #elif defined (SPI0_SPI_WAKE_ENABLE_CONST) && (SPI0_SPI_WAKE_ENABLE_CONST)
        SPI0_SpiSaveConfig();
        
    #elif defined (SPI0_UART_WAKE_ENABLE_CONST) && (SPI0_UART_WAKE_ENABLE_CONST)
        SPI0_UartSaveConfig();
        
    #elif defined (SPI0_EZI2C_WAKE_ENABLE_CONST) && (SPI0_EZI2C_WAKE_ENABLE_CONST)
        SPI0_EzI2CSaveConfig();
    
    #else
        
        SPI0_backup.enableState = (uint8) SPI0_GET_CTRL_ENABLED;
        
        /* Check enable state */
        if(0u != SPI0_backup.enableState)
        {
            SPI0_Stop();
        }
        
    #endif /* defined (SPI0_SCB_MODE_I2C_CONST_CFG) && (SPI0_I2C_WAKE_ENABLE_CONST) */
    
    SPI0_DisableTxPinsInputBuffer();
    
#endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPI0_Wakeup
********************************************************************************
*
* Summary:
*  Calls RestoreConfig function fucntion for selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPI0_Wakeup(void)
{
#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)

    SPI0_EnableTxPinsInputBuffer();
        
    if(0u != SPI0_scbEnableWake)
    {
        if(SPI0_SCB_MODE_I2C_RUNTM_CFG)
        {
            SPI0_I2CRestoreConfig();
        }
        else if(SPI0_SCB_MODE_SPI_RUNTM_CFG)
        {
            SPI0_SpiRestoreConfig();
        }
        else if(SPI0_SCB_MODE_UART_RUNTM_CFG)
        {
            SPI0_UartRestoreConfig();
        }
        else if(SPI0_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SPI0_EzI2CRestoreConfig();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    }
    else
    {    
        /* Restore enable state */
        if(0u != SPI0_backup.enableState)
        {
            SPI0_Enable();
        }
    }

#else
    
    SPI0_EnableTxPinsInputBuffer();
        
    #if defined (SPI0_I2C_WAKE_ENABLE_CONST) && (SPI0_I2C_WAKE_ENABLE_CONST)
        SPI0_I2CRestoreConfig();
        
    #elif defined (SPI0_SPI_WAKE_ENABLE_CONST) && (SPI0_SPI_WAKE_ENABLE_CONST)
        SPI0_SpiRestoreConfig();
        
    #elif defined (SPI0_UART_WAKE_ENABLE_CONST) && (SPI0_UART_WAKE_ENABLE_CONST)
        SPI0_UartRestoreConfig();
        
    #elif defined (SPI0_EZI2C_WAKE_ENABLE_CONST) && (SPI0_EZI2C_WAKE_ENABLE_CONST)
        SPI0_EzI2CRestoreConfig();
    
    #else
        /* Check enable state */
        if(0u != SPI0_backup.enableState)
        {
            SPI0_Enable();
        }
        
    #endif /* (SPI0_I2C_WAKE_ENABLE_CONST) */

#endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPI0_DisableTxPinsInputBuffer
********************************************************************************
*
* Summary:
*  Disables input buffers for TX pins. This action removes leakage current while
*  low power mode (Cypress ID 149635).
*   SCB mode is I2C and EZI2C: bus is pulled-up. Leave pins as it is.
*   SCB mode SPI:
*     Slave  - disable input buffer for MISO pin.
*     Master - disable input buffer for all pins.
*   SCB mode SmartCard: 
*     Standard and IrDA - disable input buffer for TX pin.
*     SmartCard - RX_TX pin is pulled-up. Leave pin as it is.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPI0_DisableTxPinsInputBuffer(void)
{
#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
    
    /* SCB mode is I2C and EZI2C: bus is pulled-up. Does nothing */
       
    if(SPI0_SCB_MODE_SPI_RUNTM_CFG)
    {
        if(0u != (SPI0_SPI_CTRL_REG & SPI0_SPI_CTRL_MASTER))
        /* SPI Master */
        {
        #if(SPI0_MOSI_SCL_RX_WAKE_PIN)
            SPI0_spi_mosi_i2c_scl_uart_rx_wake_INP_DIS |= \
                                                                SPI0_spi_mosi_i2c_scl_uart_rx_wake_MASK;
        #endif /* (SPI0_MOSI_SCL_RX_WAKE_PIN) */

        #if(SPI0_MOSI_SCL_RX_PIN)
            SPI0_spi_mosi_i2c_scl_uart_rx_INP_DIS |= SPI0_spi_mosi_i2c_scl_uart_rx_MASK;
        #endif /* (SPI0_MOSI_SCL_RX_PIN) */

        #if(SPI0_MISO_SDA_TX_PIN)
            SPI0_spi_miso_i2c_sda_uart_tx_INP_DIS |= SPI0_spi_miso_i2c_sda_uart_tx_MASK;
        #endif /* (SPI0_MISO_SDA_TX_PIN_PIN) */

        #if(SPI0_SCLK_PIN)
            SPI0_spi_sclk_INP_DIS |= SPI0_spi_sclk_MASK;
        #endif /* (SPI0_SCLK_PIN) */

        #if(SPI0_SS0_PIN)
            SPI0_spi_ss0_INP_DIS |= SPI0_spi_ss0_MASK;
        #endif /* (SPI0_SS1_PIN) */

        #if(SPI0_SS1_PIN)
            SPI0_spi_ss1_INP_DIS |= SPI0_spi_ss1_MASK;
        #endif /* (SPI0_SS1_PIN) */

        #if(SPI0_SS2_PIN)
            SPI0_spi_ss2_INP_DIS |= SPI0_spi_ss2_MASK;
        #endif /* (SPI0_SS2_PIN) */

        #if(SPI0_SS3_PIN)
            SPI0_spi_ss3_INP_DIS |= SPI0_spi_ss3_MASK;
        #endif /* (SPI0_SS3_PIN) */
        }
        else
        /* SPI Slave */
        {
        #if(SPI0_MISO_SDA_TX_PIN)
            SPI0_spi_miso_i2c_sda_uart_tx_INP_DIS |= SPI0_spi_miso_i2c_sda_uart_tx_MASK;
        #endif /* (SPI0_MISO_SDA_TX_PIN_PIN) */
        }
    }
    else if (SPI0_SCB_MODE_UART_RUNTM_CFG)
    {
        if(SPI0_UART_CTRL_MODE_UART_SMARTCARD != 
            (SPI0_UART_CTRL_REG & SPI0_UART_CTRL_MODE_MASK))
        /* UART Standard or IrDA */
        {
        #if(SPI0_MISO_SDA_TX_PIN)
            SPI0_spi_miso_i2c_sda_uart_tx_INP_DIS |= SPI0_spi_miso_i2c_sda_uart_tx_MASK;
        #endif /* (SPI0_MISO_SDA_TX_PIN_PIN) */
        }
    }
    else
    {
        /* Does nothing */
    }
    
#else
    
    /* SCB mode is I2C and EZI2C: bus is pulled-up. Does nothing */
        
    /* SCB mode is SPI Master */
    #if(SPI0_SPI_MASTER_PINS)
        SPI0_sclk_m_INP_DIS |= SPI0_sclk_m_MASK;
        SPI0_mosi_m_INP_DIS |= SPI0_mosi_m_MASK;
        SPI0_miso_m_INP_DIS |= SPI0_miso_m_MASK;
    #endif /* (SPI0_SPI_MASTER_PINS) */

    #if(SPI0_SPI_MASTER_SS0_PIN)
        SPI0_ss0_m_INP_DIS |= SPI0_ss0_m_MASK;
    #endif /* (SPI0_SPI_MASTER_SS0_PIN) */

    #if(SPI0_SPI_MASTER_SS1_PIN)
        SPI0_ss1_m_INP_DIS |= SPI0_ss1_m_MASK;
    #endif /* (SPI0_SPI_MASTER_SS1_PIN) */

    #if(SPI0_SPI_MASTER_SS2_PIN)
        SPI0_ss2_m_INP_DIS |= SPI0_ss2_m_MASK;
    #endif /* (SPI0_SPI_MASTER_SS2_PIN) */

    #if(SPI0_SPI_MASTER_SS3_PIN)
        SPI0_ss3_m_INP_DIS |= SPI0_ss3_m_MASK;
    #endif /* (SPI0_SPI_MASTER_SS3_PIN) */
    
    /* SCB mode is SPI Slave */
    #if(SPI0_SPI_SLAVE_PINS)
        SPI0_miso_s_INP_DIS |= SPI0_miso_s_MASK;
    #endif /* (SPI0_SPI_SLAVE_PINS) */

    /* SCB mode is UART */
    #if(SPI0_UART_TX_PIN)
        SPI0_tx_INP_DIS |= SPI0_tx_MASK;
    #endif /* (SPI0_UART_TX_PIN) */

#endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPI0_EnableTxPinsInputBuffer
********************************************************************************
*
* Summary:
*  Enables input buffers for TX pins. Restore changes done byte
*SPI0_DisableTxPinsInputBuffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPI0_EnableTxPinsInputBuffer(void)
{
#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
    if(SPI0_SCB_MODE_SPI_RUNTM_CFG)
    {
        if(0u != (SPI0_SPI_CTRL_REG & SPI0_SPI_CTRL_MASTER))
        /* SPI Master */
        {
        #if(SPI0_MOSI_SCL_RX_WAKE_PIN)
            SPI0_spi_mosi_i2c_scl_uart_rx_wake_INP_DIS &= \
                                            (uint32) ~((uint32) SPI0_spi_mosi_i2c_scl_uart_rx_wake_MASK);
        #endif /* (SPI0_MOSI_SCL_RX_WAKE_PIN) */

        #if(SPI0_MOSI_SCL_RX_PIN)
            SPI0_spi_mosi_i2c_scl_uart_rx_INP_DIS &= \
                                            (uint32) ~((uint32) SPI0_spi_mosi_i2c_scl_uart_rx_MASK);
        #endif /* (SPI0_MOSI_SCL_RX_PIN) */

        #if(SPI0_MISO_SDA_TX_PIN)
            SPI0_spi_miso_i2c_sda_uart_tx_INP_DIS &= \
                                            (uint32) ~((uint32) SPI0_spi_miso_i2c_sda_uart_tx_MASK);
        #endif /* (SPI0_MISO_SDA_TX_PIN_PIN) */

        #if(SPI0_SCLK_PIN)
            SPI0_spi_sclk_INP_DIS &= (uint32) ~((uint32) SPI0_spi_sclk_MASK);
        #endif /* (SPI0_SCLK_PIN) */

        #if(SPI0_SS0_PIN)
            SPI0_spi_ss0_INP_DIS &= (uint32) ~((uint32) SPI0_spi_ss0_MASK);
        #endif /* (SPI0_SS1_PIN) */

        #if(SPI0_SS1_PIN)
            SPI0_spi_ss1_INP_DIS &= (uint32) ~((uint32) SPI0_spi_ss1_MASK);
        #endif /* (SPI0_SS1_PIN) */

        #if(SPI0_SS2_PIN)
            SPI0_spi_ss2_INP_DIS &= (uint32) ~((uint32) SPI0_spi_ss2_MASK);
        #endif /* (SPI0_SS2_PIN) */

        #if(SPI0_SS3_PIN)
            SPI0_spi_ss3_INP_DIS &= (uint32) ~((uint32) SPI0_spi_ss3_MASK);
        #endif /* (SPI0_SS3_PIN) */
        }
        else
        /* SPI Slave */
        {
        #if(SPI0_MISO_SDA_TX_PIN)
            SPI0_spi_miso_i2c_sda_uart_tx_INP_DIS &= \
                                                (uint32) ~((uint32) SPI0_spi_miso_i2c_sda_uart_tx_MASK);
        #endif /* (SPI0_MISO_SDA_TX_PIN_PIN) */
        }
    }
    else if (SPI0_SCB_MODE_UART_RUNTM_CFG)
    {
        if(SPI0_UART_CTRL_MODE_UART_SMARTCARD != 
                (SPI0_UART_CTRL_REG & SPI0_UART_CTRL_MODE_MASK))
        /* UART Standard or IrDA */
        {
        #if(SPI0_MISO_SDA_TX_PIN)
            SPI0_spi_miso_i2c_sda_uart_tx_INP_DIS &= \
                                                (uint32) ~((uint32) SPI0_spi_miso_i2c_sda_uart_tx_MASK);
        #endif /* (SPI0_MISO_SDA_TX_PIN_PIN) */
        }
    }
    else
    {
        /* Does nothing */
    }
    
#else
        
    /* SCB mode is SPI Master */
    #if(SPI0_SPI_MASTER_PINS)
        SPI0_sclk_m_INP_DIS &= (uint32) ~((uint32) SPI0_sclk_m_MASK);
        SPI0_mosi_m_INP_DIS &= (uint32) ~((uint32) SPI0_mosi_m_MASK);
        SPI0_miso_m_INP_DIS &= (uint32) ~((uint32) SPI0_miso_m_MASK);
    #endif /* (SPI0_SPI_MASTER_PINS) */

    #if(SPI0_SPI_MASTER_SS0_PIN)
        SPI0_ss0_m_INP_DIS &= (uint32) ~((uint32) SPI0_ss0_m_MASK);
    #endif /* (SPI0_SPI_MASTER_SS0_PIN) */

    #if(SPI0_SPI_MASTER_SS1_PIN)
        SPI0_ss1_m_INP_DIS &= (uint32) ~((uint32) SPI0_ss1_m_MASK);
    #endif /* (SPI0_SPI_MASTER_SS1_PIN) */

    #if(SPI0_SPI_MASTER_SS2_PIN)
        SPI0_ss2_m_INP_DIS &= (uint32) ~((uint32) SPI0_ss2_m_MASK);
    #endif /* (SPI0_SPI_MASTER_SS2_PIN) */

    #if(SPI0_SPI_MASTER_SS3_PIN)
        SPI0_ss3_m_INP_DIS &= (uint32) ~((uint32) SPI0_ss3_m_MASK);
    #endif /* (SPI0_SPI_MASTER_SS3_PIN) */
    
    /* SCB mode is SPI Slave */
    #if(SPI0_SPI_SLAVE_PINS)
        SPI0_miso_s_INP_DIS &= (uint32) ~((uint32) SPI0_miso_s_MASK);
    #endif /* (SPI0_SPI_SLAVE_PINS) */

    /* SCB mode is UART */
    #if(SPI0_UART_TX_PIN)
        SPI0_tx_INP_DIS &= (uint32) ~((uint32) SPI0_tx_MASK);
    #endif /* (SPI0_UART_TX_PIN) */

#endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
