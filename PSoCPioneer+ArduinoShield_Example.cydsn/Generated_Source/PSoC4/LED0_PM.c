/*******************************************************************************
* File Name: LED0_PM.c
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

#include "LED0.h"


/***************************************
* Local data allocation
***************************************/
static LED0_BACKUP_STRUCT  LED0_backup = 
{
    /* enableState */
    0u,
    /* cr */
    #if(!LED0_PULSE_TYPE_HARDCODED)
       (((LED0_GREATERTHAN_OR_EQUAL == LED0_COMPARE0) ? \
                                                LED0_CTRL_COMPARE_TYPE0_GREATER_THAN_OR_EQUAL : 0u) |
        ((LED0_GREATERTHAN_OR_EQUAL == LED0_COMPARE1) ? \
                                                LED0_CTRL_COMPARE_TYPE1_GREATER_THAN_OR_EQUAL : 0u)),
    #endif /* End LED0_PULSE_TYPE_HARDCODED */
    /* seed */    
    LED0_SEED,
    /* seed_copy */    
    LED0_SEED,
    /* polynom */
    LED0_POLYNOM,
    #if(CY_UDB_V0)
        /* density0 */
        LED0_DENSITY0,
        /* density1 */
        LED0_DENSITY1,
    #endif /*End CY_UDB_V0*/
};


/*******************************************************************************
* Function Name: LED0_SaveConfig
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
*  LED0_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LED0_SaveConfig(void) 
{
    #if (CY_UDB_V0)
        #if(!LED0_PULSE_TYPE_HARDCODED)
            LED0_backup.cr = LED0_CONTROL_REG;
        #endif /* End LED0_PULSE_TYPE_HARDCODED */
        LED0_backup.seed = LED0_ReadSeed();
        LED0_backup.seed_copy = CY_GET_REG8(LED0_SEED_COPY_PTR);
        LED0_backup.polynom = LED0_ReadPolynomial();
        LED0_backup.density0 = LED0_ReadPulse0();
        LED0_backup.density1 = LED0_ReadPulse1();
    #else /* CY_UDB_V1 */
        #if(!LED0_PULSE_TYPE_HARDCODED)
            LED0_backup.cr = LED0_CONTROL_REG;
        #endif /* End LED0_PULSE_TYPE_HARDCODED */
        LED0_backup.seed = LED0_ReadSeed();
        LED0_backup.seed_copy = CY_GET_REG8(LED0_SEED_COPY_PTR);
        LED0_backup.polynom = LED0_ReadPolynomial();
    #endif  /* CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: LED0_RestoreConfig
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
*  LED0_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void LED0_RestoreConfig(void) 
{
    #if (CY_UDB_V0)
    
        uint8 enableInterrupts;
        
        #if(!LED0_PULSE_TYPE_HARDCODED)
            LED0_CONTROL_REG = LED0_backup.cr;
        #endif /* End LED0_PULSE_TYPE_HARDCODED */

        CY_SET_REG8(LED0_SEED_COPY_PTR, LED0_backup.seed_copy);
        CY_SET_REG8(LED0_SEED_PTR, LED0_backup.seed);
        LED0_WritePolynomial(LED0_backup.polynom);
        LED0_WritePulse0(LED0_backup.density0);
        LED0_WritePulse1(LED0_backup.density1);
        
        enableInterrupts = CyEnterCriticalSection();
        /* Set FIFO0_CLR bit to use FIFO0 as a simple one-byte buffer*/
        CY_SET_REG8(LED0_AUX_CONTROL_PTR, 
                        CY_GET_REG8(LED0_AUX_CONTROL_PTR) | LED0_FIFO0_CLR);
        CyExitCriticalSection(enableInterrupts);

    #else   /* CY_UDB_V1 */

        #if(!LED0_PULSE_TYPE_HARDCODED)
            LED0_CONTROL_REG = LED0_backup.cr;
        #endif /* End LED0_PULSE_TYPE_HARDCODED */

        CY_SET_REG8(LED0_SEED_COPY_PTR, LED0_backup.seed_copy);
        CY_SET_REG8(LED0_SEED_PTR, LED0_backup.seed);
        LED0_WritePolynomial(LED0_backup.polynom);
    
    #endif  /* End CY_UDB_V0 */
}


/*******************************************************************************
* Function Name: LED0_Sleep
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
*  LED0_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void LED0_Sleep(void) 
{
    #if(!LED0_PULSE_TYPE_HARDCODED)
        if((LED0_CONTROL_REG & LED0_CTRL_ENABLE) != 0u) 
        {
            LED0_backup.enableState = 1u;
        }
        else
        {
            LED0_backup.enableState = 0u;
        }
    #endif /* End LED0_PULSE_TYPE_HARDCODED */
    LED0_Stop();
    LED0_SaveConfig();
}


/*******************************************************************************
* Function Name: LED0_Wakeup
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
*  LED0_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void LED0_Wakeup(void) 
{
    LED0_RestoreConfig();
    if(LED0_backup.enableState != 0u)
    {
        LED0_Enable();
    } 
}


/* [] END OF FILE */
