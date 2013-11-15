/*******************************************************************************
* File Name: ENET_CSN.h  
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

#if !defined(CY_PINS_ENET_CSN_H) /* Pins ENET_CSN_H */
#define CY_PINS_ENET_CSN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ENET_CSN_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ENET_CSN_Write(uint8 value) ;
void    ENET_CSN_SetDriveMode(uint8 mode) ;
uint8   ENET_CSN_ReadDataReg(void) ;
uint8   ENET_CSN_Read(void) ;
uint8   ENET_CSN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ENET_CSN_DRIVE_MODE_BITS        (3)
#define ENET_CSN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ENET_CSN_DRIVE_MODE_BITS))
#define ENET_CSN_DRIVE_MODE_SHIFT       (0x00u)
#define ENET_CSN_DRIVE_MODE_MASK        (0x07u << ENET_CSN_DRIVE_MODE_SHIFT)

#define ENET_CSN_DM_ALG_HIZ         (0x00u << ENET_CSN_DRIVE_MODE_SHIFT)
#define ENET_CSN_DM_DIG_HIZ         (0x01u << ENET_CSN_DRIVE_MODE_SHIFT)
#define ENET_CSN_DM_RES_UP          (0x02u << ENET_CSN_DRIVE_MODE_SHIFT)
#define ENET_CSN_DM_RES_DWN         (0x03u << ENET_CSN_DRIVE_MODE_SHIFT)
#define ENET_CSN_DM_OD_LO           (0x04u << ENET_CSN_DRIVE_MODE_SHIFT)
#define ENET_CSN_DM_OD_HI           (0x05u << ENET_CSN_DRIVE_MODE_SHIFT)
#define ENET_CSN_DM_STRONG          (0x06u << ENET_CSN_DRIVE_MODE_SHIFT)
#define ENET_CSN_DM_RES_UPDWN       (0x07u << ENET_CSN_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define ENET_CSN_MASK               ENET_CSN__MASK
#define ENET_CSN_SHIFT              ENET_CSN__SHIFT
#define ENET_CSN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ENET_CSN_PS                     (* (reg32 *) ENET_CSN__PS)
/* Port Configuration */
#define ENET_CSN_PC                     (* (reg32 *) ENET_CSN__PC)
/* Data Register */
#define ENET_CSN_DR                     (* (reg32 *) ENET_CSN__DR)
/* Input Buffer Disable Override */
#define ENET_CSN_INP_DIS                (* (reg32 *) ENET_CSN__PC2)


#if defined(ENET_CSN__INTSTAT)  /* Interrupt Registers */

    #define ENET_CSN_INTSTAT                (* (reg32 *) ENET_CSN__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins ENET_CSN_H */


/* [] END OF FILE */
