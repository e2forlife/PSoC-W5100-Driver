/*******************************************************************************
* File Name: GREEN.c  
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
#include "GREEN.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        GREEN_PC =   (GREEN_PC & \
                                (uint32)(~(uint32)(GREEN_DRIVE_MODE_IND_MASK << (GREEN_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (GREEN_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: GREEN_Write
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
void GREEN_Write(uint8 value) 
{
    uint8 drVal = (uint8)(GREEN_DR & (uint8)(~GREEN_MASK));
    drVal = (drVal | ((uint8)(value << GREEN_SHIFT) & GREEN_MASK));
    GREEN_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: GREEN_SetDriveMode
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
void GREEN_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(GREEN__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: GREEN_Read
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
*  Macro GREEN_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 GREEN_Read(void) 
{
    return (uint8)((GREEN_PS & GREEN_MASK) >> GREEN_SHIFT);
}


/*******************************************************************************
* Function Name: GREEN_ReadDataReg
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
uint8 GREEN_ReadDataReg(void) 
{
    return (uint8)((GREEN_DR & GREEN_MASK) >> GREEN_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(GREEN_INTSTAT) 

    /*******************************************************************************
    * Function Name: GREEN_ClearInterrupt
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
    uint8 GREEN_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(GREEN_INTSTAT & GREEN_MASK);
		GREEN_INTSTAT = maskedStatus;
        return maskedStatus >> GREEN_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
