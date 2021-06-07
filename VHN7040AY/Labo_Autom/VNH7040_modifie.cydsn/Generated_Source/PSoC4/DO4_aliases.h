/*******************************************************************************
* File Name: DO4.h  
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

#if !defined(CY_PINS_DO4_ALIASES_H) /* Pins DO4_ALIASES_H */
#define CY_PINS_DO4_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DO4_0			(DO4__0__PC)
#define DO4_0_PS		(DO4__0__PS)
#define DO4_0_PC		(DO4__0__PC)
#define DO4_0_DR		(DO4__0__DR)
#define DO4_0_SHIFT	(DO4__0__SHIFT)
#define DO4_0_INTR	((uint16)((uint16)0x0003u << (DO4__0__SHIFT*2u)))

#define DO4_INTR_ALL	 ((uint16)(DO4_0_INTR))


#endif /* End Pins DO4_ALIASES_H */


/* [] END OF FILE */
