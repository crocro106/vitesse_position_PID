/*******************************************************************************
* File Name: DI_5.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_DI_5_H) /* Pins DI_5_H */
#define CY_PINS_DI_5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DI_5_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} DI_5_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DI_5_Read(void);
void    DI_5_Write(uint8 value);
uint8   DI_5_ReadDataReg(void);
#if defined(DI_5__PC) || (CY_PSOC4_4200L) 
    void    DI_5_SetDriveMode(uint8 mode);
#endif
void    DI_5_SetInterruptMode(uint16 position, uint16 mode);
uint8   DI_5_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DI_5_Sleep(void); 
void DI_5_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DI_5__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DI_5_DRIVE_MODE_BITS        (3)
    #define DI_5_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DI_5_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DI_5_SetDriveMode() function.
         *  @{
         */
        #define DI_5_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DI_5_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DI_5_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DI_5_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DI_5_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DI_5_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DI_5_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DI_5_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DI_5_MASK               DI_5__MASK
#define DI_5_SHIFT              DI_5__SHIFT
#define DI_5_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DI_5_SetInterruptMode() function.
     *  @{
     */
        #define DI_5_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DI_5_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DI_5_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DI_5_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DI_5__SIO)
    #define DI_5_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DI_5__PC) && (CY_PSOC4_4200L)
    #define DI_5_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DI_5_USBIO_DISABLE              ((uint32)(~DI_5_USBIO_ENABLE))
    #define DI_5_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DI_5_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DI_5_USBIO_ENTER_SLEEP          ((uint32)((1u << DI_5_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DI_5_USBIO_SUSPEND_DEL_SHIFT)))
    #define DI_5_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DI_5_USBIO_SUSPEND_SHIFT)))
    #define DI_5_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DI_5_USBIO_SUSPEND_DEL_SHIFT)))
    #define DI_5_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DI_5__PC)
    /* Port Configuration */
    #define DI_5_PC                 (* (reg32 *) DI_5__PC)
#endif
/* Pin State */
#define DI_5_PS                     (* (reg32 *) DI_5__PS)
/* Data Register */
#define DI_5_DR                     (* (reg32 *) DI_5__DR)
/* Input Buffer Disable Override */
#define DI_5_INP_DIS                (* (reg32 *) DI_5__PC2)

/* Interrupt configuration Registers */
#define DI_5_INTCFG                 (* (reg32 *) DI_5__INTCFG)
#define DI_5_INTSTAT                (* (reg32 *) DI_5__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DI_5_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DI_5__SIO)
    #define DI_5_SIO_REG            (* (reg32 *) DI_5__SIO)
#endif /* (DI_5__SIO_CFG) */

/* USBIO registers */
#if !defined(DI_5__PC) && (CY_PSOC4_4200L)
    #define DI_5_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DI_5_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DI_5_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DI_5_DRIVE_MODE_SHIFT       (0x00u)
#define DI_5_DRIVE_MODE_MASK        (0x07u << DI_5_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DI_5_H */


/* [] END OF FILE */
