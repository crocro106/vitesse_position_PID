/*******************************************************************************
* File Name: ENA_L298.h  
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

#if !defined(CY_PINS_ENA_L298_H) /* Pins ENA_L298_H */
#define CY_PINS_ENA_L298_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ENA_L298_aliases.h"


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
} ENA_L298_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ENA_L298_Read(void);
void    ENA_L298_Write(uint8 value);
uint8   ENA_L298_ReadDataReg(void);
#if defined(ENA_L298__PC) || (CY_PSOC4_4200L) 
    void    ENA_L298_SetDriveMode(uint8 mode);
#endif
void    ENA_L298_SetInterruptMode(uint16 position, uint16 mode);
uint8   ENA_L298_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ENA_L298_Sleep(void); 
void ENA_L298_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ENA_L298__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ENA_L298_DRIVE_MODE_BITS        (3)
    #define ENA_L298_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ENA_L298_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ENA_L298_SetDriveMode() function.
         *  @{
         */
        #define ENA_L298_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ENA_L298_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ENA_L298_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ENA_L298_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ENA_L298_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ENA_L298_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ENA_L298_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ENA_L298_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ENA_L298_MASK               ENA_L298__MASK
#define ENA_L298_SHIFT              ENA_L298__SHIFT
#define ENA_L298_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ENA_L298_SetInterruptMode() function.
     *  @{
     */
        #define ENA_L298_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ENA_L298_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ENA_L298_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ENA_L298_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ENA_L298__SIO)
    #define ENA_L298_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ENA_L298__PC) && (CY_PSOC4_4200L)
    #define ENA_L298_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ENA_L298_USBIO_DISABLE              ((uint32)(~ENA_L298_USBIO_ENABLE))
    #define ENA_L298_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ENA_L298_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ENA_L298_USBIO_ENTER_SLEEP          ((uint32)((1u << ENA_L298_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ENA_L298_USBIO_SUSPEND_DEL_SHIFT)))
    #define ENA_L298_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ENA_L298_USBIO_SUSPEND_SHIFT)))
    #define ENA_L298_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ENA_L298_USBIO_SUSPEND_DEL_SHIFT)))
    #define ENA_L298_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ENA_L298__PC)
    /* Port Configuration */
    #define ENA_L298_PC                 (* (reg32 *) ENA_L298__PC)
#endif
/* Pin State */
#define ENA_L298_PS                     (* (reg32 *) ENA_L298__PS)
/* Data Register */
#define ENA_L298_DR                     (* (reg32 *) ENA_L298__DR)
/* Input Buffer Disable Override */
#define ENA_L298_INP_DIS                (* (reg32 *) ENA_L298__PC2)

/* Interrupt configuration Registers */
#define ENA_L298_INTCFG                 (* (reg32 *) ENA_L298__INTCFG)
#define ENA_L298_INTSTAT                (* (reg32 *) ENA_L298__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ENA_L298_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ENA_L298__SIO)
    #define ENA_L298_SIO_REG            (* (reg32 *) ENA_L298__SIO)
#endif /* (ENA_L298__SIO_CFG) */

/* USBIO registers */
#if !defined(ENA_L298__PC) && (CY_PSOC4_4200L)
    #define ENA_L298_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ENA_L298_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ENA_L298_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ENA_L298_DRIVE_MODE_SHIFT       (0x00u)
#define ENA_L298_DRIVE_MODE_MASK        (0x07u << ENA_L298_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ENA_L298_H */


/* [] END OF FILE */
