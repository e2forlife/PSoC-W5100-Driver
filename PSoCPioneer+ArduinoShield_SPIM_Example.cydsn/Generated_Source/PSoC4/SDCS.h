/*******************************************************************************
* File Name: SDCS.h  
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

#if !defined(CY_PINS_SDCS_H) /* Pins SDCS_H */
#define CY_PINS_SDCS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SDCS_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SDCS_Write(uint8 value) ;
void    SDCS_SetDriveMode(uint8 mode) ;
uint8   SDCS_ReadDataReg(void) ;
uint8   SDCS_Read(void) ;
uint8   SDCS_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SDCS_DRIVE_MODE_BITS        (3)
#define SDCS_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SDCS_DRIVE_MODE_BITS))
#define SDCS_DRIVE_MODE_SHIFT       (0x00u)
#define SDCS_DRIVE_MODE_MASK        (0x07u << SDCS_DRIVE_MODE_SHIFT)

#define SDCS_DM_ALG_HIZ         (0x00u << SDCS_DRIVE_MODE_SHIFT)
#define SDCS_DM_DIG_HIZ         (0x01u << SDCS_DRIVE_MODE_SHIFT)
#define SDCS_DM_RES_UP          (0x02u << SDCS_DRIVE_MODE_SHIFT)
#define SDCS_DM_RES_DWN         (0x03u << SDCS_DRIVE_MODE_SHIFT)
#define SDCS_DM_OD_LO           (0x04u << SDCS_DRIVE_MODE_SHIFT)
#define SDCS_DM_OD_HI           (0x05u << SDCS_DRIVE_MODE_SHIFT)
#define SDCS_DM_STRONG          (0x06u << SDCS_DRIVE_MODE_SHIFT)
#define SDCS_DM_RES_UPDWN       (0x07u << SDCS_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define SDCS_MASK               SDCS__MASK
#define SDCS_SHIFT              SDCS__SHIFT
#define SDCS_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SDCS_PS                     (* (reg32 *) SDCS__PS)
/* Port Configuration */
#define SDCS_PC                     (* (reg32 *) SDCS__PC)
/* Data Register */
#define SDCS_DR                     (* (reg32 *) SDCS__DR)
/* Input Buffer Disable Override */
#define SDCS_INP_DIS                (* (reg32 *) SDCS__PC2)


#if defined(SDCS__INTSTAT)  /* Interrupt Registers */

    #define SDCS_INTSTAT                (* (reg32 *) SDCS__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins SDCS_H */


/* [] END OF FILE */
