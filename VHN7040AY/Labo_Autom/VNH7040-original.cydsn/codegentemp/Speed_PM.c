/*******************************************************************************
* File Name: Speed_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Speed.h"

static Speed_BACKUP_STRUCT Speed_backup;


/*******************************************************************************
* Function Name: Speed_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Speed_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Speed_Sleep(void)
{
    if(0u != (Speed_BLOCK_CONTROL_REG & Speed_MASK))
    {
        Speed_backup.enableState = 1u;
    }
    else
    {
        Speed_backup.enableState = 0u;
    }

    Speed_Stop();
    Speed_SaveConfig();
}


/*******************************************************************************
* Function Name: Speed_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Speed_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: Speed_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Speed_Wakeup(void)
{
    Speed_RestoreConfig();

    if(0u != Speed_backup.enableState)
    {
        Speed_Enable();
    }
}


/* [] END OF FILE */
