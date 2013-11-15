/*******************************************************************************
* File Name: LED.c
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

#include "LED.h"


/***************************************
* Local data allocation
***************************************/

uint8 LED_initVar = 0u;


/*******************************************************************************
* FUNCTION NAME:   LED_Start
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
*  The LED_initVar variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and
*  set to 1 the first time LED_Start() is called. This allows for
*  component initialization without re-initialization in all subsequent calls
*  to the LED_Start() routine. 

* Reentrant:
*  No.
*
*******************************************************************************/
void LED_Start(void) 
{
    /* If not Initialized then initialize all required hardware and software */
    if(LED_initVar == 0u)
    {
        LED_Init();
        LED_initVar = 1u;
    }
    LED_Enable();
}


/*******************************************************************************
* Function Name: LED_Init
********************************************************************************
*
* Summary:
*  Initialize component's parameters to the parameters set by user in the 
*  customizer of the component placed onto schematic. Usually called in 
*  LED_Start().
*
* Parameters:  
*  None.
*
* Return: 
*  None.
*
*******************************************************************************/
void LED_Init(void) 
{
    uint8 enableInterrupts;
    
    /* Writes Seed value, polynom value and density provided by customizer */
    LED_WriteSeed(LED_SEED);
    LED_WritePolynomial(LED_POLYNOM);
    LED_WritePulse0(LED_DENSITY0);
    LED_WritePulse1(LED_DENSITY1);
    
    enableInterrupts = CyEnterCriticalSection();
    /* Set FIFO0_CLR bit to use FIFO0 as a simple one-byte buffer*/
    CY_SET_REG16(LED_AUX_CONTROL_PTR, 
                        CY_GET_REG16(LED_AUX_CONTROL_PTR) | LED_FIFO0_CLR);
    CyExitCriticalSection(enableInterrupts);
    
    #if(!LED_PULSE_TYPE_HARDCODED)
        /* Writes density type provided by customizer */
        #if(LED_GREATERTHAN_OR_EQUAL == LED_COMPARE0)
            LED_CONTROL_REG |= LED_CTRL_COMPARE_TYPE0_GREATER_THAN_OR_EQUAL;
        #else
            LED_CONTROL_REG &= (uint8)~LED_CTRL_COMPARE_TYPE0_GREATER_THAN_OR_EQUAL;
        #endif /* End LED_COMPARE0 */    
    
        #if(LED_GREATERTHAN_OR_EQUAL == LED_COMPARE1)
            LED_CONTROL_REG |= LED_CTRL_COMPARE_TYPE1_GREATER_THAN_OR_EQUAL;
        #else
            LED_CONTROL_REG &= (uint8)~LED_CTRL_COMPARE_TYPE1_GREATER_THAN_OR_EQUAL;
        #endif /* End LED_COMPARE1 */    
    #endif /* End LED_PULSE_TYPE_HARDCODED */
}


/*******************************************************************************
* Function Name: LED_Enable
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
void LED_Enable(void) 
{
    #if(!LED_PULSE_TYPE_HARDCODED)
        /* Enable the PrISM computation */
        LED_CONTROL_REG |= LED_CTRL_ENABLE;
    #endif /* End LED_PULSE_TYPE_HARDCODED */
}


/*******************************************************************************
* FUNCTION NAME:   LED_Stop
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
void LED_Stop(void) 
{
    #if(!LED_PULSE_TYPE_HARDCODED)
        LED_CONTROL_REG &= (uint8)~LED_CTRL_ENABLE;
    #else
        /* PulseTypeHardoded option enabled - to stop PrISM use enable input */
    #endif /* End $INSTANCE_NAME`_PULSE_TYPE_HARDCODED */
}

#if(!LED_PULSE_TYPE_HARDCODED)


    /***************************************************************************
    * FUNCTION NAME:     LED_SetPulse0Mode
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
    void LED_SetPulse0Mode(uint8 pulse0Type) 
    {
        if(pulse0Type == LED_GREATERTHAN_OR_EQUAL)
        {
            LED_CONTROL_REG |= LED_CTRL_COMPARE_TYPE0_GREATER_THAN_OR_EQUAL;
        }
        else
        {
            LED_CONTROL_REG &= (uint8)~LED_CTRL_COMPARE_TYPE0_GREATER_THAN_OR_EQUAL;
        }
    }
    
    
    /***************************************************************************
    * FUNCTION NAME:   LED_SetPulse1Mode
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
    void LED_SetPulse1Mode(uint8 pulse1Type) 
    {
        if(pulse1Type == LED_GREATERTHAN_OR_EQUAL)
        {
            LED_CONTROL_REG |= LED_CTRL_COMPARE_TYPE1_GREATER_THAN_OR_EQUAL;
        }
        else
        {
            LED_CONTROL_REG &= (uint8)~LED_CTRL_COMPARE_TYPE1_GREATER_THAN_OR_EQUAL;
        }
    }

#endif /* End LED_PULSE_TYPE_HARDCODED == 0 */


/*******************************************************************************
* FUNCTION NAME:   LED_ReadSeed
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
uint16 LED_ReadSeed(void) 
{
    return( CY_GET_REG16(LED_SEED_PTR) );
}


/*******************************************************************************
* FUNCTION NAME:   LED_WriteSeed
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
void LED_WriteSeed(uint16 seed) 
{
    if(seed != 0u)
    {
        CY_SET_REG16(LED_SEED_COPY_PTR, seed);
        CY_SET_REG16(LED_SEED_PTR, seed);
    }
}


/*******************************************************************************
* FUNCTION NAME:   LED_ReadPolynomial
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
uint16 LED_ReadPolynomial(void) 
{
    return( CY_GET_REG16(LED_POLYNOM_PTR) );
}


/*******************************************************************************
* FUNCTION NAME:   LED_WritePolynomial
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
void LED_WritePolynomial(uint16 polynomial) \
                                                                
{
    CY_SET_REG16(LED_POLYNOM_PTR, polynomial);
    
}


/*******************************************************************************
* FUNCTION NAME:   LED_ReadPulse0
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
uint16 LED_ReadPulse0(void) 
{
    return( CY_GET_REG16(LED_DENSITY0_PTR) );
}


/*******************************************************************************
* FUNCTION NAME:   LED_WritePulse0
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
void LED_WritePulse0(uint16 pulseDensity0) \
                                                                
{
    CY_SET_REG16(LED_DENSITY0_PTR, pulseDensity0);
}


/*******************************************************************************
* FUNCTION NAME:   LED_ReadPulse1
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
uint16 LED_ReadPulse1(void) 
{
    return( CY_GET_REG16(LED_DENSITY1_PTR) );
}


/*******************************************************************************
* FUNCTION NAME:   LED_WritePulse1
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
void LED_WritePulse1(uint16 pulseDensity1) \
                                                                    
{
    CY_SET_REG16(LED_DENSITY1_PTR, pulseDensity1);
}


/* [] END OF FILE */
