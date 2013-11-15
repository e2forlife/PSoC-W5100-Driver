/*******************************************************************************
* File Name: ADC0.h  
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

#if !defined(CY_PINS_ADC0_H) /* Pins ADC0_H */
#define CY_PINS_ADC0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ADC0_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ADC0_Write(uint8 value) ;
void    ADC0_SetDriveMode(uint8 mode) ;
uint8   ADC0_ReadDataReg(void) ;
uint8   ADC0_Read(void) ;
uint8   ADC0_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ADC0_DRIVE_MODE_BITS        (3)
#define ADC0_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ADC0_DRIVE_MODE_BITS))
#define ADC0_DRIVE_MODE_SHIFT       (0x00u)
#define ADC0_DRIVE_MODE_MASK        (0x07u << ADC0_DRIVE_MODE_SHIFT)

#define ADC0_DM_ALG_HIZ         (0x00u << ADC0_DRIVE_MODE_SHIFT)
#define ADC0_DM_DIG_HIZ         (0x01u << ADC0_DRIVE_MODE_SHIFT)
#define ADC0_DM_RES_UP          (0x02u << ADC0_DRIVE_MODE_SHIFT)
#define ADC0_DM_RES_DWN         (0x03u << ADC0_DRIVE_MODE_SHIFT)
#define ADC0_DM_OD_LO           (0x04u << ADC0_DRIVE_MODE_SHIFT)
#define ADC0_DM_OD_HI           (0x05u << ADC0_DRIVE_MODE_SHIFT)
#define ADC0_DM_STRONG          (0x06u << ADC0_DRIVE_MODE_SHIFT)
#define ADC0_DM_RES_UPDWN       (0x07u << ADC0_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define ADC0_MASK               ADC0__MASK
#define ADC0_SHIFT              ADC0__SHIFT
#define ADC0_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ADC0_PS                     (* (reg32 *) ADC0__PS)
/* Port Configuration */
#define ADC0_PC                     (* (reg32 *) ADC0__PC)
/* Data Register */
#define ADC0_DR                     (* (reg32 *) ADC0__DR)
/* Input Buffer Disable Override */
#define ADC0_INP_DIS                (* (reg32 *) ADC0__PC2)


#if defined(ADC0__INTSTAT)  /* Interrupt Registers */

    #define ADC0_INTSTAT                (* (reg32 *) ADC0__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins ADC0_H */


/* [] END OF FILE */
