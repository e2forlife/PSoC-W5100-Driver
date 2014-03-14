/*******************************************************************************
* File Name: SPI0_PINS.h
* Version 1.10
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_SPI0_H)
#define CY_SCB_PINS_SPI0_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define SPI0_REMOVE_MOSI_SCL_RX_WAKE_PIN    (1u)
#define SPI0_REMOVE_MOSI_SCL_RX_PIN         (1u)
#define SPI0_REMOVE_MISO_SDA_TX_PIN         (1u)
#define SPI0_REMOVE_SCLK_PIN                (1u)
#define SPI0_REMOVE_SS0_PIN                 (1u)
#define SPI0_REMOVE_SS1_PIN                 (1u)
#define SPI0_REMOVE_SS2_PIN                 (1u)
#define SPI0_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define SPI0_REMOVE_I2C_PINS                (1u)
#define SPI0_REMOVE_SPI_MASTER_PINS         (0u)
#define SPI0_REMOVE_SPI_SLAVE_PINS          (1u)
#define SPI0_REMOVE_SPI_MASTER_SS0_PIN      (0u)
#define SPI0_REMOVE_SPI_MASTER_SS1_PIN      (0u)
#define SPI0_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define SPI0_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define SPI0_REMOVE_UART_TX_PIN             (1u)
#define SPI0_REMOVE_UART_RX_TX_PIN          (1u)
#define SPI0_REMOVE_UART_RX_PIN             (1u)
#define SPI0_REMOVE_UART_RX_WAKE_PIN        (1u)

/* Unconfigured pins */
#define SPI0_MOSI_SCL_RX_WAKE_PIN   (0u == SPI0_REMOVE_MOSI_SCL_RX_WAKE_PIN)
#define SPI0_MOSI_SCL_RX_PIN        (0u == SPI0_REMOVE_MOSI_SCL_RX_PIN)
#define SPI0_MISO_SDA_TX_PIN        (0u == SPI0_REMOVE_MISO_SDA_TX_PIN)
#define SPI0_SCLK_PIN               (0u == SPI0_REMOVE_SCLK_PIN)
#define SPI0_SS0_PIN                (0u == SPI0_REMOVE_SS0_PIN)
#define SPI0_SS1_PIN                (0u == SPI0_REMOVE_SS1_PIN)
#define SPI0_SS2_PIN                (0u == SPI0_REMOVE_SS2_PIN)
#define SPI0_SS3_PIN                (0u == SPI0_REMOVE_SS3_PIN)

/* Mode defined pins */
#define SPI0_I2C_PINS               (0u == SPI0_REMOVE_I2C_PINS)
#define SPI0_SPI_MASTER_PINS        (0u == SPI0_REMOVE_SPI_MASTER_PINS) 
#define SPI0_SPI_SLAVE_PINS         (0u == SPI0_REMOVE_SPI_SLAVE_PINS)
#define SPI0_SPI_MASTER_SS0_PIN     (0u == SPI0_REMOVE_SPI_MASTER_SS0_PIN)
#define SPI0_SPI_MASTER_SS1_PIN     (0u == SPI0_REMOVE_SPI_MASTER_SS1_PIN)
#define SPI0_SPI_MASTER_SS2_PIN     (0u == SPI0_REMOVE_SPI_MASTER_SS2_PIN)
#define SPI0_SPI_MASTER_SS3_PIN     (0u == SPI0_REMOVE_SPI_MASTER_SS3_PIN)
#define SPI0_UART_TX_PIN            (0u == SPI0_REMOVE_UART_TX_PIN)
#define SPI0_UART_RX_TX_PIN         (0u == SPI0_REMOVE_UART_RX_TX_PIN)
#define SPI0_UART_RX_PIN            (0u == SPI0_REMOVE_UART_RX_PIN)
#define SPI0_UART_RX_WAKE_PIN       (0u == SPI0_REMOVE_UART_RX_WAKE_PIN)


/***************************************
*             Includes
****************************************/

#if(SPI0_MOSI_SCL_RX_WAKE_PIN)
    #include "SPI0_spi_mosi_i2c_scl_uart_rx_wake.h"
#endif /* (SPI0_MOSI_SCL_RX_WAKE_PIN) */

#if(SPI0_MOSI_SCL_RX_PIN)
    #include "SPI0_spi_mosi_i2c_scl_uart_rx.h"
#endif /* (SPI0_MOSI_SCL_RX_PIN) */

#if(SPI0_MISO_SDA_TX_PIN)
    #include "SPI0_spi_miso_i2c_sda_uart_tx.h"
#endif /* (SPI0_MISO_SDA_TX_PIN_PIN) */

#if(SPI0_SCLK_PIN)
    #include "SPI0_spi_sclk.h"
#endif /* (SPI0_SCLK_PIN) */

#if(SPI0_SS0_PIN)
    #include "SPI0_spi_ss0.h"
#endif /* (SPI0_SS1_PIN) */

#if(SPI0_SS1_PIN)
    #include "SPI0_spi_ss1.h"
#endif /* (SPI0_SS1_PIN) */

#if(SPI0_SS2_PIN)
    #include "SPI0_spi_ss2.h"
#endif /* (SPI0_SS2_PIN) */

#if(SPI0_SS3_PIN)
    #include "SPI0_spi_ss3.h"
#endif /* (SPI0_SS3_PIN) */

#if(SPI0_I2C_PINS)
    #include "SPI0_scl.h"
    #include "SPI0_sda.h"
#endif /* (SPI0_I2C_PINS) */
    
#if(SPI0_SPI_MASTER_PINS)
    #include "SPI0_sclk_m.h"
    #include "SPI0_mosi_m.h"
    #include "SPI0_miso_m.h"
#endif /* (SPI0_SPI_MASTER_PINS) */

#if(SPI0_SPI_SLAVE_PINS)
    #include "SPI0_sclk_s.h"
    #include "SPI0_mosi_s.h"
    #include "SPI0_miso_s.h"
    #include "SPI0_ss_s.h"
#endif /* (SPI0_SPI_SLAVE_PINS) */

#if(SPI0_SPI_MASTER_SS0_PIN)
    #include "SPI0_ss0_m.h"
#endif /* (SPI0_SPI_MASTER_SS0_PIN) */

#if(SPI0_SPI_MASTER_SS1_PIN)
    #include "SPI0_ss1_m.h"
#endif /* (SPI0_SPI_MASTER_SS1_PIN) */

#if(SPI0_SPI_MASTER_SS2_PIN)
    #include "SPI0_ss2_m.h"
#endif /* (SPI0_SPI_MASTER_SS2_PIN) */

#if(SPI0_SPI_MASTER_SS3_PIN)
    #include "SPI0_ss3_m.h"
#endif /* (SPI0_SPI_MASTER_SS3_PIN) */

#if(SPI0_UART_TX_PIN)
    #include "SPI0_tx.h"
#endif /* (SPI0_UART_TX_PIN) */

#if(SPI0_UART_RX_TX_PIN)
    #include "SPI0_rx_tx.h"
#endif /* (SPI0_UART_RX_TX_PIN) */

#if(SPI0_UART_RX_PIN)
    #include "SPI0_rx.h"
#endif /* (SPI0_UART_RX_PIN) */

#if(SPI0_UART_RX_WAKE_PIN)
    #include "SPI0_rx_wake.h"
#endif /* (SPI0_UART_RX_WAKE_PIN) */


/***************************************
*              Registers
***************************************/

#if(SPI0_MOSI_SCL_RX_WAKE_PIN)
    #define SPI0_MOSI_SCL_RX_WAKE_HSIOM_REG  \
                                                (*(reg32 *) SPI0_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define SPI0_MOSI_SCL_RX_WAKE_HSIOM_PTR  \
                                                ( (reg32 *) SPI0_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define SPI0_MOSI_SCL_RX_WAKE_HSIOM_MASK \
                                                (SPI0_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_MASK)
    #define SPI0_MOSI_SCL_RX_WAKE_HSIOM_POS  \
                                                (SPI0_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_SHIFT)

    #define SPI0_MOSI_SCL_RX_WAKE_INTCFG_REG    (*(reg32 *) \
                                                              SPI0_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)
    #define SPI0_MOSI_SCL_RX_WAKE_INTCFG_PTR    ( (reg32 *) \
                                                              SPI0_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)

    #define SPI0_INTCFG_TYPE_MASK                  (0x03u)
    #define SPI0_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS  (SPI0_spi_mosi_i2c_scl_uart_rx_wake__SHIFT)
    #define SPI0_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK ((uint32)                                           \
                                                                    ((uint32) SPI0_INTCFG_TYPE_MASK << \
                                                                    SPI0_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS))
#endif /* (SPI0_MOSI_SCL_RX_WAKE_PIN) */

#if(SPI0_MOSI_SCL_RX_PIN)
    #define SPI0_MOSI_SCL_RX_HSIOM_REG      (*(reg32 *) SPI0_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define SPI0_MOSI_SCL_RX_HSIOM_PTR      ( (reg32 *) SPI0_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define SPI0_MOSI_SCL_RX_HSIOM_MASK     (SPI0_spi_mosi_i2c_scl_uart_rx__0__HSIOM_MASK)
    #define SPI0_MOSI_SCL_RX_HSIOM_POS      (SPI0_spi_mosi_i2c_scl_uart_rx__0__HSIOM_SHIFT)
#endif /* (SPI0_MOSI_SCL_RX_PIN) */

#if(SPI0_MISO_SDA_TX_PIN)
    #define SPI0_MISO_SDA_TX_HSIOM_REG      (*(reg32 *) SPI0_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define SPI0_MISO_SDA_TX_HSIOM_PTR      ( (reg32 *) SPI0_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define SPI0_MISO_SDA_TX_HSIOM_MASK     (SPI0_spi_miso_i2c_sda_uart_tx__0__HSIOM_MASK)
    #define SPI0_MISO_SDA_TX_HSIOM_POS      (SPI0_spi_miso_i2c_sda_uart_tx__0__HSIOM_SHIFT)
#endif /* (SPI0_MISO_SDA_TX_PIN_PIN) */

#if(SPI0_SCLK_PIN)
    #define SPI0_SCLK_HSIOM_REG     (*(reg32 *) SPI0_spi_sclk__0__HSIOM)
    #define SPI0_SCLK_HSIOM_PTR     ( (reg32 *) SPI0_spi_sclk__0__HSIOM)
    #define SPI0_SCLK_HSIOM_MASK    (SPI0_spi_sclk__0__HSIOM_MASK)
    #define SPI0_SCLK_HSIOM_POS     (SPI0_spi_sclk__0__HSIOM_SHIFT)
#endif /* (SPI0_SCLK_PIN) */

#if(SPI0_SS0_PIN)
    #define SPI0_SS0_HSIOM_REG      (*(reg32 *) SPI0_spi_ss0__0__HSIOM)
    #define SPI0_SS0_HSIOM_PTR      ( (reg32 *) SPI0_spi_ss0__0__HSIOM)
    #define SPI0_SS0_HSIOM_MASK     (SPI0_spi_ss0__0__HSIOM_MASK)
    #define SPI0_SS0_HSIOM_POS      (SPI0_spi_ss0__0__HSIOM_SHIFT)
#endif /* (SPI0_SS1_PIN) */

#if(SPI0_SS1_PIN)
    #define SPI0_SS1_HSIOM_REG      (*(reg32 *) SPI0_spi_ss1__0__HSIOM)
    #define SPI0_SS1_HSIOM_PTR      ( (reg32 *) SPI0_spi_ss1__0__HSIOM)
    #define SPI0_SS1_HSIOM_MASK     (SPI0_spi_ss1__0__HSIOM_MASK)
    #define SPI0_SS1_HSIOM_POS      (SPI0_spi_ss1__0__HSIOM_SHIFT)
#endif /* (SPI0_SS1_PIN) */

#if(SPI0_SS2_PIN)
    #define SPI0_SS2_HSIOM_REG     (*(reg32 *) SPI0_spi_ss2__0__HSIOM)
    #define SPI0_SS2_HSIOM_PTR     ( (reg32 *) SPI0_spi_ss2__0__HSIOM)
    #define SPI0_SS2_HSIOM_MASK    (SPI0_spi_ss2__0__HSIOM_MASK)
    #define SPI0_SS2_HSIOM_POS     (SPI0_spi_ss2__0__HSIOM_SHIFT)
#endif /* (SPI0_SS2_PIN) */

#if(SPI0_SS3_PIN)
    #define SPI0_SS3_HSIOM_REG     (*(reg32 *) SPI0_spi_ss3__0__HSIOM)
    #define SPI0_SS3_HSIOM_PTR     ( (reg32 *) SPI0_spi_ss3__0__HSIOM)
    #define SPI0_SS3_HSIOM_MASK    (SPI0_spi_ss3__0__HSIOM_MASK)
    #define SPI0_SS3_HSIOM_POS     (SPI0_spi_ss3__0__HSIOM_SHIFT)
#endif /* (SPI0_SS3_PIN) */

#if(SPI0_I2C_PINS)
    #define SPI0_SCL_HSIOM_REG     (*(reg32 *) SPI0_scl__0__HSIOM)
    #define SPI0_SCL_HSIOM_PTR     ( (reg32 *) SPI0_scl__0__HSIOM)
    #define SPI0_SCL_HSIOM_MASK    (SPI0_scl__0__HSIOM_MASK)
    #define SPI0_SCL_HSIOM_POS     (SPI0_scl__0__HSIOM_SHIFT)

    #define SPI0_SDA_HSIOM_REG     (*(reg32 *) SPI0_sda__0__HSIOM)
    #define SPI0_SDA_HSIOM_PTR     ( (reg32 *) SPI0_sda__0__HSIOM)
    #define SPI0_SDA_HSIOM_MASK    (SPI0_sda__0__HSIOM_MASK)
    #define SPI0_SDA_HSIOM_POS     (SPI0_sda__0__HSIOM_SHIFT)
#endif /* (SPI0_I2C_PINS) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constanst */
#define SPI0_HSIOM_DEF_SEL      (0x00u)
#define SPI0_HSIOM_GPIO_SEL     (0x00u)
#define SPI0_HSIOM_UART_SEL     (0x09u)
#define SPI0_HSIOM_I2C_SEL      (0x0Eu)
#define SPI0_HSIOM_SPI_SEL      (0x0Fu)

#define SPI0_SCB_PINS_NUMBER            (7u)
#define SPI0_MOSI_SCL_RX_PIN_INDEX      (0u) /* RX pins without interrupt */
#define SPI0_MOSI_SCL_RX_WAKE_PIN_INDEX (0u) /* RX pin with interrupt     */
#define SPI0_MISO_SDA_TX_PIN_INDEX      (1u)
#define SPI0_SCLK_PIN_INDEX             (2u)
#define SPI0_SS0_PIN_INDEX              (3u)
#define SPI0_SS1_PIN_INDEX              (4u)
#define SPI0_SS2_PIN_INDEX              (5u)
#define SPI0_SS3_PIN_INDEX              (6u)

#define SPI0_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin DM defines */
#define SPI0_PIN_DM_ALG_HIZ  (0u)
#define SPI0_PIN_DM_DIG_HIZ  (1u)
#define SPI0_PIN_DM_OD_LO    (4u)
#define SPI0_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

#define SPI0_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        /* Sets new bits-mask */                 \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

#define SPI0_SET_HSIOM_SEL(reg, mask, pos, sel) SPI0_SET_REGISTER_BITS(reg, mask, pos, sel)
#define SPI0_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        SPI0_SET_REGISTER_BITS(reg, mask, pos, intType)


/* SPI0_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  SPI0_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* Unconfigured SCB: scl singnal */
#if(SPI0_MOSI_SCL_RX_WAKE_PIN)
    #define SPI0_SET_I2C_SCL_DR(val) \
                            SPI0_spi_mosi_i2c_scl_uart_rx_wake_Write(val)

    #define SPI0_SET_I2C_SCL_HSIOM_SEL(sel) \
                    SPI0_SET_HSIOM_SEL(SPI0_MOSI_SCL_RX_WAKE_HSIOM_REG,  \
                                                   SPI0_MOSI_SCL_RX_WAKE_HSIOM_MASK, \
                                                   SPI0_MOSI_SCL_RX_WAKE_HSIOM_POS,  \
                                                   (sel))

#elif(SPI0_MOSI_SCL_RX_PIN)
    #define SPI0_SET_I2C_SCL_DR(val) \
                            SPI0_spi_mosi_i2c_scl_uart_rx_Write(val)


    #define SPI0_SET_I2C_SCL_HSIOM_SEL(sel) \
                            SPI0_SET_HSIOM_SEL(SPI0_MOSI_SCL_RX_HSIOM_REG,  \
                                                           SPI0_MOSI_SCL_RX_HSIOM_MASK, \
                                                           SPI0_MOSI_SCL_RX_HSIOM_POS,  \
                                                           (sel))
#else
    #if(!SPI0_I2C_PINS)
        #define SPI0_SET_I2C_SCL_DR(val) \
                                                 do{ ; }while(0)
        #define SPI0_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                        do{ ; }while(0)

    #endif /* (!SPI0_I2C_PINS) */
#endif /* (SPI0_MOSI_SCL_RX_PIN) */

/* SCB I2C: scl singal */
#if(SPI0_I2C_PINS)
    #define SPI0_SET_I2C_SCL_DR(val) SPI0_scl_Write(val)

    #define SPI0_SET_I2C_SCL_HSIOM_SEL(sel) \
                          SPI0_SET_HSIOM_SEL(SPI0_SCL_HSIOM_REG,  \
                                                         SPI0_SCL_HSIOM_MASK, \
                                                         SPI0_SCL_HSIOM_POS,  \
                                                         (sel))

#endif /* (SPI0_I2C_PINS) */


#endif /* (CY_SCB_PINS_SPI0_H) */


/* [] END OF FILE */
