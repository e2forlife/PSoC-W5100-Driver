/*******************************************************************************
* File Name: RED.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_RED_H) /* Pins RED_H */
#define CY_PINS_RED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RED_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    RED_Write(uint8 value) ;
void    RED_SetDriveMode(uint8 mode) ;
uint8   RED_ReadDataReg(void) ;
uint8   RED_Read(void) ;
uint8   RED_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RED_DRIVE_MODE_BITS        (3)
#define RED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RED_DRIVE_MODE_BITS))
#define RED_DRIVE_MODE_SHIFT       (0x00u)
#define RED_DRIVE_MODE_MASK        (0x07u << RED_DRIVE_MODE_SHIFT)

#define RED_DM_ALG_HIZ         (0x00u << RED_DRIVE_MODE_SHIFT)
#define RED_DM_DIG_HIZ         (0x01u << RED_DRIVE_MODE_SHIFT)
#define RED_DM_RES_UP          (0x02u << RED_DRIVE_MODE_SHIFT)
#define RED_DM_RES_DWN         (0x03u << RED_DRIVE_MODE_SHIFT)
#define RED_DM_OD_LO           (0x04u << RED_DRIVE_MODE_SHIFT)
#define RED_DM_OD_HI           (0x05u << RED_DRIVE_MODE_SHIFT)
#define RED_DM_STRONG          (0x06u << RED_DRIVE_MODE_SHIFT)
#define RED_DM_RES_UPDWN       (0x07u << RED_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define RED_MASK               RED__MASK
#define RED_SHIFT              RED__SHIFT
#define RED_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RED_PS                     (* (reg32 *) RED__PS)
/* Port Configuration */
#define RED_PC                     (* (reg32 *) RED__PC)
/* Data Register */
#define RED_DR                     (* (reg32 *) RED__DR)
/* Input Buffer Disable Override */
#define RED_INP_DIS                (* (reg32 *) RED__PC2)


#if defined(RED__INTSTAT)  /* Interrupt Registers */

    #define RED_INTSTAT                (* (reg32 *) RED__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins RED_H */


/* [] END OF FILE */
