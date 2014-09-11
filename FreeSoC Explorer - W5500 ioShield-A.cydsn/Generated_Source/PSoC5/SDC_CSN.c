/*******************************************************************************
* File Name: SDC_CSN.c  
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
#include "SDC_CSN.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 SDC_CSN__PORT == 15 && ((SDC_CSN__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: SDC_CSN_Write
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
void SDC_CSN_Write(uint8 value) 
{
    uint8 staticBits = (SDC_CSN_DR & (uint8)(~SDC_CSN_MASK));
    SDC_CSN_DR = staticBits | ((uint8)(value << SDC_CSN_SHIFT) & SDC_CSN_MASK);
}


/*******************************************************************************
* Function Name: SDC_CSN_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  SDC_CSN_DM_STRONG     Strong Drive 
*  SDC_CSN_DM_OD_HI      Open Drain, Drives High 
*  SDC_CSN_DM_OD_LO      Open Drain, Drives Low 
*  SDC_CSN_DM_RES_UP     Resistive Pull Up 
*  SDC_CSN_DM_RES_DWN    Resistive Pull Down 
*  SDC_CSN_DM_RES_UPDWN  Resistive Pull Up/Down 
*  SDC_CSN_DM_DIG_HIZ    High Impedance Digital 
*  SDC_CSN_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void SDC_CSN_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(SDC_CSN_0, mode);
}


/*******************************************************************************
* Function Name: SDC_CSN_Read
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
*  Macro SDC_CSN_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SDC_CSN_Read(void) 
{
    return (SDC_CSN_PS & SDC_CSN_MASK) >> SDC_CSN_SHIFT;
}


/*******************************************************************************
* Function Name: SDC_CSN_ReadDataReg
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
uint8 SDC_CSN_ReadDataReg(void) 
{
    return (SDC_CSN_DR & SDC_CSN_MASK) >> SDC_CSN_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SDC_CSN_INTSTAT) 

    /*******************************************************************************
    * Function Name: SDC_CSN_ClearInterrupt
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
    uint8 SDC_CSN_ClearInterrupt(void) 
    {
        return (SDC_CSN_INTSTAT & SDC_CSN_MASK) >> SDC_CSN_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
