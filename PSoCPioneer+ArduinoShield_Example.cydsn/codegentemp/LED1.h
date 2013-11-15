/*******************************************************************************
* File Name: LED1.h
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


#if !defined(CY_PrISM_LED1_H)    /* CY_PrISM_LED1_H */
#define CY_PrISM_LED1_H

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
                                     
#define LED1_RESOLUTION             (8u)
#define LED1_PULSE_TYPE_HARDCODED   (0u)


/***************************************
*       Type defines
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    #if(!LED1_PULSE_TYPE_HARDCODED)
        uint8 cr;
    #endif /* End LED1_PULSE_TYPE_HARDCODED */
    uint8 seed;
    uint8 seed_copy;
    uint8 polynom;
    #if(CY_UDB_V0)
        uint8 density0;
        uint8 density1;
    #endif /* End CY_UDB_V0 */
} LED1_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void LED1_Start(void) ;
void LED1_Stop(void) ;
void LED1_SetPulse0Mode(uint8 pulse0Type) ;
void LED1_SetPulse1Mode(uint8 pulse1Type) ;
uint8 LED1_ReadSeed(void) ;
void LED1_WriteSeed(uint8 seed) ;
uint8 LED1_ReadPolynomial(void) ;
void LED1_WritePolynomial(uint8 polynomial) \
                                                                ;
uint8 LED1_ReadPulse0(void) ;
void LED1_WritePulse0(uint8 pulseDensity0) \
                                                                ;
uint8 LED1_ReadPulse1(void) ;
void LED1_WritePulse1(uint8 pulseDensity1) \
                                                                ;
void LED1_Sleep(void) ;
void LED1_Wakeup(void) ;
void LED1_SaveConfig(void) ;
void LED1_RestoreConfig(void) ;
void LED1_Enable(void) ;
void LED1_Init(void) ;


/***************************************
*          API Constants
***************************************/

/* Constants for SetPulse0Mode(), SetPulse1Mode(), pulse type */
#define LED1_LESSTHAN_OR_EQUAL      (0x00u)
#define LED1_GREATERTHAN_OR_EQUAL   (0x01u)


/***************************************
* Global variables external identifier
***************************************/

extern uint8 LED1_initVar;


/***************************************
*    Initial Parameter Constants
***************************************/

#define LED1_POLYNOM                (0xB8u)
#define LED1_SEED                   (0xFFu)
#define LED1_DENSITY0               (0x1u)
#define LED1_DENSITY1               (0x1u)
#define LED1_COMPARE0               (0u)
#define LED1_COMPARE1               (0u)


/***************************************
*              Registers
***************************************/

#if (LED1_RESOLUTION  <= 8u) /* 8bit - PrISM */
    #define LED1_DENSITY0_REG       (* (reg8 *) LED1_sC8_PrISMdp_u0__D0_REG)
    #define LED1_DENSITY0_PTR       (  (reg8 *) LED1_sC8_PrISMdp_u0__D0_REG)
    #define LED1_DENSITY1_REG       (* (reg8 *) LED1_sC8_PrISMdp_u0__D1_REG)
    #define LED1_DENSITY1_PTR       (  (reg8 *) LED1_sC8_PrISMdp_u0__D1_REG)
    #define LED1_POLYNOM_REG        (* (reg8 *) LED1_sC8_PrISMdp_u0__A1_REG)
    #define LED1_POLYNOM_PTR        (  (reg8 *) LED1_sC8_PrISMdp_u0__A1_REG)
    #define LED1_SEED_REG           (* (reg8 *) LED1_sC8_PrISMdp_u0__A0_REG)
    #define LED1_SEED_PTR           (  (reg8 *) LED1_sC8_PrISMdp_u0__A0_REG)
    #define LED1_SEED_COPY_REG      (* (reg8 *) LED1_sC8_PrISMdp_u0__F0_REG)
    #define LED1_SEED_COPY_PTR      (  (reg8 *) LED1_sC8_PrISMdp_u0__F0_REG)
    #define LED1_AUX_CONTROL_REG    (* (reg8 *) LED1_sC8_PrISMdp_u0__DP_AUX_CTL_REG)
    #define LED1_AUX_CONTROL_PTR    (  (reg8 *) LED1_sC8_PrISMdp_u0__DP_AUX_CTL_REG)
#elif (LED1_RESOLUTION <= 16u) /* 16bit - PrISM */
    #if(CY_PSOC3) /* 8-bit address space */
        #define LED1_DENSITY0_PTR       ((reg16 *) LED1_sC16_PrISMdp_u0__D0_REG)
        #define LED1_DENSITY1_PTR       ((reg16 *) LED1_sC16_PrISMdp_u0__D1_REG)
        #define LED1_POLYNOM_PTR        ((reg16 *) LED1_sC16_PrISMdp_u0__A1_REG)
        #define LED1_SEED_PTR           ((reg16 *) LED1_sC16_PrISMdp_u0__A0_REG)
        #define LED1_SEED_COPY_PTR      ((reg16 *) LED1_sC16_PrISMdp_u0__F0_REG)
        #define LED1_AUX_CONTROL_PTR    ((reg16 *) LED1_sC16_PrISMdp_u0__DP_AUX_CTL_REG)
    #else /* 16-bit address space */
        #define LED1_DENSITY0_PTR       ((reg16 *) LED1_sC16_PrISMdp_u0__16BIT_D0_REG)
        #define LED1_DENSITY1_PTR       ((reg16 *) LED1_sC16_PrISMdp_u0__16BIT_D1_REG)
        #define LED1_POLYNOM_PTR        ((reg16 *) LED1_sC16_PrISMdp_u0__16BIT_A1_REG)
        #define LED1_SEED_PTR           ((reg16 *) LED1_sC16_PrISMdp_u0__16BIT_A0_REG)
        #define LED1_SEED_COPY_PTR      ((reg16 *) LED1_sC16_PrISMdp_u0__16BIT_F0_REG)
        #define LED1_AUX_CONTROL_PTR    ((reg16 *) LED1_sC16_PrISMdp_u0__16BIT_DP_AUX_CTL_REG)
    #endif /* CY_PSOC3 */
#elif (LED1_RESOLUTION <= 24u) /* 24bit - PrISM */
    #define LED1_DENSITY0_PTR       ((reg32 *) LED1_sC24_PrISMdp_u0__D0_REG)
    #define LED1_DENSITY1_PTR       ((reg32 *) LED1_sC24_PrISMdp_u0__D1_REG)
    #define LED1_POLYNOM_PTR        ((reg32 *) LED1_sC24_PrISMdp_u0__A1_REG)
    #define LED1_SEED_PTR           ((reg32 *) LED1_sC24_PrISMdp_u0__A0_REG)
    #define LED1_SEED_COPY_PTR      ((reg32 *) LED1_sC24_PrISMdp_u0__F0_REG)
    #define LED1_AUX_CONTROL_PTR    ((reg32 *) LED1_sC24_PrISMdp_u0__DP_AUX_CTL_REG)
#else /* 32bit - PrISM */
    #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
        #define LED1_DENSITY0_PTR       ((reg32 *) LED1_sC32_PrISMdp_u0__D0_REG)
        #define LED1_DENSITY1_PTR       ((reg32 *) LED1_sC32_PrISMdp_u0__D1_REG)
        #define LED1_POLYNOM_PTR        ((reg32 *) LED1_sC32_PrISMdp_u0__A1_REG)
        #define LED1_SEED_PTR           ((reg32 *) LED1_sC32_PrISMdp_u0__A0_REG)
        #define LED1_SEED_COPY_PTR      ((reg32 *) LED1_sC32_PrISMdp_u0__F0_REG)
        #define LED1_AUX_CONTROL_PTR    ((reg32 *) LED1_sC32_PrISMdp_u0__DP_AUX_CTL_REG)
    #else /* 32-bit address space */    
        #define LED1_DENSITY0_PTR       ((reg32 *) LED1_sC32_PrISMdp_u0__32BIT_D0_REG)
        #define LED1_DENSITY1_PTR       ((reg32 *) LED1_sC32_PrISMdp_u0__32BIT_D1_REG)
        #define LED1_POLYNOM_PTR        ((reg32 *) LED1_sC32_PrISMdp_u0__32BIT_A1_REG)
        #define LED1_SEED_PTR           ((reg32 *) LED1_sC32_PrISMdp_u0__32BIT_A0_REG)
        #define LED1_SEED_COPY_PTR      ((reg32 *) LED1_sC32_PrISMdp_u0__32BIT_F0_REG)
        #define LED1_AUX_CONTROL_PTR    ((reg32 *) LED1_sC32_PrISMdp_u0__32BIT_DP_AUX_CTL_REG)
    #endif
#endif /* End LED1_RESOLUTION */

#define LED1_CONTROL_REG   (* (reg8 *) LED1_SyncCtl_ControlReg__CONTROL_REG)
#define LED1_CONTROL_PTR   (  (reg8 *) LED1_SyncCtl_ControlReg__CONTROL_REG)


/***************************************
*       Register Constants
***************************************/

#define LED1_CTRL_ENABLE                                (0x01u)
#define LED1_CTRL_COMPARE_TYPE0_GREATER_THAN_OR_EQUAL   (0x02u)
#define LED1_CTRL_COMPARE_TYPE1_GREATER_THAN_OR_EQUAL   (0x04u)

#if (LED1_RESOLUTION  <= 8u) /* 8bit - PrISM */
    #define LED1_FIFO0_CLR                              (0x01u)
#elif (LED1_RESOLUTION <= 16u) /* 16bit - PrISM */
    #define LED1_FIFO0_CLR                              (0x0101u)
#elif (LED1_RESOLUTION <= 24u) /* 24bit - PrISM */
    #define LED1_FIFO0_CLR                              (0x010101Lu)
#else /* 32bit - PrISM */
    #define LED1_FIFO0_CLR                              (0x01010101Lu)
#endif /* End LED1_RESOLUTION */


/***************************************
* Renamed global variables or defines 
* for backward compatible
***************************************/
#define LED1_ReadPusle0     LED1_ReadPulse0
#define LED1_ReadPusle1     LED1_ReadPulse1


#endif  /* End CY_PrISM_LED1_H */


/* [] END OF FILE */
