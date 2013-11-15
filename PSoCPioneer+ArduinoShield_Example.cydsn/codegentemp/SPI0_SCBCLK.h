/*******************************************************************************
* File Name: SPI0_SCBCLK.h
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

#if !defined(CY_CLOCK_SPI0_SCBCLK_H)
#define CY_CLOCK_SPI0_SCBCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void SPI0_SCBCLK_Start(void);
void SPI0_SCBCLK_Stop(void);

void SPI0_SCBCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 SPI0_SCBCLK_GetDividerRegister(void);
uint8  SPI0_SCBCLK_GetFractionalDividerRegister(void);

#define SPI0_SCBCLK_Enable()                         SPI0_SCBCLK_Start()
#define SPI0_SCBCLK_Disable()                        SPI0_SCBCLK_Stop()
#define SPI0_SCBCLK_SetDividerRegister(clkDivider, reset)  \
                        SPI0_SCBCLK_SetFractionalDividerRegister((clkDivider), 0)
#define SPI0_SCBCLK_SetDivider(clkDivider)           SPI0_SCBCLK_SetDividerRegister((clkDivider), 1)
#define SPI0_SCBCLK_SetDividerValue(clkDivider)      SPI0_SCBCLK_SetDividerRegister((clkDivider) - 1, 1)


/***************************************
*             Registers
***************************************/

#define SPI0_SCBCLK_DIV_REG    (*(reg32 *)SPI0_SCBCLK__REGISTER)
#define SPI0_SCBCLK_ENABLE_REG SPI0_SCBCLK_DIV_REG

#endif /* !defined(CY_CLOCK_SPI0_SCBCLK_H) */

/* [] END OF FILE */
