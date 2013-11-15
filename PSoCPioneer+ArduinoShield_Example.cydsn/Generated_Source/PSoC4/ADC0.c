/*******************************************************************************
* File Name: ADC0.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "ADC0.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        ADC0_PC =   (ADC0_PC & \
                                (uint32)(~(uint32)(ADC0_DRIVE_MODE_IND_MASK << (ADC0_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (ADC0_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: ADC0_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void ADC0_Write(uint8 value) 
{
    uint8 drVal = (uint8)(ADC0_DR & (uint8)(~ADC0_MASK));
    drVal = (drVal | ((uint8)(value << ADC0_SHIFT) & ADC0_MASK));
    ADC0_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: ADC0_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void ADC0_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(ADC0__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: ADC0_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro ADC0_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ADC0_Read(void) 
{
    return (uint8)((ADC0_PS & ADC0_MASK) >> ADC0_SHIFT);
}


/*******************************************************************************
* Function Name: ADC0_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 ADC0_ReadDataReg(void) 
{
    return (uint8)((ADC0_DR & ADC0_MASK) >> ADC0_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ADC0_INTSTAT) 

    /*******************************************************************************
    * Function Name: ADC0_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 ADC0_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(ADC0_INTSTAT & ADC0_MASK);
		ADC0_INTSTAT = maskedStatus;
        return maskedStatus >> ADC0_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
