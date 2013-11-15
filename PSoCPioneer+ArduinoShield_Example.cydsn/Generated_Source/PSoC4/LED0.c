/*******************************************************************************
* File Name: LED0.c
* Version 2.20
*
* Description:
*  This file provides the source code of the API for the PrISM Component.
*
* Note:
*  The PRiSM Component consists of a 8, 16, 24, 32 - bit PrISM, it
*  depends on length Polynomial value and user selected Seed Value. 
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "LED0.h"


/***************************************
* Local data allocation
***************************************/

uint8 LED0_initVar = 0u;


/*******************************************************************************
* FUNCTION NAME:   LED0_Start
********************************************************************************
*
* Summary:
*  The start function sets Polynomial, Seed and Pulse Density registers provided
*  by customizer. PrISM computation starts on rising edge of input clock.
*
* Parameters:  
*  None.
*
* Return:  
*  None.
*
* Global variables:
*  The LED0_initVar variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and
*  set to 1 the first time LED0_Start() is called. This allows for
*  component initialization without re-initialization in all subsequent calls
*  to the LED0_Start() routine. 

* Reentrant:
*  No.
*
*******************************************************************************/
void LED0_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(LED0_initVar == 0u)
    {
        LED0_Init();
        LED0_initVar = 1u;
    }
    LED0_Enable();
}


/*******************************************************************************
* Function Name: LED0_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  LED0_Start().
*
* Parameters:  
*  None.
*
* Return: 
*  None.
*
*******************************************************************************/
void LED0_Init(void) 
{
    uint8 enableInterrupts;
    
    /* Writes Seed value, polynom value and density provided by customizer */
    LED0_WriteSeed(LED0_SEED);
    LED0_WritePolynomial(LED0_POLYNOM);
    LED0_WritePulse0(LED0_DENSITY0);
    LED0_WritePulse1(LED0_DENSITY1);
    
    enableInterrupts = CyEnterCriticalSection();
    /* Set FIFO0_CLR bit to use FIFO0 as a simple one-byte buffer*/
    CY_SET_REG8(LED0_AUX_CONTROL_PTR, 
                        CY_GET_REG8(LED0_AUX_CONTROL_PTR) | LED0_FIFO0_CLR);
    CyExitCriticalSection(enableInterrupts);
    
    #if(!LED0_PULSE_TYPE_HARDCODED)
        /* Writes density type provided by customizer */
        #if(LED0_GREATERTHAN_OR_EQUAL == LED0_COMPARE0)
            LED0_CONTROL_REG |= LED0_CTRL_COMPARE_TYPE0_GREATER_THAN_OR_EQUAL;
        #else
            LED0_CONTROL_REG &= (uint8)~LED0_CTRL_COMPARE_TYPE0_GREATER_THAN_OR_EQUAL;
        #endif /* End LED0_COMPARE0 */    
    
        #if(LED0_GREATERTHAN_OR_EQUAL == LED0_COMPARE1)
            LED0_CONTROL_REG |= LED0_CTRL_COMPARE_TYPE1_GREATER_THAN_OR_EQUAL;
        #else
            LED0_CONTROL_REG &= (uint8)~LED0_CTRL_COMPARE_TYPE1_GREATER_THAN_OR_EQUAL;
        #endif /* End LED0_COMPARE1 */    
    #endif /* End LED0_PULSE_TYPE_HARDCODED */
}


/*******************************************************************************
* Function Name: LED0_Enable
********************************************************************************
*  
* Summary: 
*  Enables the PrISM block operation
*
* Parameters:  
*  None.
*
* Return: 
*  None.
*
*******************************************************************************/
void LED0_Enable(void) 
{
    #if(!LED0_PULSE_TYPE_HARDCODED)
        /* Enable the PrISM computation */
        LED0_CONTROL_REG |= LED0_CTRL_ENABLE;
    #endif /* End LED0_PULSE_TYPE_HARDCODED */
}


/*******************************************************************************
* FUNCTION NAME:   LED0_Stop
********************************************************************************
*
* Summary:
*  Stops PrISM computation. Outputs remain constant.
*
* Parameters:  
*  None.
*
* Return: 
*  None.
*
*******************************************************************************/
void LED0_Stop(void) 
{
    #if(!LED0_PULSE_TYPE_HARDCODED)
        LED0_CONTROL_REG &= (uint8)~LED0_CTRL_ENABLE;
    #else
        /* PulseTypeHardoded option enabled - to stop PrISM use enable input */
    #endif /* End $INSTANCE_NAME`_PULSE_TYPE_HARDCODED */
}

#if(!LED0_PULSE_TYPE_HARDCODED)


    /***************************************************************************
    * FUNCTION NAME:     LED0_SetPulse0Mode
    ****************************************************************************
    *
    * Summary:
    *  Sets the pulse density type for Density0. Less than or Equal(<=) or 
    *  Greater than or Equal(>=).
    *
    * Parameters:
    *  pulse0Type: Selected pulse density type.
    *
    * Return:
    *  None.
    *
    ***************************************************************************/
    void LED0_SetPulse0Mode(uint8 pulse0Type) 
    {
        if(pulse0Type == LED0_GREATERTHAN_OR_EQUAL)
        {
            LED0_CONTROL_REG |= LED0_CTRL_COMPARE_TYPE0_GREATER_THAN_OR_EQUAL;
        }
        else
        {
            LED0_CONTROL_REG &= (uint8)~LED0_CTRL_COMPARE_TYPE0_GREATER_THAN_OR_EQUAL;
        }
    }
    
    
    /***************************************************************************
    * FUNCTION NAME:   LED0_SetPulse1Mode
    ****************************************************************************
    *
    * Summary:
    *  Sets the pulse density type for Density1. Less than or Equal(<=) or 
    *  Greater than or Equal(>=).
    *
    * Parameters:  
    *  pulse1Type: Selected pulse density type.
    *
    * Return:
    *  None.
    *
    ***************************************************************************/
    void LED0_SetPulse1Mode(uint8 pulse1Type) 
    {
        if(pulse1Type == LED0_GREATERTHAN_OR_EQUAL)
        {
            LED0_CONTROL_REG |= LED0_CTRL_COMPARE_TYPE1_GREATER_THAN_OR_EQUAL;
        }
        else
        {
            LED0_CONTROL_REG &= (uint8)~LED0_CTRL_COMPARE_TYPE1_GREATER_THAN_OR_EQUAL;
        }
    }

#endif /* End LED0_PULSE_TYPE_HARDCODED == 0 */


/*******************************************************************************
* FUNCTION NAME:   LED0_ReadSeed
********************************************************************************
*
* Summary:
*  Reads the PrISM Seed register.
*
* Parameters:
*  None.
*
* Return:
*  Current Period register value.
*
*******************************************************************************/
uint8 LED0_ReadSeed(void) 
{
    return( CY_GET_REG8(LED0_SEED_PTR) );
}


/*******************************************************************************
* FUNCTION NAME:   LED0_WriteSeed
********************************************************************************
*
* Summary:
*  Writes the PrISM Seed register with the start value.
*
* Parameters:
*  seed: Seed register value.
*
* Return:
*  None.
*
*******************************************************************************/
void LED0_WriteSeed(uint8 seed) 
{
    if(seed != 0u)
    {
        CY_SET_REG8(LED0_SEED_COPY_PTR, seed);
        CY_SET_REG8(LED0_SEED_PTR, seed);
    }
}


/*******************************************************************************
* FUNCTION NAME:   LED0_ReadPolynomial
********************************************************************************
*
* Summary:
*  Reads the PrISM polynomial.
*
* Parameters:
*  None.
*
* Return:
*  PrISM polynomial.
*
*******************************************************************************/
uint8 LED0_ReadPolynomial(void) 
{
    return( CY_GET_REG8(LED0_POLYNOM_PTR) );
}


/*******************************************************************************
* FUNCTION NAME:   LED0_WritePolynomial
********************************************************************************
*
* Summary:
*  Writes the PrISM polynomial.
*
* Parameters:
*  polynomial: PrISM polynomial.
*
* Return:
*  None.
*
*******************************************************************************/
void LED0_WritePolynomial(uint8 polynomial) \
                                                                
{
    CY_SET_REG8(LED0_POLYNOM_PTR, polynomial);
    
}


/*******************************************************************************
* FUNCTION NAME:   LED0_ReadPulse0
********************************************************************************
*
* Summary:
*  Reads the PrISM Pulse Density0 register.
*
* Parameters:
*  None.
*
* Return:
*  Pulse Density0 register value.
*
*******************************************************************************/
uint8 LED0_ReadPulse0(void) 
{
    return( CY_GET_REG8(LED0_DENSITY0_PTR) );
}


/*******************************************************************************
* FUNCTION NAME:   LED0_WritePulse0
********************************************************************************
*
* Summary:
*  Writes the PrISM Pulse Density0 register with the Pulse Density value.
*
* Parameters:
*  pulseDensity0: Pulse Density value.
*
* Return:
*  None.
*
*******************************************************************************/
void LED0_WritePulse0(uint8 pulseDensity0) \
                                                                
{
    CY_SET_REG8(LED0_DENSITY0_PTR, pulseDensity0);
}


/*******************************************************************************
* FUNCTION NAME:   LED0_ReadPulse1
********************************************************************************
*
* Summary:
*  Reads the PrISM Pulse Density1 register.
*
* Parameters:
*  None.
*
* Return:
*  Pulse Density1 register value.
*
*******************************************************************************/
uint8 LED0_ReadPulse1(void) 
{
    return( CY_GET_REG8(LED0_DENSITY1_PTR) );
}


/*******************************************************************************
* FUNCTION NAME:   LED0_WritePulse1
********************************************************************************
*
* Summary:
*  Writes the PrISM Pulse Density1 register with the Pulse Density value.
*
* Parameters:
*  pulseDensity1: Pulse Density value.
*
* Return:
*  None.
*
*******************************************************************************/
void LED0_WritePulse1(uint8 pulseDensity1) \
                                                                    
{
    CY_SET_REG8(LED0_DENSITY1_PTR, pulseDensity1);
}


/* [] END OF FILE */
