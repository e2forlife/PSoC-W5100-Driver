/*******************************************************************************
* File Name: SDCS.c  
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
#include "SDCS.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        SDCS_PC =   (SDCS_PC & \
                                (uint32)(~(uint32)(SDCS_DRIVE_MODE_IND_MASK << (SDCS_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (SDCS_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: SDCS_Write
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
void SDCS_Write(uint8 value) 
{
    uint8 drVal = (uint8)(SDCS_DR & (uint8)(~SDCS_MASK));
    drVal = (drVal | ((uint8)(value << SDCS_SHIFT) & SDCS_MASK));
    SDCS_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: SDCS_SetDriveMode
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
void SDCS_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(SDCS__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: SDCS_Read
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
*  Macro SDCS_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SDCS_Read(void) 
{
    return (uint8)((SDCS_PS & SDCS_MASK) >> SDCS_SHIFT);
}


/*******************************************************************************
* Function Name: SDCS_ReadDataReg
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
uint8 SDCS_ReadDataReg(void) 
{
    return (uint8)((SDCS_DR & SDCS_MASK) >> SDCS_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SDCS_INTSTAT) 

    /*******************************************************************************
    * Function Name: SDCS_ClearInterrupt
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
    uint8 SDCS_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(SDCS_INTSTAT & SDCS_MASK);
		SDCS_INTSTAT = maskedStatus;
        return maskedStatus >> SDCS_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
