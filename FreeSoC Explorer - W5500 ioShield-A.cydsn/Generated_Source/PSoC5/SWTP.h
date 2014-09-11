/*******************************************************************************
* File Name: SWTP.h  
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

#if !defined(CY_PINS_SWTP_H) /* Pins SWTP_H */
#define CY_PINS_SWTP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SWTP_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SWTP__PORT == 15 && ((SWTP__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    SWTP_Write(uint8 value) ;
void    SWTP_SetDriveMode(uint8 mode) ;
uint8   SWTP_ReadDataReg(void) ;
uint8   SWTP_Read(void) ;
uint8   SWTP_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SWTP_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define SWTP_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define SWTP_DM_RES_UP          PIN_DM_RES_UP
#define SWTP_DM_RES_DWN         PIN_DM_RES_DWN
#define SWTP_DM_OD_LO           PIN_DM_OD_LO
#define SWTP_DM_OD_HI           PIN_DM_OD_HI
#define SWTP_DM_STRONG          PIN_DM_STRONG
#define SWTP_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define SWTP_MASK               SWTP__MASK
#define SWTP_SHIFT              SWTP__SHIFT
#define SWTP_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SWTP_PS                     (* (reg8 *) SWTP__PS)
/* Data Register */
#define SWTP_DR                     (* (reg8 *) SWTP__DR)
/* Port Number */
#define SWTP_PRT_NUM                (* (reg8 *) SWTP__PRT) 
/* Connect to Analog Globals */                                                  
#define SWTP_AG                     (* (reg8 *) SWTP__AG)                       
/* Analog MUX bux enable */
#define SWTP_AMUX                   (* (reg8 *) SWTP__AMUX) 
/* Bidirectional Enable */                                                        
#define SWTP_BIE                    (* (reg8 *) SWTP__BIE)
/* Bit-mask for Aliased Register Access */
#define SWTP_BIT_MASK               (* (reg8 *) SWTP__BIT_MASK)
/* Bypass Enable */
#define SWTP_BYP                    (* (reg8 *) SWTP__BYP)
/* Port wide control signals */                                                   
#define SWTP_CTL                    (* (reg8 *) SWTP__CTL)
/* Drive Modes */
#define SWTP_DM0                    (* (reg8 *) SWTP__DM0) 
#define SWTP_DM1                    (* (reg8 *) SWTP__DM1)
#define SWTP_DM2                    (* (reg8 *) SWTP__DM2) 
/* Input Buffer Disable Override */
#define SWTP_INP_DIS                (* (reg8 *) SWTP__INP_DIS)
/* LCD Common or Segment Drive */
#define SWTP_LCD_COM_SEG            (* (reg8 *) SWTP__LCD_COM_SEG)
/* Enable Segment LCD */
#define SWTP_LCD_EN                 (* (reg8 *) SWTP__LCD_EN)
/* Slew Rate Control */
#define SWTP_SLW                    (* (reg8 *) SWTP__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SWTP_PRTDSI__CAPS_SEL       (* (reg8 *) SWTP__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SWTP_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SWTP__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SWTP_PRTDSI__OE_SEL0        (* (reg8 *) SWTP__PRTDSI__OE_SEL0) 
#define SWTP_PRTDSI__OE_SEL1        (* (reg8 *) SWTP__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SWTP_PRTDSI__OUT_SEL0       (* (reg8 *) SWTP__PRTDSI__OUT_SEL0) 
#define SWTP_PRTDSI__OUT_SEL1       (* (reg8 *) SWTP__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SWTP_PRTDSI__SYNC_OUT       (* (reg8 *) SWTP__PRTDSI__SYNC_OUT) 


#if defined(SWTP__INTSTAT)  /* Interrupt Registers */

    #define SWTP_INTSTAT                (* (reg8 *) SWTP__INTSTAT)
    #define SWTP_SNAP                   (* (reg8 *) SWTP__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SWTP_H */


/* [] END OF FILE */
