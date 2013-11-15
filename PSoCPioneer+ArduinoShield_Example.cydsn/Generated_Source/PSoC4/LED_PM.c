/*******************************************************************************
* File Name: LED_PM.c
* Version 2.20
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality of the PrISM component
*
* Note:
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
static LED_BACKUP_STRUCT  LED_backup = 
{
    /* enableState */
    0u,
    /* cr */
    #if(!LED_PULSE_TYPE_HARDCODED)
       (((LED_GREATERTHAN_OR_EQUAL == LED_COMPARE0) ? \
                                                LED_CTRL_COMPARE_TYPE0_GREATER_THAN_OR_EQUAL : 0u) |
        ((LED_GREATERTHAN_OR_EQUAL == LED_COMPARE1) ? \
                                                LED_CTRL_COMPARE_TYPE1_GREATER_THAN_OR_EQUAL : 0u)),
    #endif /* End LED_PULSE_TYPE_HARDCODED */
    /* seed */    
    LED_SEED,
    /* seed_copy */    
    LED_SEED,
    /* polynom */
    LED_POLYNOM,
    #if(CY_UDB_V0)
        /* density0 */
        LED_DENSITY0,
        /* density1 */
        LED_DENSITY1,
    #endif /*End CY_UDB_V0*/
};


/*******************************************************************************
* Function Name: LED_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*  
* Parameters:  
*  None.
*
* Return: 
*  None.
*
* Global Variables:
*  LED_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LED_SaveConfig(void) 
{
    #if (CY_UDB_V0)
        #if(!LED_PULSE_TYPE_HARDCODED)
            LED_backup.cr = LED_CONTROL_REG;
        #endif /* End LED_PULSE_TYPE_HARDCODED */
        LED_backup.seed = LED_ReadSeed();
        LED_backup.seed_copy = CY_GET_REG16(LED_SEED_COPY_PTR);
        LED_backup.polynom = LED_ReadPolynomial();
        LED_backup.density0 = LED_ReadPulse0();
        LED_backup.density1 = LED_ReadPulse1();
    #else /* CY_UDB_V1 */
        #if(!LED_PULSE_TYPE_HARDCODED)
            LED_backup.cr = LED_CONTROL_REG;
        #endif /* End LED_PULSE_TYPE_HARDCODED */
        LED_backup.seed = LED_ReadSeed();
        LED_backup.seed_copy = CY_GET_REG16(LED_SEED_COPY_PTR);
        LED_backup.polynom = LED_ReadPolynomial();
    #endif  /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: LED_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  None.
*
* Return: 
*  None.
*
* Global Variables:
*  LED_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void LED_RestoreConfig(void) 
{
    #if (CY_UDB_V0)
    
        uint8 enableInterrupts;
        
        #if(!LED_PULSE_TYPE_HARDCODED)
            LED_CONTROL_REG = LED_backup.cr;
        #endif /* End LED_PULSE_TYPE_HARDCODED */

        CY_SET_REG16(LED_SEED_COPY_PTR, LED_backup.seed_copy);
        CY_SET_REG16(LED_SEED_PTR, LED_backup.seed);
        LED_WritePolynomial(LED_backup.polynom);
        LED_WritePulse0(LED_backup.density0);
        LED_WritePulse1(LED_backup.density1);
        
        enableInterrupts = CyEnterCriticalSection();
        /* Set FIFO0_CLR bit to use FIFO0 as a simple one-byte buffer*/
        CY_SET_REG16(LED_AUX_CONTROL_PTR, 
                        CY_GET_REG16(LED_AUX_CONTROL_PTR) | LED_FIFO0_CLR);
        CyExitCriticalSection(enableInterrupts);

    #else   /* CY_UDB_V1 */

        #if(!LED_PULSE_TYPE_HARDCODED)
            LED_CONTROL_REG = LED_backup.cr;
        #endif /* End LED_PULSE_TYPE_HARDCODED */

        CY_SET_REG16(LED_SEED_COPY_PTR, LED_backup.seed_copy);
        CY_SET_REG16(LED_SEED_PTR, LED_backup.seed);
        LED_WritePolynomial(LED_backup.polynom);
    
    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: LED_Sleep
********************************************************************************
*
* Summary:
*  Stops and saves the user configuration
*  
* Parameters:  
*  None.
*
* Return: 
*  None.
*
* Global Variables:
*  LED_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LED_Sleep(void) 
{
    #if(!LED_PULSE_TYPE_HARDCODED)
        if((LED_CONTROL_REG & LED_CTRL_ENABLE) != 0u) 
        {
            LED_backup.enableState = 1u;
        }
        else
        {
            LED_backup.enableState = 0u;
        }
    #endif /* End LED_PULSE_TYPE_HARDCODED */
    LED_Stop();
    LED_SaveConfig();
}


/*******************************************************************************
* Function Name: LED_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  None.
*
* Return: 
*  None.
*
* Global Variables:
*  LED_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void LED_Wakeup(void) 
{
    LED_RestoreConfig();
    if(LED_backup.enableState != 0u)
    {
        LED_Enable();
    } 
}


/* [] END OF FILE */
