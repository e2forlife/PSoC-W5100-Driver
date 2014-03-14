/*******************************************************************************
* File Name: SPI0_BOOT.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the bootloader
*  communication support in SCB Component.
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

#if(SPI0_SCB_MODE_I2C_INC)
    #include "SPI0_I2C.h"
#endif /* (SPI0_SCB_MODE_I2C_INC) */

#if(SPI0_SCB_MODE_EZI2C_INC)
    #include "SPI0_EZI2C.h"
#endif /* (SPI0_SCB_MODE_EZI2C_INC) */

#if(SPI0_SCB_MODE_SPI_INC || SPI0_SCB_MODE_UART_INC)
    #include "SPI0_SPI_UART.h"
#endif /* (SPI0_SCB_MODE_SPI_INC || SPI0_SCB_MODE_UART_INC) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPI0) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/*******************************************************************************
* Function Name: SPI0_CyBtldrCommStart
********************************************************************************
*
* Summary:
*  Calls Start function fucntion of the bootloader communication component for
*  selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPI0_CyBtldrCommStart(void)
{
    #if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
        if(SPI0_SCB_MODE_I2C_RUNTM_CFG)
        {
            SPI0_I2CCyBtldrCommStart();
        }
        else if(SPI0_SCB_MODE_SPI_RUNTM_CFG)
        {
            SPI0_SpiCyBtldrCommStart();
        }
        else if(SPI0_SCB_MODE_UART_RUNTM_CFG)
        {
            SPI0_UartCyBtldrCommStart();
        }
        else if(SPI0_SCB_MODE_EZI2C_RUNTM_CFG)
        {
             SPI0_EzI2CCyBtldrCommStart();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(SPI0_SCB_MODE_I2C_CONST_CFG)
        SPI0_I2CCyBtldrCommStart();

    #elif(SPI0_SCB_MODE_SPI_CONST_CFG)
        SPI0_SpiCyBtldrCommStart();

    #elif(SPI0_SCB_MODE_UART_CONST_CFG)
        SPI0_UartCyBtldrCommStart();

    #elif(SPI0_SCB_MODE_EZI2C_CONST_CFG)
        SPI0_EzI2CCyBtldrCommStart();

    #else
        /* Do nothing */

    #endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPI0_CyBtldrCommStop
********************************************************************************
*
* Summary:
*  Calls Stop function fucntion of the bootloader communication component for
*  selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPI0_CyBtldrCommStop(void)
{
    #if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
        if(SPI0_SCB_MODE_I2C_RUNTM_CFG)
        {
            SPI0_I2CCyBtldrCommStop();
        }
        else if(SPI0_SCB_MODE_SPI_RUNTM_CFG)
        {
            SPI0_SpiCyBtldrCommStop();
        }
        else if(SPI0_SCB_MODE_UART_RUNTM_CFG)
        {
            SPI0_UartCyBtldrCommStop();
        }
        else if(SPI0_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SPI0_EzI2CCyBtldrCommStop();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(SPI0_SCB_MODE_I2C_CONST_CFG)
        SPI0_I2CCyBtldrCommStop();

    #elif(SPI0_SCB_MODE_SPI_CONST_CFG)
        SPI0_SpiCyBtldrCommStop();

    #elif(SPI0_SCB_MODE_UART_CONST_CFG)
        SPI0_UartCyBtldrCommStop();

    #elif(SPI0_SCB_MODE_EZI2C_CONST_CFG)
        SPI0_EzI2CCyBtldrCommStop();

    #else
        /* Do nothing */

    #endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPI0_CyBtldrCommReset
********************************************************************************
*
* Summary:
*  Calls reset function fucntion of the bootloader communication component for
*  selected mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SPI0_CyBtldrCommReset(void)
{
    #if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
        if(SPI0_SCB_MODE_I2C_RUNTM_CFG)
        {
            SPI0_I2CCyBtldrCommReset();
        }
        else if(SPI0_SCB_MODE_SPI_RUNTM_CFG)
        {
            SPI0_SpiCyBtldrCommReset();
        }
        else if(SPI0_SCB_MODE_UART_RUNTM_CFG)
        {
            SPI0_UartCyBtldrCommReset();
        }
        else if(SPI0_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SPI0_EzI2CCyBtldrCommReset();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #elif(SPI0_SCB_MODE_I2C_CONST_CFG)
        SPI0_I2CCyBtldrCommReset();

    #elif(SPI0_SCB_MODE_SPI_CONST_CFG)
        SPI0_SpiCyBtldrCommReset();

    #elif(SPI0_SCB_MODE_UART_CONST_CFG)
        SPI0_UartCyBtldrCommReset();

    #elif(SPI0_SCB_MODE_EZI2C_CONST_CFG)
        SPI0_EzI2CCyBtldrCommReset();

    #else
        /* Do nothing */

    #endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SPI0_CyBtldrCommRead
********************************************************************************
*
* Summary:
*  Calls read fucntion of the bootloader communication component for selected
*  mode.
*
* Parameters:
*  pData:    Pointer to storage for the block of data to be read from the
*            bootloader host
*  size:     Number of bytes to be read.
*  count:    Pointer to the variable to write the number of bytes actually
*            read.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus SPI0_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
        if(SPI0_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = SPI0_I2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(SPI0_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = SPI0_SpiCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(SPI0_SCB_MODE_UART_RUNTM_CFG)
        {
            status = SPI0_UartCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(SPI0_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = SPI0_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }

    #elif(SPI0_SCB_MODE_I2C_CONST_CFG)
        status = SPI0_I2CCyBtldrCommRead(pData, size, count, timeOut);

    #elif(SPI0_SCB_MODE_SPI_CONST_CFG)
        status = SPI0_SpiCyBtldrCommRead(pData, size, count, timeOut);

    #elif(SPI0_SCB_MODE_UART_CONST_CFG)
        status = SPI0_UartCyBtldrCommRead(pData, size, count, timeOut);

    #elif(SPI0_SCB_MODE_EZI2C_CONST_CFG)
        status = SPI0_EzI2CCyBtldrCommRead(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}


/*******************************************************************************
* Function Name: SPI0_CyBtldrCommWrite
********************************************************************************
*
* Summary:
*  Calls write fucntion of the bootloader communication component for selected
*  mode.
*
* Parameters:
*  pData:    Pointer to the block of data to be written to the bootloader host.
*  size:     Number of bytes to be written.
*  count:    Pointer to the variable to write the number of bytes actually
*            written.
*  timeOut:  Number of units in 10 ms to wait before returning because of a
*            timeout.
*
* Return:
*  Returns CYRET_SUCCESS if no problem was encountered or returns the value
*  that best describes the problem.
*
*******************************************************************************/
cystatus SPI0_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(SPI0_SCB_MODE_UNCONFIG_CONST_CFG)
        if(SPI0_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = SPI0_I2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(SPI0_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = SPI0_SpiCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(SPI0_SCB_MODE_UART_RUNTM_CFG)
        {
            status = SPI0_UartCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(SPI0_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = SPI0_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }
    #elif(SPI0_SCB_MODE_I2C_CONST_CFG)
        status = SPI0_I2CCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(SPI0_SCB_MODE_SPI_CONST_CFG)
        status = SPI0_SpiCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(SPI0_SCB_MODE_UART_CONST_CFG)
        status = SPI0_UartCyBtldrCommWrite(pData, size, count, timeOut);

    #elif(SPI0_SCB_MODE_EZI2C_CONST_CFG)
        status = SPI0_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);

    #else
        status = CYRET_INVALID_STATE; /* Unknown mode: return status */

    #endif /* (SPI0_SCB_MODE_UNCONFIG_CONST_CFG) */

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPI0) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */


/* [] END OF FILE */
