/*******************************************************************************
* File Name: SWTP.c  
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
#include "SWTP.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 SWTP__PORT == 15 && ((SWTP__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: SWTP_Write
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
void SWTP_Write(uint8 value) 
{
    uint8 staticBits = (SWTP_DR & (uint8)(~SWTP_MASK));
    SWTP_DR = staticBits | ((uint8)(value << SWTP_SHIFT) & SWTP_MASK);
}


/*******************************************************************************
* Function Name: SWTP_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  SWTP_DM_STRONG     Strong Drive 
*  SWTP_DM_OD_HI      Open Drain, Drives High 
*  SWTP_DM_OD_LO      Open Drain, Drives Low 
*  SWTP_DM_RES_UP     Resistive Pull Up 
*  SWTP_DM_RES_DWN    Resistive Pull Down 
*  SWTP_DM_RES_UPDWN  Resistive Pull Up/Down 
*  SWTP_DM_DIG_HIZ    High Impedance Digital 
*  SWTP_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void SWTP_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(SWTP_0, mode);
}


/*******************************************************************************
* Function Name: SWTP_Read
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
*  Macro SWTP_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SWTP_Read(void) 
{
    return (SWTP_PS & SWTP_MASK) >> SWTP_SHIFT;
}


/*******************************************************************************
* Function Name: SWTP_ReadDataReg
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
uint8 SWTP_ReadDataReg(void) 
{
    return (SWTP_DR & SWTP_MASK) >> SWTP_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SWTP_INTSTAT) 

    /*******************************************************************************
    * Function Name: SWTP_ClearInterrupt
    ********************************************************************************
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
    uint8 SWTP_ClearInterrupt(void) 
    {
        return (SWTP_INTSTAT & SWTP_MASK) >> SWTP_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
