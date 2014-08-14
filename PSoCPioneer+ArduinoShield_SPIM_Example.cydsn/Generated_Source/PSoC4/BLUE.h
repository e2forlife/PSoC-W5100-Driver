/*******************************************************************************
* File Name: BLUE.h  
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

#if !defined(CY_PINS_BLUE_H) /* Pins BLUE_H */
#define CY_PINS_BLUE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BLUE_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    BLUE_Write(uint8 value) ;
void    BLUE_SetDriveMode(uint8 mode) ;
uint8   BLUE_ReadDataReg(void) ;
uint8   BLUE_Read(void) ;
uint8   BLUE_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define BLUE_DRIVE_MODE_BITS        (3)
#define BLUE_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BLUE_DRIVE_MODE_BITS))
#define BLUE_DRIVE_MODE_SHIFT       (0x00u)
#define BLUE_DRIVE_MODE_MASK        (0x07u << BLUE_DRIVE_MODE_SHIFT)

#define BLUE_DM_ALG_HIZ         (0x00u << BLUE_DRIVE_MODE_SHIFT)
#define BLUE_DM_DIG_HIZ         (0x01u << BLUE_DRIVE_MODE_SHIFT)
#define BLUE_DM_RES_UP          (0x02u << BLUE_DRIVE_MODE_SHIFT)
#define BLUE_DM_RES_DWN         (0x03u << BLUE_DRIVE_MODE_SHIFT)
#define BLUE_DM_OD_LO           (0x04u << BLUE_DRIVE_MODE_SHIFT)
#define BLUE_DM_OD_HI           (0x05u << BLUE_DRIVE_MODE_SHIFT)
#define BLUE_DM_STRONG          (0x06u << BLUE_DRIVE_MODE_SHIFT)
#define BLUE_DM_RES_UPDWN       (0x07u << BLUE_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define BLUE_MASK               BLUE__MASK
#define BLUE_SHIFT              BLUE__SHIFT
#define BLUE_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BLUE_PS                     (* (reg32 *) BLUE__PS)
/* Port Configuration */
#define BLUE_PC                     (* (reg32 *) BLUE__PC)
/* Data Register */
#define BLUE_DR                     (* (reg32 *) BLUE__DR)
/* Input Buffer Disable Override */
#define BLUE_INP_DIS                (* (reg32 *) BLUE__PC2)


#if defined(BLUE__INTSTAT)  /* Interrupt Registers */

    #define BLUE_INTSTAT                (* (reg32 *) BLUE__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins BLUE_H */


/* [] END OF FILE */
