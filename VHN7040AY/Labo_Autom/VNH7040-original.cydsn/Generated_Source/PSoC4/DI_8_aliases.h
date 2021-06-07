/*******************************************************************************
* File Name: DI_8.h  
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

#if !defined(CY_PINS_DI_8_ALIASES_H) /* Pins DI_8_ALIASES_H */
#define CY_PINS_DI_8_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DI_8_0			(DI_8__0__PC)
#define DI_8_0_PS		(DI_8__0__PS)
#define DI_8_0_PC		(DI_8__0__PC)
#define DI_8_0_DR		(DI_8__0__DR)
#define DI_8_0_SHIFT	(DI_8__0__SHIFT)
#define DI_8_0_INTR	((uint16)((uint16)0x0003u << (DI_8__0__SHIFT*2u)))

#define DI_8_INTR_ALL	 ((uint16)(DI_8_0_INTR))


#endif /* End Pins DI_8_ALIASES_H */


/* [] END OF FILE */
