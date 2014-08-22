/*******************************************************************************
* File Name: W5200_RST.h  
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

#if !defined(CY_PINS_W5200_RST_H) /* Pins W5200_RST_H */
#define CY_PINS_W5200_RST_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "W5200_RST_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 W5200_RST__PORT == 15 && ((W5200_RST__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    W5200_RST_Write(uint8 value) ;
void    W5200_RST_SetDriveMode(uint8 mode) ;
uint8   W5200_RST_ReadDataReg(void) ;
uint8   W5200_RST_Read(void) ;
uint8   W5200_RST_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define W5200_RST_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define W5200_RST_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define W5200_RST_DM_RES_UP          PIN_DM_RES_UP
#define W5200_RST_DM_RES_DWN         PIN_DM_RES_DWN
#define W5200_RST_DM_OD_LO           PIN_DM_OD_LO
#define W5200_RST_DM_OD_HI           PIN_DM_OD_HI
#define W5200_RST_DM_STRONG          PIN_DM_STRONG
#define W5200_RST_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define W5200_RST_MASK               W5200_RST__MASK
#define W5200_RST_SHIFT              W5200_RST__SHIFT
#define W5200_RST_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define W5200_RST_PS                     (* (reg8 *) W5200_RST__PS)
/* Data Register */
#define W5200_RST_DR                     (* (reg8 *) W5200_RST__DR)
/* Port Number */
#define W5200_RST_PRT_NUM                (* (reg8 *) W5200_RST__PRT) 
/* Connect to Analog Globals */                                                  
#define W5200_RST_AG                     (* (reg8 *) W5200_RST__AG)                       
/* Analog MUX bux enable */
#define W5200_RST_AMUX                   (* (reg8 *) W5200_RST__AMUX) 
/* Bidirectional Enable */                                                        
#define W5200_RST_BIE                    (* (reg8 *) W5200_RST__BIE)
/* Bit-mask for Aliased Register Access */
#define W5200_RST_BIT_MASK               (* (reg8 *) W5200_RST__BIT_MASK)
/* Bypass Enable */
#define W5200_RST_BYP                    (* (reg8 *) W5200_RST__BYP)
/* Port wide control signals */                                                   
#define W5200_RST_CTL                    (* (reg8 *) W5200_RST__CTL)
/* Drive Modes */
#define W5200_RST_DM0                    (* (reg8 *) W5200_RST__DM0) 
#define W5200_RST_DM1                    (* (reg8 *) W5200_RST__DM1)
#define W5200_RST_DM2                    (* (reg8 *) W5200_RST__DM2) 
/* Input Buffer Disable Override */
#define W5200_RST_INP_DIS                (* (reg8 *) W5200_RST__INP_DIS)
/* LCD Common or Segment Drive */
#define W5200_RST_LCD_COM_SEG            (* (reg8 *) W5200_RST__LCD_COM_SEG)
/* Enable Segment LCD */
#define W5200_RST_LCD_EN                 (* (reg8 *) W5200_RST__LCD_EN)
/* Slew Rate Control */
#define W5200_RST_SLW                    (* (reg8 *) W5200_RST__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define W5200_RST_PRTDSI__CAPS_SEL       (* (reg8 *) W5200_RST__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define W5200_RST_PRTDSI__DBL_SYNC_IN    (* (reg8 *) W5200_RST__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define W5200_RST_PRTDSI__OE_SEL0        (* (reg8 *) W5200_RST__PRTDSI__OE_SEL0) 
#define W5200_RST_PRTDSI__OE_SEL1        (* (reg8 *) W5200_RST__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define W5200_RST_PRTDSI__OUT_SEL0       (* (reg8 *) W5200_RST__PRTDSI__OUT_SEL0) 
#define W5200_RST_PRTDSI__OUT_SEL1       (* (reg8 *) W5200_RST__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define W5200_RST_PRTDSI__SYNC_OUT       (* (reg8 *) W5200_RST__PRTDSI__SYNC_OUT) 


#if defined(W5200_RST__INTSTAT)  /* Interrupt Registers */

    #define W5200_RST_INTSTAT                (* (reg8 *) W5200_RST__INTSTAT)
    #define W5200_RST_SNAP                   (* (reg8 *) W5200_RST__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_W5200_RST_H */


/* [] END OF FILE */
