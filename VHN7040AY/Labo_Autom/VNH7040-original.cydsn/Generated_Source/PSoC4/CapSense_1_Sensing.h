/***************************************************************************//**
* \file CapSense_1_Sensing.h
* \version 4.10
*
* \brief
* This file provides the headers of APIs specific to implementation of the
* sensing FW block.
*
* \see CapSense_1 v4.10 Datasheet
*
*//*****************************************************************************
* Copyright (2016-2017), Cypress Semiconductor Corporation.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*******************************************************************************/

#if !defined(CY_SENSE_CapSense_1_SENSING_H)
#define CY_SENSE_CapSense_1_SENSING_H

#include <CyLib.h>
#include <cyfitter.h>
#include "cytypes.h"
#include "CapSense_1_Configuration.h"
#include "CapSense_1_Structure.h"
#if (CapSense_1_DISABLE == CapSense_1_CSD2X_EN)
    #include "CapSense_1_ISR.h"
#endif /* (CapSense_1_DISABLE == CapSense_1_CSD2X_EN) */

#if (CapSense_1_ENABLE == CapSense_1_CSX_EN)
    #include "CapSense_1_SensingCSX_LL.h"
#endif /* (CapSense_1_ENABLE == CapSense_1_CSX_EN) */
#if (CapSense_1_ENABLE == CapSense_1_ISX_EN)
    #include "CapSense_1_SensingISX_LL.h"
#endif /* (CapSense_1_ENABLE == CapSense_1_ISX_EN) */
#if (CapSense_1_ENABLE == CapSense_1_CSD_EN)
    #include "CapSense_1_SensingCSD_LL.h"
#endif /* (CapSense_1_ENABLE == CapSense_1_CSD_EN) */
#if (CapSense_1_ENABLE == CapSense_1_CSD2X_EN)
    #include "CapSense_1_SensingCSD2X_LL.h"
#endif /* (CapSense_1_ENABLE == CapSense_1_CSD2X_EN) */
#if (CapSense_1_CSD_SS_DIS != CapSense_1_CSD_AUTOTUNE)
    #include "CapSense_1_SmartSense_LL.h"
#endif  /* (CapSense_1_CSD_SS_DIS != CapSense_1_CSD_AUTOTUNE) */
#if (CapSense_1_ENABLE == CapSense_1_ADC_EN)
    #include "CapSense_1_Adc.h"
#endif /* (CapSense_1_ENABLE == CapSense_1_ADC_EN) */

/*******************************************************************************
* Enumeration types definition
*******************************************************************************/

/* Pin states */
#define CapSense_1_GROUND                         (0u)
#define CapSense_1_HIGHZ                          (1u)
#define CapSense_1_SHIELD                         (2u)
#define CapSense_1_SENSOR                         (3u)
#define CapSense_1_TX_PIN                         (4u)
#define CapSense_1_RX_PIN                         (5u)

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
* \cond (SECTION_C_HIGH_LEVEL || SECTION_I_HIGH_LEVEL)
* \addtogroup group_c_high_level
* \{
*/

cystatus CapSense_1_SetupWidget(uint32 widgetId);
cystatus CapSense_1_Scan(void);
cystatus CapSense_1_ScanAllWidgets(void);
uint32 CapSense_1_IsBusy(void);

/** \}
* \endcond */

/**
* \cond (SECTION_C_LOW_LEVEL || SECTION_I_LOW_LEVEL)
* \addtogroup group_c_low_level
* \{
*/

void CapSense_1_SetPinState(uint32 widgetId, uint32 sensorElement, uint32 state);
#if (CapSense_1_ANYMODE_AUTOCAL)
    cystatus CapSense_1_CalibrateWidget(uint32 widgetId);
    cystatus CapSense_1_CalibrateAllWidgets(void);
#endif /* (CapSense_1_ANYMODE_AUTOCAL)  */

/** \}
* \endcond */

/**
* \cond SECTION_C_INTERNAL
* \addtogroup group_c_internal
* \{
*/

cystatus CapSense_1_SsInitialize(void);
void CapSense_1_SsSetModClkClockDivider(uint32 modClk);
void CapSense_1_SsSetSnsClockDivider(uint32 snsClk);
void CapSense_1_SsSetClockDividers(uint32 snsClk, uint32 modClk);
void CapSense_1_SsIsrInitialize(cyisraddress address);
void CapSense_1_SsPostAllWidgetsScan(void);
void CapSense_1_SsSetIOsInDefaultState(void);
#if ((CapSense_1_ENABLE == CapSense_1_CSD_CSX_EN) || \
     (CapSense_1_ENABLE == CapSense_1_CSD_ISX_EN) || \
     (CapSense_1_ENABLE == CapSense_1_SELF_TEST_EN) || \
     (CapSense_1_ENABLE == CapSense_1_ADC_EN))
    void CapSense_1_SsSwitchSensingMode(CapSense_1_SENSE_METHOD_ENUM mode);
#endif  /* ((CapSense_1_ENABLE == CapSense_1_CSD_CSX_EN) || \
            (CapSense_1_ENABLE == CapSense_1_SELF_TEST_EN) || \
            (CapSense_1_ENABLE == CapSense_1_ADC_EN)) */
#if (CapSense_1_CSD_SS_DIS != CapSense_1_CSD_AUTOTUNE)
    cystatus CapSense_1_SsAutoTune(void);
#endif /* (CapSense_1_CSD_SS_DIS != CapSense_1_CSD_AUTOTUNE) */
#if (CapSense_1_ENABLE == CapSense_1_MULTI_FREQ_SCAN_EN)
    void CapSense_1_SsChangeImoFreq(uint32 value);
#endif  /* (CapSense_1_ENABLE == CapSense_1_MULTI_FREQ_SCAN_EN) */
#if (CapSense_1_ENABLE == CapSense_1_ADC_EN)
    cystatus CapSense_1_SsReleaseResources(void);
#endif  /* (CapSense_1_ENABLE == CapSense_1_ADC_EN) */

void CapSense_1_SsSetIOsInDefaultState(void);

#if((CapSense_1_ENABLE == CapSense_1_CSD_EN) ||\
    (CapSense_1_ENABLE == CapSense_1_CSD2X_EN) ||\
    (((CapSense_1_ENABLE == CapSense_1_CSX_EN) || (CapSense_1_ENABLE == CapSense_1_ISX_EN)) && (CapSense_1_ENABLE == CapSense_1_CSDV2)))
    void CapSense_1_SsInitializeSourceSenseClk(void);
#endif /* ((CapSense_1_ENABLE == CapSense_1_CSD_EN) ||\
           (CapSense_1_ENABLE == CapSense_1_CSD2X_EN) ||\
           ((CapSense_1_ENABLE == CapSense_1_CSX_EN) && (CapSense_1_ENABLE == CapSense_1_CSDV2))) */
#if ((CapSense_1_ENABLE == CapSense_1_CSD_EN) ||\
    (CapSense_1_ENABLE == CapSense_1_CSD2X_EN))
    void CapSense_1_SsClearCSDSensors(void);
    uint32 CapSense_1_SsCSDGetColSnsClkDivider(uint32 widgetId);
    #if (CapSense_1_ENABLE == (CapSense_1_CSD_MATRIX_WIDGET_EN || CapSense_1_CSD_TOUCHPAD_WIDGET_EN))
        uint32 CapSense_1_SsCSDGetRowSnsClkDivider(uint32 widgetId);
    #endif /* (CapSense_1_ENABLE == (CapSense_1_CSD_MATRIX_WIDGET_EN || CapSense_1_CSD_TOUCHPAD_WIDGET_EN)) */
    #if (CapSense_1_CLK_SOURCE_PRSAUTO == CapSense_1_CSD_SNS_CLK_SOURCE)
        uint8 CapSense_1_SsCSDCalcPrsSize(uint32 snsClkDivider, uint32 resolution);
    #endif /* (CapSense_1_CLK_SOURCE_PRSAUTO == CapSense_1_CSD_SNS_CLK_SOURCE) */
#endif /* ((CapSense_1_ENABLE == CapSense_1_CSD_EN) ||\
           (CapSense_1_ENABLE == CapSense_1_CSD2X_EN)) */

/** \}
* \endcond */


/****************************************************************************
* m0s8csd, m0s8peri, hsiom, and IO hardware-related registers address
****************************************************************************/

#define CapSense_1_DR_MASK                                (0x00000001Lu)

#if (CapSense_1_ENABLE == CapSense_1_CSDV2)

    /* CSDv2 block registers   */
    #define CapSense_1_CONFIG_REG                         (*(reg32 *) CYREG_CSD_CONFIG)
    #define CapSense_1_CONFIG_PTR                         ( (reg32 *) CYREG_CSD_CONFIG)

    #define CapSense_1_STAT_SEQ_REG                       (*(reg32 *) CYREG_CSD_CONFIG)
    #define CapSense_1_STAT_SEQ_PTR                       ( (reg32 *) CYREG_CSD_CONFIG)

    #define CapSense_1_IDAC_MOD_REG                       (*(reg32 *) CYREG_CSD_IDACA)
    #define CapSense_1_IDAC_MOD_PTR                       ( (reg32 *) CYREG_CSD_IDACA)

    #define CapSense_1_IDAC_COMP_REG                      (*(reg32 *) CYREG_CSD_IDACB)
    #define CapSense_1_IDAC_COMP_PTR                      ( (reg32 *) CYREG_CSD_IDACB)

    #define CapSense_1_SENSE_PERIOD_REG                   (*(reg32 *) CYREG_CSD_SENSE_PERIOD)
    #define CapSense_1_SENSE_PERIOD_PTR                   ( (reg32 *) CYREG_CSD_SENSE_PERIOD)

    #define CapSense_1_RESULT_VAL1_REG                    (*(reg32 *) CYREG_CSD_RESULT_VAL1)
    #define CapSense_1_RESULT_VAL1_PTR                    ( (reg32 *) CYREG_CSD_RESULT_VAL1)

    #define CapSense_1_RESULT_VAL2_REG                    (*(reg32 *) CYREG_CSD_RESULT_VAL2)
    #define CapSense_1_RESULT_VAL2_PTR                    ( (reg32 *) CYREG_CSD_RESULT_VAL2)

    #define CapSense_1_INTR_REG                           (*(reg32 *) CYREG_CSD_INTR)
    #define CapSense_1_INTR_PTR                           ( (reg32 *) CYREG_CSD_INTR)

    #define CapSense_1_INTR_SET_REG                       (*(reg32 *) CYREG_CSD_INTR_SET)
    #define CapSense_1_INTR_SET_PTR                       ( (reg32 *) CYREG_CSD_INTR_SET)

    #define CapSense_1_INTR_MASK_REG                      (*(reg32 *) CYREG_CSD_INTR_MASK)
    #define CapSense_1_INTR_MASK_PTR                      ( (reg32 *) CYREG_CSD_INTR_MASK)

    #define CapSense_1_COUNTER_REG                        (CapSense_1_RESULT_VAL1_REG)
    #define CapSense_1_COUNTER_PTR                        (CapSense_1_RESULT_VAL1_PTR)

    #define CapSense_1_REFGEN_REG                         (*(reg32 *) CYREG_CSD_REFGEN)
    #define CapSense_1_REFGEN_PTR                         ( (reg32 *) CYREG_CSD_REFGEN)

    #define CapSense_1_SEQ_TIME_REG                       (*(reg32 *) CYREG_CSD_SEQ_TIME)
    #define CapSense_1_SEQ_TIME_PTR                       ( (reg32 *) CYREG_CSD_SEQ_TIME)

    #define CapSense_1_SEQ_INIT_CNT_REG                   (*(reg32 *) CYREG_CSD_SEQ_INIT_CNT)
    #define CapSense_1_SEQ_INIT_CNT_PTR                   ( (reg32 *) CYREG_CSD_SEQ_INIT_CNT)

    #define CapSense_1_SEQ_NORM_CNT_REG                   (*(reg32 *) CYREG_CSD_SEQ_NORM_CNT)
    #define CapSense_1_SEQ_NORM_CNT_PTR                   ( (reg32 *) CYREG_CSD_SEQ_NORM_CNT)

    #define CapSense_1_SEQ_START_REG                      (*(reg32 *) CYREG_CSD_SEQ_START)
    #define CapSense_1_SEQ_START_PTR                      ( (reg32 *) CYREG_CSD_SEQ_START)

    #define CapSense_1_CSDCMP_REG                         (*(reg32 *) CYREG_CSD_CSDCMP)
    #define CapSense_1_CSDCMP_PTR                         ( (reg32 *) CYREG_CSD_CSDCMP)

    #define CapSense_1_HSCMP_REG                          (*(reg32 *) CYREG_CSD_HSCMP)
    #define CapSense_1_HSCMP_PTR                          ( (reg32 *) CYREG_CSD_HSCMP)

    #define CapSense_1_SENSE_DUTY_REG                     (*(reg32 *) CYREG_CSD_SENSE_DUTY)
    #define CapSense_1_SENSE_DUTY_PTR                     ( (reg32 *) CYREG_CSD_SENSE_DUTY)

    #define CapSense_1_AMBUF_REG                          (*(reg32 *) CYREG_CSD_AMBUF)
    #define CapSense_1_AMBUF_PTR                          ( (reg32 *) CYREG_CSD_AMBUF)

    #define CapSense_1_SW_BYP_SEL_REG                     (*(reg32 *) CYREG_CSD_SW_BYP_SEL)
    #define CapSense_1_SW_BYP_SEL_PTR                     ( (reg32 *) CYREG_CSD_SW_BYP_SEL)

    #define CapSense_1_SW_CMP_P_SEL_REG                   (*(reg32 *) CYREG_CSD_SW_CMP_P_SEL)
    #define CapSense_1_SW_CMP_P_SEL_PTR                   ( (reg32 *) CYREG_CSD_SW_CMP_P_SEL)

    #define CapSense_1_SW_REFGEN_SEL_REG                  (*(reg32 *) CYREG_CSD_SW_REFGEN_SEL)
    #define CapSense_1_SW_REFGEN_SEL_PTR                  ( (reg32 *) CYREG_CSD_SW_REFGEN_SEL)

    #define CapSense_1_SW_CMP_N_SEL_REG                   (*(reg32 *) CYREG_CSD_SW_CMP_N_SEL)
    #define CapSense_1_SW_CMP_N_SEL_PTR                   ( (reg32 *) CYREG_CSD_SW_CMP_N_SEL)

    #define CapSense_1_SW_RES_REG                         (*(reg32 *) CYREG_CSD_SW_RES)
    #define CapSense_1_SW_RES_PTR                         ( (reg32 *) CYREG_CSD_SW_RES)

    #define CapSense_1_SW_HS_P_SEL_REG                    (*(reg32 *) CYREG_CSD_SW_HS_P_SEL)
    #define CapSense_1_SW_HS_P_SEL_PTR                    ( (reg32 *) CYREG_CSD_SW_HS_P_SEL)

    #define CapSense_1_SW_SHIELD_SEL_REG                  (*(reg32 *) CYREG_CSD_SW_SHIELD_SEL)
    #define CapSense_1_SW_SHIELD_SEL_PTR                  ( (reg32 *) CYREG_CSD_SW_SHIELD_SEL)

    #define CapSense_1_SW_AMUXBUF_SEL_REG                 (*(reg32 *) CYREG_CSD_SW_AMUXBUF_SEL)
    #define CapSense_1_SW_AMUXBUF_SEL_PTR                 ( (reg32 *) CYREG_CSD_SW_AMUXBUF_SEL)

    #define CapSense_1_SW_HS_N_SEL_REG                    (*(reg32 *) CYREG_CSD_SW_HS_N_SEL)
    #define CapSense_1_SW_HS_N_SEL_PTR                    ( (reg32 *) CYREG_CSD_SW_HS_N_SEL)

    #define CapSense_1_SW_FW_MOD_SEL_REG                  (*(reg32 *) CYREG_CSD_SW_FW_MOD_SEL)
    #define CapSense_1_SW_FW_MOD_SEL_PTR                  ( (reg32 *) CYREG_CSD_SW_FW_MOD_SEL)

    #define CapSense_1_SW_FW_TANK_SEL_REG                 (*(reg32 *) CYREG_CSD_SW_FW_TANK_SEL)
    #define CapSense_1_SW_FW_TANK_SEL_PTR                 ( (reg32 *) CYREG_CSD_SW_FW_TANK_SEL)

    #define CapSense_1_SW_DSI_SEL_REG                     (*(reg32 *) CYREG_CSD_SW_DSI_SEL)
    #define CapSense_1_SW_DSI_SEL_PTR                     ( (reg32 *) CYREG_CSD_SW_DSI_SEL)

    #define CapSense_1_ADC_CTL_REG                        (*(reg32 *) CYREG_CSD_ADC_CTL)
    #define CapSense_1_ADC_CTL_PTR                        ( (reg32 *) CYREG_CSD_ADC_CTL)
#else

    #if (CapSense_1_ENABLE == CapSense_1_CSD2X_EN)
        /* CSD0 block registers   */
        #define CapSense_1_CONFIG_REG                     (*(reg32 *) CapSense_1_CSD0__CSD_CONFIG)
        #define CapSense_1_CONFIG_PTR                     ( (reg32 *) CapSense_1_CSD0__CSD_CONFIG)
        #define CapSense_1_IDAC_CONTR_REG                 (*(reg32 *) CapSense_1_IDACMod0_cy_psoc4_idac__CONTROL)
        #define CapSense_1_IDAC_CONTR_PTR                 ( (reg32 *) CapSense_1_IDACMod0_cy_psoc4_idac__CONTROL)
        #define CapSense_1_IDAC_REG                       (*(reg32 *) CapSense_1_IDACMod0_cy_psoc4_idac__CSD_IDAC)
        #define CapSense_1_IDAC_PTR                       ( (reg32 *) CapSense_1_IDACMod0_cy_psoc4_idac__CSD_IDAC)
        #define CapSense_1_COUNTER_REG                    (*(reg32 *) CapSense_1_CSD0__CSD_COUNTER)
        #define CapSense_1_COUNTER_PTR                    ( (reg32 *) CapSense_1_CSD0__CSD_COUNTER)
        #define CapSense_1_STATUS_REG                     (*(reg32 *) CapSense_1_CSD0__CSD_STATUS)
        #define CapSense_1_STATUS_PTR                     ( (reg32 *) CapSense_1_CSD0__CSD_STATUS)
        #define CapSense_1_INTR_REG                       (*(reg32 *) CapSense_1_CSD0__CSD_INTR)
        #define CapSense_1_INTR_PTR                       ( (reg32 *) CapSense_1_CSD0__CSD_INTR)
        #define CapSense_1_INTR_SET_REG                   (*(reg32 *) CapSense_1_CSD0__CSD_INTR_SET)
        #define CapSense_1_INTR_SET_PTR                   ( (reg32 *) CapSense_1_CSD0__CSD_INTR_SET)
        #define CapSense_1_PWM_REG                        (*(reg32 *) CapSense_1_CSD0__CSD_PWM)
        #define CapSense_1_PWM_PTR                        ( (reg32 *) CapSense_1_CSD0__CSD_PWM)
        #define CapSense_1_TRIM1_REG                      (*(reg32 *) CapSense_1_IDACMod0_cy_psoc4_idac__CSD_TRIM1)
        #define CapSense_1_TRIM1_PTR                      ( (reg32 *) CapSense_1_IDACMod0_cy_psoc4_idac__CSD_TRIM1)
        #define CapSense_1_TRIM2_REG                      (*(reg32 *) CapSense_1_IDACMod0_cy_psoc4_idac__CSD_TRIM2)
        #define CapSense_1_TRIM2_PTR                      ( (reg32 *) CapSense_1_IDACMod0_cy_psoc4_idac__CSD_TRIM2)
    #else
        /* CSD block registers   */
        #define CapSense_1_CONFIG_REG                     (*(reg32 *) CapSense_1_CSD__CSD_CONFIG)
        #define CapSense_1_CONFIG_PTR                     ( (reg32 *) CapSense_1_CSD__CSD_CONFIG)
        #define CapSense_1_IDAC_CONTR_REG                 (*(reg32 *) CapSense_1_IDACMod_cy_psoc4_idac__CONTROL)
        #define CapSense_1_IDAC_CONTR_PTR                 ( (reg32 *) CapSense_1_IDACMod_cy_psoc4_idac__CONTROL)
        #define CapSense_1_IDAC_REG                       (*(reg32 *) CapSense_1_IDACMod_cy_psoc4_idac__CSD_IDAC)
        #define CapSense_1_IDAC_PTR                       ( (reg32 *) CapSense_1_IDACMod_cy_psoc4_idac__CSD_IDAC)
        #define CapSense_1_COUNTER_REG                    (*(reg32 *) CapSense_1_CSD__CSD_COUNTER)
        #define CapSense_1_COUNTER_PTR                    ( (reg32 *) CapSense_1_CSD__CSD_COUNTER)
        #define CapSense_1_STATUS_REG                     (*(reg32 *) CapSense_1_CSD__CSD_STATUS)
        #define CapSense_1_STATUS_PTR                     ( (reg32 *) CapSense_1_CSD__CSD_STATUS)
        #define CapSense_1_INTR_REG                       (*(reg32 *) CapSense_1_CSD__CSD_INTR)
        #define CapSense_1_INTR_PTR                       ( (reg32 *) CapSense_1_CSD__CSD_INTR)
        #define CapSense_1_INTR_SET_REG                   (*(reg32 *) CYREG_CSD_INTR_SET)
        #define CapSense_1_INTR_SET_PTR                   ( (reg32 *) CYREG_CSD_INTR_SET)
        #define CapSense_1_PWM_REG                        (*(reg32 *) CYREG_CSD_PWM)
        #define CapSense_1_PWM_PTR                        ( (reg32 *) CYREG_CSD_PWM)
        #define CapSense_1_TRIM1_REG                      (*(reg32 *) CapSense_1_IDACMod_cy_psoc4_idac__CSD_TRIM1)
        #define CapSense_1_TRIM1_PTR                      ( (reg32 *) CapSense_1_IDACMod_cy_psoc4_idac__CSD_TRIM1)
        #define CapSense_1_TRIM2_REG                      (*(reg32 *) CapSense_1_IDACMod_cy_psoc4_idac__CSD_TRIM2)
        #define CapSense_1_TRIM2_PTR                      ( (reg32 *) CapSense_1_IDACMod_cy_psoc4_idac__CSD_TRIM2)
    #endif /* (CapSense_1_ENABLE == CapSense_1_CSD2X_EN) */

    #if (CapSense_1_DISABLE == CapSense_1_CSD2X_EN)
        #if (CY_PSOC4_4100M || CY_PSOC4_4200M || CY_PSOC4_4200L)
            #if (1u != CapSense_1_CSD__CSD_NUMBER)
                #define CapSense_1_SFLASH_TRIM1_REG           (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)
                #define CapSense_1_SFLASH_TRIM1_PTR           ( (reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)

                #define CapSense_1_SFLASH_TRIM2_REG           (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
                #define CapSense_1_SFLASH_TRIM2_PTR           ( (reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
            #else
                #define CapSense_1_SFLASH_TRIM1_REG           (*(reg8 *) CYREG_SFLASH_CSD1_TRIM1_CSD)
                #define CapSense_1_SFLASH_TRIM1_PTR           ( (reg8 *) CYREG_SFLASH_CSD1_TRIM1_CSD)

                #define CapSense_1_SFLASH_TRIM2_REG           (*(reg8 *) CYREG_SFLASH_CSD1_TRIM2_CSD)
                #define CapSense_1_SFLASH_TRIM2_PTR           ( (reg8 *) CYREG_SFLASH_CSD1_TRIM2_CSD)
            #endif /* (1u != CapSense_1_CSD__CSD_NUMBER) */
        #else
            #define CapSense_1_SFLASH_TRIM1_REG               (*(reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)
            #define CapSense_1_SFLASH_TRIM1_PTR               ( (reg8 *) CYREG_SFLASH_CSD_TRIM1_CSD)

            #define CapSense_1_SFLASH_TRIM2_REG               (*(reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
            #define CapSense_1_SFLASH_TRIM2_PTR               ( (reg8 *) CYREG_SFLASH_CSD_TRIM2_CSD)
        #endif /* (CY_PSOC4_4100M || CY_PSOC4_4200M || CY_PSOC4_4200L) */
    #endif /* (CapSense_1_DISABLE == CapSense_1_CSD2X_EN) */
#endif /* (CapSense_1_ENABLE == CapSense_1_CSDV2) */

/* CSDv1 and CSDv2 PERI CLOCK registers */
#if defined(CYIPBLOCK_m0s8peri_VERSION)
    #define CapSense_1_IS_M0S8PERI_BLOCK                  (1u)
    #define CapSense_1_M0S8PERI_BLOCK_VER                 ((CYIPBLOCK_m0s8peri_VERSION))
#else
    #define CapSense_1_IS_M0S8PERI_BLOCK                  (0u)
    #define CapSense_1_M0S8PERI_BLOCK_VER                 (0u)
#endif /* (CYIPBLOCK_m0s8peri_VERSION) */

#if (CapSense_1_ENABLE == CapSense_1_IS_M0S8PERI_BLOCK)
    #define CapSense_1_MODCLK_DIV_REG                     (*(reg32 *)CapSense_1_ModClk__DIV_REGISTER)
    #define CapSense_1_MODCLK_DIV_PTR                     ( (reg32 *)CapSense_1_ModClk__DIV_REGISTER)
    #define CapSense_1_MODCLK_CMD_REG                     (*(reg32 *)CYREG_PERI_DIV_CMD)
    #define CapSense_1_MODCLK_CMD_PTR                     ( (reg32 *)CYREG_PERI_DIV_CMD)
    #if (CapSense_1_DISABLE == CapSense_1_CSDV2)
        #define CapSense_1_SNSCLK_DIV_REG                 (*(reg32 *)CapSense_1_SnsClk__DIV_REGISTER)
        #define CapSense_1_SNSCLK_DIV_PTR                 ( (reg32 *)CapSense_1_SnsClk__DIV_REGISTER)
        #define CapSense_1_SNSCLK_CMD_REG                 (*(reg32 *)CYREG_PERI_DIV_CMD)
        #define CapSense_1_SNSCLK_CMD_PTR                 ( (reg32 *)CYREG_PERI_DIV_CMD)
    #endif /* (CapSense_1_DISABLE == CapSense_1_CSDV2) */
#else
    #define CapSense_1_MODCLK_DIV_REG                     (*(reg32 *)CapSense_1_ModClk__REGISTER)
    #define CapSense_1_MODCLK_DIV_PTR                     ( (reg32 *)CapSense_1_ModClk__REGISTER)
    #define CapSense_1_SNSCLK_DIV_REG                     (*(reg32 *)CapSense_1_SnsClk__REGISTER)
    #define CapSense_1_SNSCLK_DIV_PTR                     ( (reg32 *)CapSense_1_SnsClk__REGISTER)
    #define CapSense_1_MODCLK_CMD_REG                     (CapSense_1_MODCLK_DIV_REG)
    #define CapSense_1_MODCLK_CMD_PTR                     (CapSense_1_MODCLK_DIV_PTR)
    #define CapSense_1_SNSCLK_CMD_REG                     (CapSense_1_SNSCLK_DIV_REG)
    #define CapSense_1_SNSCLK_CMD_PTR                     (CapSense_1_SNSCLK_DIV_PTR)
#endif /* (CapSense_1_ENABLE == CapSense_1_IS_M0S8PERI_BLOCK) */

/****************************************************************************
* m0s8csd, m0s8peri, hsiom, and IO hardware-related registers masks
****************************************************************************/
#if (CapSense_1_ENABLE == CapSense_1_CSDV2)

    #if(0u != CapSense_1_CSX_EN)
        #define CapSense_1_CMOD_CONNECTION                (CapSense_1_CSD__CSHIELD_PAD)
    #else
        #define CapSense_1_CMOD_CONNECTION                (CapSense_1_CSD__DEDICATED_IO0)
    #endif /* (CapSense_1_CSX_EN == 1u) */

    #if ((CapSense_1_ENABLE == CapSense_1_CSD_SHIELD_EN) && \
         (CapSense_1_ENABLE == CapSense_1_CSD_SHIELD_TANK_EN))
        #define CapSense_1_CTANK_CONNECTION           (CapSense_1_CSD__DEDICATED_IO1)
    #else
        #define CapSense_1_CTANK_CONNECTION               (0u)
    #endif /* ((CapSense_1_ENABLE == CapSense_1_CSD_SHIELD_EN) && \
               (CapSense_1_ENABLE == CapSense_1_CSD_SHIELD_TANK_EN)) */

    /* CSDv2 masks for the resistance or low EMI (slow ramp)  */
    #define CapSense_1_RES_LOW                            (0u)
    #define CapSense_1_RES_MED                            (1u)
    #define CapSense_1_RES_HIGH                           (2u)
    #define CapSense_1_RES_LOWEMI                         (3u)

    /* CSDv2 masks for the waveforms for corresponding switch  */
    #define CapSense_1_STATIC_OPEN                        (0x00000000Lu)
    #define CapSense_1_STATIC_CLOSE                       (0x00000001Lu)
    #define CapSense_1_PHI1                               (0x00000002Lu)
    #define CapSense_1_PHI2                               (0x00000003Lu)
    #define CapSense_1_PHI1_HSCMP                         (0x00000004Lu)
    #define CapSense_1_PHI2_HSCMP                         (0x00000005Lu)
    #define CapSense_1_HSCMP                              (0x00000006Lu)

    #define CapSense_1_SW_DSI_CMOD                        (1uL << 4u)
    #define CapSense_1_SW_DSI_CTANK                       (1uL << 0u)

    /* CSDv2 CSD_CONFIG register masks    */
    #define CapSense_1_CONFIG_FILTER_DELAY_MASK           (((0x00000001Lu << CYFLD_CSD_FILTER_DELAY__SIZE) - 1u) << CYFLD_CSD_FILTER_DELAY__OFFSET)
    #define CapSense_1_CONFIG_FILTER_DELAY_2_CYCLES       (0x00000002Lu)
    #define CapSense_1_CONFIG_FILTER_DELAY_3_CYCLES       (0x00000003Lu)
    #define CapSense_1_CONFIG_FILTER_DELAY_4_CYCLES       (0x00000004Lu)
    #define CapSense_1_CONFIG_FILTER_DELAY_12MHZ          (CapSense_1_CONFIG_FILTER_DELAY_2_CYCLES << CYFLD_CSD_FILTER_DELAY__OFFSET)
    #define CapSense_1_CONFIG_FILTER_DELAY_24MHZ          (CapSense_1_CONFIG_FILTER_DELAY_3_CYCLES << CYFLD_CSD_FILTER_DELAY__OFFSET)
    #define CapSense_1_CONFIG_FILTER_DELAY_48MHZ          (CapSense_1_CONFIG_FILTER_DELAY_4_CYCLES << CYFLD_CSD_FILTER_DELAY__OFFSET)
    #define CapSense_1_CONFIG_SHIELD_DELAY_MASK           (((0x00000001Lu << CYFLD_CSD_SHIELD_DELAY__SIZE) - 1u) << CYFLD_CSD_SHIELD_DELAY__OFFSET)
    #define CapSense_1_CONFIG_SENSE_EN_MASK               (((0x00000001Lu << CYFLD_CSD_SENSE_EN__SIZE) - 1u) << CYFLD_CSD_SENSE_EN__OFFSET)
    #define CapSense_1_CONFIG_CHARGE_MODE_MASK            (((0x00000001Lu << CYFLD_CSD_CHARGE_MODE__SIZE) - 1u) << CYFLD_CSD_CHARGE_MODE__OFFSET)
    #define CapSense_1_CONFIG_MUTUAL_CAP_MASK             (((0x00000001Lu << CYFLD_CSD_MUTUAL_CAP__SIZE) - 1u) << CYFLD_CSD_MUTUAL_CAP__OFFSET)
    #define CapSense_1_CONFIG_CSX_DUAL_CNT_MASK           (((0x00000001Lu << CYFLD_CSD_CSX_DUAL_CNT__SIZE) - 1u) << CYFLD_CSD_CSX_DUAL_CNT__OFFSET)
    #define CapSense_1_CONFIG_DSI_COUNT_SEL_MASK          (((0x00000001Lu << CYFLD_CSD_DSI_COUNT_SEL__SIZE) - 1u) << CYFLD_CSD_DSI_COUNT_SEL__OFFSET)
    #define CapSense_1_CONFIG_DSI_SAMPLE_EN_MASK          (((0x00000001Lu << CYFLD_CSD_DSI_SAMPLE_EN__SIZE) - 1u) << CYFLD_CSD_DSI_SAMPLE_EN__OFFSET)
    #define CapSense_1_CONFIG_SAMPLE_SYNC_MASK            (((0x00000001Lu << CYFLD_CSD_SAMPLE_SYNC__SIZE) - 1u) << CYFLD_CSD_SAMPLE_SYNC__OFFSET)
    #define CapSense_1_CONFIG_DSI_SENSE_EN_MASK           (((0x00000001Lu << CYFLD_CSD_DSI_SENSE_EN__SIZE) - 1u) << CYFLD_CSD_DSI_SENSE_EN__OFFSET)
    #define CapSense_1_CONFIG_LP_MODE_MASK                (((0x00000001Lu << CYFLD_CSD_LP_MODE__SIZE) - 1u) << CYFLD_CSD_LP_MODE__OFFSET)
    #define CapSense_1_CONFIG_ENABLE_MASK                 (((0x00000001Lu << CYFLD_CSD_ENABLE__SIZE) - 1u) << CYFLD_CSD_ENABLE__OFFSET)

    /* CSDv2 CSD_STATUS register masks    */
    #define CapSense_1_STATUS_CSD_CHARGE_MASK             (((0x00000001Lu << CYFLD_CSD_CSD_CHARGE__SIZE) - 1u) << CYFLD_CSD_CSD_CHARGE__OFFSET)
    #define CapSense_1_STATUS_CSD_SENSE_MASK              (((0x00000001Lu << CYFLD_CSD_CSD_SENSE__SIZE) - 1u) << CYFLD_CSD_CSD_SENSE__OFFSET)
    #define CapSense_1_STATUS_HSCMP_OUT_MASK              (((0x00000001Lu << CYFLD_CSD_HSCMP_OUT__SIZE) - 1u) << CYFLD_CSD_HSCMP_OUT__OFFSET)
    #define CapSense_1_STATUS_CSDCMP_OUT_MASK             (((0x00000001Lu << CYFLD_CSD_CSDCMP_OUT__SIZE) - 1u) << CYFLD_CSD_CSDCMP_OUT__OFFSET)

    /* CSDv2 STAT_SEQ register masks    */
    #define CapSense_1_STAT_SEQ_SEQ_STATE_MASK            (((0x00000001Lu << CYFLD_CSD_SEQ_STATE__SIZE) - 1u) << CYFLD_CSD_SEQ_STATE__OFFSET)
    #define CapSense_1_STAT_SEQ_ADC_STATE_MASK            (((0x00000001Lu << CYFLD_CSD_ADC_STATE__SIZE) - 1u) << CYFLD_CSD_ADC_STATE__OFFSET)

    /* CSDv2 sequencer state codes */
    #define CapSense_1_STAT_SEQ_IDLE                      (0x00000000Lu << CYFLD_CSD_SEQ_STATE__OFFSET)
    #define CapSense_1_STAT_SEQ_INIT_COARSE               (0x00000001Lu << CYFLD_CSD_SEQ_STATE__OFFSET)
    #define CapSense_1_STAT_SEQ_AUTO_ZERO_0               (0x00000002Lu << CYFLD_CSD_SEQ_STATE__OFFSET)
    #define CapSense_1_STAT_SEQ_SAMPLE_INIT               (0x00000003Lu << CYFLD_CSD_SEQ_STATE__OFFSET)
    #define CapSense_1_STAT_SEQ_AUTO_ZERO_1               (0x00000004Lu << CYFLD_CSD_SEQ_STATE__OFFSET)
    #define CapSense_1_STAT_SEQ_SAMPLE_NORM               (0x00000005Lu << CYFLD_CSD_SEQ_STATE__OFFSET)


    /* CSDv2 STAT_CNTS register masks    */
    #define CapSense_1_STAT_CNTS_NUM_CONV_MASK            (((0x00000001Lu << CYFLD_CSD_NUM_CONV__SIZE) - 1u) << CYFLD_CSD_NUM_CONV__OFFSET)

    /* CSDv2 RESULT_VAL1 register masks    */
    #define CapSense_1_RESULT_VAL1_VALUE_MASK             (((0x00000001Lu << CYFLD_CSD_VALUE__SIZE) - 1u) << CYFLD_CSD_VALUE__OFFSET)
    #define CapSense_1_RESULT_VAL1_BAD_CONVS_MASK         (((0x00000001Lu << CYFLD_CSD_BAD_CONVS__SIZE) - 1u) << CYFLD_CSD_BAD_CONVS__OFFSET)

    /* CSDv2 RESULT_VAL2 register masks    */
    #define CapSense_1_RESULT_VAL2_VALUE_MASK             (0x0000FFFFLu)

    /* CSDv2 INTR register masks    */
    #define CapSense_1_INTR_SAMPLE_MASK                   (((0x00000001Lu << CYFLD_CSD_SAMPLE__SIZE) - 1u) << CYFLD_CSD_SAMPLE__OFFSET)
    #define CapSense_1_INTR_INIT_MASK                     (((0x00000001Lu << CYFLD_CSD_INIT__SIZE) - 1u) << CYFLD_CSD_INIT__OFFSET)
    #define CapSense_1_INTR_ADC_RES_MASK                  (((0x00000001Lu << CYFLD_CSD_ADC_RES__SIZE) - 1u) << CYFLD_CSD_ADC_RES__OFFSET)

    /* CSDv2 INTR_SET register masks    */
    #define CapSense_1_INTR_SET_SAMPLE_MASK               (CapSense_1_INTR_SAMPLE_MASK)
    #define CapSense_1_INTR_SET_INIT_MASK                 (CapSense_1_INTR_INIT_MASK)
    #define CapSense_1_INTR_SET_ADC_RES_MASK              (CapSense_1_INTR_ADC_RES_MASK)
    #define CapSense_1_INTR_SET_MASK                      (CapSense_1_INTR_SET_SAMPLE_MASK | \
                                                                 CapSense_1_INTR_SET_INIT_MASK | \
                                                                 CapSense_1_INTR_SET_ADC_RES_MASK)

    /* CSDv2 INTR_MASK register masks    */
    #define CapSense_1_INTR_MASK_SAMPLE_MASK              (CapSense_1_INTR_SAMPLE_MASK)
    #define CapSense_1_INTR_MASK_INIT_MASK                (CapSense_1_INTR_INIT_MASK)
    #define CapSense_1_INTR_MASK_ADC_RES_MASK             (CapSense_1_INTR_ADC_RES_MASK)


    /* CSDv2 HSCMP v2 register masks    */
    #define CapSense_1_HSCMP_EN_MASK                      (((0x00000001Lu << CYFLD_CSD_HSCMP_EN__SIZE) - 1u) << CYFLD_CSD_HSCMP_EN__OFFSET)
    #define CapSense_1_HSCMP_INVERT_MASK                  (((0x00000001Lu << CYFLD_CSD_HSCMP_INVERT__SIZE) - 1u) << CYFLD_CSD_HSCMP_INVERT__OFFSET)
    #define CapSense_1_CSD_AZ_EN_MASK                     (((0x00000001Lu << CYFLD_CSD_AZ_EN__SIZE) - 1u) << CYFLD_CSD_AZ_EN__OFFSET)

    /* CSDv2 AMBUF v2 register masks    */
    #define CapSense_1_AMBUF_AMBUF_EN_MASK                ((0x00000001Lu << CYFLD_CSD_PWR_MODE__SIZE) - 1u)
    #define CapSense_1_AMBUF_PWR_MODE_OFF                 (CYVAL_CSD_PWR_MODE_OFF)
    #define CapSense_1_AMBUF_PWR_MODE_NORM                (CYVAL_CSD_PWR_MODE_NORM)
    #define CapSense_1_AMBUF_PWR_MODE_HI                  (CYVAL_CSD_PWR_MODE_HI)

    /* CSDv2 REFGEN v2 register masks    */
    #define CapSense_1_REFGEN_REFGEN_EN_MASK              ((0x00000001Lu << CYFLD_CSD_REFGEN_EN__SIZE) - 1u)
    #define CapSense_1_REFGEN_BYPASS_MASK                 (((0x00000001Lu << CYFLD_CSD_BYPASS__SIZE) - 1u) << CYFLD_CSD_BYPASS__OFFSET)
    #define CapSense_1_REFGEN_VDDA_EN_MASK                (((0x00000001Lu << CYFLD_CSD_VDDA_EN__SIZE) - 1u) << CYFLD_CSD_VDDA_EN__OFFSET)
    #define CapSense_1_REFGEN_RES_EN_MASK                 (((0x00000001Lu << CYFLD_CSD_RES_EN__SIZE) - 1u) << CYFLD_CSD_RES_EN__OFFSET)
    #define CapSense_1_REFGEN_GAIN_MASK                   (((0x00000001Lu << CYFLD_CSD_GAIN__SIZE) - 1u) << CYFLD_CSD_GAIN__OFFSET)
    #define CapSense_1_REFGEN_VREFLO_SEL_MASK             (((0x00000001Lu << CYFLD_CSD_VREFLO_SEL__SIZE) - 1u) << CYFLD_CSD_VREFLO_SEL__OFFSET)
    #define CapSense_1_REFGEN_VREFLO_INT_MASK             (((0x00000001Lu << CYFLD_CSD_VREFLO_INT__SIZE) - 1u) << CYFLD_CSD_VREFLO_INT__OFFSET)

    /* CSDv2 IDACA v2 register masks  */
    #define CapSense_1_IDAC_MOD_VAL_MASK                  (((0x00000001Lu << CYFLD_CSD_VAL__SIZE) - 1u) << CYFLD_CSD_VAL__OFFSET)
    #define CapSense_1_IDAC_MOD_POLARITY_MASK             (((0x00000001Lu << CYFLD_CSD_POLARITY__SIZE) - 1u) << CYFLD_CSD_POLARITY__OFFSET)
    #define CapSense_1_IDAC_MOD_POLARITY_VSSA_SRC         ((uint32)CYVAL_CSD_POLARITY_VSSA_SRC << CYFLD_CSD_POLARITY__OFFSET)
    #define CapSense_1_IDAC_MOD_POLARITY_VDDA_SNK         ((uint32)CYVAL_CSD_POLARITY_VDDA_SNK << CYFLD_CSD_POLARITY__OFFSET)
    #define CapSense_1_IDAC_MOD_POLARITY_SENSE            ((uint32)CYVAL_CSD_POLARITY_SENSE << CYFLD_CSD_POLARITY__OFFSET)
    #define CapSense_1_IDAC_MOD_POLARITY_SENSE_INV        ((uint32)CYVAL_CSD_POLARITY_SENSE_INV << CYFLD_CSD_POLARITY__OFFSET)
    #define CapSense_1_IDAC_MOD_POL_DYN_MASK              (((0x00000001Lu << CYFLD_CSD_POL_DYN__SIZE) - 1u) << CYFLD_CSD_POL_DYN__OFFSET)
    #define CapSense_1_IDAC_MOD_LEG1_MODE_MASK            (((0x00000001Lu << CYFLD_CSD_LEG1_MODE__SIZE) - 1u) << CYFLD_CSD_LEG1_MODE__OFFSET)
    #define CapSense_1_IDAC_MOD_LEG1_MODE_GP_STATIC_MASK  (CYVAL_CSD_LEG1_MODE_GP_STATIC)
    #define CapSense_1_IDAC_MOD_LEG1_MODE_GP_MASK         ((uint32)CYVAL_CSD_LEG1_MODE_GP << CYFLD_CSD_LEG1_MODE__OFFSET)
    #define CapSense_1_IDAC_MOD_LEG1_MODE_CSD_STATIC_MASK ((uint32)CYVAL_CSD_LEG1_MODE_CSD_STATIC << CYFLD_CSD_LEG1_MODE__OFFSET)
    #define CapSense_1_IDAC_MOD_LEG1_MODE_CSD_MASK        (0x00000003Lu << CYFLD_CSD_LEG1_MODE__OFFSET)
    #define CapSense_1_IDAC_MOD_LEG2_MODE_MASK            (((0x00000001Lu << CYFLD_CSD_LEG2_MODE__SIZE) - 1u) << CYFLD_CSD_LEG2_MODE__OFFSET)
    #define CapSense_1_IDAC_MOD_LEG2_MODE_GP_STATIC_MASK  (CYVAL_CSD_LEG2_MODE_GP_STATIC)
    #define CapSense_1_IDAC_MOD_LEG2_MODE_GP_MASK         ((uint32)CYVAL_CSD_LEG2_MODE_GP << CYFLD_CSD_LEG2_MODE__OFFSET)
    #define CapSense_1_IDAC_MOD_LEG2_MODE_CSD_STATIC_MASK (0x00000002Lu << CYFLD_CSD_LEG2_MODE__OFFSET)
    #define CapSense_1_IDAC_MOD_LEG2_MODE_CSD_MASK        ((uint32)CYVAL_CSD_LEG2_MODE_CSD << CYFLD_CSD_LEG2_MODE__OFFSET)
    #define CapSense_1_IDAC_MOD_BAL_MODE_PHI1             ((uint32)CYVAL_CSD_BAL_MODE_PHI1 << CYFLD_CSD_BAL_MODE__OFFSET)

    #define CapSense_1_IDAC_MOD_DSI_CTRL_EN_MASK          (0x00200000Lu)
    #define CapSense_1_IDAC_MOD_RANGE_MASK                (0x00C00000Lu)
    #define CapSense_1_IDAC_MOD_RANGE_IDAC_LO_MASK        (0x00000000Lu)
    #define CapSense_1_IDAC_MOD_RANGE_IDAC_MED_MASK       (0x00400000Lu)
    #define CapSense_1_IDAC_MOD_RANGE_IDAC_HI_MASK        (0x00800000Lu)
    #define CapSense_1_IDAC_MOD_LEG1_EN_MASK              (0x01000000Lu)
    #define CapSense_1_IDAC_MOD_LEG2_EN_MASK              (0x02000000Lu)

    /* CSDv2 IDACB v2 register masks  */
    #define CapSense_1_IDAC_COMP_VAL_MASK                  (((0x00000001Lu << CYFLD_CSD_VAL__SIZE) - 1u) << CYFLD_CSD_VAL__OFFSET)
    #define CapSense_1_IDAC_COMP_POLARITY_MASK             (((0x00000001Lu << CYFLD_CSD_POLARITY__SIZE) - 1u) << CYFLD_CSD_POLARITY__OFFSET)
    #define CapSense_1_IDAC_COMP_POLARITY_VSSA_SRC         ((uint32)CYVAL_CSD_POLARITY_VSSA_SRC << CYFLD_CSD_POLARITY__OFFSET)
    #define CapSense_1_IDAC_COMP_POLARITY_VDDA_SNK         ((uint32)CYVAL_CSD_POLARITY_VDDA_SNK << CYFLD_CSD_POLARITY__OFFSET)
    #define CapSense_1_IDAC_COMP_POLARITY_SENSE            ((uint32)CYVAL_CSD_POLARITY_SENSE << CYFLD_CSD_POLARITY__OFFSET)
    #define CapSense_1_IDAC_COMP_POLARITY_SENSE_INV        ((uint32)CYVAL_CSD_POLARITY_SENSE_INV << CYFLD_CSD_POLARITY__OFFSET)
    #define CapSense_1_IDAC_COMP_POL_DYN_MASK              (((0x00000001Lu << CYFLD_CSD_POL_DYN__SIZE) - 1u) << CYFLD_CSD_POL_DYN__OFFSET)
    #define CapSense_1_IDAC_COMP_LEG1_MODE_MASK            (((0x00000001Lu << CYFLD_CSD_LEG1_MODE__SIZE) - 1u) << CYFLD_CSD_LEG1_MODE__OFFSET)
    #define CapSense_1_IDAC_COMP_LEG1_MODE_GP_STATIC_MASK  (CYVAL_CSD_LEG1_MODE_GP_STATIC)
    #define CapSense_1_IDAC_COMP_LEG1_MODE_GP_MASK         ((uint32)CYVAL_CSD_LEG1_MODE_GP << CYFLD_CSD_LEG1_MODE__OFFSET)
    #define CapSense_1_IDAC_COMP_LEG1_MODE_CSD_STATIC_MASK ((uint32)CYVAL_CSD_LEG1_MODE_CSD_STATIC << CYFLD_CSD_LEG1_MODE__OFFSET)
    #define CapSense_1_IDAC_COMP_LEG1_MODE_CSD_MASK        (0x00000003Lu << CYFLD_CSD_LEG1_MODE__OFFSET)
    #define CapSense_1_IDAC_COMP_LEG2_MODE_MASK            (((0x00000001Lu << CYFLD_CSD_LEG2_MODE__SIZE) - 1u) << CYFLD_CSD_LEG2_MODE__OFFSET)
    #define CapSense_1_IDAC_COMP_LEG2_MODE_GP_STATIC_MASK  (CYVAL_CSD_LEG2_MODE_GP_STATIC)
    #define CapSense_1_IDAC_COMP_LEG2_MODE_GP_MASK         ((uint32)CYVAL_CSD_LEG2_MODE_GP << CYFLD_CSD_LEG2_MODE__OFFSET)
    #define CapSense_1_IDAC_COMP_LEG2_MODE_CSD_STATIC_MASK (0x00000002Lu << CYFLD_CSD_LEG2_MODE__OFFSET)
    #define CapSense_1_IDAC_COMP_LEG2_MODE_CSD_MASK        ((uint32)CYVAL_CSD_LEG2_MODE_CSD << CYFLD_CSD_LEG2_MODE__OFFSET)
    #define CapSense_1_IDAC_COMP_DSI_CTRL_EN_MASK          (0x00200000Lu)
    #define CapSense_1_IDAC_COMP_RANGE_MASK                (0x00C00000Lu)
    #define CapSense_1_IDAC_COMP_RANGE_IDAC_LO_MASK        (0x00000000Lu)
    #define CapSense_1_IDAC_COMP_RANGE_IDAC_MED_MASK       (0x00400000Lu)
    #define CapSense_1_IDAC_COMP_RANGE_IDAC_HI_MASK        (0x00800000Lu)
    #define CapSense_1_IDAC_COMP_LEG1_EN_MASK              (0x01000000Lu)
    #define CapSense_1_IDAC_COMP_LEG2_EN_MASK              (0x02000000Lu)

    /* CSDv2 SENSE_PERIOD register masks  */
    #define CapSense_1_SENSE_PERIOD_SENSE_DIV_MASK        (((0x00000001Lu << CYFLD_CSD_SENSE_DIV__SIZE) - 1u) << CYFLD_CSD_SENSE_DIV__OFFSET)
    #define CapSense_1_SENSE_PERIOD_LFSR_SIZE_MASK        (((0x00000001Lu << CYFLD_CSD_LFSR_SIZE__SIZE) - 1u) << CYFLD_CSD_LFSR_SIZE__OFFSET)
    #define CapSense_1_SENSE_PERIOD_LFSR_SCALE_MASK       (((0x00000001Lu << CYFLD_CSD_LFSR_SCALE__SIZE) - 1u) << CYFLD_CSD_LFSR_SCALE__OFFSET)
    #define CapSense_1_SENSE_PERIOD_LFSR_CLEAR_MASK       (((0x00000001Lu << CYFLD_CSD_LFSR_CLEAR__SIZE) - 1u) << CYFLD_CSD_LFSR_CLEAR__OFFSET)
    #define CapSense_1_SENSE_PERIOD_SEL_LFSR_MSB_MASK     (((0x00000001Lu << CYFLD_CSD_SEL_LFSR_MSB__SIZE) - 1u) << CYFLD_CSD_SEL_LFSR_MSB__OFFSET)
    #define CapSense_1_SENSE_6MHZ                         (6u)
    #define CapSense_1_SENSE_PERIOD_SENSE_DIV_6MHZ        (CYDEV_BCLK__HFCLK__KHZ/CapSense_1_CSD_SCANSPEED_DIVIDER/CapSense_1_SENSE_6MHZ)

    /* CSDv2 SW_BYP_SEL register masks  */
    #define CapSense_1_SW_BYP_SEL_SW_BYA_MASK             (((0x00000001Lu << CYFLD_CSD_SW_BYA__SIZE) - 1u) << CYFLD_CSD_SW_BYA__OFFSET)
    #define CapSense_1_SW_BYP_SEL_SW_BYB_MASK             (((0x00000001Lu << CYFLD_CSD_SW_BYB__SIZE) - 1u) << CYFLD_CSD_SW_BYB__OFFSET)
    #define CapSense_1_SW_BYP_SEL_SW_CBCC_MASK            (((0x00000001Lu << CYFLD_CSD_SW_CBCC__SIZE) - 1u) << CYFLD_CSD_SW_CBCC__OFFSET)

    /* CSDv2 SW_REFGEN_SEL register masks  */
    #define CapSense_1_SW_REFGEN_SEL_SW_IAIB_MASK         (((0x00000001Lu << CYFLD_CSD_SW_IAIB__SIZE) - 1u) << CYFLD_CSD_SW_IAIB__OFFSET)
    #define CapSense_1_SW_REFGEN_SEL_SW_IBCB_MASK         (((0x00000001Lu << CYFLD_CSD_SW_IBCB__SIZE) - 1u) << CYFLD_CSD_SW_IBCB__OFFSET)
    #define CapSense_1_SW_REFGEN_SEL_SW_SGMB_MASK         (((0x00000001Lu << CYFLD_CSD_SW_SGMB__SIZE) - 1u) << CYFLD_CSD_SW_SGMB__OFFSET)
    #define CapSense_1_SW_REFGEN_SEL_SW_SGRE_MASK         (((0x00000001Lu << CYFLD_CSD_SW_SGRE__SIZE) - 1u) << CYFLD_CSD_SW_SGRE__OFFSET)
    #define CapSense_1_SW_REFGEN_SEL_SW_SGR_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SGR__SIZE) - 1u) << CYFLD_CSD_SW_SGR__OFFSET)

    /* CSDv2 SW_CMP_N_SEL register masks  */
    #define CapSense_1_SW_CMP_N_SEL_SW_SCRH_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SCRH__SIZE) - 1u) << CYFLD_CSD_SW_SCRH__OFFSET)
    #define CapSense_1_SW_CMP_N_SEL_SW_SCRH_STATIC_OPEN   (CapSense_1_STATIC_OPEN << CYFLD_CSD_SW_SCRH__OFFSET)
    #define CapSense_1_SW_CMP_N_SEL_SW_SCRH_STATIC_CLOSE  (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_SCRH__OFFSET)
    #define CapSense_1_SW_CMP_N_SEL_SW_SCRL_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SCRL__SIZE) - 1u) << CYFLD_CSD_SW_SCRL__OFFSET)
    #define CapSense_1_SW_CMP_N_SEL_SW_SCRL_STATIC_OPEN   (CapSense_1_STATIC_OPEN << CYFLD_CSD_SW_SCRL__OFFSET)
    #define CapSense_1_SW_CMP_N_SEL_SW_SCRL_STATIC_CLOSE  (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_SCRL__OFFSET)

    /* CSDv2 SEQ_TIME register masks  */
    #define CapSense_1_SEQ_TIME_AZ_TIME_MASK              (((0x00000001Lu << CYFLD_CSD_AZ_TIME__SIZE) - 1u) << CYFLD_CSD_AZ_TIME__OFFSET)

    /* CSDv2 SEQ_INIT_CNT register masks  */
    #define CapSense_1_SEQ_INIT_CNT_CONV_CNT_MASK         (((0x00000001Lu << CYFLD_CSD_CONV_CNT__SIZE) - 1u) << CYFLD_CSD_CONV_CNT__OFFSET)

    /* CSDv2 SEQ_NORM_CNT register masks  */
    #define CapSense_1_SEQ_NORM_CNT_CONV_CNT_MASK         (((0x00000001Lu << CYFLD_CSD_CONV_CNT__SIZE) - 1u) << CYFLD_CSD_CONV_CNT__OFFSET)

    /* CSDv2 SW_RES register masks  */
    #define CapSense_1_SW_RES_RES_HCAV_MASK               (((0x00000001Lu << CYFLD_CSD_RES_HCAV__SIZE) - 1u) << CYFLD_CSD_RES_HCAV__OFFSET)
    #define CapSense_1_SW_RES_RES_HCAG_MASK               (((0x00000001Lu << CYFLD_CSD_RES_HCAG__SIZE) - 1u) << CYFLD_CSD_RES_HCAG__OFFSET)
    #define CapSense_1_SW_RES_RES_HCBV_MASK               (((0x00000001Lu << CYFLD_CSD_RES_HCBV__SIZE) - 1u) << CYFLD_CSD_RES_HCBV__OFFSET)
    #define CapSense_1_SW_RES_RES_HCBG_MASK               (((0x00000001Lu << CYFLD_CSD_RES_HCBG__SIZE) - 1u) << CYFLD_CSD_RES_HCBG__OFFSET)
    #define CapSense_1_SW_RES_RES_F1PM_MASK               (((0x00000001Lu << CYFLD_CSD_RES_F1PM__SIZE) - 1u) << CYFLD_CSD_RES_F1PM__OFFSET)
    #define CapSense_1_SW_RES_RES_F2PT_MASK               (((0x00000001Lu << CYFLD_CSD_RES_F2PT__SIZE) - 1u) << CYFLD_CSD_RES_F2PT__OFFSET)

    #define CapSense_1_SW_RES_RES_DEFAULT                 ((CapSense_1_CSD_INIT_SWITCH_RES << CYFLD_CSD_RES_HCAV__OFFSET) | \
                                                                 (CapSense_1_CSD_SHIELD_SWITCH_RES << CYFLD_CSD_RES_HCBV__OFFSET))

    /* CSDv2 SW_HS_P_SEL register masks  */
    #define CapSense_1_SW_HS_P_SEL_SW_HMPM_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HMPM__SIZE) - 1u) << CYFLD_CSD_SW_HMPM__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMPM_STATIC_OPEN    (CapSense_1_STATIC_OPEN << CYFLD_CSD_SW_HMPM__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE   (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_HMPM__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMPT_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HMPT__SIZE) - 1u) << CYFLD_CSD_SW_HMPT__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMPT_STATIC_OPEN    (CapSense_1_STATIC_OPEN << CYFLD_CSD_SW_HMPT__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE   (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_HMPT__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMPS_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HMPS__SIZE) - 1u) << CYFLD_CSD_SW_HMPS__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMPS_STATIC_OPEN    (CapSense_1_STATIC_OPEN << CYFLD_CSD_SW_HMPS__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE   (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_HMPS__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMMA_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HMMA__SIZE) - 1u) << CYFLD_CSD_SW_HMMA__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMMA_STATIC_OPEN    (CapSense_1_STATIC_OPEN << CYFLD_CSD_SW_HMMA__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMMA_STATIC_CLOSE   (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_HMMA__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMMB_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HMMB__SIZE) - 1u) << CYFLD_CSD_SW_HMMB__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMMB_STATIC_OPEN    (CapSense_1_STATIC_OPEN << CYFLD_CSD_SW_HMMB__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE   (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_HMMB__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMCA_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HMCA__SIZE) - 1u) << CYFLD_CSD_SW_HMCA__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMCB_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HMCB__SIZE) - 1u) << CYFLD_CSD_SW_HMCB__OFFSET)
    #define CapSense_1_SW_HS_P_SEL_SW_HMRH_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HMRH__SIZE) - 1u) << CYFLD_CSD_SW_HMRH__OFFSET)

    /* CSDv2 SW_SHIELD_SEL register masks  */
    #define CapSense_1_SW_SHIELD_SEL_SW_HCAV_MASK         (((0x00000001Lu << CYFLD_CSD_SW_HCAV__SIZE) - 1u) << CYFLD_CSD_SW_HCAV__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCAV_STATIC_OPEN  (CapSense_1_STATIC_OPEN)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCAV_HSCMP        (CapSense_1_HSCMP)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCAG_MASK         (((0x00000001Lu << CYFLD_CSD_SW_HCAG__SIZE) - 1u) << CYFLD_CSD_SW_HCAG__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCBV_MASK         (((0x00000001Lu << CYFLD_CSD_SW_HCBV__SIZE) - 1u) << CYFLD_CSD_SW_HCBV__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCBV_HSCMP        (CapSense_1_HSCMP << CYFLD_CSD_SW_HCBV__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCBV_PHI1         (CapSense_1_PHI1 << CYFLD_CSD_SW_HCBV__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCBV_PHI2         (CapSense_1_PHI2 << CYFLD_CSD_SW_HCBV__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCBV_PHI1_HSCMP   (CapSense_1_PHI1_HSCMP << CYFLD_CSD_SW_HCBV__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCBV_PHI2_HSCMP   (CapSense_1_PHI2_HSCMP << CYFLD_CSD_SW_HCBV__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCBV_STATIC_OPEN  (CapSense_1_STATIC_OPEN << CYFLD_CSD_SW_HCBV__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCBG_MASK         (((0x00000001Lu << CYFLD_CSD_SW_HCBG__SIZE) - 1u) << CYFLD_CSD_SW_HCBG__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCBG_HSCMP        (CapSense_1_HSCMP << CYFLD_CSD_SW_HCBG__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCBG_PHI1         (CapSense_1_PHI1 << CYFLD_CSD_SW_HCBG__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCBG_PHI2         (CapSense_1_PHI2 << CYFLD_CSD_SW_HCBG__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCBG_PHI1_HSCMP   (CapSense_1_PHI1_HSCMP << CYFLD_CSD_SW_HCBG__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCBG_PHI2_HSCMP   (CapSense_1_PHI2_HSCMP << CYFLD_CSD_SW_HCBG__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCBG_STATIC_OPEN  (CapSense_1_STATIC_OPEN << CYFLD_CSD_SW_HCBG__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCCV_MASK         (((0x00000001Lu << CYFLD_CSD_SW_HCCV__SIZE) - 1u) << CYFLD_CSD_SW_HCCV__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCCG_MASK         (((0x00000001Lu << CYFLD_CSD_SW_HCCG__SIZE) - 1u) << CYFLD_CSD_SW_HCCG__OFFSET)

    /* CSDv2 SEQ_START register masks  */
    #define CapSense_1_SEQ_START_START_MASK               (((0x00000001Lu << CYFLD_CSD_START__SIZE) - 1u) << CYFLD_CSD_START__OFFSET)
    #define CapSense_1_SEQ_START_SEQ_MODE_MASK            (((0x00000001Lu << CYFLD_CSD_SEQ_MODE__SIZE) - 1u) << CYFLD_CSD_SEQ_MODE__OFFSET)
    #define CapSense_1_SEQ_START_ABORT_MASK               (((0x00000001Lu << CYFLD_CSD_ABORT__SIZE) - 1u) << CYFLD_CSD_ABORT__OFFSET)
    #define CapSense_1_SEQ_START_DSI_START_EN_MASK        (((0x00000001Lu << CYFLD_CSD_DSI_START_EN__SIZE) - 1u) << CYFLD_CSD_DSI_START_EN__OFFSET)
    #define CapSense_1_SEQ_START_AZ0_SKIP_MASK            (((0x00000001Lu << CYFLD_CSD_AZ0_SKIP__SIZE) - 1u) << CYFLD_CSD_AZ0_SKIP__OFFSET)
    #define CapSense_1_SEQ_START_AZ1_SKIP_MASK            (((0x00000001Lu << CYFLD_CSD_AZ1_SKIP__SIZE) - 1u) << CYFLD_CSD_AZ1_SKIP__OFFSET)

    /* CSDv2 SW_CMP_P_SEL register masks  */
    #define CapSense_1_SW_CMP_P_SEL_SW_SFPM_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SFPM__SIZE) - 1u) << CYFLD_CSD_SW_SFPM__OFFSET)
    #define CapSense_1_SW_CMP_P_SEL_SW_SFPM_STATIC_OPEN   (CapSense_1_STATIC_OPEN << CYFLD_CSD_SW_SFPM__OFFSET)
    #define CapSense_1_SW_CMP_P_SEL_SW_SFPM_STATIC_CLOSE  (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_SFPM__OFFSET)
    #define CapSense_1_SW_CMP_P_SEL_SW_SFPT_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SFPT__SIZE) - 1u) << CYFLD_CSD_SW_SFPT__OFFSET)
    #define CapSense_1_SW_CMP_P_SEL_SW_SFPT_STATIC_OPEN   (CapSense_1_STATIC_OPEN << CYFLD_CSD_SW_SFPT__OFFSET)
    #define CapSense_1_SW_CMP_P_SEL_SW_SFPT_STATIC_CLOSE  (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_SFPT__OFFSET)
    #define CapSense_1_SW_CMP_P_SEL_SW_SFPS_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SFPS__SIZE) - 1u) << CYFLD_CSD_SW_SFPS__OFFSET)
    #define CapSense_1_SW_CMP_P_SEL_SW_SFPS_STATIC_OPEN   (CapSense_1_STATIC_OPEN << CYFLD_CSD_SW_SFPS__OFFSET)
    #define CapSense_1_SW_CMP_P_SEL_SW_SFPS_STATIC_CLOSE  (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_SFPS__OFFSET)
    #define CapSense_1_SW_CMP_P_SEL_SW_SFMA_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SFMA__SIZE) - 1u) << CYFLD_CSD_SW_SFMA__OFFSET)
    #define CapSense_1_SW_CMP_P_SEL_SW_SFMB_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SFMB__SIZE) - 1u) << CYFLD_CSD_SW_SFMB__OFFSET)
    #define CapSense_1_SW_CMP_P_SEL_SW_SFCA_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SFCA__SIZE) - 1u) << CYFLD_CSD_SW_SFCA__OFFSET)
    #define CapSense_1_SW_CMP_P_SEL_SW_SFCB_MASK          (((0x00000001Lu << CYFLD_CSD_SW_SFCB__SIZE) - 1u) << CYFLD_CSD_SW_SFCB__OFFSET)

    /* CSDv2 CSDCMP register masks    */
    #define CapSense_1_CSDCMP_CSDCMP_EN_MASK              (((0x00000001Lu << CYFLD_CSD_CSDCMP_EN__SIZE) - 1u) << CYFLD_CSD_CSDCMP_EN__OFFSET)
    #define CapSense_1_CSDCMP_POLARITY_SEL_MASK           (((0x00000001Lu << CYFLD_CSD_POLARITY_SEL__SIZE) - 1u) << CYFLD_CSD_POLARITY_SEL__OFFSET)
    #define CapSense_1_CSDCMP_FEEDBACK_MODE_MASK          (((0x00000001Lu << CYFLD_CSD_FEEDBACK_MODE__SIZE) - 1u) << CYFLD_CSD_FEEDBACK_MODE__OFFSET)
    #define CapSense_1_CSDCMP_AZ_EN_MASK                  (((0x00000001Lu << CYFLD_CSD_AZ_EN__SIZE) - 1u) << CYFLD_CSD_AZ_EN__OFFSET)

    /* CSDv2 SENSE_DUTY register masks  */
    #define CapSense_1_SENSE_DUTY_SENSE_WIDTH_MASK        (((0x00000001Lu << CYFLD_CSD_SENSE_WIDTH__SIZE) - 1u) << CYFLD_CSD_SENSE_WIDTH__OFFSET)
    #define CapSense_1_SENSE_DUTY_SENSE_POL_MASK          (((0x00000001Lu << CYFLD_CSD_SENSE_POL__SIZE) - 1u) << CYFLD_CSD_SENSE_POL__OFFSET)
    #define CapSense_1_SENSE_DUTY_OVERLAP_PHI1_MASK       (((0x00000001Lu << CYFLD_CSD_OVERLAP_PHI1__SIZE) - 1u) << CYFLD_CSD_OVERLAP_PHI1__OFFSET)
    #define CapSense_1_SENSE_DUTY_OVERLAP_PHI2_MASK       (((0x00000001Lu << CYFLD_CSD_OVERLAP_PHI2__SIZE) - 1u) << CYFLD_CSD_OVERLAP_PHI2__OFFSET)

    /* CSDv2 SW_AMUXBUF_SEL register masks  */
    #define CapSense_1_SW_AMUXBUF_SEL_SW_IRBY_MASK        (((0x00000001Lu << CYFLD_CSD_SW_IRBY__SIZE) - 1u) << CYFLD_CSD_SW_IRBY__OFFSET)
    #define CapSense_1_SW_AMUXBUF_SEL_SW_IRLB_MASK        (((0x00000001Lu << CYFLD_CSD_SW_IRLB__SIZE) - 1u) << CYFLD_CSD_SW_IRLB__OFFSET)
    #define CapSense_1_SW_AMUXBUF_SEL_SW_IRLB_STATIC_CLOSE (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_IRLB__OFFSET)
    #define CapSense_1_SW_AMUXBUF_SEL_SW_ICA_MASK         (((0x00000001Lu << CYFLD_CSD_SW_ICA__SIZE) - 1u) << CYFLD_CSD_SW_ICA__OFFSET)
    #define CapSense_1_SW_AMUXBUF_SEL_SW_ICB_MASK         (((0x00000001Lu << CYFLD_CSD_SW_ICB__SIZE) - 1u) << CYFLD_CSD_SW_ICB__OFFSET)
    #define CapSense_1_SW_AMUXBUF_SEL_SW_ICB_PHI2_HSCMP   (CapSense_1_PHI2_HSCMP << CYFLD_CSD_SW_ICB__OFFSET)
    #define CapSense_1_SW_AMUXBUF_SEL_SW_IRLI_MASK        (((0x00000001Lu << CYFLD_CSD_SW_IRLI__SIZE) - 1u) << CYFLD_CSD_SW_IRLI__OFFSET)
    #define CapSense_1_SW_AMUXBUF_SEL_SW_IRH_MASK         (((0x00000001Lu << CYFLD_CSD_SW_IRH__SIZE) - 1u) << CYFLD_CSD_SW_IRH__OFFSET)
    #define CapSense_1_SW_AMUXBUF_SEL_SW_IRH_STATIC_CLOSE (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_IRH__OFFSET)
    #define CapSense_1_SW_AMUXBUF_SEL_SW_IRL_MASK         (((0x00000001Lu << CYFLD_CSD_SW_IRL__SIZE) - 1u) << CYFLD_CSD_SW_IRL__OFFSET)
    #define CapSense_1_SW_AMUXBUF_SEL_SW_IRL_MASK         (((0x00000001Lu << CYFLD_CSD_SW_IRL__SIZE) - 1u) << CYFLD_CSD_SW_IRL__OFFSET)
    #define CapSense_1_SW_AMUXBUF_SEL_SW_DEFAULT          (0x01030000Lu)
    #define CapSense_1_SW_AMUXBUF_SEL_SW_ICB_PHI2         (0x00030000uL)
    #define CapSense_1_SW_AMUXBUF_SEL_SW_ICB_PHI1         (CapSense_1_PHI1 << CYFLD_CSD_SW_ICB__OFFSET)

    /* CSDv2 SW_FW_TANK_SEL register masks  */
    #define CapSense_1_SW_HS_N_SEL_SW_HCCC_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HCCC__SIZE) - 1u) << CYFLD_CSD_SW_HCCC__OFFSET)
    #define CapSense_1_SW_HS_N_SEL_SW_HCCD_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HCCD__SIZE) - 1u) << CYFLD_CSD_SW_HCCD__OFFSET)
    #define CapSense_1_SW_HS_N_SEL_SW_HCRH_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HCRH__SIZE) - 1u) << CYFLD_CSD_SW_HCRH__OFFSET)
    #define CapSense_1_SW_HS_N_SEL_SW_HCRH_STATIC_OPEN    (CapSense_1_STATIC_OPEN << CYFLD_CSD_SW_HCRH__OFFSET)
    #define CapSense_1_SW_HS_N_SEL_SW_HCRH_STATIC_CLOSE   (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_HCRH__OFFSET)
    #define CapSense_1_SW_HS_N_SEL_SW_HCRL_MASK           (((0x00000001Lu << CYFLD_CSD_SW_HCRL__SIZE) - 1u) << CYFLD_CSD_SW_HCRL__OFFSET)
    #define CapSense_1_SW_HS_N_SEL_SW_HCRL_STATIC_OPEN    (CapSense_1_STATIC_OPEN << CYFLD_CSD_SW_HCRL__OFFSET)
    #define CapSense_1_SW_HS_N_SEL_SW_HCRL_STATIC_CLOSE   (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_HCRL__OFFSET)

    /* CSDv2 SW_FW_MOD_SEL register masks  */
    #define CapSense_1_SW_FW_MOD_SEL_SW_F1PM_MASK         (((0x00000001Lu << CYFLD_CSD_SW_F1PM__SIZE) - 1u) << CYFLD_CSD_SW_F1PM__OFFSET)
    #define CapSense_1_SW_FW_MOD_SEL_SW_F1PM_STATIC_CLOSE (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_F1PM__OFFSET)
    #define CapSense_1_SW_FW_MOD_SEL_SW_F1MA_MASK         (((0x00000001Lu << CYFLD_CSD_SW_F1MA__SIZE) - 1u) << CYFLD_CSD_SW_F1MA__OFFSET)
    #define CapSense_1_SW_FW_MOD_SEL_SW_F1MA_STATIC_CLOSE (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_F1MA__OFFSET)
    #define CapSense_1_SW_FW_MOD_SEL_SW_F1CA_MASK         (((0x00000001Lu << CYFLD_CSD_SW_F1CA__SIZE) - 1u) << CYFLD_CSD_SW_F1CA__OFFSET)
    #define CapSense_1_SW_FW_MOD_SEL_SW_F1CA_STATIC_CLOSE (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_F1CA__OFFSET)

    /* CSDv2 SW_FW_TANK_SEL register masks  */
    #define CapSense_1_SW_FW_TANK_SEL_SW_F2PT_MASK        (((0x00000001Lu << CYFLD_CSD_SW_F2PT__SIZE) - 1u) << CYFLD_CSD_SW_F2PT__OFFSET)
    #define CapSense_1_SW_FW_TANK_SEL_SW_F2PT_STATIC_CLOSE (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_F2PT__OFFSET)
    #define CapSense_1_SW_FW_TANK_SEL_SW_F2CB_MASK        (((0x00000001Lu << CYFLD_CSD_SW_F2CB__SIZE) - 1u) << CYFLD_CSD_SW_F2CB__OFFSET)
    #define CapSense_1_SW_FW_TANK_SEL_SW_F2CB_PHI2        (CapSense_1_PHI2 << CYFLD_CSD_SW_F2CB__OFFSET)
    #define CapSense_1_SW_FW_TANK_SEL_SW_F2MA_MASK        (((0x00000001Lu << CYFLD_CSD_SW_F2MA__SIZE) - 1u) << CYFLD_CSD_SW_F2MA__OFFSET)
    #define CapSense_1_SW_FW_TANK_SEL_SW_F2MA_STATIC_CLOSE (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_F2MA__OFFSET)
    #define CapSense_1_SW_FW_TANK_SEL_SW_F2CA_MASK        (((0x00000001Lu << CYFLD_CSD_SW_F2CA__SIZE) - 1u) << CYFLD_CSD_SW_F2CA__OFFSET)
    #define CapSense_1_SW_FW_TANK_SEL_SW_F2CA_STATIC_CLOSE (CapSense_1_STATIC_CLOSE << CYFLD_CSD_SW_F2CA__OFFSET)

    /* Defining default CSDv2 configuration according to settings in customizer. */
    #define CapSense_1_DEFAULT_CSD_CONFIG                 (CapSense_1_CONFIG_FILTER_DELAY_2_CYCLES | CapSense_1_CONFIG_SAMPLE_SYNC_MASK)

    /* CSDv2 CTANK masks    */
    #define CapSense_1_CTANK_DR_VDDIO                     (0x0u)
    #define CapSense_1_CTANK_DR_VSSIO                     (CapSense_1_DR_MASK << CapSense_1_CSH_SHIFT)

    /* CSDv2 IDACs' masks */
    #if (CapSense_1_IDAC_SINKING == CapSense_1_CSD_IDAC_CONFIG)
        #define CapSense_1_DEFAULT_IDAC_MOD_POLARITY      (CapSense_1_IDAC_MOD_POLARITY_VDDA_SNK)
        #define CapSense_1_DEFAULT_IDAC_COMP_POLARITY     (CapSense_1_IDAC_COMP_POLARITY_VDDA_SNK)
        #define CapSense_1_CSH_DR_CONFIG                  (CapSense_1_CTANK_DR_VSSIO)
    #else
        #define CapSense_1_DEFAULT_IDAC_MOD_POLARITY      (0x00000000Lu)
        #define CapSense_1_DEFAULT_IDAC_COMP_POLARITY     (0x00000000Lu)
        #define CapSense_1_CSH_DR_CONFIG                  (CapSense_1_CTANK_DR_VDDIO)
    #endif /*  (CapSense_1_IDAC_SINKING == CapSense_1_CSD_IDAC_CONFIG) */

    #if (CapSense_1_ENABLE == CapSense_1_CSD_IDAC_COMP_EN)
        #if (CapSense_1_ENABLE == CapSense_1_CSD_DEDICATED_IDAC_COMP_EN)
            #if (0u != CapSense_1_TOTAL_CSD_WIDGETS)
                #define CapSense_1_IDACB_USED             (1u)
            #else
                #define CapSense_1_IDACB_USED             (0u)
            #endif /* (0u != CapSense_1_TOTAL_CSD_WIDGETS) */
            #define CapSense_1_DEFAULT_IDAC_MOD_LEG2_MODE (CapSense_1_IDAC_MOD_LEG2_MODE_GP_STATIC_MASK)
            #define CapSense_1_DEFAULT_IDAC_COMP_LEG1_MODE (CapSense_1_IDAC_COMP_LEG1_EN_MASK |\
                                                                CapSense_1_IDAC_COMP_LEG1_MODE_CSD_STATIC_MASK)
            #define CapSense_1_DEFAULT_SW_REFGEN_SEL      (CapSense_1_SW_REFGEN_SEL_SW_SGR_MASK |\
                                                                CapSense_1_SW_REFGEN_SEL_SW_IAIB_MASK)
        #else
            #define CapSense_1_IDACB_USED                 (0u)
            #define CapSense_1_DEFAULT_IDAC_MOD_LEG2_MODE (CapSense_1_IDAC_MOD_LEG2_EN_MASK |\
                                                                CapSense_1_IDAC_MOD_LEG2_MODE_CSD_STATIC_MASK)
            #define CapSense_1_DEFAULT_IDAC_COMP_LEG1_MODE (CapSense_1_IDAC_COMP_LEG1_MODE_GP_STATIC_MASK)
            #define CapSense_1_DEFAULT_SW_REFGEN_SEL      (CapSense_1_SW_REFGEN_SEL_SW_SGR_MASK)
        #endif /* (CapSense_1_ENABLE == CapSense_1_CSD_DEDICATED_IDAC_COMP_EN)) */
    #else
        #define CapSense_1_IDACB_USED                     (0u)
        #define CapSense_1_DEFAULT_IDAC_MOD_LEG2_MODE     (CapSense_1_IDAC_MOD_LEG2_MODE_GP_STATIC_MASK)
        #define CapSense_1_DEFAULT_IDAC_COMP_LEG1_MODE    (CapSense_1_IDAC_COMP_LEG1_MODE_GP_STATIC_MASK)
        #define CapSense_1_DEFAULT_SW_REFGEN_SEL          (CapSense_1_SW_REFGEN_SEL_SW_SGR_MASK)
    #endif /* (CapSense_1_ENABLE == CapSense_1_CSD_IDAC_COMP_EN) */

    #define CapSense_1_DEFAULT_IDAC_MOD_LEG1_MODE         (CapSense_1_IDAC_MOD_LEG1_EN_MASK |\
                                                                CapSense_1_IDAC_MOD_LEG1_MODE_CSD_MASK)
    #define CapSense_1_DEFAULT_IDAC_COMP_LEG2_MODE        (CapSense_1_IDAC_COMP_LEG2_MODE_GP_STATIC_MASK)

    /* IDACs ranges */
    #if (CapSense_1_IDAC_GAIN_LOW == CapSense_1_CSD_IDAC_GAIN)
        #define CapSense_1_DEFAULT_IDAC_MOD_RANGE         (CapSense_1_IDAC_MOD_RANGE_IDAC_LO_MASK)
        #define CapSense_1_DEFAULT_IDAC_COMP_RANGE        (CapSense_1_IDAC_MOD_RANGE_IDAC_LO_MASK)
    #elif (CapSense_1_IDAC_GAIN_MEDIUM == CapSense_1_CSD_IDAC_GAIN)
        #define CapSense_1_DEFAULT_IDAC_MOD_RANGE         (CapSense_1_IDAC_MOD_RANGE_IDAC_MED_MASK)
        #define CapSense_1_DEFAULT_IDAC_COMP_RANGE        (CapSense_1_IDAC_MOD_RANGE_IDAC_MED_MASK)
    #else
        #define CapSense_1_DEFAULT_IDAC_MOD_RANGE         (CapSense_1_IDAC_MOD_RANGE_IDAC_HI_MASK)
        #define CapSense_1_DEFAULT_IDAC_COMP_RANGE        (CapSense_1_IDAC_MOD_RANGE_IDAC_HI_MASK)
    #endif /* (CapSense_1_CSD_IDAC_GAIN == CapSense_1_IDAC_RANGE_8X) */

    #define CapSense_1_DEFAULT_IDAC_MOD                   (CapSense_1_DEFAULT_IDAC_MOD_RANGE |\
                                                                CapSense_1_DEFAULT_IDAC_MOD_POLARITY |\
                                                                CapSense_1_DEFAULT_IDAC_MOD_LEG1_MODE |\
                                                                CapSense_1_DEFAULT_IDAC_MOD_LEG2_MODE)

    #define CapSense_1_DEFAULT_IDAC_COMP                  (CapSense_1_DEFAULT_IDAC_COMP_RANGE |\
                                                                CapSense_1_DEFAULT_IDAC_COMP_POLARITY |\
                                                                CapSense_1_DEFAULT_IDAC_COMP_LEG1_MODE |\
                                                                CapSense_1_DEFAULT_IDAC_COMP_LEG2_MODE)

    #define CapSense_1_CALIBRATE_IDAC_MOD                 (CapSense_1_DEFAULT_IDAC_MOD_RANGE |\
                                                                CapSense_1_DEFAULT_IDAC_MOD_POLARITY |\
                                                                CapSense_1_DEFAULT_IDAC_MOD_LEG1_MODE |\
                                                                CapSense_1_IDAC_MOD_LEG2_MODE_GP_STATIC_MASK)

    #define CapSense_1_CALIBRATE_IDAC_COMP                (CapSense_1_DEFAULT_IDAC_COMP_RANGE |\
                                                                CapSense_1_DEFAULT_IDAC_COMP_POLARITY |\
                                                                CapSense_1_IDAC_COMP_LEG1_MODE_GP_STATIC_MASK |\
                                                                CapSense_1_IDAC_COMP_LEG2_MODE_GP_STATIC_MASK)

    #define CapSense_1_CALIBRATE_SW_REFGEN_SEL            (CapSense_1_SW_REFGEN_SEL_SW_SGR_MASK)

    #define CapSense_1_DEFAULT_REFGEN_GAIN                (CapSense_1_CSD_GAIN << CYFLD_CSD_GAIN__OFFSET)
    #define CapSense_1_VREF_HI_OVERSHOOT_CORRECTION       (0x00000001Lu)
    #define CapSense_1_VREF_LOW_MAX_VALUE                 (31Lu)
    #define CapSense_1_DEFAULT_REFGEN_VREFLO_SEL          ((CapSense_1_VREF_LOW_MAX_VALUE - CapSense_1_VREF_HI_OVERSHOOT_CORRECTION) \
                                                                  <<  CYFLD_CSD_VREFLO_SEL__OFFSET)

    #define CapSense_1_REFGEN_WITH_SHIELD                 (CapSense_1_REFGEN_REFGEN_EN_MASK |\
                                                                CapSense_1_REFGEN_RES_EN_MASK |\
                                                                CapSense_1_DEFAULT_REFGEN_GAIN |\
                                                                CapSense_1_DEFAULT_REFGEN_VREFLO_SEL)

    #define CapSense_1_REFGEN_NO_SHIELD                  (CapSense_1_REFGEN_REFGEN_EN_MASK |\
                                                                CapSense_1_REFGEN_RES_EN_MASK |\
                                                                CapSense_1_DEFAULT_REFGEN_GAIN)

    #define CapSense_1_SENSE_PERIOD_LFSR_SIZE_SHIFT       (CYFLD_CSD_LFSR_SIZE__OFFSET)

    /* Initial PRS mode */
    #define CapSense_1_PRS_8_CONFIG                       (CapSense_1_CLK_SOURCE_PRS8)
    #define CapSense_1_PRS_12_CONFIG                      (CapSense_1_CLK_SOURCE_PRS12)

    #if (CapSense_1_CLK_SOURCE_DIRECT == CapSense_1_CSD_SNS_CLK_SOURCE)
        #define CapSense_1_DEFAULT_SENSE_PERIOD           (CapSense_1_CLK_SOURCE_DIRECT)
    #elif (CapSense_1_CLK_SOURCE_PRSAUTO == CapSense_1_CSD_SNS_CLK_SOURCE)
        #define CapSense_1_DEFAULT_SENSE_PERIOD           (CapSense_1_CLK_SOURCE_SSC2)
    #elif ((CapSense_1_CLK_SOURCE_PRS8) == CapSense_1_CSD_SNS_CLK_SOURCE)
        #define CapSense_1_DEFAULT_SENSE_PERIOD           (CapSense_1_CSD_SNS_CLK_SOURCE)
    #elif ((CapSense_1_CLK_SOURCE_PRS12) == CapSense_1_CSD_SNS_CLK_SOURCE)
        #define CapSense_1_DEFAULT_SENSE_PERIOD           (CapSense_1_CSD_SNS_CLK_SOURCE)
    #else
        #define CapSense_1_DEFAULT_SENSE_PERIOD           (CapSense_1_CSD_SNS_CLK_SOURCE)
    #endif /* (CapSense_1_CLK_SOURCE_DIRECT != CapSense_1_CSD_SNS_CLK_SOURCE) */

    #define CapSense_1_DEFAULT_MODULATION_MODE            (CapSense_1_DEFAULT_SENSE_PERIOD)

    /* SW_HS_P_SEL switches state for Coarse initialization of CMOD (sense path) */
    #if ((CapSense_1_ENABLE == CapSense_1_CSD_CSX_EN) || \
         (CapSense_1_ENABLE == CapSense_1_CSD_ISX_EN) || \
         (CapSense_1_ENABLE == CapSense_1_CSD_EN))
        #if (CapSense_1_CSD__CMOD_PAD == CapSense_1_CMOD_CONNECTION)
            #define CapSense_1_HS_P_SEL_COARSE_CMOD             (CapSense_1_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #elif (CapSense_1_CSD__CSHIELD_PAD == CapSense_1_CMOD_CONNECTION)
            #define CapSense_1_HS_P_SEL_COARSE_CMOD             (CapSense_1_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #else
            #define CapSense_1_HS_P_SEL_COARSE_CMOD             (CapSense_1_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #endif /* (CapSense_1_CSD__CMOD_PAD == CapSense_1_CMOD_CONNECTION) */
    #else
        #define CapSense_1_HS_P_SEL_COARSE_CMOD                 (0x00000000uL)
    #endif /* ((CapSense_1_ENABLE == CapSense_1_CSD_CSX_EN) && (CapSense_1_ENABLE == CapSense_1_CSD_EN)) */

    #if ((0u != CapSense_1_CSD_SHIELD_TANK_EN) && (CapSense_1_ENABLE == CapSense_1_CSD_SHIELD_EN))
        /* SW_HS_P_SEL switches state for Coarse initialization of CTANK (sense path) */
        #if (CapSense_1_CSD__CSH_TANK_PAD == CapSense_1_CTANK_CONNECTION)
            #define CapSense_1_HS_P_SEL_COARSE_TANK             (CapSense_1_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
            #define CapSense_1_HS_P_SEL_SCAN_TANK               (CapSense_1_SW_HS_P_SEL_SW_HMPT_STATIC_CLOSE)
        #elif (CapSense_1_CSD__CSHIELD_PAD == CapSense_1_CTANK_CONNECTION)
            #define CapSense_1_HS_P_SEL_COARSE_TANK             (CapSense_1_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
            #define CapSense_1_HS_P_SEL_SCAN_TANK               (CapSense_1_SW_HS_P_SEL_SW_HMPS_STATIC_CLOSE)
        #elif (CapSense_1_CSD__CMOD_PAD == CapSense_1_CTANK_CONNECTION)
            #define CapSense_1_HS_P_SEL_COARSE_TANK             (CapSense_1_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
            #define CapSense_1_HS_P_SEL_SCAN_TANK               (CapSense_1_SW_HS_P_SEL_SW_HMPM_STATIC_CLOSE)
        #else
            #define CapSense_1_HS_P_SEL_COARSE_TANK             (CapSense_1_SW_HS_P_SEL_SW_HMMA_STATIC_CLOSE)
            #define CapSense_1_HS_P_SEL_SCAN_TANK               (CapSense_1_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
        #endif /* (CapSense_1_CSD__CSH_TANK_PAD == CapSense_1_CTANK_CONNECTION) */
        #define CapSense_1_SW_HS_P_SEL_SCAN                     (CapSense_1_HS_P_SEL_SCAN_TANK)
    #else
        #define CapSense_1_HS_P_SEL_COARSE_TANK                 (0x00000000uL)
        #define CapSense_1_SW_HS_P_SEL_SCAN                     (CapSense_1_SW_HS_P_SEL_SW_HMMB_STATIC_CLOSE)
    #endif /* ((0u != CapSense_1_CSD__CSD_CSH_TANK_ENABLE) && (CapSense_1_ENABLE == CapSense_1_CSD_SHIELD_EN)) */

    #define CapSense_1_SW_HS_P_SEL_COARSE                 (CapSense_1_HS_P_SEL_COARSE_CMOD | CapSense_1_HS_P_SEL_COARSE_TANK)

    /***************************************
    * CSDv2 Registers shifts
    ***************************************/
    #define CapSense_1_SHIELD_DELAY_SHIFT                 (CYFLD_CSD_SHIELD_DELAY__OFFSET)
    #define CapSense_1_LFSR_SIZE_SHIFT                    (CYFLD_CSD_LFSR_SIZE__OFFSET)
    #define CapSense_1_RESULT_VAL1_BAD_CONVS_SHIFT        (CYFLD_CSD_BAD_CONVS__OFFSET)
    #define CapSense_1_SW_SHIELD_SEL_SW_HCBV_SHIFT        (CYFLD_CSD_SW_HCBV__OFFSET)

    /***************************************
    * LFSR Register masks
    ***************************************/
    #define CapSense_1_RESOLUTION_OFFSET                  (0u)
    #define CapSense_1_LFSR_TABLE_SIZE                    (4u)

    #define CapSense_1_PRS_LENGTH_2_BITS                  (0x00000003Lu)
    #define CapSense_1_PRS_LENGTH_3_BITS                  (0x00000007Lu)
    #define CapSense_1_PRS_LENGTH_4_BITS                  (0x0000000FLu)
    #define CapSense_1_PRS_LENGTH_5_BITS                  (0x0000001FLu)
    #define CapSense_1_PRS_LENGTH_8_BITS                  (0x000000FFLu)
    #define CapSense_1_PRS_LENGTH_12_BITS                 (0x00000FFFLu)

    #if(CapSense_1_ENABLE != CapSense_1_CSDV2_REF9P6UA_EN)
        #define CapSense_1_SNSCLK_SSC1_PERIOD                (3u)
        #define CapSense_1_SNSCLK_SSC2_PERIOD                (7u)
        #define CapSense_1_SNSCLK_SSC3_PERIOD                (15u)
        #define CapSense_1_SNSCLK_SSC4_PERIOD                (31u)

        #define CapSense_1_SNSCLK_SSC1_RANGE                 (1u)
        #define CapSense_1_SNSCLK_SSC2_RANGE                 (3u)
        #define CapSense_1_SNSCLK_SSC3_RANGE                 (7u)
        #define CapSense_1_SNSCLK_SSC4_RANGE                 (15u)
    #else

        #define CapSense_1_SNSCLK_SSC1_PERIOD                (63u)
        #define CapSense_1_SNSCLK_SSC2_PERIOD                (127u)
        #define CapSense_1_SNSCLK_SSC3_PERIOD                (511u)
        #define CapSense_1_SNSCLK_SSC4_PERIOD                (1023u)

        #define CapSense_1_SNSCLK_SSC1_RANGE                 (16u)
        #define CapSense_1_SNSCLK_SSC2_RANGE                 (16u)
        #define CapSense_1_SNSCLK_SSC3_RANGE                 (16u)
        #define CapSense_1_SNSCLK_SSC4_RANGE                 (16u)
    #endif /* (CapSense_1_ENABLE != CapSense_1_CSDV2_REF9P6UA_EN) */

    #define CapSense_1_LFSR_DITHER_PERCENTAGE             (10uL)
    #define CapSense_1_SNSCLK_SSC1_THRESHOLD              (CapSense_1_LFSR_DITHER_PERCENTAGE * CapSense_1_SNSCLK_SSC1_RANGE)
    #define CapSense_1_SNSCLK_SSC2_THRESHOLD              (CapSense_1_LFSR_DITHER_PERCENTAGE * CapSense_1_SNSCLK_SSC2_RANGE)
    #define CapSense_1_SNSCLK_SSC3_THRESHOLD              (CapSense_1_LFSR_DITHER_PERCENTAGE * CapSense_1_SNSCLK_SSC3_RANGE)
    #define CapSense_1_SNSCLK_SSC4_THRESHOLD              (CapSense_1_LFSR_DITHER_PERCENTAGE * CapSense_1_SNSCLK_SSC4_RANGE)

    #define CapSense_1_HFCLK_SNSCLK_FACTOR                (160u)
    #define CapSense_1_SKIP_INIT_CYCLES                   (4u)

#else

    /* CSDv1 CSD_CONFIG register masks    */
    #define CapSense_1_CONFIG_BYPASS_SEL_MASK         (0x00000004Lu)
    #define CapSense_1_CONFIG_FILTER_EN_MASK          (0x00000008Lu)
    #define CapSense_1_CONFIG_DUAL_CAP_EN_MASK        (0x00000010Lu)
    #define CapSense_1_CONFIG_PRS_CLEAR_MASK          (0x00000020Lu)
    #define CapSense_1_CONFIG_PRS_SELECT_MASK         (0x00000040Lu)
    #define CapSense_1_CONFIG_PRS_12_8_MASK           (0x00000080Lu)
    #define CapSense_1_CONFIG_SHIELD_DELAY_MASK       (0x00000600Lu)
    #define CapSense_1_CONFIG_SENSE_COMP_BW_MASK      (0x00000800Lu)
    #define CapSense_1_CONFIG_SENSE_EN_MASK           (0x00001000Lu)
    #define CapSense_1_CONFIG_REFBUF_EN_MASK          (0x00002000Lu)
    #define CapSense_1_CONFIG_COMP_MODE_MASK          (0x00004000Lu)
    #define CapSense_1_CONFIG_COMP_PIN_MASK           (0x00008000Lu)
    #define CapSense_1_CONFIG_POLARITY_MASK           (0x00010000Lu)
    #define CapSense_1_CONFIG_POLARITY2_MASK          (0x00020000Lu)
    #define CapSense_1_CONFIG_MUTUALCAP_EN_MASK       (0x00040000Lu)
    #define CapSense_1_CONFIG_SENSE_COMP_EN_MASK      (0x00080000Lu)
    #define CapSense_1_CONFIG_REFBUF_OUTSEL_MASK      (0x00200000Lu)
    #define CapSense_1_CONFIG_SENSE_INSEL_MASK        (0x00400000Lu)
    #define CapSense_1_CONFIG_REFBUF_DRV_MASK         (0x01800000Lu)
    #define CapSense_1_CONFIG_DDFTSEL_MASK            (0x1C000000Lu)
    #define CapSense_1_CONFIG_ADFTEN_MASK             (0x20000000Lu)
    #define CapSense_1_CONFIG_DDFT_COMP_MASK          (0x40000000Lu)
    #define CapSense_1_CONFIG_ENABLE_MASK             (0x80000000Lu)

    /* CSDv1 CSD_IDAC register masks  */
    #define CapSense_1_IDAC_MOD_MASK                  (0x000000FFLu)
    #define CapSense_1_IDAC_MOD_MODE_MASK             (0x00000300Lu)
    #define CapSense_1_IDAC_MOD_RANGE_MASK            (0x00000400Lu)
    #define CapSense_1_IDAC_POLARITY1_MIR_MASK        (0x00001000Lu)
    #define CapSense_1_IDAC_COMP_MASK                 (0x007F0000Lu)
    #define CapSense_1_IDAC_COMP_MODE_MASK            (0x03000000Lu)
    #define CapSense_1_IDAC_COMP_RANGE_MASK           (0x04000000Lu)
    #define CapSense_1_IDAC_POLARITY2_MIR_MASK        (0x10000000Lu)
    #define CapSense_1_IDAC_FEEDBACK_MODE_MASK        (0x40000000Lu)
    #define CapSense_1_IDAC_MOD_MODE_OFF              (0x00000000Lu)
    #define CapSense_1_IDAC_MOD_MODE_FIXED            (0x00000100Lu)
    #define CapSense_1_IDAC_MOD_MODE_VARIABLE         (0x00000200Lu)
    #define CapSense_1_IDAC_MOD_MODE_DSI              (0x00000300Lu)
    #define CapSense_1_IDAC_COMP_MODE_OFF             (0x00000000Lu)
    #define CapSense_1_IDAC_COMP_MODE_FIXED           (0x01000000Lu)
    #define CapSense_1_IDAC_COMP_MODE_VARIABLE        (0x02000000Lu)
    #define CapSense_1_IDAC_COMP_MODE_DSI             (0x03000000Lu)
    #define CapSense_1_IDAC_MOD_VALUE_SHIFT           (0u)
    #define CapSense_1_IDAC_MOD_CFG_MASK              (CapSense_1_IDAC_POLARITY1_MIR_MASK |\
                                                            CapSense_1_IDAC_MOD_RANGE_MASK |\
                                                            CapSense_1_IDAC_MOD_MODE_MASK |\
                                                            CapSense_1_IDAC_MOD_MASK)

    #define CapSense_1_IDAC_COMP_CFG_MASK              (CapSense_1_IDAC_POLARITY2_MIR_MASK |\
                                                            CapSense_1_IDAC_COMP_RANGE_MASK |\
                                                            CapSense_1_IDAC_COMP_MODE_MASK |\
                                                            CapSense_1_IDAC_COMP_MASK)

    /* CSDv1 CSD_COUNTER register masks   */
    #define CapSense_1_COUNTER_COUNTER_MASK           (0x0000FFFFLu)
    #define CapSense_1_COUNTER_PERIOD_MASK            (0xFFFF0000Lu)

    /* CSDv1 CSD_STATUS register masks    */
    #define CapSense_1_STATUS_CSD_CHARGE_MASK         (0x00000001Lu)
    #define CapSense_1_STATUS_CSD_SENSE_MASK          (0x00000002Lu)
    #define CapSense_1_STATUS_COMP_OUT_MASK           (0x00000004Lu)
    #define CapSense_1_STATUS_SAMPLE                  (0x00000008Lu)

    /* CSDv1 CSD_INTR, CSD_INTR_SET register masks  */
    #define CapSense_1_INTR_CSD_MASK                  (0x00000001Lu)
    #define CapSense_1_INTR_SET_CSD_MASK              (0x00000001Lu)
    #define CapSense_1_INTR_SET_MASK                  (CapSense_1_INTR_SET_CSD_MASK)

    /* CSDv1 CSD_PWM register masks   */
    #define CapSense_1_PWM_COUNT_MASK                 (0x0000000FLu)
    #define CapSense_1_PWM_SEL_MASK                   (0x00000030Lu)

    /* CSDv1 CSD_TRIM1/2 (for IDAC) register masks    */
    #define CapSense_1_IDAC_TRIM2_MOD_SNK_MASK        (0x0000000FLu)
    #define CapSense_1_IDAC_TRIM2_COMP_SNK_MASK       (0x000000F0Lu)
    #define CapSense_1_IDAC_TRIM1_MOD_SRC_MASK        (0x0000000FLu)
    #define CapSense_1_IDAC_TRIM1_COMP_SRC_MASK       (0x000000F0Lu)

    /* CSDv1 CSD_TRIM FLASH register masks    */
    #define CapSense_1_SFLASH_TRIM_IDAC_MOD_MASK      (0x0FLu)
    #define CapSense_1_SFLASH_TRIM_IDAC_COMP_MASK     (0xF0Lu)

    /* CSDv1 Clock register masks    */
    #define CapSense_1_SNSCLK_CMD_DIV_SHIFT           (0u)
    #define CapSense_1_SNSCLK_CMD_PA_DIV_SHIFT        (8u)
    #define CapSense_1_SNSCLK_CMD_DISABLE_SHIFT       (30u)
    #define CapSense_1_SNSCLK_CMD_ENABLE_SHIFT        (31u)
    #define CapSense_1_SNSCLK_CMD_DISABLE_MASK        ((uint32)((uint32)1u << CapSense_1_SNSCLK_CMD_DISABLE_SHIFT))
    #define CapSense_1_SNSCLK_CMD_ENABLE_MASK         ((uint32)((uint32)1u << CapSense_1_SNSCLK_CMD_ENABLE_SHIFT))

    /* CSDv1 CTANK masks    */
    #define CapSense_1_CTANK_DR_VDDIO                 (0x0u)
    #define CapSense_1_CTANK_DR_VSSIO                 (CapSense_1_DR_MASK << CapSense_1_CSH_SHIFT)

    #define CapSense_1_PRS_8_CONFIG                   CapSense_1_CONFIG_PRS_SELECT_MASK
    #define CapSense_1_PRS_12_CONFIG                  (CapSense_1_CONFIG_PRS_12_8_MASK |\
                                                            CapSense_1_CONFIG_PRS_SELECT_MASK)

    /* CSDv1 Initial PRS mode */
    #if (CapSense_1_CLK_SOURCE_PRS8 == CapSense_1_CSD_SNS_CLK_SOURCE)
        #define CapSense_1_DEFAULT_MODULATION_MODE    CapSense_1_CONFIG_PRS_SELECT_MASK

    #elif (CapSense_1_CLK_SOURCE_PRS12 == CapSense_1_CSD_SNS_CLK_SOURCE)
        #define CapSense_1_DEFAULT_MODULATION_MODE    (CapSense_1_CONFIG_PRS_12_8_MASK |\
                                                            CapSense_1_CONFIG_PRS_SELECT_MASK)
    #else
        #define CapSense_1_DEFAULT_MODULATION_MODE    (0u)
    #endif /* (CapSense_1_CSD_SNS_CLK_SOURCE == CapSense_1_PRS_8BITS) */

    #if (CapSense_1_DISABLE == CapSense_1_CSD2X_EN)

    /* CSDv1 Set IDAC polarity */
    #if (CapSense_1_CSD_IDAC_CONFIG == CapSense_1_IDAC_SINKING)
        #define CapSense_1_DEFAULT_IDAC_POLARITY      CapSense_1_CONFIG_POLARITY_MASK
        #define CapSense_1_CSH_DR_CONFIG              CapSense_1_CTANK_DR_VDDIO
    #else
        #define CapSense_1_DEFAULT_IDAC_POLARITY      (0u)
        #define CapSense_1_CSH_DR_CONFIG              CapSense_1_CTANK_DR_VSSIO
    #endif /* (CapSense_1_CSD_IDAC_CONFIG == CapSense_1_IDAC_SINKING) */

    /* Defining default CSD configuration according to settings in customizer. */
    #define CapSense_1_DEFAULT_CSD_CONFIG             (CapSense_1_CONFIG_SENSE_COMP_BW_MASK |\
                                                             CapSense_1_DEFAULT_IDAC_POLARITY |\
                                                             CapSense_1_CONFIG_SENSE_INSEL_MASK |\
                                                             CapSense_1_CONFIG_REFBUF_DRV_MASK)

    #define CapSense_1_CSD_ENABLE_MASK                (CapSense_1_CONFIG_ENABLE_MASK |\
                                                             CapSense_1_CONFIG_SENSE_EN_MASK |\
                                                             CapSense_1_CONFIG_SENSE_COMP_EN_MASK)

    /* CSDv1 Defining mask intended for clearing bits related to pre-charging options. */
    #define CapSense_1_PRECHARGE_CONFIG_MASK          (CapSense_1_CONFIG_REFBUF_EN_MASK |\
                                                             CapSense_1_CONFIG_COMP_MODE_MASK |\
                                                             CapSense_1_CONFIG_COMP_PIN_MASK  |\
                                                             CapSense_1_CONFIG_REFBUF_OUTSEL_MASK)

    #define CapSense_1_CMOD_PRECHARGE_CONFIG          (CapSense_1_DEFAULT_CSD_CONFIG |\
                                                             CapSense_1_CONFIG_REFBUF_EN_MASK |\
                                                             CapSense_1_CONFIG_COMP_PIN_MASK)

    #define CapSense_1_CMOD_PRECHARGE_CONFIG_CSD_EN   (CapSense_1_DEFAULT_CSD_CONFIG |\
                                                             CapSense_1_CSD_ENABLE_MASK |\
                                                             CapSense_1_CONFIG_REFBUF_EN_MASK |\
                                                             CapSense_1_CONFIG_COMP_PIN_MASK)


    /* CSDv1 Ctank pre-charge mode configuration */
    #if(CapSense_1_CSD_CSH_PRECHARGE_SRC == CapSense_1_CSH_PRECHARGE_VREF)
        #if (CapSense_1_ENABLE == CapSense_1_CSD_SHIELD_EN)
            #define  CapSense_1_CTANK_PRECHARGE_CONFIG    (CapSense_1_DEFAULT_CSD_CONFIG |\
                                                                 CapSense_1_CONFIG_REFBUF_EN_MASK |\
                                                                 CapSense_1_CONFIG_PRS_CLEAR_MASK |\
                                                                 CapSense_1_CONFIG_REFBUF_OUTSEL_MASK)
        #else
            #define  CapSense_1_CTANK_PRECHARGE_CONFIG    (CapSense_1_DEFAULT_CSD_CONFIG |\
                                                                 CapSense_1_CONFIG_REFBUF_OUTSEL_MASK |\
                                                                 CapSense_1_CONFIG_PRS_CLEAR_MASK)
        #endif /* (CapSense_1_ENABLE == CapSense_1_CSD_SHIELD_EN) */
    #else
        #define  CapSense_1_CTANK_PRECHARGE_CONFIG        (CapSense_1_DEFAULT_CSD_CONFIG |\
                                                                CapSense_1_CONFIG_REFBUF_OUTSEL_MASK |\
                                                                CapSense_1_CONFIG_REFBUF_EN_MASK |\
                                                                CapSense_1_CONFIG_COMP_MODE_MASK |\
                                                                CapSense_1_CONFIG_PRS_CLEAR_MASK |\
                                                                CapSense_1_CONFIG_COMP_PIN_MASK)
    #endif /* (CapSense_1_CSD_CSH_PRECHARGE_SRC == CapSense_1__CSH_PRECHARGE_IO_BUF) */

    #define  CapSense_1_CTANK_PRECHARGE_CONFIG_CSD_EN     (CapSense_1_CTANK_PRECHARGE_CONFIG |\
                                                                 CapSense_1_CONFIG_ENABLE_MASK |\
                                                                 CapSense_1_CONFIG_SENSE_COMP_EN_MASK)

    #endif /* (CapSense_1_DISABLE == CapSense_1_CSD2X_EN) */

    #define CapSense_1_RESOLUTION_OFFSET                  (16u)
    #define CapSense_1_PRS_LENGTH_12_BITS                 (0x00000FFFLu)
    #define CapSense_1_PRS_LENGTH_8_BITS                  (0x000000FFLu)
    #define CapSense_1_CSD_PRS_12_BIT                     (CapSense_1_CONFIG_PRS_12_8_MASK)
    #define CapSense_1_PRS_MODE_MASK                      (CapSense_1_CONFIG_PRS_12_8_MASK)

    /***************************************
    * CSDv1 Registers shifts
    ***************************************/
    #define CapSense_1_SHIELD_DELAY_SHIFT                 (0x09u)
    #define CapSense_1_IDAC_COMP_DATA_OFFSET              (16u)

#endif /* (CapSense_1_ENABLE == CapSense_1_CSDV2) */

    /* CSDv1 and CSDv2 Clock register masks    */
    #define CapSense_1_MODCLK_CMD_DIV_SHIFT               (0u)
    #define CapSense_1_MODCLK_CMD_PA_DIV_SHIFT            (8u)
    #define CapSense_1_MODCLK_CMD_DISABLE_SHIFT           (30u)
    #define CapSense_1_MODCLK_CMD_ENABLE_SHIFT            (31u)
    #define CapSense_1_MODCLK_CMD_DISABLE_MASK            ((uint32)((uint32)1u << CapSense_1_MODCLK_CMD_DISABLE_SHIFT))
    #define CapSense_1_MODCLK_CMD_ENABLE_MASK             ((uint32)((uint32)1u << CapSense_1_MODCLK_CMD_ENABLE_SHIFT))

/* CintB and CintA pin registers  */
#if ((CapSense_1_ENABLE == CapSense_1_CSX_EN) \
    || (CapSense_1_ENABLE == CapSense_1_ISX_EN) \
    || (CapSense_1_ENABLE == CapSense_1_CSD_CSX_EN) \
    || (CapSense_1_ENABLE == CapSense_1_CSD_ISX_EN))

    #define CapSense_1_CintA_PC_REG                       (* (reg32 *) CapSense_1_CintA__0__PC)
    #define CapSense_1_CintA_DR_REG                       (* (reg32 *) CapSense_1_CintA__0__DR)
    #define CapSense_1_CintA_HSIOM_REG                    (* (reg32 *) CapSense_1_CintA__0__HSIOM)
    #define CapSense_1_CintB_PC_REG                       (* (reg32 *) CapSense_1_CintB__0__PC)
    #define CapSense_1_CintB_DR_REG                       (* (reg32 *) CapSense_1_CintB__0__DR)
    #define CapSense_1_CintB_HSIOM_REG                    (* (reg32 *) CapSense_1_CintB__0__HSIOM)

    #define CapSense_1_CintA_PC_PTR                       ((reg32 *) CapSense_1_CintA__0__PC)
    #define CapSense_1_CintA_DR_PTR                       ((reg32 *) CapSense_1_CintA__0__DR)
    #define CapSense_1_CintA_HSIOM_PTR                    ((reg32 *) CapSense_1_CintA__0__HSIOM)
    #define CapSense_1_CintB_PC_PTR                       ((reg32 *) CapSense_1_CintB__0__PC)
    #define CapSense_1_CintB_DR_PTR                       ((reg32 *) CapSense_1_CintB__0__DR)
    #define CapSense_1_CintB_HSIOM_PTR                    ((reg32 *) CapSense_1_CintB__0__HSIOM)

    /* CintB and CintA pin masks                                                */
    #define CapSense_1_CintA_HSIOM_MASK                   ((uint32)CapSense_1_CintA__0__HSIOM_MASK)
    #define CapSense_1_CintA_HSIOM_SHIFT                  ((uint32)CapSense_1_CintA__0__HSIOM_SHIFT)
    #define CapSense_1_CintA_SHIFT                        ((uint32)CapSense_1_CintA__0__SHIFT)

    #define CapSense_1_CintB_HSIOM_MASK                   ((uint32)CapSense_1_CintB__0__HSIOM_MASK)
    #define CapSense_1_CintB_HSIOM_SHIFT                  ((uint32)CapSense_1_CintB__0__HSIOM_SHIFT)
    #define CapSense_1_CintB_SHIFT                        ((uint32)CapSense_1_CintB__0__SHIFT)

#endif  /* ((CapSense_1_ENABLE == CapSense_1_CSX_EN) || (CapSense_1_ENABLE == CapSense_1_CSD_CSX_EN)) */

/* CMOD and CSH capacitor port-pins registers */
#if ((CapSense_1_ENABLE == CapSense_1_CSD_EN) || \
     (CapSense_1_ENABLE == CapSense_1_CSD_CSX_EN) || \
     (CapSense_1_ENABLE == CapSense_1_CSD_ISX_EN))

    #define CapSense_1_CSH_PC_REG                         (* (reg32 *) CapSense_1_Csh__PC)
    #define CapSense_1_CSH_PC_PTR                         (  (reg32 *) CapSense_1_Csh__PC)
    #define CapSense_1_CSH_DR_REG                         (* (reg32 *) CapSense_1_Csh__DR)
    #define CapSense_1_CSH_DR_PTR                         (  (reg32 *) CapSense_1_Csh__DR)
    #define CapSense_1_CSH_HSIOM_REG                      (* (reg32 *) CapSense_1_Csh__0__HSIOM)
    #define CapSense_1_CSH_HSIOM_PTR                      (  (reg32 *) CapSense_1_Csh__0__HSIOM)

    #define CapSense_1_CMOD_PC_REG                        (* (reg32 *) CapSense_1_Cmod__PC)
    #define CapSense_1_CMOD_PC_PTR                        (  (reg32 *) CapSense_1_Cmod__PC)
    #define CapSense_1_CMOD_PC_SHIFT                      (CapSense_1_Cmod__0__SHIFT * 3u)
    #define CapSense_1_CMOD_DR_REG                        (* (reg32 *) CapSense_1_Cmod__DR)
    #define CapSense_1_CMOD_DR_PTR                        (  (reg32 *) CapSense_1_Cmod__DR)
    #define CapSense_1_CMOD_DR_SHIFT                      CapSense_1_Cmod__0__SHIFT
    #define CapSense_1_CMOD_HSIOM_REG                     (* (reg32 *) CapSense_1_Cmod__0__HSIOM)
    #define CapSense_1_CMOD_HSIOM_PTR                     (  (reg32 *) CapSense_1_Cmod__0__HSIOM)

    /* Cmod and Csh pin masks */
    #define CapSense_1_CMOD_HSIOM_MASK                    CapSense_1_Cmod__0__HSIOM_MASK
    #define CapSense_1_CMOD_HSIOM_SHIFT                   CapSense_1_Cmod__0__HSIOM_SHIFT
    #define CapSense_1_CSH_HSIOM_MASK                     CapSense_1_Csh__0__HSIOM_MASK
    #define CapSense_1_CSH_HSIOM_SHIFT                    CapSense_1_Csh__0__HSIOM_SHIFT
    #define CapSense_1_CSH_SHIFT                          CapSense_1_Csh__0__SHIFT
    #define CapSense_1_CSH_PC_SHIFT                       (CapSense_1_Csh__0__SHIFT * 3u)

#endif  /* ((CapSense_1_ENABLE == CapSense_1_CSD_EN) || (CapSense_1_ENABLE == CapSense_1_CSD_CSX_EN)) */

/* GPIO register masks */
#define CapSense_1_CSH_TO_AMUXBUS_B_MASK                  (0x00000007Lu)
#define CapSense_1_CSH_PC_MASK                            (0x00000007Lu)
#define CapSense_1_CSH_PC_STRONG_MODE                     (0x00000006Lu)

#define CapSense_1_HSIOM_SEL_MASK                         (0x0000000FLu)
#define CapSense_1_HSIOM_SEL_GPIO                         (0x00000000Lu)
#define CapSense_1_HSIOM_SEL_CSD_SENSE                    (0x00000004Lu)
#define CapSense_1_HSIOM_SEL_CSD_SHIELD                   (0x00000005Lu)
#define CapSense_1_HSIOM_SEL_AMUXA                        (0x00000006Lu)
#define CapSense_1_HSIOM_SEL_AMUXB                        (0x00000007Lu)
#define CapSense_1_HSIOM_SEL_ACT_0                        (0x00000008Lu)

#define CapSense_1_GPIO_PC_MASK                           (0x00000007Lu)
#define CapSense_1_GPIO_HIGHZ_MASK                        (0x00000007Lu)
#define CapSense_1_GPIO_STRGDRV                           (0x00000006Lu)

#define CapSense_1_SNS_GROUND_CONNECT                     (0x00000006Lu)

#define CapSense_1_GPIO_PC_BIT_SIZE                       (3u)

/***************************************
* API Constants
***************************************/

#define CapSense_1_MOD_CSD_CLK_12MHZ                      (12000000uL)
#define CapSense_1_MOD_CSD_CLK_24MHZ                      (24000000uL)
#define CapSense_1_MOD_CSD_CLK_48MHZ                      (48000000uL)

/* ISR Number to work with CyLib functions */
#if (CapSense_1_ENABLE == CapSense_1_CSD2X_EN)
    #define CapSense_1_ISR0_NUMBER                         (CapSense_1_ISR0__INTC_NUMBER)
    #define CapSense_1_ISR1_NUMBER                         (CapSense_1_ISR1__INTC_NUMBER)
#else
    #define CapSense_1_ISR_NUMBER                         (CapSense_1_ISR__INTC_NUMBER)
#endif /* (CapSense_1_ENABLE == CapSense_1_CSD2X_EN) */

/* Multi-frequency scanning constants */
#define CapSense_1_FREQ_CHANNEL_0                         (0u)
#define CapSense_1_FREQ_CHANNEL_1                         (1u)
#define CapSense_1_FREQ_CHANNEL_2                         (2u)

/* Bit-mask which says that scanning is not complete */
#if (CapSense_1_ENABLE == CapSense_1_CSD2X_EN)
    /* Bit 18: WIDGET BUSY flag status for CSD2X (scan is ccomplete for both channels */
    #define CapSense_1_STATUS_CSD01_BUSY_SIZE             (0x00000001Lu)
    #define CapSense_1_STATUS_CSD01_BUSY_SHIFT            (18u)
    #define CapSense_1_STATUS_CSD01_BUSY_MASK             (CapSense_1_STATUS_CSD01_BUSY_SIZE << CapSense_1_STATUS_CSD01_BUSY_SHIFT)

    #define CapSense_1_SW_STS_BUSY                        (CapSense_1_STATUS_CSD01_BUSY_MASK)
#else
    #define CapSense_1_SW_STS_BUSY                        (CapSense_1_STATUS_CSD0_MASK)
#endif  /* (CapSense_1_ENABLE == CapSense_1_CSD2X_EN) */
#define CapSense_1_NOT_BUSY                               (0u)

#define CapSense_1_WDGT_SW_STS_BUSY                       (CapSense_1_STATUS_WDGT0_BUSY_MASK)

/* Definition of time interval that is enough for charging 100nF capacitor */
#define CapSense_1_AVG_CYCLES_PER_LOOP                    (5u)
#define CapSense_1_MAX_CHARGE_TIME_US                     (100u)
#define CapSense_1_SOFTWARE_WDT_CYCLES_NUM                (((CYDEV_BCLK__SYSCLK__MHZ) * (CapSense_1_MAX_CHARGE_TIME_US)) /\
                                                                 (CapSense_1_AVG_CYCLES_PER_LOOP))

#define CapSense_1_DELAY_EXTRACYCLES_NUM                  (9u)
#define CapSense_1_GLITCH_ELIMINATION_CYCLES_CALC         (CapSense_1_CSD_PRESCAN_SETTLING_TIME * CYDEV_BCLK__SYSCLK__MHZ)
#define CapSense_1_CMOD_DISCHARGE_TIME                    (2u)
#define CapSense_1_CMOD_DISCHARGE_CYCLES_CALC             (CapSense_1_CMOD_DISCHARGE_TIME * CYDEV_BCLK__SYSCLK__MHZ)

#if(CapSense_1_GLITCH_ELIMINATION_CYCLES_CALC >= CapSense_1_DELAY_EXTRACYCLES_NUM)
    #define CapSense_1_GLITCH_ELIMINATION_CYCLES          (CapSense_1_GLITCH_ELIMINATION_CYCLES_CALC -\
                                                                CapSense_1_DELAY_EXTRACYCLES_NUM)
#else
    #define CapSense_1_GLITCH_ELIMINATION_CYCLES          (CapSense_1_GLITCH_ELIMINATION_CYCLES_CALC)
#endif /* (CapSense_1_GLITCH_ELIMINATION_CYCLES_CALC >= CapSense_1_DELAY_EXTRACYCLES_NUM) */

#if(CapSense_1_CMOD_DISCHARGE_CYCLES_CALC >= CapSense_1_DELAY_EXTRACYCLES_NUM)
    #define CapSense_1_CMOD_DISCHARGE_CYCLES              (CapSense_1_CMOD_DISCHARGE_CYCLES_CALC -\
                                                                CapSense_1_DELAY_EXTRACYCLES_NUM)
#else
    #define CapSense_1_CMOD_DISCHARGE_CYCLES              (CapSense_1_CMOD_DISCHARGE_CYCLES_CALC)
#endif /* (CapSense_1_CMOD_DISCHARGE_CYCLES_CALC >= CapSense_1_DELAY_EXTRACYCLES_NUM) */

#define CapSense_1_PRECHARGE_IDAC_MOD_VAL                 (0xF0u)
#define CapSense_1_CSD_IDAC_PRECHARGE_CONFIG              (CapSense_1_IDAC_MOD_MODE_VARIABLE |\
                                                                 CapSense_1_IDAC_MOD_RANGE_MASK |\
                                                                 CapSense_1_IDAC_FEEDBACK_MODE_MASK |\
                                                                 CapSense_1_PRECHARGE_IDAC_MOD_VAL)

#define CapSense_1_CNT_RESOLUTION_12_BITS                 (0x0FFF0000Lu)
#define CapSense_1_ONE_CYCLE                              (0x00010000Lu)
#define CapSense_1_RESOLUTION_16_BITS                     (0xFFFF0000Lu)
#define CapSense_1_DISCONNECT_IO_FLAG                     (1u)
#define CapSense_1_PRESCALERS_TBL_SIZE                    (16u)

/* Calibration constants */
#define CapSense_1_CALIBRATION_LEVEL_85                   (85u)
#define CapSense_1_PERCENTAGE_100                         (0x00000064Lu)
#define CapSense_1_IDAC_MOD_MAX_CALIB_ERROR_NEG           (10u)
#define CapSense_1_IDAC_MOD_MAX_CALIB_ERROR_POS           (10u)
#define CapSense_1_IDAC_MOD_MAX_INT_MATH_SHIFT            (16u)
#define CapSense_1_IDAC_MOD_MAX_CALIB_ERROR_MULT          ((((CapSense_1_PERCENTAGE_100 + CapSense_1_IDAC_MOD_MAX_CALIB_ERROR_POS + 1u) \
                                                                 << CapSense_1_IDAC_MOD_MAX_INT_MATH_SHIFT) / CapSense_1_PERCENTAGE_100))
#define CapSense_1_IDAC_MOD_MIN_CALIB_ERROR_MULT          ((((CapSense_1_PERCENTAGE_100 - CapSense_1_IDAC_MOD_MAX_CALIB_ERROR_NEG - 1u) \
                                                                 << CapSense_1_IDAC_MOD_MAX_INT_MATH_SHIFT) / CapSense_1_PERCENTAGE_100))

#if (CapSense_1_ENABLE == CapSense_1_CSDV2)
    #define CapSense_1_CSD_IDAC_BITS_USED                 (7u)
#else
    #define CapSense_1_CSD_IDAC_BITS_USED                 (8u)
#endif /* (CapSense_1_ENABLE == CapSense_1_CSDV2) */
#define CapSense_1_CAL_MIDDLE_BIT                         (1uL << (CapSense_1_CSD_IDAC_BITS_USED - 1u))
#define CapSense_1_MAX_16_BITS_VALUE                      (0x0000FFFFLu)
#define CapSense_1_MAX_SCAN_TIME                          (CapSense_1_MAX_16_BITS_VALUE * CapSense_1_CSD_SCANSPEED_DIVIDER)
#define CapSense_1_CALIBR_WATCHDOG_CYCLES_NUM             (CapSense_1_MAX_SCAN_TIME / CapSense_1_AVG_CYCLES_PER_LOOP)
#define CapSense_1_ALL_WIDGETS_WATCHDOG_CYCLES_NUM        (CapSense_1_TOTAL_WIDGETS * CapSense_1_CALIBR_WATCHDOG_CYCLES_NUM)

#if (CapSense_1_DISABLE == CapSense_1_CSD2X_EN)
    #if (CapSense_1_IDAC_GAIN_8X == CapSense_1_CSD_IDAC_GAIN)
        #define CapSense_1_CSD_IDAC_GAIN_VALUE_NA             (2400u)
    #elif (CapSense_1_IDAC_GAIN_HIGH == CapSense_1_CSD_IDAC_GAIN)
        #define CapSense_1_CSD_IDAC_GAIN_VALUE_NA             (2400u)
    #elif (CapSense_1_IDAC_GAIN_4X == CapSense_1_CSD_IDAC_GAIN)
        #define CapSense_1_CSD_IDAC_GAIN_VALUE_NA             (1200u)
    #elif (CapSense_1_IDAC_GAIN_MEDIUM == CapSense_1_CSD_IDAC_GAIN)
        #define CapSense_1_CSD_IDAC_GAIN_VALUE_NA             (300u)
    #else
        #define CapSense_1_CSD_IDAC_GAIN_VALUE_NA             (37u)
    #endif /* (CapSense_1_IDAC_GAIN_8X == CapSense_1_CSD_IDAC_GAIN) */
#endif /* (CapSense_1_DISABLE == CapSense_1_CSD2X_EN) */

#if (CapSense_1_ENABLE == CapSense_1_CSD_IDAC_COMP_EN)
    #define CapSense_1_CSD_DUAL_IDAC_FACTOR               (2u)
#else
    #define CapSense_1_CSD_DUAL_IDAC_FACTOR               (1u)
#endif /* (CapSense_1_ENABLE == CapSense_1_CSD_IDAC_COMP_EN) */

#define CapSense_1_EMPTY_SLOT                          (255u)

/***************************************
* Global software/external variables
***************************************/
#if ((CapSense_1_ENABLE == CapSense_1_CSD_CSX_EN) || \
     (CapSense_1_ENABLE == CapSense_1_ADC_EN))
    extern CapSense_1_SENSE_METHOD_ENUM CapSense_1_currentSenseMethod;
#endif /* ((CapSense_1_ENABLE == CapSense_1_CSD_CSX_EN) || \
     (CapSense_1_ENABLE == CapSense_1_ADC_EN)) */

#if(CapSense_1_ENABLE == CapSense_1_MULTI_FREQ_SCAN_EN)
    extern uint8 CapSense_1_scanFreqIndex;
    extern uint8 CapSense_1_immunity[CapSense_1_NUM_SCAN_FREQS];
#else
    extern const uint8 CapSense_1_scanFreqIndex;
#endif /* (CapSense_1_ENABLE == CapSense_1_MULTI_FREQ_SCAN_EN) */
#if (CapSense_1_ENABLE == CapSense_1_CSD2X_EN)
    extern volatile uint8 CapSense_1_widgetIndex0;
    extern volatile uint8 CapSense_1_sensorIndex0;
    extern volatile uint8 CapSense_1_widgetIndex1;
    extern volatile uint8 CapSense_1_sensorIndex1;
#else
    extern volatile uint8 CapSense_1_widgetIndex;
    extern volatile uint8 CapSense_1_sensorIndex;
#endif /* (CapSense_1_ENABLE == CapSense_1_CSD2X_EN) */
extern uint8 CapSense_1_requestScanAllWidget;
#if (CapSense_1_ENABLE == CapSense_1_CSD2X_EN)
    extern CapSense_1_RAM_SNS_STRUCT *CapSense_1_curRamSnsPtr0;
    extern CapSense_1_RAM_SNS_STRUCT *CapSense_1_curRamSnsPtr1;
#else
    extern CapSense_1_RAM_SNS_STRUCT *CapSense_1_curRamSnsPtr;
#endif /* (CapSense_1_ENABLE == CapSense_1_CSD2X_EN) */
#if ((CapSense_1_ENABLE == CapSense_1_CSD_GANGED_SNS_EN) || \
     (CapSense_1_ENABLE == CapSense_1_CSX_EN) || \
     (CapSense_1_ENABLE == CapSense_1_ISX_EN))
    #if (CapSense_1_ENABLE == CapSense_1_CSD2X_EN)
         extern CapSense_1_FLASH_WD_STRUCT const *CapSense_1_curFlashWdgtPtr0;
         extern CapSense_1_FLASH_WD_STRUCT const *CapSense_1_curFlashWdgtPtr1;
    #else
         extern CapSense_1_FLASH_WD_STRUCT const *CapSense_1_curFlashWdgtPtr;
    #endif /* (CapSense_1_ENABLE == CapSense_1_CSD2X_EN) */
#endif /* ((CapSense_1_ENABLE == CapSense_1_CSD_GANGED_SNS_EN) || \
           (CapSense_1_ENABLE == CapSense_1_CSX_EN))  */
#if (CapSense_1_ENABLE == CapSense_1_CSD_GANGED_SNS_EN)
    /*  Pointer to Flash structure holding info of sensor to be scanned  */
    #if (CapSense_1_ENABLE == CapSense_1_CSD2X_EN)
        extern CapSense_1_FLASH_SNS_STRUCT const *CapSense_1_curFlashSnsPtr0;
        extern CapSense_1_FLASH_SNS_STRUCT const *CapSense_1_curFlashSnsPtr1;
    #else
        extern CapSense_1_FLASH_SNS_STRUCT const *CapSense_1_curFlashSnsPtr;
    #endif /* (CapSense_1_ENABLE == CapSense_1_CSD2X_EN) */
#endif /* (CapSense_1_ENABLE == CapSense_1_CSD_GANGED_SNS_EN)  */
#if (CapSense_1_CSD_SS_DIS != CapSense_1_CSD_AUTOTUNE)
    extern uint8 CapSense_1_prescalersTuningDone;
    extern const uint8 CapSense_1_prescalerTable[CapSense_1_PRESCALERS_TBL_SIZE];
#endif /* (CapSense_1_CSD_SS_DIS != CapSense_1_CSD_AUTOTUNE) */
#if (CapSense_1_ENABLE == CapSense_1_CSD2X_EN)
    extern CapSense_1_FLASH_IO_STRUCT const *CapSense_1_curSnsIOPtr0;
    extern CapSense_1_FLASH_IO_STRUCT const *CapSense_1_curSnsIOPtr1;
#else
    extern CapSense_1_FLASH_IO_STRUCT const *CapSense_1_curSnsIOPtr;
#endif /* (CapSense_1_ENABLE == CapSense_1_CSD2X_EN) */

#endif /* End CY_SENSE_CapSense_1_SENSING_H */


/* [] END OF FILE */
