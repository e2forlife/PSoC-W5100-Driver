/*******************************************************************************
* File Name: MOSI_1.h  
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

#if !defined(CY_PINS_MOSI_1_H) /* Pins MOSI_1_H */
#define CY_PINS_MOSI_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MOSI_1_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 MOSI_1__PORT == 15 && ((MOSI_1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    MOSI_1_Write(uint8 value) ;
void    MOSI_1_SetDriveMode(uint8 mode) ;
uint8   MOSI_1_ReadDataReg(void) ;
uint8   MOSI_1_Read(void) ;
uint8   MOSI_1_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define MOSI_1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define MOSI_1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define MOSI_1_DM_RES_UP          PIN_DM_RES_UP
#define MOSI_1_DM_RES_DWN         PIN_DM_RES_DWN
#define MOSI_1_DM_OD_LO           PIN_DM_OD_LO
#define MOSI_1_DM_OD_HI           PIN_DM_OD_HI
#define MOSI_1_DM_STRONG          PIN_DM_STRONG
#define MOSI_1_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define MOSI_1_MASK               MOSI_1__MASK
#define MOSI_1_SHIFT              MOSI_1__SHIFT
#define MOSI_1_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MOSI_1_PS                     (* (reg8 *) MOSI_1__PS)
/* Data Register */
#define MOSI_1_DR                     (* (reg8 *) MOSI_1__DR)
/* Port Number */
#define MOSI_1_PRT_NUM                (* (reg8 *) MOSI_1__PRT) 
/* Connect to Analog Globals */                                                  
#define MOSI_1_AG                     (* (reg8 *) MOSI_1__AG)                       
/* Analog MUX bux enable */
#define MOSI_1_AMUX                   (* (reg8 *) MOSI_1__AMUX) 
/* Bidirectional Enable */                                                        
#define MOSI_1_BIE                    (* (reg8 *) MOSI_1__BIE)
/* Bit-mask for Aliased Register Access */
#define MOSI_1_BIT_MASK               (* (reg8 *) MOSI_1__BIT_MASK)
/* Bypass Enable */
#define MOSI_1_BYP                    (* (reg8 *) MOSI_1__BYP)
/* Port wide control signals */                                                   
#define MOSI_1_CTL                    (* (reg8 *) MOSI_1__CTL)
/* Drive Modes */
#define MOSI_1_DM0                    (* (reg8 *) MOSI_1__DM0) 
#define MOSI_1_DM1                    (* (reg8 *) MOSI_1__DM1)
#define MOSI_1_DM2                    (* (reg8 *) MOSI_1__DM2) 
/* Input Buffer Disable Override */
#define MOSI_1_INP_DIS                (* (reg8 *) MOSI_1__INP_DIS)
/* LCD Common or Segment Drive */
#define MOSI_1_LCD_COM_SEG            (* (reg8 *) MOSI_1__LCD_COM_SEG)
/* Enable Segment LCD */
#define MOSI_1_LCD_EN                 (* (reg8 *) MOSI_1__LCD_EN)
/* Slew Rate Control */
#define MOSI_1_SLW                    (* (reg8 *) MOSI_1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MOSI_1_PRTDSI__CAPS_SEL       (* (reg8 *) MOSI_1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MOSI_1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MOSI_1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MOSI_1_PRTDSI__OE_SEL0        (* (reg8 *) MOSI_1__PRTDSI__OE_SEL0) 
#define MOSI_1_PRTDSI__OE_SEL1        (* (reg8 *) MOSI_1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MOSI_1_PRTDSI__OUT_SEL0       (* (reg8 *) MOSI_1__PRTDSI__OUT_SEL0) 
#define MOSI_1_PRTDSI__OUT_SEL1       (* (reg8 *) MOSI_1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MOSI_1_PRTDSI__SYNC_OUT       (* (reg8 *) MOSI_1__PRTDSI__SYNC_OUT) 


#if defined(MOSI_1__INTSTAT)  /* Interrupt Registers */

    #define MOSI_1_INTSTAT                (* (reg8 *) MOSI_1__INTSTAT)
    #define MOSI_1_SNAP                   (* (reg8 *) MOSI_1__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_MOSI_1_H */


/* [] END OF FILE */
