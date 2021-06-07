/*******************************************************************************
* File Name: sensrotation_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "sensrotation.h"

/* Check for removal by optimization */
#if !defined(sensrotation_Sync_ctrl_reg__REMOVED)

static sensrotation_BACKUP_STRUCT  sensrotation_backup = {0u};

    
/*******************************************************************************
* Function Name: sensrotation_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void sensrotation_SaveConfig(void) 
{
    sensrotation_backup.controlState = sensrotation_Control;
}


/*******************************************************************************
* Function Name: sensrotation_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void sensrotation_RestoreConfig(void) 
{
     sensrotation_Control = sensrotation_backup.controlState;
}


/*******************************************************************************
* Function Name: sensrotation_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void sensrotation_Sleep(void) 
{
    sensrotation_SaveConfig();
}


/*******************************************************************************
* Function Name: sensrotation_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void sensrotation_Wakeup(void)  
{
    sensrotation_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
