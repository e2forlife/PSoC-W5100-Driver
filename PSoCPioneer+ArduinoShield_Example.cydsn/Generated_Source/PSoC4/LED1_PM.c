/*******************************************************************************
* File Name: LED1_PM.c
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

#include "LED1.h"


/***************************************
* Local data allocation
***************************************/
static LED1_BACKUP_STRUCT  LED1_backup = 
{
    /* enableState */
    0u,
    /* cr */
    #if(!LED1_PULSE_TYPE_HARDCODED)
       (((LED1_GREATERTHAN_OR_EQUAL == LED1_COMPARE0) ? \
                                                LED1_CTRL_COMPARE_TYPE0_GREATER_THAN_OR_EQUAL : 0u) |
        ((LED1_GREATERTHAN_OR_EQUAL == LED1_COMPARE1) ? \
                                                LED1_CTRL_COMPARE_TYPE1_GREATER_THAN_OR_EQUAL : 0u)),
    #endif /* End LED1_PULSE_TYPE_HARDCODED */
    /* seed */    
    LED1_SEED,
    /* seed_copy */    
    LED1_SEED,
    /* polynom */
    LED1_POLYNOM,
    #if(CY_UDB_V0)
        /* density0 */
        LED1_DENSITY0,
        /* density1 */
        LED1_DENSITY1,
    #endif /*End CY_UDB_V0*/
};


/*******************************************************************************
* Function Name: LED1_SaveConfig
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
*  LED1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LED1_SaveConfig(void) 
{
    #if (CY_UDB_V0)
        #if(!LED1_PULSE_TYPE_HARDCODED)
            LED1_backup.cr = LED1_CONTROL_REG;
        #endif /* End LED1_PULSE_TYPE_HARDCODED */
        LED1_backup.seed = LED1_ReadSeed();
        LED1_backup.seed_copy = CY_GET_REG8(LED1_SEED_COPY_PTR);
        LED1_backup.polynom = LED1_ReadPolynomial();
        LED1_backup.density0 = LED1_ReadPulse0();
        LED1_backup.density1 = LED1_ReadPulse1();
    #else /* CY_UDB_V1 */
        #if(!LED1_PULSE_TYPE_HARDCODED)
            LED1_backup.cr = LED1_CONTROL_REG;
        #endif /* End LED1_PULSE_TYPE_HARDCODED */
        LED1_backup.seed = LED1_ReadSeed();
        LED1_backup.seed_copy = CY_GET_REG8(LED1_SEED_COPY_PTR);
        LED1_backup.polynom = LED1_ReadPolynomial();
    #endif  /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: LED1_RestoreConfig
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
*  LED1_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void LED1_RestoreConfig(void) 
{
    #if (CY_UDB_V0)
    
        uint8 enableInterrupts;
        
        #if(!LED1_PULSE_TYPE_HARDCODED)
            LED1_CONTROL_REG = LED1_backup.cr;
        #endif /* End LED1_PULSE_TYPE_HARDCODED */

        CY_SET_REG8(LED1_SEED_COPY_PTR, LED1_backup.seed_copy);
        CY_SET_REG8(LED1_SEED_PTR, LED1_backup.seed);
        LED1_WritePolynomial(LED1_backup.polynom);
        LED1_WritePulse0(LED1_backup.density0);
        LED1_WritePulse1(LED1_backup.density1);
        
        enableInterrupts = CyEnterCriticalSection();
        /* Set FIFO0_CLR bit to use FIFO0 as a simple one-byte buffer*/
        CY_SET_REG8(LED1_AUX_CONTROL_PTR, 
                        CY_GET_REG8(LED1_AUX_CONTROL_PTR) | LED1_FIFO0_CLR);
        CyExitCriticalSection(enableInterrupts);

    #else   /* CY_UDB_V1 */

        #if(!LED1_PULSE_TYPE_HARDCODED)
            LED1_CONTROL_REG = LED1_backup.cr;
        #endif /* End LED1_PULSE_TYPE_HARDCODED */

        CY_SET_REG8(LED1_SEED_COPY_PTR, LED1_backup.seed_copy);
        CY_SET_REG8(LED1_SEED_PTR, LED1_backup.seed);
        LED1_WritePolynomial(LED1_backup.polynom);
    
    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: LED1_Sleep
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
*  LED1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LED1_Sleep(void) 
{
    #if(!LED1_PULSE_TYPE_HARDCODED)
        if((LED1_CONTROL_REG & LED1_CTRL_ENABLE) != 0u) 
        {
            LED1_backup.enableState = 1u;
        }
        else
        {
            LED1_backup.enableState = 0u;
        }
    #endif /* End LED1_PULSE_TYPE_HARDCODED */
    LED1_Stop();
    LED1_SaveConfig();
}


/*******************************************************************************
* Function Name: LED1_Wakeup
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
*  LED1_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void LED1_Wakeup(void) 
{
    LED1_RestoreConfig();
    if(LED1_backup.enableState != 0u)
    {
        LED1_Enable();
    } 
}


/* [] END OF FILE */
