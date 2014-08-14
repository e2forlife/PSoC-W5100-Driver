/*******************************************************************************
* File Name: SPI0_IntClock.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_SPI0_IntClock_H)
#define CY_CLOCK_SPI0_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void SPI0_IntClock_StartEx(uint32 alignClkDiv);
#define SPI0_IntClock_Start() \
    SPI0_IntClock_StartEx(SPI0_IntClock__PA_DIV_ID)

#else

void SPI0_IntClock_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void SPI0_IntClock_Stop(void);

void SPI0_IntClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 SPI0_IntClock_GetDividerRegister(void);
uint8  SPI0_IntClock_GetFractionalDividerRegister(void);

#define SPI0_IntClock_Enable()                         SPI0_IntClock_Start()
#define SPI0_IntClock_Disable()                        SPI0_IntClock_Stop()
#define SPI0_IntClock_SetDividerRegister(clkDivider, reset)  \
    SPI0_IntClock_SetFractionalDividerRegister((clkDivider), 0u)
#define SPI0_IntClock_SetDivider(clkDivider)           SPI0_IntClock_SetDividerRegister((clkDivider), 1u)
#define SPI0_IntClock_SetDividerValue(clkDivider)      SPI0_IntClock_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define SPI0_IntClock_DIV_ID     SPI0_IntClock__DIV_ID

#define SPI0_IntClock_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define SPI0_IntClock_CTRL_REG   (*(reg32 *)SPI0_IntClock__CTRL_REGISTER)
#define SPI0_IntClock_DIV_REG    (*(reg32 *)SPI0_IntClock__DIV_REGISTER)

#define SPI0_IntClock_CMD_DIV_SHIFT          (0u)
#define SPI0_IntClock_CMD_PA_DIV_SHIFT       (8u)
#define SPI0_IntClock_CMD_DISABLE_SHIFT      (30u)
#define SPI0_IntClock_CMD_ENABLE_SHIFT       (31u)

#define SPI0_IntClock_CMD_DISABLE_MASK       ((uint32)((uint32)1u << SPI0_IntClock_CMD_DISABLE_SHIFT))
#define SPI0_IntClock_CMD_ENABLE_MASK        ((uint32)((uint32)1u << SPI0_IntClock_CMD_ENABLE_SHIFT))

#define SPI0_IntClock_DIV_FRAC_MASK  (0x000000F8u)
#define SPI0_IntClock_DIV_FRAC_SHIFT (3u)
#define SPI0_IntClock_DIV_INT_MASK   (0xFFFFFF00u)
#define SPI0_IntClock_DIV_INT_SHIFT  (8u)

#else 

#define SPI0_IntClock_DIV_REG        (*(reg32 *)SPI0_IntClock__REGISTER)
#define SPI0_IntClock_ENABLE_REG     SPI0_IntClock_DIV_REG
#define SPI0_IntClock_DIV_FRAC_MASK  SPI0_IntClock__FRAC_MASK
#define SPI0_IntClock_DIV_FRAC_SHIFT (16u)
#define SPI0_IntClock_DIV_INT_MASK   SPI0_IntClock__DIVIDER_MASK
#define SPI0_IntClock_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_SPI0_IntClock_H) */

/* [] END OF FILE */
