/*******************************************************************************
* File Name: QuadDec_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "QuadDec.h"

static QuadDec_backupStruct QuadDec_backup;


/*******************************************************************************
* Function Name: QuadDec_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  QuadDec_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void QuadDec_SaveConfig(void) 
{
    #if (!QuadDec_UsingFixedFunction)

        QuadDec_backup.CounterUdb = QuadDec_ReadCounter();

        #if(!QuadDec_ControlRegRemoved)
            QuadDec_backup.CounterControlRegister = QuadDec_ReadControlRegister();
        #endif /* (!QuadDec_ControlRegRemoved) */

    #endif /* (!QuadDec_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  QuadDec_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void QuadDec_RestoreConfig(void) 
{      
    #if (!QuadDec_UsingFixedFunction)

       QuadDec_WriteCounter(QuadDec_backup.CounterUdb);

        #if(!QuadDec_ControlRegRemoved)
            QuadDec_WriteControlRegister(QuadDec_backup.CounterControlRegister);
        #endif /* (!QuadDec_ControlRegRemoved) */

    #endif /* (!QuadDec_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  QuadDec_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void QuadDec_Sleep(void) 
{
    #if(!QuadDec_ControlRegRemoved)
        /* Save Counter's enable state */
        if(QuadDec_CTRL_ENABLE == (QuadDec_CONTROL & QuadDec_CTRL_ENABLE))
        {
            /* Counter is enabled */
            QuadDec_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            QuadDec_backup.CounterEnableState = 0u;
        }
    #else
        QuadDec_backup.CounterEnableState = 1u;
        if(QuadDec_backup.CounterEnableState != 0u)
        {
            QuadDec_backup.CounterEnableState = 0u;
        }
    #endif /* (!QuadDec_ControlRegRemoved) */
    
    QuadDec_Stop();
    QuadDec_SaveConfig();
}


/*******************************************************************************
* Function Name: QuadDec_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  QuadDec_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void QuadDec_Wakeup(void) 
{
    QuadDec_RestoreConfig();
    #if(!QuadDec_ControlRegRemoved)
        if(QuadDec_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            QuadDec_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!QuadDec_ControlRegRemoved) */
    
}


/* [] END OF FILE */
