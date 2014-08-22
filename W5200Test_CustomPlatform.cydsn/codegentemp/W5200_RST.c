/*******************************************************************************
* File Name: W5200_RST.c  
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
#include "W5200_RST.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 W5200_RST__PORT == 15 && ((W5200_RST__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: W5200_RST_Write
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
void W5200_RST_Write(uint8 value) 
{
    uint8 staticBits = (W5200_RST_DR & (uint8)(~W5200_RST_MASK));
    W5200_RST_DR = staticBits | ((uint8)(value << W5200_RST_SHIFT) & W5200_RST_MASK);
}


/*******************************************************************************
* Function Name: W5200_RST_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  W5200_RST_DM_STRONG     Strong Drive 
*  W5200_RST_DM_OD_HI      Open Drain, Drives High 
*  W5200_RST_DM_OD_LO      Open Drain, Drives Low 
*  W5200_RST_DM_RES_UP     Resistive Pull Up 
*  W5200_RST_DM_RES_DWN    Resistive Pull Down 
*  W5200_RST_DM_RES_UPDWN  Resistive Pull Up/Down 
*  W5200_RST_DM_DIG_HIZ    High Impedance Digital 
*  W5200_RST_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void W5200_RST_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(W5200_RST_0, mode);
}


/*******************************************************************************
* Function Name: W5200_RST_Read
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
*  Macro W5200_RST_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 W5200_RST_Read(void) 
{
    return (W5200_RST_PS & W5200_RST_MASK) >> W5200_RST_SHIFT;
}


/*******************************************************************************
* Function Name: W5200_RST_ReadDataReg
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
uint8 W5200_RST_ReadDataReg(void) 
{
    return (W5200_RST_DR & W5200_RST_MASK) >> W5200_RST_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(W5200_RST_INTSTAT) 

    /*******************************************************************************
    * Function Name: W5200_RST_ClearInterrupt
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
    uint8 W5200_RST_ClearInterrupt(void) 
    {
        return (W5200_RST_INTSTAT & W5200_RST_MASK) >> W5200_RST_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
