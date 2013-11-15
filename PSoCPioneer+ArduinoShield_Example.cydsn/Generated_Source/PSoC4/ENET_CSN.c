/*******************************************************************************
* File Name: ENET_CSN.c  
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
#include "ENET_CSN.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        ENET_CSN_PC =   (ENET_CSN_PC & \
                                (uint32)(~(uint32)(ENET_CSN_DRIVE_MODE_IND_MASK << (ENET_CSN_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (ENET_CSN_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: ENET_CSN_Write
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
void ENET_CSN_Write(uint8 value) 
{
    uint8 drVal = (uint8)(ENET_CSN_DR & (uint8)(~ENET_CSN_MASK));
    drVal = (drVal | ((uint8)(value << ENET_CSN_SHIFT) & ENET_CSN_MASK));
    ENET_CSN_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: ENET_CSN_SetDriveMode
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
void ENET_CSN_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(ENET_CSN__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: ENET_CSN_Read
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
*  Macro ENET_CSN_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ENET_CSN_Read(void) 
{
    return (uint8)((ENET_CSN_PS & ENET_CSN_MASK) >> ENET_CSN_SHIFT);
}


/*******************************************************************************
* Function Name: ENET_CSN_ReadDataReg
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
uint8 ENET_CSN_ReadDataReg(void) 
{
    return (uint8)((ENET_CSN_DR & ENET_CSN_MASK) >> ENET_CSN_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ENET_CSN_INTSTAT) 

    /*******************************************************************************
    * Function Name: ENET_CSN_ClearInterrupt
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
    uint8 ENET_CSN_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(ENET_CSN_INTSTAT & ENET_CSN_MASK);
		ENET_CSN_INTSTAT = maskedStatus;
        return maskedStatus >> ENET_CSN_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
