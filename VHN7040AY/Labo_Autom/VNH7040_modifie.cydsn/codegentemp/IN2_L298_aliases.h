/*******************************************************************************
* File Name: IN2_L298.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_IN2_L298_ALIASES_H) /* Pins IN2_L298_ALIASES_H */
#define CY_PINS_IN2_L298_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define IN2_L298_0			(IN2_L298__0__PC)
#define IN2_L298_0_PS		(IN2_L298__0__PS)
#define IN2_L298_0_PC		(IN2_L298__0__PC)
#define IN2_L298_0_DR		(IN2_L298__0__DR)
#define IN2_L298_0_SHIFT	(IN2_L298__0__SHIFT)
#define IN2_L298_0_INTR	((uint16)((uint16)0x0003u << (IN2_L298__0__SHIFT*2u)))

#define IN2_L298_INTR_ALL	 ((uint16)(IN2_L298_0_INTR))


#endif /* End Pins IN2_L298_ALIASES_H */


/* [] END OF FILE */
