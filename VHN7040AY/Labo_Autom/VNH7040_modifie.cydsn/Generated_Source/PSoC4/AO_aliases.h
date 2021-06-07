/*******************************************************************************
* File Name: AO.h  
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

#if !defined(CY_PINS_AO_ALIASES_H) /* Pins AO_ALIASES_H */
#define CY_PINS_AO_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define AO_0			(AO__0__PC)
#define AO_0_PS		(AO__0__PS)
#define AO_0_PC		(AO__0__PC)
#define AO_0_DR		(AO__0__DR)
#define AO_0_SHIFT	(AO__0__SHIFT)
#define AO_0_INTR	((uint16)((uint16)0x0003u << (AO__0__SHIFT*2u)))

#define AO_INTR_ALL	 ((uint16)(AO_0_INTR))


#endif /* End Pins AO_ALIASES_H */


/* [] END OF FILE */
