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
#include "cypins.h"
#include "SDCS_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SDCS__PORT == 15 && ((SDCS__MASK & 0xC0) != 0))


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
#define SDCS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define SDCS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define SDCS_DM_RES_UP          PIN_DM_RES_UP
#define SDCS_DM_RES_DWN         PIN_DM_RES_DWN
#define SDCS_DM_OD_LO           PIN_DM_OD_LO
#define SDCS_DM_OD_HI           PIN_DM_OD_HI
#define SDCS_DM_STRONG          PIN_DM_STRONG
#define SDCS_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define SDCS_MASK               SDCS__MASK
#define SDCS_SHIFT              SDCS__SHIFT
#define SDCS_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SDCS_PS                     (* (reg8 *) SDCS__PS)
/* Data Register */
#define SDCS_DR                     (* (reg8 *) SDCS__DR)
/* Port Number */
#define SDCS_PRT_NUM                (* (reg8 *) SDCS__PRT) 
/* Connect to Analog Globals */                                                  
#define SDCS_AG                     (* (reg8 *) SDCS__AG)                       
/* Analog MUX bux enable */
#define SDCS_AMUX                   (* (reg8 *) SDCS__AMUX) 
/* Bidirectional Enable */                                                        
#define SDCS_BIE                    (* (reg8 *) SDCS__BIE)
/* Bit-mask for Aliased Register Access */
#define SDCS_BIT_MASK               (* (reg8 *) SDCS__BIT_MASK)
/* Bypass Enable */
#define SDCS_BYP                    (* (reg8 *) SDCS__BYP)
/* Port wide control signals */                                                   
#define SDCS_CTL                    (* (reg8 *) SDCS__CTL)
/* Drive Modes */
#define SDCS_DM0                    (* (reg8 *) SDCS__DM0) 
#define SDCS_DM1                    (* (reg8 *) SDCS__DM1)
#define SDCS_DM2                    (* (reg8 *) SDCS__DM2) 
/* Input Buffer Disable Override */
#define SDCS_INP_DIS                (* (reg8 *) SDCS__INP_DIS)
/* LCD Common or Segment Drive */
#define SDCS_LCD_COM_SEG            (* (reg8 *) SDCS__LCD_COM_SEG)
/* Enable Segment LCD */
#define SDCS_LCD_EN                 (* (reg8 *) SDCS__LCD_EN)
/* Slew Rate Control */
#define SDCS_SLW                    (* (reg8 *) SDCS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SDCS_PRTDSI__CAPS_SEL       (* (reg8 *) SDCS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SDCS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SDCS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SDCS_PRTDSI__OE_SEL0        (* (reg8 *) SDCS__PRTDSI__OE_SEL0) 
#define SDCS_PRTDSI__OE_SEL1        (* (reg8 *) SDCS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SDCS_PRTDSI__OUT_SEL0       (* (reg8 *) SDCS__PRTDSI__OUT_SEL0) 
#define SDCS_PRTDSI__OUT_SEL1       (* (reg8 *) SDCS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SDCS_PRTDSI__SYNC_OUT       (* (reg8 *) SDCS__PRTDSI__SYNC_OUT) 


#if defined(SDCS__INTSTAT)  /* Interrupt Registers */

    #define SDCS_INTSTAT                (* (reg8 *) SDCS__INTSTAT)
    #define SDCS_SNAP                   (* (reg8 *) SDCS__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SDCS_H */


/* [] END OF FILE */
