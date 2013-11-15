/*******************************************************************************
* File Name: SPI0_IntClock.h
* Version 2.0
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

void SPI0_IntClock_Start(void);
void SPI0_IntClock_Stop(void);

void SPI0_IntClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 SPI0_IntClock_GetDividerRegister(void);
uint8  SPI0_IntClock_GetFractionalDividerRegister(void);

#define SPI0_IntClock_Enable()                         SPI0_IntClock_Start()
#define SPI0_IntClock_Disable()                        SPI0_IntClock_Stop()
#define SPI0_IntClock_SetDividerRegister(clkDivider, reset)  \
                        SPI0_IntClock_SetFractionalDividerRegister((clkDivider), 0)
#define SPI0_IntClock_SetDivider(clkDivider)           SPI0_IntClock_SetDividerRegister((clkDivider), 1)
#define SPI0_IntClock_SetDividerValue(clkDivider)      SPI0_IntClock_SetDividerRegister((clkDivider) - 1, 1)


/***************************************
*             Registers
***************************************/

#define SPI0_IntClock_DIV_REG    (*(reg32 *)SPI0_IntClock__REGISTER)
#define SPI0_IntClock_ENABLE_REG SPI0_IntClock_DIV_REG

#endif /* !defined(CY_CLOCK_SPI0_IntClock_H) */

/* [] END OF FILE */
