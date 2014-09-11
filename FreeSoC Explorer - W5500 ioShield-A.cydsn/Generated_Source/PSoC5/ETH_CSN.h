/*******************************************************************************
* File Name: ETH_CSN.h  
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

#if !defined(CY_PINS_ETH_CSN_H) /* Pins ETH_CSN_H */
#define CY_PINS_ETH_CSN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ETH_CSN_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ETH_CSN__PORT == 15 && ((ETH_CSN__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    ETH_CSN_Write(uint8 value) ;
void    ETH_CSN_SetDriveMode(uint8 mode) ;
uint8   ETH_CSN_ReadDataReg(void) ;
uint8   ETH_CSN_Read(void) ;
uint8   ETH_CSN_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ETH_CSN_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define ETH_CSN_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define ETH_CSN_DM_RES_UP          PIN_DM_RES_UP
#define ETH_CSN_DM_RES_DWN         PIN_DM_RES_DWN
#define ETH_CSN_DM_OD_LO           PIN_DM_OD_LO
#define ETH_CSN_DM_OD_HI           PIN_DM_OD_HI
#define ETH_CSN_DM_STRONG          PIN_DM_STRONG
#define ETH_CSN_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define ETH_CSN_MASK               ETH_CSN__MASK
#define ETH_CSN_SHIFT              ETH_CSN__SHIFT
#define ETH_CSN_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ETH_CSN_PS                     (* (reg8 *) ETH_CSN__PS)
/* Data Register */
#define ETH_CSN_DR                     (* (reg8 *) ETH_CSN__DR)
/* Port Number */
#define ETH_CSN_PRT_NUM                (* (reg8 *) ETH_CSN__PRT) 
/* Connect to Analog Globals */                                                  
#define ETH_CSN_AG                     (* (reg8 *) ETH_CSN__AG)                       
/* Analog MUX bux enable */
#define ETH_CSN_AMUX                   (* (reg8 *) ETH_CSN__AMUX) 
/* Bidirectional Enable */                                                        
#define ETH_CSN_BIE                    (* (reg8 *) ETH_CSN__BIE)
/* Bit-mask for Aliased Register Access */
#define ETH_CSN_BIT_MASK               (* (reg8 *) ETH_CSN__BIT_MASK)
/* Bypass Enable */
#define ETH_CSN_BYP                    (* (reg8 *) ETH_CSN__BYP)
/* Port wide control signals */                                                   
#define ETH_CSN_CTL                    (* (reg8 *) ETH_CSN__CTL)
/* Drive Modes */
#define ETH_CSN_DM0                    (* (reg8 *) ETH_CSN__DM0) 
#define ETH_CSN_DM1                    (* (reg8 *) ETH_CSN__DM1)
#define ETH_CSN_DM2                    (* (reg8 *) ETH_CSN__DM2) 
/* Input Buffer Disable Override */
#define ETH_CSN_INP_DIS                (* (reg8 *) ETH_CSN__INP_DIS)
/* LCD Common or Segment Drive */
#define ETH_CSN_LCD_COM_SEG            (* (reg8 *) ETH_CSN__LCD_COM_SEG)
/* Enable Segment LCD */
#define ETH_CSN_LCD_EN                 (* (reg8 *) ETH_CSN__LCD_EN)
/* Slew Rate Control */
#define ETH_CSN_SLW                    (* (reg8 *) ETH_CSN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ETH_CSN_PRTDSI__CAPS_SEL       (* (reg8 *) ETH_CSN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ETH_CSN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ETH_CSN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ETH_CSN_PRTDSI__OE_SEL0        (* (reg8 *) ETH_CSN__PRTDSI__OE_SEL0) 
#define ETH_CSN_PRTDSI__OE_SEL1        (* (reg8 *) ETH_CSN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ETH_CSN_PRTDSI__OUT_SEL0       (* (reg8 *) ETH_CSN__PRTDSI__OUT_SEL0) 
#define ETH_CSN_PRTDSI__OUT_SEL1       (* (reg8 *) ETH_CSN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ETH_CSN_PRTDSI__SYNC_OUT       (* (reg8 *) ETH_CSN__PRTDSI__SYNC_OUT) 


#if defined(ETH_CSN__INTSTAT)  /* Interrupt Registers */

    #define ETH_CSN_INTSTAT                (* (reg8 *) ETH_CSN__INTSTAT)
    #define ETH_CSN_SNAP                   (* (reg8 *) ETH_CSN__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ETH_CSN_H */


/* [] END OF FILE */
