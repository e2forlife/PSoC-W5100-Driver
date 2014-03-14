/*******************************************************************************
* File Name: SPI0_ss0_m.h  
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

#if !defined(CY_PINS_SPI0_ss0_m_H) /* Pins SPI0_ss0_m_H */
#define CY_PINS_SPI0_ss0_m_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SPI0_ss0_m_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SPI0_ss0_m_Write(uint8 value) ;
void    SPI0_ss0_m_SetDriveMode(uint8 mode) ;
uint8   SPI0_ss0_m_ReadDataReg(void) ;
uint8   SPI0_ss0_m_Read(void) ;
uint8   SPI0_ss0_m_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SPI0_ss0_m_DRIVE_MODE_BITS        (3)
#define SPI0_ss0_m_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SPI0_ss0_m_DRIVE_MODE_BITS))
#define SPI0_ss0_m_DRIVE_MODE_SHIFT       (0x00u)
#define SPI0_ss0_m_DRIVE_MODE_MASK        (0x07u << SPI0_ss0_m_DRIVE_MODE_SHIFT)

#define SPI0_ss0_m_DM_ALG_HIZ         (0x00u << SPI0_ss0_m_DRIVE_MODE_SHIFT)
#define SPI0_ss0_m_DM_DIG_HIZ         (0x01u << SPI0_ss0_m_DRIVE_MODE_SHIFT)
#define SPI0_ss0_m_DM_RES_UP          (0x02u << SPI0_ss0_m_DRIVE_MODE_SHIFT)
#define SPI0_ss0_m_DM_RES_DWN         (0x03u << SPI0_ss0_m_DRIVE_MODE_SHIFT)
#define SPI0_ss0_m_DM_OD_LO           (0x04u << SPI0_ss0_m_DRIVE_MODE_SHIFT)
#define SPI0_ss0_m_DM_OD_HI           (0x05u << SPI0_ss0_m_DRIVE_MODE_SHIFT)
#define SPI0_ss0_m_DM_STRONG          (0x06u << SPI0_ss0_m_DRIVE_MODE_SHIFT)
#define SPI0_ss0_m_DM_RES_UPDWN       (0x07u << SPI0_ss0_m_DRIVE_MODE_SHIFT)

/* Digital Port Constants */
#define SPI0_ss0_m_MASK               SPI0_ss0_m__MASK
#define SPI0_ss0_m_SHIFT              SPI0_ss0_m__SHIFT
#define SPI0_ss0_m_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SPI0_ss0_m_PS                     (* (reg32 *) SPI0_ss0_m__PS)
/* Port Configuration */
#define SPI0_ss0_m_PC                     (* (reg32 *) SPI0_ss0_m__PC)
/* Data Register */
#define SPI0_ss0_m_DR                     (* (reg32 *) SPI0_ss0_m__DR)
/* Input Buffer Disable Override */
#define SPI0_ss0_m_INP_DIS                (* (reg32 *) SPI0_ss0_m__PC2)


#if defined(SPI0_ss0_m__INTSTAT)  /* Interrupt Registers */

    #define SPI0_ss0_m_INTSTAT                (* (reg32 *) SPI0_ss0_m__INTSTAT)

#endif /* Interrupt Registers */

#endif /* End Pins SPI0_ss0_m_H */


/* [] END OF FILE */
