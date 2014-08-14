/*******************************************************************************
* File Name: GREEN.h  
* Version 2.0
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_GREEN_H) /* Pins GREEN_H */
#define CY_PINS_GREEN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "GREEN_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    GREEN_Write(uint8 value) ;
void    GREEN_SetDriveMode(uint8 mode) ;
uint8   GREEN_ReadDataReg(void) ;
uint8   GREEN_Read(void) ;
uint8   GREEN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define GREEN_DRIVE_MODE_BITS        (3)
#define GREEN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - GREEN_DRIVE_MODE_BITS))
#define GREEN_DRIVE_MODE_SHIFT       (0x00u)
#define GREEN_DRIVE_MODE_MASK        (0x07u << GREEN_DRIVE_MODE_SHIFT)

#define GREEN_DM_ALG_HIZ         (0x00u << GREEN_DRIVE_MODE_SHIFT)
#define GREEN_DM_DIG_HIZ         (0x01u << GREEN_DRIVE_MODE_SHIFT)
#define GREEN_DM_RES_UP          (0x02u << GREEN_DRIVE_MODE_SHIFT)
#define GREEN_DM_RES_DWN         (0x03u << GREEN_DRIVE_MODE_SHIFT)
#define GREEN_DM_OD_LO           (0x04u << GREEN_DRIVE_MODE_SHIFT)
#define GREEN_DM_OD_HI           (0x05u << GREEN_DRIVE_MODE_SHIFT)
#define GREEN_DM_STRONG          (0x06u << GREEN_DRIVE_MODE_SHIFT)
#define GREEN_DM_RES_UPDWN       (0x07u << GREEN_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define GREEN_MASK               GREEN__MASK
#define GREEN_SHIFT              GREEN__SHIFT
#define GREEN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define GREEN_PS                     (* (reg32 *) GREEN__PS)
/* Port Configuration */
#define GREEN_PC                     (* (reg32 *) GREEN__PC)
/* Data Register */
#define GREEN_DR                     (* (reg32 *) GREEN__DR)
/* Input Buffer Disable Override */
#define GREEN_INP_DIS                (* (reg32 *) GREEN__PC2)


#if defined(GREEN__INTSTAT)  /* Interrupt Registers */

    #define GREEN_INTSTAT                (* (reg32 *) GREEN__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins GREEN_H */


/* [] END OF FILE */
