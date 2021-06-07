/*******************************************************************************
* File Name: AO.h  
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

#if !defined(CY_PINS_AO_H) /* Pins AO_H */
#define CY_PINS_AO_H

#include "cytypes.h"
#include "cyfitter.h"
#include "AO_aliases.h"


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
} AO_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   AO_Read(void);
void    AO_Write(uint8 value);
uint8   AO_ReadDataReg(void);
#if defined(AO__PC) || (CY_PSOC4_4200L) 
    void    AO_SetDriveMode(uint8 mode);
#endif
void    AO_SetInterruptMode(uint16 position, uint16 mode);
uint8   AO_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void AO_Sleep(void); 
void AO_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(AO__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define AO_DRIVE_MODE_BITS        (3)
    #define AO_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - AO_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the AO_SetDriveMode() function.
         *  @{
         */
        #define AO_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define AO_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define AO_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define AO_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define AO_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define AO_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define AO_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define AO_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define AO_MASK               AO__MASK
#define AO_SHIFT              AO__SHIFT
#define AO_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in AO_SetInterruptMode() function.
     *  @{
     */
        #define AO_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define AO_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define AO_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define AO_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(AO__SIO)
    #define AO_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(AO__PC) && (CY_PSOC4_4200L)
    #define AO_USBIO_ENABLE               ((uint32)0x80000000u)
    #define AO_USBIO_DISABLE              ((uint32)(~AO_USBIO_ENABLE))
    #define AO_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define AO_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define AO_USBIO_ENTER_SLEEP          ((uint32)((1u << AO_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << AO_USBIO_SUSPEND_DEL_SHIFT)))
    #define AO_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << AO_USBIO_SUSPEND_SHIFT)))
    #define AO_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << AO_USBIO_SUSPEND_DEL_SHIFT)))
    #define AO_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(AO__PC)
    /* Port Configuration */
    #define AO_PC                 (* (reg32 *) AO__PC)
#endif
/* Pin State */
#define AO_PS                     (* (reg32 *) AO__PS)
/* Data Register */
#define AO_DR                     (* (reg32 *) AO__DR)
/* Input Buffer Disable Override */
#define AO_INP_DIS                (* (reg32 *) AO__PC2)

/* Interrupt configuration Registers */
#define AO_INTCFG                 (* (reg32 *) AO__INTCFG)
#define AO_INTSTAT                (* (reg32 *) AO__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define AO_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(AO__SIO)
    #define AO_SIO_REG            (* (reg32 *) AO__SIO)
#endif /* (AO__SIO_CFG) */

/* USBIO registers */
#if !defined(AO__PC) && (CY_PSOC4_4200L)
    #define AO_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define AO_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define AO_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define AO_DRIVE_MODE_SHIFT       (0x00u)
#define AO_DRIVE_MODE_MASK        (0x07u << AO_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins AO_H */


/* [] END OF FILE */
