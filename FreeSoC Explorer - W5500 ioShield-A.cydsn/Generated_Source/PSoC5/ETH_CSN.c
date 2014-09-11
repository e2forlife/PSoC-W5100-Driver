/*******************************************************************************
* File Name: ETH_CSN.c  
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
#include "ETH_CSN.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 ETH_CSN__PORT == 15 && ((ETH_CSN__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: ETH_CSN_Write
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
void ETH_CSN_Write(uint8 value) 
{
    uint8 staticBits = (ETH_CSN_DR & (uint8)(~ETH_CSN_MASK));
    ETH_CSN_DR = staticBits | ((uint8)(value << ETH_CSN_SHIFT) & ETH_CSN_MASK);
}


/*******************************************************************************
* Function Name: ETH_CSN_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  ETH_CSN_DM_STRONG     Strong Drive 
*  ETH_CSN_DM_OD_HI      Open Drain, Drives High 
*  ETH_CSN_DM_OD_LO      Open Drain, Drives Low 
*  ETH_CSN_DM_RES_UP     Resistive Pull Up 
*  ETH_CSN_DM_RES_DWN    Resistive Pull Down 
*  ETH_CSN_DM_RES_UPDWN  Resistive Pull Up/Down 
*  ETH_CSN_DM_DIG_HIZ    High Impedance Digital 
*  ETH_CSN_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void ETH_CSN_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(ETH_CSN_0, mode);
}


/*******************************************************************************
* Function Name: ETH_CSN_Read
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
*  Macro ETH_CSN_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ETH_CSN_Read(void) 
{
    return (ETH_CSN_PS & ETH_CSN_MASK) >> ETH_CSN_SHIFT;
}


/*******************************************************************************
* Function Name: ETH_CSN_ReadDataReg
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
uint8 ETH_CSN_ReadDataReg(void) 
{
    return (ETH_CSN_DR & ETH_CSN_MASK) >> ETH_CSN_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ETH_CSN_INTSTAT) 

    /*******************************************************************************
    * Function Name: ETH_CSN_ClearInterrupt
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
    uint8 ETH_CSN_ClearInterrupt(void) 
    {
        return (ETH_CSN_INTSTAT & ETH_CSN_MASK) >> ETH_CSN_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
