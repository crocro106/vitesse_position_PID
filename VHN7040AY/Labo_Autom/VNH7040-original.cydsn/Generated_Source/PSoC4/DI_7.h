/*******************************************************************************
* File Name: DI_7.h  
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

#if !defined(CY_PINS_DI_7_H) /* Pins DI_7_H */
#define CY_PINS_DI_7_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DI_7_aliases.h"


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
} DI_7_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DI_7_Read(void);
void    DI_7_Write(uint8 value);
uint8   DI_7_ReadDataReg(void);
#if defined(DI_7__PC) || (CY_PSOC4_4200L) 
    void    DI_7_SetDriveMode(uint8 mode);
#endif
void    DI_7_SetInterruptMode(uint16 position, uint16 mode);
uint8   DI_7_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DI_7_Sleep(void); 
void DI_7_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DI_7__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DI_7_DRIVE_MODE_BITS        (3)
    #define DI_7_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DI_7_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DI_7_SetDriveMode() function.
         *  @{
         */
        #define DI_7_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DI_7_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DI_7_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DI_7_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DI_7_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DI_7_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DI_7_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DI_7_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DI_7_MASK               DI_7__MASK
#define DI_7_SHIFT              DI_7__SHIFT
#define DI_7_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DI_7_SetInterruptMode() function.
     *  @{
     */
        #define DI_7_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DI_7_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DI_7_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DI_7_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DI_7__SIO)
    #define DI_7_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DI_7__PC) && (CY_PSOC4_4200L)
    #define DI_7_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DI_7_USBIO_DISABLE              ((uint32)(~DI_7_USBIO_ENABLE))
    #define DI_7_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DI_7_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DI_7_USBIO_ENTER_SLEEP          ((uint32)((1u << DI_7_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DI_7_USBIO_SUSPEND_DEL_SHIFT)))
    #define DI_7_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DI_7_USBIO_SUSPEND_SHIFT)))
    #define DI_7_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DI_7_USBIO_SUSPEND_DEL_SHIFT)))
    #define DI_7_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DI_7__PC)
    /* Port Configuration */
    #define DI_7_PC                 (* (reg32 *) DI_7__PC)
#endif
/* Pin State */
#define DI_7_PS                     (* (reg32 *) DI_7__PS)
/* Data Register */
#define DI_7_DR                     (* (reg32 *) DI_7__DR)
/* Input Buffer Disable Override */
#define DI_7_INP_DIS                (* (reg32 *) DI_7__PC2)

/* Interrupt configuration Registers */
#define DI_7_INTCFG                 (* (reg32 *) DI_7__INTCFG)
#define DI_7_INTSTAT                (* (reg32 *) DI_7__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DI_7_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DI_7__SIO)
    #define DI_7_SIO_REG            (* (reg32 *) DI_7__SIO)
#endif /* (DI_7__SIO_CFG) */

/* USBIO registers */
#if !defined(DI_7__PC) && (CY_PSOC4_4200L)
    #define DI_7_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DI_7_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DI_7_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DI_7_DRIVE_MODE_SHIFT       (0x00u)
#define DI_7_DRIVE_MODE_MASK        (0x07u << DI_7_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DI_7_H */


/* [] END OF FILE */
