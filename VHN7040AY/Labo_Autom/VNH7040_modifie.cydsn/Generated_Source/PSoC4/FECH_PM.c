/*******************************************************************************
* File Name: FECH_PM.c
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

#include "FECH.h"

static FECH_BACKUP_STRUCT FECH_backup;


/*******************************************************************************
* Function Name: FECH_SaveConfig
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
void FECH_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: FECH_Sleep
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
void FECH_Sleep(void)
{
    if(0u != (FECH_BLOCK_CONTROL_REG & FECH_MASK))
    {
        FECH_backup.enableState = 1u;
    }
    else
    {
        FECH_backup.enableState = 0u;
    }

    FECH_Stop();
    FECH_SaveConfig();
}


/*******************************************************************************
* Function Name: FECH_RestoreConfig
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
void FECH_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: FECH_Wakeup
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
void FECH_Wakeup(void)
{
    FECH_RestoreConfig();

    if(0u != FECH_backup.enableState)
    {
        FECH_Enable();
    }
}


/* [] END OF FILE */
