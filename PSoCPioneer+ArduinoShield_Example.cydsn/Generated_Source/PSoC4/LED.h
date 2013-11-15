/*******************************************************************************
* File Name: LED.h
* Version 2.20
*
* Description:
*  This file provides constants and parameter values for the PrISM
*  Component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_PrISM_LED_H)    /* CY_PrISM_LED_H */
#define CY_PrISM_LED_H

#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PrISM_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*    Initial Parameter Constants
***************************************/
                                     
#define LED_RESOLUTION             (16u)
#define LED_PULSE_TYPE_HARDCODED   (0u)


/***************************************
*       Type defines
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    #if(!LED_PULSE_TYPE_HARDCODED)
        uint8 cr;
    #endif /* End LED_PULSE_TYPE_HARDCODED */
    uint16 seed;
    uint16 seed_copy;
    uint16 polynom;
    #if(CY_UDB_V0)
        uint16 density0;
        uint16 density1;
    #endif /* End CY_UDB_V0 */
} LED_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void LED_Start(void) ;
void LED_Stop(void) ;
void LED_SetPulse0Mode(uint8 pulse0Type) ;
void LED_SetPulse1Mode(uint8 pulse1Type) ;
uint16 LED_ReadSeed(void) ;
void LED_WriteSeed(uint16 seed) ;
uint16 LED_ReadPolynomial(void) ;
void LED_WritePolynomial(uint16 polynomial) \
                                                                ;
uint16 LED_ReadPulse0(void) ;
void LED_WritePulse0(uint16 pulseDensity0) \
                                                                ;
uint16 LED_ReadPulse1(void) ;
void LED_WritePulse1(uint16 pulseDensity1) \
                                                                ;
void LED_Sleep(void) ;
void LED_Wakeup(void) ;
void LED_SaveConfig(void) ;
void LED_RestoreConfig(void) ;
void LED_Enable(void) ;
void LED_Init(void) ;


/***************************************
*          API Constants
***************************************/

/* Constants for SetPulse0Mode(), SetPulse1Mode(), pulse type */
#define LED_LESSTHAN_OR_EQUAL      (0x00u)
#define LED_GREATERTHAN_OR_EQUAL   (0x01u)


/***************************************
* Global variables external identifier
***************************************/

extern uint8 LED_initVar;


/***************************************
*    Initial Parameter Constants
***************************************/

#define LED_POLYNOM                (0xB400u)
#define LED_SEED                   (0xFFFFu)
#define LED_DENSITY0               (0x1u)
#define LED_DENSITY1               (0x1u)
#define LED_COMPARE0               (0u)
#define LED_COMPARE1               (0u)


/***************************************
*              Registers
***************************************/

#if (LED_RESOLUTION  <= 8u) /* 8bit - PrISM */
    #define LED_DENSITY0_REG       (* (reg8 *) LED_sC8_PrISMdp_u0__D0_REG)
    #define LED_DENSITY0_PTR       (  (reg8 *) LED_sC8_PrISMdp_u0__D0_REG)
    #define LED_DENSITY1_REG       (* (reg8 *) LED_sC8_PrISMdp_u0__D1_REG)
    #define LED_DENSITY1_PTR       (  (reg8 *) LED_sC8_PrISMdp_u0__D1_REG)
    #define LED_POLYNOM_REG        (* (reg8 *) LED_sC8_PrISMdp_u0__A1_REG)
    #define LED_POLYNOM_PTR        (  (reg8 *) LED_sC8_PrISMdp_u0__A1_REG)
    #define LED_SEED_REG           (* (reg8 *) LED_sC8_PrISMdp_u0__A0_REG)
    #define LED_SEED_PTR           (  (reg8 *) LED_sC8_PrISMdp_u0__A0_REG)
    #define LED_SEED_COPY_REG      (* (reg8 *) LED_sC8_PrISMdp_u0__F0_REG)
    #define LED_SEED_COPY_PTR      (  (reg8 *) LED_sC8_PrISMdp_u0__F0_REG)
    #define LED_AUX_CONTROL_REG    (* (reg8 *) LED_sC8_PrISMdp_u0__DP_AUX_CTL_REG)
    #define LED_AUX_CONTROL_PTR    (  (reg8 *) LED_sC8_PrISMdp_u0__DP_AUX_CTL_REG)
#elif (LED_RESOLUTION <= 16u) /* 16bit - PrISM */
    #if(CY_PSOC3) /* 8-bit address space */
        #define LED_DENSITY0_PTR       ((reg16 *) LED_sC16_PrISMdp_u0__D0_REG)
        #define LED_DENSITY1_PTR       ((reg16 *) LED_sC16_PrISMdp_u0__D1_REG)
        #define LED_POLYNOM_PTR        ((reg16 *) LED_sC16_PrISMdp_u0__A1_REG)
        #define LED_SEED_PTR           ((reg16 *) LED_sC16_PrISMdp_u0__A0_REG)
        #define LED_SEED_COPY_PTR      ((reg16 *) LED_sC16_PrISMdp_u0__F0_REG)
        #define LED_AUX_CONTROL_PTR    ((reg16 *) LED_sC16_PrISMdp_u0__DP_AUX_CTL_REG)
    #else /* 16-bit address space */
        #define LED_DENSITY0_PTR       ((reg16 *) LED_sC16_PrISMdp_u0__16BIT_D0_REG)
        #define LED_DENSITY1_PTR       ((reg16 *) LED_sC16_PrISMdp_u0__16BIT_D1_REG)
        #define LED_POLYNOM_PTR        ((reg16 *) LED_sC16_PrISMdp_u0__16BIT_A1_REG)
        #define LED_SEED_PTR           ((reg16 *) LED_sC16_PrISMdp_u0__16BIT_A0_REG)
        #define LED_SEED_COPY_PTR      ((reg16 *) LED_sC16_PrISMdp_u0__16BIT_F0_REG)
        #define LED_AUX_CONTROL_PTR    ((reg16 *) LED_sC16_PrISMdp_u0__16BIT_DP_AUX_CTL_REG)
    #endif /* CY_PSOC3 */
#elif (LED_RESOLUTION <= 24u) /* 24bit - PrISM */
    #define LED_DENSITY0_PTR       ((reg32 *) LED_sC24_PrISMdp_u0__D0_REG)
    #define LED_DENSITY1_PTR       ((reg32 *) LED_sC24_PrISMdp_u0__D1_REG)
    #define LED_POLYNOM_PTR        ((reg32 *) LED_sC24_PrISMdp_u0__A1_REG)
    #define LED_SEED_PTR           ((reg32 *) LED_sC24_PrISMdp_u0__A0_REG)
    #define LED_SEED_COPY_PTR      ((reg32 *) LED_sC24_PrISMdp_u0__F0_REG)
    #define LED_AUX_CONTROL_PTR    ((reg32 *) LED_sC24_PrISMdp_u0__DP_AUX_CTL_REG)
#else /* 32bit - PrISM */
    #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
        #define LED_DENSITY0_PTR       ((reg32 *) LED_sC32_PrISMdp_u0__D0_REG)
        #define LED_DENSITY1_PTR       ((reg32 *) LED_sC32_PrISMdp_u0__D1_REG)
        #define LED_POLYNOM_PTR        ((reg32 *) LED_sC32_PrISMdp_u0__A1_REG)
        #define LED_SEED_PTR           ((reg32 *) LED_sC32_PrISMdp_u0__A0_REG)
        #define LED_SEED_COPY_PTR      ((reg32 *) LED_sC32_PrISMdp_u0__F0_REG)
        #define LED_AUX_CONTROL_PTR    ((reg32 *) LED_sC32_PrISMdp_u0__DP_AUX_CTL_REG)
    #else /* 32-bit address space */    
        #define LED_DENSITY0_PTR       ((reg32 *) LED_sC32_PrISMdp_u0__32BIT_D0_REG)
        #define LED_DENSITY1_PTR       ((reg32 *) LED_sC32_PrISMdp_u0__32BIT_D1_REG)
        #define LED_POLYNOM_PTR        ((reg32 *) LED_sC32_PrISMdp_u0__32BIT_A1_REG)
        #define LED_SEED_PTR           ((reg32 *) LED_sC32_PrISMdp_u0__32BIT_A0_REG)
        #define LED_SEED_COPY_PTR      ((reg32 *) LED_sC32_PrISMdp_u0__32BIT_F0_REG)
        #define LED_AUX_CONTROL_PTR    ((reg32 *) LED_sC32_PrISMdp_u0__32BIT_DP_AUX_CTL_REG)
    #endif
#endif /* End LED_RESOLUTION */

#define LED_CONTROL_REG   (* (reg8 *) LED_SyncCtl_ControlReg__CONTROL_REG)
#define LED_CONTROL_PTR   (  (reg8 *) LED_SyncCtl_ControlReg__CONTROL_REG)


/***************************************
*       Register Constants
***************************************/

#define LED_CTRL_ENABLE                                (0x01u)
#define LED_CTRL_COMPARE_TYPE0_GREATER_THAN_OR_EQUAL   (0x02u)
#define LED_CTRL_COMPARE_TYPE1_GREATER_THAN_OR_EQUAL   (0x04u)

#if (LED_RESOLUTION  <= 8u) /* 8bit - PrISM */
    #define LED_FIFO0_CLR                              (0x01u)
#elif (LED_RESOLUTION <= 16u) /* 16bit - PrISM */
    #define LED_FIFO0_CLR                              (0x0101u)
#elif (LED_RESOLUTION <= 24u) /* 24bit - PrISM */
    #define LED_FIFO0_CLR                              (0x010101Lu)
#else /* 32bit - PrISM */
    #define LED_FIFO0_CLR                              (0x01010101Lu)
#endif /* End LED_RESOLUTION */


/***************************************
* Renamed global variables or defines 
* for backward compatible
***************************************/
#define LED_ReadPusle0     LED_ReadPulse0
#define LED_ReadPusle1     LED_ReadPulse1


#endif  /* End CY_PrISM_LED_H */


/* [] END OF FILE */
