/*******************************************************************************
* File Name: SPI_IntClock.h
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

#if !defined(CY_CLOCK_SPI_IntClock_H)
#define CY_CLOCK_SPI_IntClock_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/

void SPI_IntClock_Start(void);
void SPI_IntClock_Stop(void);

void SPI_IntClock_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 SPI_IntClock_GetDividerRegister(void);
uint8  SPI_IntClock_GetFractionalDividerRegister(void);

#define SPI_IntClock_Enable()                         SPI_IntClock_Start()
#define SPI_IntClock_Disable()                        SPI_IntClock_Stop()
#define SPI_IntClock_SetDividerRegister(clkDivider, reset)  \
                        SPI_IntClock_SetFractionalDividerRegister((clkDivider), 0)
#define SPI_IntClock_SetDivider(clkDivider)           SPI_IntClock_SetDividerRegister((clkDivider), 1)
#define SPI_IntClock_SetDividerValue(clkDivider)      SPI_IntClock_SetDividerRegister((clkDivider) - 1, 1)


/***************************************
*             Registers
***************************************/

#define SPI_IntClock_DIV_REG    (*(reg32 *)SPI_IntClock__REGISTER)
#define SPI_IntClock_ENABLE_REG SPI_IntClock_DIV_REG

#endif /* !defined(CY_CLOCK_SPI_IntClock_H) */

/* [] END OF FILE */
