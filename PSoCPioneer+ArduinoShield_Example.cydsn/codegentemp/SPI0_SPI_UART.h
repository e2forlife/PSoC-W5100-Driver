/*******************************************************************************
* File Name: SPI0_SPI_UART.h
* Version 1.10
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_SPI0_H)
#define CY_SCB_SPI_UART_SPI0_H

#include "SPI0.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define SPI0_SPI_MODE                   (1u)
#define SPI0_SPI_SUB_MODE               (0u)
#define SPI0_SPI_CLOCK_MODE             (0u)
#define SPI0_SPI_OVS_FACTOR             (8u)
#define SPI0_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define SPI0_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define SPI0_SPI_RX_DATA_BITS_NUM       (8u)
#define SPI0_SPI_TX_DATA_BITS_NUM       (8u)
#define SPI0_SPI_WAKE_ENABLE            (0u)
#define SPI0_SPI_BITS_ORDER             (1u)
#define SPI0_SPI_TRANSFER_SEPARATION    (1u)
#define SPI0_SPI_NUMBER_OF_SS_LINES     (2u)
#define SPI0_SPI_RX_BUFFER_SIZE         (8u)
#define SPI0_SPI_TX_BUFFER_SIZE         (8u)

#define SPI0_SPI_INTERRUPT_MODE         (0u)

#define SPI0_SPI_INTR_RX_MASK           (0u)
#define SPI0_SPI_INTR_TX_MASK           (0u)

#define SPI0_SPI_RX_TRIGGER_LEVEL       (7u)
#define SPI0_SPI_TX_TRIGGER_LEVEL       (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define SPI0_UART_SUB_MODE              (0u)
#define SPI0_UART_DIRECTION             (3u)
#define SPI0_UART_DATA_BITS_NUM         (8u)
#define SPI0_UART_PARITY_TYPE           (2u)
#define SPI0_UART_STOP_BITS_NUM         (2u)
#define SPI0_UART_OVS_FACTOR            (12u)
#define SPI0_UART_IRDA_LOW_POWER        (0u)
#define SPI0_UART_MEDIAN_FILTER_ENABLE  (0u)
#define SPI0_UART_RETRY_ON_NACK         (0u)
#define SPI0_UART_IRDA_POLARITY         (0u)
#define SPI0_UART_DROP_ON_FRAME_ERR     (0u)
#define SPI0_UART_DROP_ON_PARITY_ERR    (0u)
#define SPI0_UART_WAKE_ENABLE           (0u)
#define SPI0_UART_RX_BUFFER_SIZE        (8u)
#define SPI0_UART_TX_BUFFER_SIZE        (8u)
#define SPI0_UART_MP_MODE_ENABLE        (0u)
#define SPI0_UART_MP_ACCEPT_ADDRESS     (0u)
#define SPI0_UART_MP_RX_ADDRESS         (2u)
#define SPI0_UART_MP_RX_ADDRESS_MASK    (255u)

#define SPI0_UART_INTERRUPT_MODE        (0u)

#define SPI0_UART_INTR_RX_MASK          (0u)
#define SPI0_UART_INTR_TX_MASK          (0u)

#define SPI0_UART_RX_TRIGGER_LEVEL      (7u)
#define SPI0_UART_TX_TRIGGER_LEVEL      (0u)

/* Sources of RX errors */
#define SPI0_INTR_RX_ERR        (SPI0_INTR_RX_OVERFLOW    | \
                                             SPI0_INTR_RX_UNDERFLOW   | \
                                             SPI0_INTR_RX_FRAME_ERROR | \
                                             SPI0_INTR_RX_PARITY_ERROR)

/* UART direction enum */
#define SPI0_UART_RX    (1u)
#define SPI0_UART_TX    (2u)
#define SPI0_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Direction */
    #define SPI0_RX_DIRECTION           (1u)
    #define SPI0_TX_DIRECTION           (1u)
    #define SPI0_UART_RX_DIRECTION      (1u)
    #define SPI0_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for uncofigured mode */
    #define SPI0_INTERNAL_RX_SW_BUFFER   (0u)
    #define SPI0_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define SPI0_RX_BUFFER_SIZE (SPI0_rxBufferSize)
    #define SPI0_TX_BUFFER_SIZE (SPI0_txBufferSize)

    /* Return true if buffer is provided */
    #define SPI0_CHECK_RX_SW_BUFFER (NULL != SPI0_rxBuffer)
    #define SPI0_CHECK_TX_SW_BUFFER (NULL != SPI0_txBuffer)

    /* Alwasy provde global variables to support RX and TX buffers */
    #define SPI0_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define SPI0_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define SPI0_SPI_WAKE_ENABLE_CONST  (1u)
    #define SPI0_CHECK_SPI_WAKE_ENABLE  (0u != SPI0_scbEnableWake)
    #define SPI0_UART_WAKE_ENABLE_CONST (1u)

#else

    /* SPI internal RX and TX buffers */
    #define SPI0_INTERNAL_SPI_RX_SW_BUFFER  (SPI0_SPI_RX_BUFFER_SIZE > \
                                                                                            SPI0_FIFO_SIZE)
    #define SPI0_INTERNAL_SPI_TX_SW_BUFFER  (SPI0_SPI_TX_BUFFER_SIZE > \
                                                                                            SPI0_FIFO_SIZE)

    /* UART internal RX and TX buffers */
    #define SPI0_INTERNAL_UART_RX_SW_BUFFER  (SPI0_UART_RX_BUFFER_SIZE > \
                                                                                            SPI0_FIFO_SIZE)
    #define SPI0_INTERNAL_UART_TX_SW_BUFFER  (SPI0_UART_TX_BUFFER_SIZE > \
                                                                                            SPI0_FIFO_SIZE)

    /* SPI Direction */
    #define SPI0_SPI_RX_DIRECTION (1u)
    #define SPI0_SPI_TX_DIRECTION (1u)

    /* UART Direction */
    #define SPI0_UART_RX_DIRECTION (0u != (SPI0_UART_DIRECTION & SPI0_UART_RX))
    #define SPI0_UART_TX_DIRECTION (0u != (SPI0_UART_DIRECTION & SPI0_UART_TX))

    /* Direction */
    #define SPI0_RX_DIRECTION ((SPI0_SCB_MODE_SPI_CONST_CFG) ? \
                                            (SPI0_SPI_RX_DIRECTION) : (SPI0_UART_RX_DIRECTION))

    #define SPI0_TX_DIRECTION ((SPI0_SCB_MODE_SPI_CONST_CFG) ? \
                                            (SPI0_SPI_TX_DIRECTION) : (SPI0_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART */
    #if(SPI0_SCB_MODE_SPI_CONST_CFG)

        /* Internal SPI RX and TX buffer */
        #define SPI0_INTERNAL_RX_SW_BUFFER  (SPI0_INTERNAL_SPI_RX_SW_BUFFER)
        #define SPI0_INTERNAL_TX_SW_BUFFER  (SPI0_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define SPI0_RX_BUFFER_SIZE         (SPI0_SPI_RX_BUFFER_SIZE + 1u)
        #define SPI0_TX_BUFFER_SIZE         (SPI0_SPI_TX_BUFFER_SIZE)
        
        /* Get wakeup enable option */
        #define SPI0_SPI_WAKE_ENABLE_CONST  (0u != SPI0_SPI_WAKE_ENABLE)
        #define SPI0_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* Internal UART RX and TX buffer */
        #define SPI0_INTERNAL_RX_SW_BUFFER  (SPI0_INTERNAL_UART_RX_SW_BUFFER)
        #define SPI0_INTERNAL_TX_SW_BUFFER  (SPI0_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define SPI0_RX_BUFFER_SIZE         (SPI0_UART_RX_BUFFER_SIZE + 1u)
        #define SPI0_TX_BUFFER_SIZE         (SPI0_UART_TX_BUFFER_SIZE)
        
        /* Get wakeup enable option */
        #define SPI0_SPI_WAKE_ENABLE_CONST  (0u)
        #define SPI0_UART_WAKE_ENABLE_CONST (0u != SPI0_UART_WAKE_ENABLE)
    #endif /* (SPI0_SCB_MODE_SPI_CONST_CFG) */

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define SPI0_CHECK_RX_SW_BUFFER (SPI0_INTERNAL_RX_SW_BUFFER)
    #define SPI0_CHECK_TX_SW_BUFFER (SPI0_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define SPI0_INTERNAL_RX_SW_BUFFER_CONST    (SPI0_INTERNAL_RX_SW_BUFFER)
    #define SPI0_INTERNAL_TX_SW_BUFFER_CONST    (SPI0_INTERNAL_TX_SW_BUFFER)
    
    /* Wakeup for SPI */
    #define SPI0_CHECK_SPI_WAKE_ENABLE  (SPI0_SPI_WAKE_ENABLE_CONST)

#endif /* End (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Bootloader communication interface enable: NOT supported yet */
#define SPI0_SPI_BTLDR_COMM_ENABLED   ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPI0) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

#define SPI0_UART_BTLDR_COMM_ENABLED   ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPI0) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))


/***************************************
*       Type Definitions
***************************************/

/* SPI0_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
} SPI0_SPI_INIT_STRUCT;

/* SPI0_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
} SPI0_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
    void SPI0_SpiInit(const SPI0_SPI_INIT_STRUCT *config);
#endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(SPI0_SCB_MODE_SPI_INC)
    void SPI0_SpiSetActiveSlaveSelect(uint32 activeSelect);
#endif /* (SPI0_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
    void SPI0_UartInit(const SPI0_UART_INIT_STRUCT *config);
#endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(SPI0_SCB_MODE_UART_INC)
    void SPI0_UartSetRxAddress(uint32 address);
    void SPI0_UartSetRxAddressMask(uint32 addressMask);
#endif /* (SPI0_SCB_MODE_UART_INC) */

/* UART RX direction APIs */
#if(SPI0_UART_RX_DIRECTION)
    uint32 SPI0_UartGetChar(void);
    uint32 SPI0_UartGetByte(void);
#endif /* (SPI0_UART_RX_DIRECTION) */

/* UART TX direction APIs */
#if(SPI0_UART_TX_DIRECTION)
    #define SPI0_UartPutChar(ch)    SPI0_SpiUartWriteTxData((uint32)(ch))
    void SPI0_UartPutString(const char8 string[]);
    void SPI0_UartPutCRLF(uint32 txDataByte);
#endif /* (SPI0_UART_TX_DIRECTION) */

/* Common APIs Rx direction */
#if(SPI0_RX_DIRECTION)
    uint32 SPI0_SpiUartReadRxData(void);
    uint32 SPI0_SpiUartGetRxBufferSize(void);
    void   SPI0_SpiUartClearRxBuffer(void);
#endif /* (SPI0_RX_DIRECTION) */

/* Common APIs Tx direction */
#if(SPI0_TX_DIRECTION)
    void   SPI0_SpiUartWriteTxData(uint32 txDataByte);
    void   SPI0_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    void   SPI0_SpiUartClearTxBuffer(void);
    uint32 SPI0_SpiUartGetTxBufferSize(void);
#endif /* (SPI0_TX_DIRECTION) */

CY_ISR_PROTO(SPI0_SPI_UART_ISR);

#if(SPI0_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(SPI0_UART_WAKEUP_ISR);
#endif /* (SPI0_UART_RX_WAKEUP_IRQ) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SPI0_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void SPI0_SpiCyBtldrCommStart(void);
    void SPI0_SpiCyBtldrCommStop (void);
    void SPI0_SpiCyBtldrCommReset(void);
    cystatus SPI0_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SPI0_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SPI0_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SPI0_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void SPI0_UartCyBtldrCommStart(void);
    void SPI0_UartCyBtldrCommStop (void);
    void SPI0_UartCyBtldrCommReset(void);
    cystatus SPI0_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SPI0_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SPI0_UART_BTLDR_COMM_ENABLED) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   SPI0_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 SPI0_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   SPI0_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 SPI0_GetWordFromTxBuffer(uint32 idx);

#else

    /* RX direction */
    #if(SPI0_INTERNAL_RX_SW_BUFFER_CONST)
        #define SPI0_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    SPI0_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define SPI0_GetWordFromRxBuffer(idx) SPI0_rxBufferInternal[(idx)]

    #endif /* (SPI0_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(SPI0_INTERNAL_TX_SW_BUFFER_CONST)
        #define SPI0_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        SPI0_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define SPI0_GetWordFromTxBuffer(idx) SPI0_txBufferInternal[(idx)]

    #endif /* (SPI0_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (SPI0_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI mode enum */
#define SPI0_SPI_SLAVE  (0u)
#define SPI0_SPI_MASTER (1u)

/* SPI sub mode enum */
#define SPI0_SPI_MODE_MOTOROLA      (0x00u)
#define SPI0_SPI_MODE_TI_COINCIDES  (0x01u)
#define SPI0_SPI_MODE_TI_PRECEDES   (0x11u)
#define SPI0_SPI_MODE_NATIONAL      (0x02u)
#define SPI0_SPI_MODE_MASK          (0x03u)
#define SPI0_SPI_MODE_TI_PRECEDES_MASK  (0x10u)

/* SPI phase and polarity mode enum */
#define SPI0_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define SPI0_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define SPI0_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define SPI0_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define SPI0_BITS_ORDER_LSB_FIRST   (0u)
#define SPI0_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define SPI0_SPI_TRANSFER_SEPARATED     (0u)
#define SPI0_SPI_TRANSFER_CONTINUOUS    (1u)

/* "activeSS" constants for SpiSetActiveSlaveSelect() function */
#define SPI0_SPIM_ACTIVE_SS0    (0x00u)
#define SPI0_SPIM_ACTIVE_SS1    (0x01u)
#define SPI0_SPIM_ACTIVE_SS2    (0x02u)
#define SPI0_SPIM_ACTIVE_SS3    (0x03u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define SPI0_UART_MODE_STD          (0u)
#define SPI0_UART_MODE_SMARTCARD    (1u)
#define SPI0_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define SPI0_UART_RX    (1u)
#define SPI0_UART_TX    (2u)
#define SPI0_UART_TX_RX (3u)

/* UART parity enum */
#define SPI0_UART_PARITY_EVEN   (0u)
#define SPI0_UART_PARITY_ODD    (1u)
#define SPI0_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define SPI0_UART_STOP_BITS_1   (1u)
#define SPI0_UART_STOP_BITS_1_5 (2u)
#define SPI0_UART_STOP_BITS_2   (3u)

/* UART IrDA low power OVS enum */
#define SPI0_UART_IRDA_LP_OVS16     (16u)
#define SPI0_UART_IRDA_LP_OVS32     (32u)
#define SPI0_UART_IRDA_LP_OVS48     (48u)
#define SPI0_UART_IRDA_LP_OVS96     (96u)
#define SPI0_UART_IRDA_LP_OVS192    (192u)
#define SPI0_UART_IRDA_LP_OVS768    (768u)
#define SPI0_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define SPI0_UART_MP_MARK       (0x100u)
#define SPI0_UART_MP_SPACE      (0x000u)


/***************************************
*     Vars with External Linkage
***************************************/

#if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const SPI0_SPI_INIT_STRUCT  SPI0_configSpi;
    extern const SPI0_UART_INIT_STRUCT SPI0_configUart;
#endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define SPI0_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & SPI0_INTR_SLAVE_SPI_BUS_ERROR)
#define SPI0_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & SPI0_INTR_MASTER_SPI_DONE)
#define SPI0_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~SPI0_INTR_SLAVE_SPI_BUS_ERROR)

#define SPI0_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~SPI0_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define SPI0_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((SPI0_UART_IRDA_LP_OVS16   == (oversample)) ? SPI0_CTRL_OVS_IRDA_LP_OVS16 : \
         ((SPI0_UART_IRDA_LP_OVS32   == (oversample)) ? SPI0_CTRL_OVS_IRDA_LP_OVS32 : \
          ((SPI0_UART_IRDA_LP_OVS48   == (oversample)) ? SPI0_CTRL_OVS_IRDA_LP_OVS48 : \
           ((SPI0_UART_IRDA_LP_OVS96   == (oversample)) ? SPI0_CTRL_OVS_IRDA_LP_OVS96 : \
            ((SPI0_UART_IRDA_LP_OVS192  == (oversample)) ? SPI0_CTRL_OVS_IRDA_LP_OVS192 : \
             ((SPI0_UART_IRDA_LP_OVS768  == (oversample)) ? SPI0_CTRL_OVS_IRDA_LP_OVS768 : \
              ((SPI0_UART_IRDA_LP_OVS1536 == (oversample)) ? SPI0_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          SPI0_CTRL_OVS_IRDA_LP_OVS16)))))))

#define SPI0_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (SPI0_UART_RX & (direction))) ? \
                                                                    (SPI0_RX_CTRL_ENABLED) : (0u))

#define SPI0_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (SPI0_UART_TX & (direction))) ? \
                                                                    (SPI0_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define SPI0_CTRL_SPI      (SPI0_CTRL_MODE_SPI)
#define SPI0_SPI_RX_CTRL   (SPI0_RX_CTRL_ENABLED)
#define SPI0_SPI_TX_CTRL   (SPI0_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#if(SPI0_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define SPI0_SPI_DEFAULT_CTRL \
                    (SPI0_GET_CTRL_OVS(SPI0_SPI_OVS_FACTOR)         | \
                     SPI0_GET_CTRL_EC_AM_MODE(SPI0_SPI_WAKE_ENABLE) | \
                     SPI0_CTRL_SPI)

    #define SPI0_SPI_DEFAULT_SPI_CTRL \
                    (SPI0_GET_SPI_CTRL_CONTINUOUS    (SPI0_SPI_TRANSFER_SEPARATION)       | \
                     SPI0_GET_SPI_CTRL_SELECT_PRECEDE(SPI0_SPI_SUB_MODE &                   \
                                                                  SPI0_SPI_MODE_TI_PRECEDES_MASK)     | \
                     SPI0_GET_SPI_CTRL_SCLK_MODE     (SPI0_SPI_CLOCK_MODE)                | \
                     SPI0_GET_SPI_CTRL_LATE_MISO_SAMPLE(SPI0_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     SPI0_GET_SPI_CTRL_SUB_MODE      (SPI0_SPI_SUB_MODE)                  | \
                     SPI0_GET_SPI_CTRL_MASTER_MODE   (SPI0_SPI_MODE))

    /* RX direction */
    #define SPI0_SPI_DEFAULT_RX_CTRL \
                    (SPI0_GET_RX_CTRL_DATA_WIDTH(SPI0_SPI_RX_DATA_BITS_NUM)     | \
                     SPI0_GET_RX_CTRL_BIT_ORDER (SPI0_SPI_BITS_ORDER)           | \
                     SPI0_GET_RX_CTRL_MEDIAN    (SPI0_SPI_MEDIAN_FILTER_ENABLE) | \
                     SPI0_SPI_RX_CTRL)

    #define SPI0_SPI_DEFAULT_RX_FIFO_CTRL \
                    SPI0_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(SPI0_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define SPI0_SPI_DEFAULT_TX_CTRL \
                    (SPI0_GET_TX_CTRL_DATA_WIDTH(SPI0_SPI_TX_DATA_BITS_NUM) | \
                     SPI0_GET_TX_CTRL_BIT_ORDER (SPI0_SPI_BITS_ORDER)       | \
                     SPI0_SPI_TX_CTRL)

    #define SPI0_SPI_DEFAULT_TX_FIFO_CTRL \
                    SPI0_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(SPI0_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define SPI0_SPI_DEFAULT_INTR_SPI_EC_MASK   (SPI0_NO_INTR_SOURCES)

    #define SPI0_SPI_DEFAULT_INTR_I2C_EC_MASK   (SPI0_NO_INTR_SOURCES)
    #define SPI0_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (SPI0_SPI_INTR_RX_MASK & SPI0_INTR_SLAVE_SPI_BUS_ERROR)

    #define SPI0_SPI_DEFAULT_INTR_MASTER_MASK \
                    (SPI0_SPI_INTR_TX_MASK & SPI0_INTR_MASTER_SPI_DONE)

    #define SPI0_SPI_DEFAULT_INTR_RX_MASK \
                    (SPI0_SPI_INTR_RX_MASK & (uint32) ~SPI0_INTR_SLAVE_SPI_BUS_ERROR)

    #define SPI0_SPI_DEFAULT_INTR_TX_MASK \
                    (SPI0_SPI_INTR_TX_MASK & (uint32) ~SPI0_INTR_MASTER_SPI_DONE)

#endif /* (SPI0_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define SPI0_CTRL_UART      (SPI0_CTRL_MODE_UART)
#define SPI0_UART_RX_CTRL   (SPI0_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define SPI0_UART_TX_CTRL   (SPI0_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(SPI0_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(SPI0_UART_MODE_IRDA == SPI0_UART_SUB_MODE)

        #define SPI0_DEFAULT_CTRL_OVS   ((0u != SPI0_UART_IRDA_LOW_POWER) ?              \
                                (SPI0_UART_GET_CTRL_OVS_IRDA_LP(SPI0_UART_OVS_FACTOR)) : \
                                (SPI0_CTRL_OVS_IRDA_OVS16))

    #else

        #define SPI0_DEFAULT_CTRL_OVS   SPI0_GET_CTRL_OVS(SPI0_UART_OVS_FACTOR)

    #endif /* (SPI0_UART_MODE_IRDA == SPI0_UART_SUB_MODE) */

    #define SPI0_UART_DEFAULT_CTRL \
                                (SPI0_GET_CTRL_ADDR_ACCEPT(SPI0_UART_MP_ACCEPT_ADDRESS) | \
                                 SPI0_DEFAULT_CTRL_OVS                                              | \
                                 SPI0_CTRL_UART)

    #define SPI0_UART_DEFAULT_UART_CTRL \
                                    (SPI0_GET_UART_CTRL_MODE(SPI0_UART_SUB_MODE))

    /* RX direction */
    #define SPI0_UART_DEFAULT_RX_CTRL_PARITY \
                                ((SPI0_UART_PARITY_NONE != SPI0_UART_PARITY_TYPE) ?      \
                                  (SPI0_GET_UART_RX_CTRL_PARITY(SPI0_UART_PARITY_TYPE) | \
                                   SPI0_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define SPI0_UART_DEFAULT_UART_RX_CTRL \
                    (SPI0_GET_UART_RX_CTRL_MODE(SPI0_UART_STOP_BITS_NUM)                    | \
                     SPI0_GET_UART_RX_CTRL_POLARITY(SPI0_UART_IRDA_POLARITY)                | \
                     SPI0_GET_UART_RX_CTRL_MP_MODE(SPI0_UART_MP_MODE_ENABLE)                | \
                     SPI0_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(SPI0_UART_DROP_ON_PARITY_ERR) | \
                     SPI0_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(SPI0_UART_DROP_ON_FRAME_ERR)   | \
                     SPI0_UART_DEFAULT_RX_CTRL_PARITY)

    #define SPI0_UART_DEFAULT_RX_CTRL \
                                (SPI0_GET_RX_CTRL_DATA_WIDTH(SPI0_UART_DATA_BITS_NUM)        | \
                                 SPI0_GET_RX_CTRL_MEDIAN    (SPI0_UART_MEDIAN_FILTER_ENABLE) | \
                                 SPI0_GET_UART_RX_CTRL_ENABLED(SPI0_UART_DIRECTION))

    #define SPI0_UART_DEFAULT_RX_FIFO_CTRL \
                                SPI0_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(SPI0_UART_RX_TRIGGER_LEVEL)

    #define SPI0_UART_DEFAULT_RX_MATCH_REG  ((0u != SPI0_UART_MP_MODE_ENABLE) ?          \
                                (SPI0_GET_RX_MATCH_ADDR(SPI0_UART_MP_RX_ADDRESS) | \
                                 SPI0_GET_RX_MATCH_MASK(SPI0_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define SPI0_UART_DEFAULT_TX_CTRL_PARITY (SPI0_UART_DEFAULT_RX_CTRL_PARITY)

    #define SPI0_UART_DEFAULT_UART_TX_CTRL \
                                (SPI0_GET_UART_TX_CTRL_MODE(SPI0_UART_STOP_BITS_NUM)       | \
                                 SPI0_GET_UART_TX_CTRL_RETRY_NACK(SPI0_UART_RETRY_ON_NACK) | \
                                 SPI0_UART_DEFAULT_TX_CTRL_PARITY)

    #define SPI0_UART_DEFAULT_TX_CTRL \
                                (SPI0_GET_TX_CTRL_DATA_WIDTH(SPI0_UART_DATA_BITS_NUM) | \
                                 SPI0_GET_UART_TX_CTRL_ENABLED(SPI0_UART_DIRECTION))

    #define SPI0_UART_DEFAULT_TX_FIFO_CTRL \
                                SPI0_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(SPI0_UART_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define SPI0_UART_DEFAULT_INTR_I2C_EC_MASK  (SPI0_NO_INTR_SOURCES)
    #define SPI0_UART_DEFAULT_INTR_SPI_EC_MASK  (SPI0_NO_INTR_SOURCES)
    #define SPI0_UART_DEFAULT_INTR_SLAVE_MASK   (SPI0_NO_INTR_SOURCES)
    #define SPI0_UART_DEFAULT_INTR_MASTER_MASK  (SPI0_NO_INTR_SOURCES)
    #define SPI0_UART_DEFAULT_INTR_RX_MASK      (SPI0_UART_INTR_RX_MASK)
    #define SPI0_UART_DEFAULT_INTR_TX_MASK      (SPI0_UART_INTR_TX_MASK)

#endif /* (SPI0_SCB_MODE_UART_CONST_CFG) */

#endif /* CY_SCB_SPI_UART_SPI0_H */


/* [] END OF FILE */
