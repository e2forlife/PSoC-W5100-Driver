/*******************************************************************************
* File Name: BLUE.c  
* Version 2.0
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "BLUE.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        BLUE_PC =   (BLUE_PC & \
                                (uint32)(~(uint32)(BLUE_DRIVE_MODE_IND_MASK << (BLUE_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (BLUE_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: BLUE_Write
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
void BLUE_Write(uint8 value) 
{
    uint8 drVal = (uint8)(BLUE_DR & (uint8)(~BLUE_MASK));
    drVal = (drVal | ((uint8)(value << BLUE_SHIFT) & BLUE_MASK));
    BLUE_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: BLUE_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  BLUE_DM_STRONG     Strong Drive 
*  BLUE_DM_OD_HI      Open Drain, Drives High 
*  BLUE_DM_OD_LO      Open Drain, Drives Low 
*  BLUE_DM_RES_UP     Resistive Pull Up 
*  BLUE_DM_RES_DWN    Resistive Pull Down 
*  BLUE_DM_RES_UPDWN  Resistive Pull Up/Down 
*  BLUE_DM_DIG_HIZ    High Impedance Digital 
*  BLUE_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void BLUE_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(BLUE__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: BLUE_Read
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
*  Macro BLUE_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 BLUE_Read(void) 
{
    return (uint8)((BLUE_PS & BLUE_MASK) >> BLUE_SHIFT);
}


/*******************************************************************************
* Function Name: BLUE_ReadDataReg
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
uint8 BLUE_ReadDataReg(void) 
{
    return (uint8)((BLUE_DR & BLUE_MASK) >> BLUE_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(BLUE_INTSTAT) 

    /*******************************************************************************
    * Function Name: BLUE_ClearInterrupt
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
    uint8 BLUE_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(BLUE_INTSTAT & BLUE_MASK);
		BLUE_INTSTAT = maskedStatus;
        return maskedStatus >> BLUE_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
