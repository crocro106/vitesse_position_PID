/***************************************************************************//**
* \file CapSense_1_Control.c
* \version 4.10
*
* \brief
* This file provides the source code to the Control module API of the Component.
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

#include "cytypes.h"
#include "CyLib.h"
#include "cyPm.h"
#include "CapSense_1_Configuration.h"
#include "CapSense_1_Structure.h"
#include "CapSense_1_Control.h"
#include "CapSense_1_Processing.h"
#include "CapSense_1_Filter.h"
#include "CapSense_1_Sensing.h"
#include "CapSense_1_Tuner.h"

#if (CapSense_1_ENABLE == CapSense_1_SELF_TEST_EN)
    #include "CapSense_1_SelfTest.h"
#endif

#if (0u != CapSense_1_ADC_EN)
    #include "CapSense_1_Adc.h"
#endif /* (0u != CapSense_1_ADC_EN) */

/***********************************************************************************************************************
* Local definition
***********************************************************************************************************************/
#define CapSense_1_INIT_DONE   (1u)
#define CapSense_1_INIT_NEEDED (0u)

/***********************************************************************************************************************
* Local variables
***********************************************************************************************************************/
static uint8 CapSense_1_InitVar = CapSense_1_INIT_NEEDED;

/*******************************************************************************
* Function Name: CapSense_1_Start
****************************************************************************//**
*
* \brief
*  Initializes Component hardware and firmware modules. This function should be 
*  called by the application program prior to calling any other function of the 
*  Component.
*
* \details
*  This function initializes the Component hardware and firmware modules and 
*  should be called by the application program prior to calling any other API
*  of the Component. When this function is called, the following tasks are 
*  executed as part of the initialization process:
*    1. Initialize the registers of the \ref group_structures variable 
*       CapSense_1_dsRam based on the user selection in Component 
*       configuration wizard. 
*    2. Configure the hardware to perform sensing.
*    \if SECTION_C_HIGH_LEVEL
*    3. If SmartSense Auto-tuning is selected for the CSD Tuning mode in the 
*       Basic tab, the auto-tuning algorithm is executed to set the optimal 
*       values for the hardware parameters of the widgets/sensors.
*    \endif
*    4. Calibrate the sensors and find the optimal values for IDACs of each 
*       widget / sensor, if Enable auto-calibration is enabled on the
*       Advanced -> Mode Setting subtab.
*    5. Perform a scan for all sensors and initialize the baseline history. 
*       During the scan, CPU is in the sleep mode to save power.
*    6. If the firmware filters are enabled in the Advanced General tab, the 
*       filter histories are also initialized.

*  Any next call of this API repeats an initialization process except for 
*  data structure initialization. Therefore, it is possible to change the 
*  Component configuration from the application program by writing to the 
*  data structure registers and calling this function again. This is also 
*  done inside the CapSense_1_RunTuner() function when a restart command 
*  is received. 
*
*  When the Component operation is stopped by the CapSense_1_Stop() 
*  function, the CapSense_1_Start() function repeats an initialization 
*  process including data structure initialization.
*
* \return
*  Returns the status of the initialization process. If CYRET_SUCCESS is not 
*  received, some of the initialization fails and the Component may not operate
*  as expected.
*
*******************************************************************************/
cystatus CapSense_1_Start(void)
{
    cystatus result;
    uint32 watchdogTimer;
    
    /* Initialize CapSense_1 modules */
    result = CapSense_1_Initialize();
   
    #if (CapSense_1_CSD_AUTOTUNE != CapSense_1_CSD_SS_DIS)
        if (CYRET_SUCCESS == result)
        {
            result = CapSense_1_SsAutoTune();
        }
    #endif /* #if (CapSense_1_CSD_AUTOTUNE != CapSense_1_CSD_SS_DIS) */

    #if (CapSense_1_ANY_NONSS_AUTOCAL)
        if (CYRET_SUCCESS == result)
        {
            result = CapSense_1_CalibrateAllWidgets();
        }
    #endif /* (CapSense_1_ANY_NONSS_AUTOCAL) */

    if (CYRET_SUCCESS == result)
    {
        result = CapSense_1_ScanAllWidgets();
    }

    if (CYRET_SUCCESS == result)
    {
        /* Wait for scan to finish. */
        watchdogTimer = CapSense_1_ALL_WIDGETS_WATCHDOG_CYCLES_NUM;
        while(CapSense_1_NOT_BUSY != CapSense_1_IsBusy()
              && (watchdogTimer != 0uL))
        {
            watchdogTimer--;
        }
    }
    CapSense_1_FtInitialize();
    CapSense_1_InitializeAllBaselines();

    #if (0u != CapSense_1_ADC_EN)
        CapSense_1_AdcInitialize();
    #endif /* (0u != CapSense_1_ADC_EN) */

    return result;
}

/*******************************************************************************
* Function Name: CapSense_1_Initialize
****************************************************************************//**
*
* \brief
*  This function initializes the CapSense_1 Component.
*
* \details
*  This API initializes all sub-modules of the CapSense_1 Component:
*   - Data Structure - set the default Component parameters defined in the Customizer.
*   - Data Processing - resets all widget statuses.
*   - Tuner - resets tuning state.
*   - Sensing - prepares CSD HW for operation.
*
*  Note that Data Structure module is initialized only once after the reset or
*  CapSense_1_Stop() API is called. The repeated calls of Initialize API
*  will not re-initialize Data Structure. This is done to preserve Component
*  parameters that user may set in runtime.
*
*  If default Component parameters are needed the CapSense_1_DsInitialize()
*  API must be called directly from the application code.
*
* \return
*  Return CYRET_SUCCESS if the initialization was successful.
*
*******************************************************************************/
cystatus CapSense_1_Initialize(void)
{
    cystatus result;

    /* The Data Structure and Tuner are initialized only once */
    if (CapSense_1_INIT_NEEDED == CapSense_1_InitVar)
    {
        CapSense_1_DsInitialize();
        CapSense_1_TuInitialize();
        CapSense_1_InitVar = CapSense_1_INIT_DONE;
    }

    CapSense_1_DpInitialize();

    result = CapSense_1_SsInitialize();

    return result;
}

/*******************************************************************************
* Function Name: CapSense_1_Stop
****************************************************************************//**
*
* \brief
*  Stops the Component operation.
*
* \details
*  This function stops the Component operation, no sensor scanning can be 
*  executed when the Component is stopped. Once stopped, the hardware block may 
*  be reconfigured by the application program for any other special usage. The 
*  Component operation can be resumed by calling the CapSense_1_Resume() 
*  function or the Component can be reset by calling the 
*  CapSense_1_Start() function.
*  
*  This function should be called when no scanning is in progress. 
*  I.e. CapSense_1_IsBusy() returns a non-busy status.
*
* \return
*  Returns the status of the stop process. If CYRET_SUCCESS is not received, 
*  the stop process fails and retries may be required.
*
*******************************************************************************/
cystatus CapSense_1_Stop(void)
{
    cystatus result = CYRET_SUCCESS;

    #if (CapSense_1_ENABLE == CapSense_1_ADC_EN)
        /* Release CSD resources */
        result = CapSense_1_SsReleaseResources();

        /* Release ADC resources */
        CapSense_1_AdcStop();
    #endif /* (CapSense_1_ENABLE == CapSense_1_ADC_EN) */

    CapSense_1_InitVar = CapSense_1_INIT_NEEDED;

    return result;
}

/*******************************************************************************
* Function Name: CapSense_1_Resume
****************************************************************************//**
*
* \brief
*  Resumes the Component operation if CapSense_1_Stop() function was 
*  called previously.
*
* \details
*  This function resumes the Component operation if the operation is stopped
*  previously by the CapSense_1_Stop() function. The following tasks are 
*  executed as part of the operation resume process:
*    1. Reset all Widgets/Sensors status.
*    2. Configure the hardware to perform capacitive sensing.
*
* \return
*  Returns the status of the resume process. If CYRET_SUCCESS is not received,
*  the resume process fails and retries may be required.
*
*******************************************************************************/
cystatus CapSense_1_Resume(void)
{
    cystatus result;

    /* The Tuner are initialized only once to do not break communication */
    if (CapSense_1_INIT_NEEDED == CapSense_1_InitVar)
    {
        CapSense_1_TuInitialize();
        CapSense_1_InitVar = CapSense_1_INIT_DONE;
    }
    CapSense_1_DpInitialize();

    result = CapSense_1_SsInitialize();

    return result;
}

/*******************************************************************************
* Function Name: CapSense_1_ProcessAllWidgets
****************************************************************************//**
*
* \brief
*  Performs full data processing of all enabled widgets.
*
* \details
*  This function performs all data processes for all enabled widgets in the 
*  Component. The following tasks are executed as part of processing all the 
*  widgets:
*    1. Apply raw-count filters to raw counts, if they are enabled in the 
*       customizer.
*    2. Update thresholds if the SmartSense Full Auto-Tuning is enabled in
*       the customizer.
*    3. Update the Baselines and Difference counts for all sensors.
*    4. Update the sensor and widget status (on/off), update centroid for 
*       sliders and X/Y position for touchpads.
*  
*  Disabled widgets are not processed. To disable/enable a widget, set 
*  appropriate values in the 
*  CapSense_1_WDGT_ENABLE<RegisterNumber>_PARAM_ID register using the
*  CapSense_1_SetParam() function.
*  This function should be called only after all the sensors in the Component
*  are scanned. Calling this function multiple times without sensor scanning
*  causes unexpected behavior.
*
*  If Self-test library is enabled this function executes baseline duplication
*  test. Refer to CapSense_1_CheckBaselineDuplication() for details.
*
* \return
*  Returns the status of the processing operation. If CYRET_SUCCESS is not received, 
*  the processing fails and retries may be required.
*
*******************************************************************************/
cystatus CapSense_1_ProcessAllWidgets(void)
{
    uint32 wdgtId;
    cystatus result = CYRET_SUCCESS;
    CapSense_1_FLASH_WD_STRUCT const *ptrFlashWdgt;

    ptrFlashWdgt = CapSense_1_dsFlash.wdgtArray;

    for (wdgtId = 0u; wdgtId < CapSense_1_TOTAL_WIDGETS; wdgtId++)
    {
        if (0uL != CapSense_1_GET_WIDGET_EN_STATUS(wdgtId))
        {
            switch(CapSense_1_GET_SENSE_METHOD(ptrFlashWdgt))
            {
            #if (0u != CapSense_1_TOTAL_CSD_WIDGETS)
                case CapSense_1_SENSE_METHOD_CSD_E:
                    result = CapSense_1_DpProcessCsdWidgetRawCounts(ptrFlashWdgt);
                    CapSense_1_DpProcessCsdWidgetStatus(wdgtId, ptrFlashWdgt);
                    break;
            #endif /* #if (0u != CapSense_1_TOTAL_CSD_WIDGETS) */

            #if (0u != CapSense_1_TOTAL_CSX_WIDGETS)
                case CapSense_1_SENSE_METHOD_CSX_E:
                    result = CapSense_1_DpProcessCsxWidgetRawCounts(ptrFlashWdgt);
                    CapSense_1_DpProcessCsxWidgetStatus(wdgtId, ptrFlashWdgt);
                    break;
            #endif /* #if (0u != CapSense_1_TOTAL_CSX_WIDGETS) */

            #if (0u != CapSense_1_TOTAL_ISX_WIDGETS)
                case CapSense_1_SENSE_METHOD_ISX_E:
                    result = CapSense_1_DpProcessIsxWidgetRawCounts(ptrFlashWdgt);
                    CapSense_1_DpProcessIsxWidgetStatus(wdgtId, ptrFlashWdgt);
                    break;
            #endif /* #if (0u != CapSense_1_TOTAL_ISX_WIDGETS) */

            default:
                CYASSERT(0u);
                break;
            }
                    
            #if (CapSense_1_ENABLE == CapSense_1_TST_BSLN_DUPLICATION_EN)
                if (CYRET_SUCCESS != result)
                {
                    CapSense_1_UpdateTestResultBaselineDuplication(wdgtId, result);
                    result = CYRET_BAD_DATA;
                }
            #endif /* (CapSense_1_ENABLE == CapSense_1_TST_BSLN_DUPLICATION_EN) */
                    
        }
        ptrFlashWdgt++;
    }
    return result;
}

/*******************************************************************************
* Function Name: CapSense_1_ProcessWidget
****************************************************************************//**
*
* \brief
*  Performs full data processing of the specified widget if it is enabled.
*
* \details
*  This function performs exactly the same tasks as 
*  CapSense_1_ProcessAllWidgets(), but only for a specified widget. This 
*  function can be used along with the CapSense_1_SetupWidget() and 
*  CapSense_1_Scan() functions to scan and process data for a specific
*  widget. This function should be called only after all the sensors in the 
*  widgets are scanned. A disabled widget is not processed by this function.
*  
*  The pipeline scan method (i.e. during scanning of a widget perform processing
*  of the previously scanned widget) can be implemented using this function and
*  it may reduce the total scan/process time, increase the refresh rate and 
*  decrease the power consumption.
*
*  If Self-test library is enabled this function executes baseline duplication
*  test. Refer to CapSense_1_CheckBaselineDuplication() for details.
*
* \param widgetId 
*  Specify the ID number of the widget to be processed. 
*  A macro for the widget ID can be found in the 
*  CapSense_1 Configuration header file defined as
*  CapSense_1_<WidgetName>_WDGT_ID
*
* \return
*  Returns the status of the widget processing:
*  - CYRET_SUCCESS if operation is successfully completed
*  - CYRET_BAD_PARAM if the input parameter is invalid
*  - CYRET_INVALID_STATE if the specified widget is disabled
*  - CYRET_BAD_DATA if processing was failed
*
*******************************************************************************/
cystatus CapSense_1_ProcessWidget(uint32 widgetId)
{
    cystatus result = CYRET_SUCCESS;
    CapSense_1_FLASH_WD_STRUCT const *ptrFlashWdgt;

    if (widgetId >= CapSense_1_TOTAL_WIDGETS)
    {
        result = CYRET_BAD_PARAM;
    }

    if ((CYRET_SUCCESS == result) && (0uL == CapSense_1_GET_WIDGET_EN_STATUS(widgetId)))
    {
        result = CYRET_INVALID_STATE;
    }

    if (CYRET_SUCCESS == result)
    {
        ptrFlashWdgt = &CapSense_1_dsFlash.wdgtArray[widgetId];

        switch(CapSense_1_GET_SENSE_METHOD(ptrFlashWdgt))
        {
        #if (0u != CapSense_1_TOTAL_CSD_WIDGETS)
            case CapSense_1_SENSE_METHOD_CSD_E:
                result = CapSense_1_DpProcessCsdWidgetRawCounts(ptrFlashWdgt);
                CapSense_1_DpProcessCsdWidgetStatus(widgetId, ptrFlashWdgt);
                break;
        #endif /* #if (0u != CapSense_1_TOTAL_CSD_WIDGETS) */

        #if (0u != CapSense_1_TOTAL_CSX_WIDGETS)
            case CapSense_1_SENSE_METHOD_CSX_E:
                result = CapSense_1_DpProcessCsxWidgetRawCounts(ptrFlashWdgt);
                CapSense_1_DpProcessCsxWidgetStatus(widgetId, ptrFlashWdgt);
                break;
        #endif /* #if (0u != CapSense_1_TOTAL_CSX_WIDGETS) */

        #if (0u != CapSense_1_TOTAL_ISX_WIDGETS)
            case CapSense_1_SENSE_METHOD_ISX_E:
                result = CapSense_1_DpProcessIsxWidgetRawCounts(ptrFlashWdgt);
                CapSense_1_DpProcessIsxWidgetStatus(widgetId, ptrFlashWdgt);
                break;
        #endif /* #if (0u != CapSense_1_TOTAL_ISX_WIDGETS) */

        default:
            CYASSERT(0u);
            break;
        }

        #if (CapSense_1_ENABLE == CapSense_1_TST_BSLN_DUPLICATION_EN)
            if (CYRET_SUCCESS != result)
            {
                CapSense_1_UpdateTestResultBaselineDuplication(widgetId, result);
                result = CYRET_BAD_DATA;
            }
        #endif /* (CapSense_1_ENABLE == CapSense_1_TST_BSLN_DUPLICATION_EN) */
    }
    return result;
}


/*******************************************************************************
* Function Name: CapSense_1_ProcessWidgetExt
****************************************************************************//**
*
* \brief
*  Performs customized data processing on the selected widget.
*
* \details
*  This function performs data processes for the specified widget specified by 
*  the mode parameter. The execution order of the requested operations is from 
*  LSB to MSB of the mode parameter. If a different order is needed, this API 
*  can be called multiple times with the required mode parameter. 
*  
*  This function can be used with any of the available scan functions. This 
*  function should be called only after all sensors in the specified widget are
*  scanned. Calling this function multiple times with the same mode without 
*  sensor scanning causes unexpected behavior. This function ignores the value 
*  of the wdgtEnable register. 
*  \if SECTION_C_LOW_LEVEL
*  The CapSense_1_PROCESS_CALC_NOISE and 
*  CapSense_1_PROCESS_THRESHOLDS flags are supported by the CSD sensing
*  method only when the auto-tuning mode is enabled.
*  \endif
*  The pipeline scan method (i.e. during scanning of a widget perform processing
*  of a previously scanned widget) can be implemented using this function and it
*  may reduce the total scan/process time, increase the refresh rate and 
*  decrease the power consumption.
*
*  If Self-test library is enabled this function executes baseline duplication
*  test. Refer to CapSense_1_CheckBaselineDuplication() for details.
*
* \param widgetId 
*  Specify the ID number of the widget to be processed. 
*  A macro for the widget ID can be found in the CapSense_1 Configuration header 
*  file defined as CapSense_1_<WidgetName>_WDGT_ID.

* \param mode 
*  Specify the type of widget processing that needs to be executed for the 
*  specified widget:
*    1.	Bits [31..6] - Reserved
*    2.	Bits [5..0] - CapSense_1_PROCESS_ALL - Execute all tasks
*    3.	Bit [5] - CapSense_1_PROCESS_STATUS - Update Status (on/off, 
*       centroid position)
*    \if SECTION_C_LOW_LEVEL
*    4.	Bit [4] - CapSense_1_PROCESS_THRESHOLDS - Update Thresholds 
*       (only in CSD auto-tuning mode)
*    5.	Bit [3] - CapSense_1_PROCESS_CALC_NOISE - Calculate Noise (only in
*       CSD auto-tuning mode)
*    \endif
*    6.	Bit [2] - CapSense_1_PROCESS_DIFFCOUNTS - Update Difference Counts
*    7.	Bit [1] - CapSense_1_PROCESS_BASELINE - Update Baselines
*    8.	Bit [0] - CapSense_1_PROCESS_FILTER - Run Firmware Filter
*
* \return
*  Returns the status of the widget processing operation:
*  - CYRET_SUCCESS if processing is successfully performed
*  - CYRET_BAD_PARAM if the input parameter is invalid
*  - CYRET_BAD_DATA if processing was failed
*
*******************************************************************************/
cystatus CapSense_1_ProcessWidgetExt(uint32 widgetId, uint32 mode)
{
    uint32 snsCount;
    cystatus result = CYRET_BAD_PARAM;
    CapSense_1_FLASH_WD_STRUCT const *ptrFlashWdgt;
    CapSense_1_PTR_FILTER_VARIANT fltrHistV;
    CapSense_1_RAM_SNS_STRUCT *ptrSns;

    #if (0u != CapSense_1_TOTAL_CSD_WIDGETS)
        uint32 isProxWdgt;
    #endif

    if (widgetId < CapSense_1_TOTAL_WIDGETS)
    {
        ptrFlashWdgt = &CapSense_1_dsFlash.wdgtArray[widgetId];
        snsCount = CapSense_1_GET_SNS_CNT_BY_PTR(ptrFlashWdgt);
        ptrSns = ptrFlashWdgt->ptr2SnsRam;
        fltrHistV.ptr = ptrFlashWdgt->ptr2FltrHistory;

        switch(CapSense_1_GET_SENSE_METHOD(ptrFlashWdgt))
        {
        #if (0u != CapSense_1_TOTAL_CSD_WIDGETS)
            case CapSense_1_SENSE_METHOD_CSD_E:
            {
                /* Determine if widget is type of proximity.
                 * The Proximity widgets use different filters and
                 * therefore have different filter history object structure */
                isProxWdgt =
                    (CapSense_1_GET_WIDGET_TYPE(ptrFlashWdgt) == CapSense_1_WD_PROXIMITY_E) ? 1Lu : 0Lu;

                /* Run the desired processing for the all CSD widget sensors */
                for (;snsCount-- > 0u;)
                {
                    result = CapSense_1_DpProcessCsdSensorRawCountsExt(ptrFlashWdgt, ptrSns, fltrHistV, mode);

                    #if (CapSense_1_ENABLE == CapSense_1_TST_BSLN_DUPLICATION_EN)
                        if (CYRET_SUCCESS != result)
                        {
                            result = (result | CapSense_1_TST_LSBYTE) & snsCount;
                        }
                    #endif /* (CapSense_1_ENABLE == CapSense_1_TST_BSLN_DUPLICATION_EN) */

                    /* Move to the next sensor and filter history objects */
                    ptrSns++;
                    CapSense_1_INC_FLTR_OBJ_VARIANT(isProxWdgt, fltrHistV);
                }

                if (0u != (mode & CapSense_1_PROCESS_STATUS))
                {
                    CapSense_1_DpProcessCsdWidgetStatus(widgetId, ptrFlashWdgt);
                }
                break;
            }
        #endif /* #if (0u != CapSense_1_TOTAL_CSD_WIDGETS) */

        #if (0u != CapSense_1_TOTAL_CSX_WIDGETS)
            case CapSense_1_SENSE_METHOD_CSX_E:

                #if (0u != CapSense_1_CSX_MULTIPHASE_TX_EN)
                    if ((0u != (mode & CapSense_1_PROCESS_DECONVOLUTION)) &&
                        (0u != (ptrFlashWdgt->staticConfig & CapSense_1_MULTIPHASE_TX_MASK)))
                    {
                        CapSense_1_DpDeconvolution(ptrFlashWdgt);
                    }
                #endif /* #if (0u != CapSense_1_CSX_MULTIPHASE_TX_EN) */

                /* Run the desired processing for the all CSX widget sensors */
                for (;snsCount-- > 0u;)
                {
                    result = CapSense_1_DpProcessCsxSensorRawCountsExt(ptrFlashWdgt, ptrSns, fltrHistV, mode);

                    #if (CapSense_1_ENABLE == CapSense_1_TST_BSLN_DUPLICATION_EN)
                        if (CYRET_SUCCESS != result)
                        {
                            result = (result | CapSense_1_TST_LSBYTE) & snsCount;
                        }
                    #endif /* (CapSense_1_ENABLE == CapSense_1_TST_BSLN_DUPLICATION_EN) */

                    /* Move to the next sensor and filter history objects */
                    ptrSns++;
                    CapSense_1_INC_FLTR_OBJ_VARIANT(0u, fltrHistV);
                }

                if (0u != (mode & CapSense_1_PROCESS_STATUS))
                {
                    CapSense_1_DpProcessCsxWidgetStatus(widgetId, ptrFlashWdgt);
                }
                break;
        #endif /* #if (0u != CapSense_1_TOTAL_CSX_WIDGETS) */

        #if (0u != CapSense_1_TOTAL_ISX_WIDGETS)
            case CapSense_1_SENSE_METHOD_ISX_E:
                /* Run the desired processing for the all ISX widget sensors */
                for (;snsCount-- > 0u;)
                {
                    result = CapSense_1_DpProcessIsxSensorRawCountsExt(ptrFlashWdgt, ptrSns, fltrHistV, mode);
                    
                    #if (CapSense_1_ENABLE == CapSense_1_TST_BSLN_DUPLICATION_EN)
                        if (CYRET_SUCCESS != result)
                        {
                            result = (result | CapSense_1_TST_LSBYTE) & snsCount;
                        }
                    #endif /* (CapSense_1_ENABLE == CapSense_1_TST_BSLN_DUPLICATION_EN) */
                    
                    /* Move to the next sensor and filter history objects */
                    ptrSns++;
                    CapSense_1_INC_FLTR_OBJ_VARIANT(0u, fltrHistV);
                }

                if (0u != (mode & CapSense_1_PROCESS_STATUS))
                {
                    CapSense_1_DpProcessIsxWidgetStatus(widgetId, ptrFlashWdgt);
                }
                break;
        #endif /* #if (0u != CapSense_1_TOTAL_ISX_WIDGETS) */
        
        default:
            CYASSERT(0u);
            break;
        }

        #if (CapSense_1_ENABLE == CapSense_1_TST_BSLN_DUPLICATION_EN)
            if (CYRET_SUCCESS != result)
            {
                CapSense_1_UpdateTestResultBaselineDuplication(widgetId, snsCount);
                result = CYRET_BAD_DATA;
            }
        #endif /* (CapSense_1_ENABLE == CapSense_1_TST_BSLN_DUPLICATION_EN) */
    }
    return result;
}

/*******************************************************************************
* Function Name: CapSense_1_ProcessSensorExt
****************************************************************************//**
*
* \brief
*  Performs customized data processing on the selected widget's sensor.
*
* \details
*  This function performs data processes for the specified sensor specified by
*  the mode parameter. The execution order of the requested operations is from 
*  LSB to MSB of the mode parameter. If a different order is needed, this 
*  function can be called multiple times with the required mode parameter.
*  
*  This function can be used with any of the available scan functions. This 
*  function should be called only after a specified sensor in the widget is 
*  scanned. Calling this function multiple times with the same mode without 
*  sensor scanning causes unexpected behavior. This function ignores the value 
*  of the wdgtEnable register. 
*  
*  \if SECTION_C_LOW_LEVEL
*  The CapSense_1_PROCESS_CALC_NOISE and 
*  CapSense_1_PROCESS_THRESHOLDS flags are supported by the CSD sensing 
*  method only when the auto-tuning mode is enabled.
*  \endif
*
*  The pipeline scan method (i.e. during scanning of a sensor perform processing
*  of a previously scanned sensor) can be implemented using this function and it
*  may reduce the total scan/process time, increase the refresh rate and 
*  decrease the power consumption.
*
*  If Self-test library is enabled this function executes baseline duplication
*  test. Refer to CapSense_1_CheckBaselineDuplication() for details.
*
* \param widgetId  
*  Specify the ID number of the widget to process one of its sensors. 
*  A macro for the widget ID can be found in the 
*  CapSense_1 Configuration header file defined as 
*  CapSense_1_<WidgetName>_WDGT_ID
*  
* \param sensorId  
*  Specify the ID number of the sensor within the widget to process it.
*  A macro for the sensor ID within a specified widget can be found in the
*  CapSense_1 Configuration header file defined as 
*  CapSense_1_<WidgetName>_SNS<SensorNumber>_ID
*  
* \param mode      
*  Specify the type of the sensor processing that needs to be executed for the
*  specified sensor:
*    1. Bits [31..5] - Reserved
*    2. Bits [4..0] - CapSense_1_PROCESS_ALL - Executes all tasks
*    \if SECTION_C_LOW_LEVEL
*    3. Bit [4] - CapSense_1_PROCESS_THRESHOLDS - Updates Thresholds (only
*       in auto-tuning mode)
*    4. Bit [3] - CapSense_1_PROCESS_CALC_NOISE - Calculates Noise (only 
*       in auto-tuning mode)
*    \endif
*    5. Bit [2] - CapSense_1_PROCESS_DIFFCOUNTS - Updates Difference Count
*    6. Bit [1] - CapSense_1_PROCESS_BASELINE - Updates Baseline
*    7. Bit [0] - CapSense_1_PROCESS_FILTER - Runs Firmware Filter
*
* \return
*  Returns the status of the sensor process operation:
*  - CYRET_SUCCESS if processing is successfully performed
*  - CYRET_BAD_PARAM if the input parameter is invalid
*  - CYRET_BAD_DATA if processing was failed
*
*******************************************************************************/
cystatus CapSense_1_ProcessSensorExt(uint32 widgetId, uint32 sensorId, uint32 mode)
{
    cystatus result = CYRET_BAD_PARAM;
    CapSense_1_FLASH_WD_STRUCT const *ptrFlashWdgt;
    CapSense_1_PTR_FILTER_VARIANT fltrHistV;
    CapSense_1_RAM_SNS_STRUCT *ptrSns;

    if ((widgetId < CapSense_1_TOTAL_WIDGETS) && (sensorId < CapSense_1_GET_SENSOR_COUNT(widgetId)))
    {
        result = CYRET_SUCCESS;

        ptrFlashWdgt = &CapSense_1_dsFlash.wdgtArray[widgetId];
        fltrHistV.ptr = ptrFlashWdgt->ptr2FltrHistory;
        ptrSns = ptrFlashWdgt->ptr2SnsRam;
        ptrSns += sensorId;

        switch(CapSense_1_GET_SENSE_METHOD(ptrFlashWdgt))
        {
        #if (0u != CapSense_1_TOTAL_CSD_WIDGETS)
            case CapSense_1_SENSE_METHOD_CSD_E:
                if (CapSense_1_WD_PROXIMITY_E == (CapSense_1_WD_TYPE_ENUM)ptrFlashWdgt->wdgtType)
                {
                    #if (0u != CapSense_1_PROX_RC_FILTER_EN)
                        fltrHistV.ptr = &fltrHistV.ptrProx[sensorId];
                    #endif /* #if (0u != CapSense_1_PROX_RC_FILTER_EN) */
                }
                else
                {
                    #if (0u != CapSense_1_REGULAR_RC_FILTER_EN)
                        fltrHistV.ptr = &fltrHistV.ptrRegular[sensorId];
                    #endif /* #if (0u != CapSense_1_REGULAR_RC_FILTER_EN) */
                }

                result = CapSense_1_DpProcessCsdSensorRawCountsExt(ptrFlashWdgt, ptrSns, fltrHistV, mode);
                break;
        #endif /* #if (0u != CapSense_1_TOTAL_CSD_WIDGETS) */

        #if (0u != CapSense_1_TOTAL_CSX_WIDGETS)
            case CapSense_1_SENSE_METHOD_CSX_E:
                #if (0u != CapSense_1_REGULAR_RC_FILTER_EN)
                    fltrHistV.ptr = &fltrHistV.ptrRegular[sensorId];
                #endif /* #if (0u != CapSense_1_REGULAR_RC_FILTER_EN) */

                result = CapSense_1_DpProcessCsxSensorRawCountsExt(ptrFlashWdgt, ptrSns, fltrHistV, mode);
                break;
        #endif /* #if (0u != CapSense_1_TOTAL_CSX_WIDGETS) */
        
        #if (0u != CapSense_1_TOTAL_ISX_WIDGETS)
            case CapSense_1_SENSE_METHOD_ISX_E:
                if (CapSense_1_WD_PROXIMITY_E == (CapSense_1_WD_TYPE_ENUM)ptrFlashWdgt->wdgtType)
                {
                    #if (0u != CapSense_1_PROX_RC_FILTER_EN)
                        fltrHistV.ptr = &fltrHistV.ptrProx[sensorId];
                    #endif /* #if (0u != CapSense_1_PROX_RC_FILTER_EN) */
                }
                else
                {
                    #if (0u != CapSense_1_REGULAR_RC_FILTER_EN)
                        fltrHistV.ptr = &fltrHistV.ptrRegular[sensorId];
                    #endif /* #if (0u != CapSense_1_REGULAR_RC_FILTER_EN) */
                }

                result = CapSense_1_DpProcessIsxSensorRawCountsExt(ptrFlashWdgt, ptrSns, fltrHistV, mode);
                break;
        #endif /* #if (0u != CapSense_1_TOTAL_ISX_WIDGETS) */

        default:
            CYASSERT(0u);
            break;
        }
                
        #if (CapSense_1_ENABLE == CapSense_1_TST_BSLN_DUPLICATION_EN)
            if (CYRET_SUCCESS != result)
            {
                CapSense_1_UpdateTestResultBaselineDuplication(widgetId, sensorId);
                result = CYRET_BAD_DATA;
            }
        #endif /* (CapSense_1_ENABLE == CapSense_1_TST_BSLN_DUPLICATION_EN) */
        
    }
    return result;
}

/*******************************************************************************
* Function Name: CapSense_1_Sleep
****************************************************************************//**
*
* \brief
*  Prepares the Component to deep sleep.
*
* \details
*  Currently this function is empty and exists as a place for future updates, 
*  this function shall be used to prepare the Component to enter deep sleep.
*
*******************************************************************************/
void CapSense_1_Sleep(void)
{
}


/*******************************************************************************
* Function Name: CapSense_1_Wakeup
****************************************************************************//**
*
* \brief
*  This function shall be used to resume the Component after exiting deep sleep.
*
* \details
*  This function resumes the Component after sleep.
*
*******************************************************************************/
void CapSense_1_Wakeup(void)
{
	#if(CapSense_1_ENABLE == CapSense_1_CSDV2)
		#if(CapSense_1_CSDV2_ANALOG_WAKEUP_DELAY_US > 0uL)
			CyDelayUs(CapSense_1_CSDV2_ANALOG_WAKEUP_DELAY_US);
		#endif /* (CapSense_1_CSDV2_ANALOG_WAKEUP_DELAY_US > 0uL) */
    #endif /* (CapSense_1_ENABLE == CapSense_1_CSDV2) */
}


/* [] END OF FILE */
