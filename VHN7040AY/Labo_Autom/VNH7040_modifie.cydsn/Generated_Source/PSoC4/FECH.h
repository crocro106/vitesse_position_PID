/*******************************************************************************
* File Name: FECH.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the FECH
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_FECH_H)
#define CY_TCPWM_FECH_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} FECH_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  FECH_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define FECH_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define FECH_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define FECH_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define FECH_QUAD_ENCODING_MODES            (0lu)
#define FECH_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define FECH_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define FECH_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define FECH_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define FECH_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define FECH_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define FECH_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define FECH_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define FECH_TC_RUN_MODE                    (0lu)
#define FECH_TC_COUNTER_MODE                (0lu)
#define FECH_TC_COMP_CAP_MODE               (2lu)
#define FECH_TC_PRESCALER                   (0lu)

/* Signal modes */
#define FECH_TC_RELOAD_SIGNAL_MODE          (0lu)
#define FECH_TC_COUNT_SIGNAL_MODE           (3lu)
#define FECH_TC_START_SIGNAL_MODE           (0lu)
#define FECH_TC_STOP_SIGNAL_MODE            (0lu)
#define FECH_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define FECH_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define FECH_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define FECH_TC_START_SIGNAL_PRESENT        (0lu)
#define FECH_TC_STOP_SIGNAL_PRESENT         (0lu)
#define FECH_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define FECH_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define FECH_PWM_KILL_EVENT                 (0lu)
#define FECH_PWM_STOP_EVENT                 (0lu)
#define FECH_PWM_MODE                       (4lu)
#define FECH_PWM_OUT_N_INVERT               (0lu)
#define FECH_PWM_OUT_INVERT                 (0lu)
#define FECH_PWM_ALIGN                      (0lu)
#define FECH_PWM_RUN_MODE                   (0lu)
#define FECH_PWM_DEAD_TIME_CYCLE            (0lu)
#define FECH_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define FECH_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define FECH_PWM_COUNT_SIGNAL_MODE          (3lu)
#define FECH_PWM_START_SIGNAL_MODE          (0lu)
#define FECH_PWM_STOP_SIGNAL_MODE           (0lu)
#define FECH_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define FECH_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define FECH_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define FECH_PWM_START_SIGNAL_PRESENT       (0lu)
#define FECH_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define FECH_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define FECH_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define FECH_TC_PERIOD_VALUE                (3lu)
#define FECH_TC_COMPARE_VALUE               (65535lu)
#define FECH_TC_COMPARE_BUF_VALUE           (65535lu)
#define FECH_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define FECH_PWM_PERIOD_VALUE               (3lu)
#define FECH_PWM_PERIOD_BUF_VALUE           (65535lu)
#define FECH_PWM_PERIOD_SWAP                (0lu)
#define FECH_PWM_COMPARE_VALUE              (1lu)
#define FECH_PWM_COMPARE_BUF_VALUE          (65535lu)
#define FECH_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define FECH__LEFT 0
#define FECH__RIGHT 1
#define FECH__CENTER 2
#define FECH__ASYMMETRIC 3

#define FECH__X1 0
#define FECH__X2 1
#define FECH__X4 2

#define FECH__PWM 4
#define FECH__PWM_DT 5
#define FECH__PWM_PR 6

#define FECH__INVERSE 1
#define FECH__DIRECT 0

#define FECH__CAPTURE 2
#define FECH__COMPARE 0

#define FECH__TRIG_LEVEL 3
#define FECH__TRIG_RISING 0
#define FECH__TRIG_FALLING 1
#define FECH__TRIG_BOTH 2

#define FECH__INTR_MASK_TC 1
#define FECH__INTR_MASK_CC_MATCH 2
#define FECH__INTR_MASK_NONE 0
#define FECH__INTR_MASK_TC_CC 3

#define FECH__UNCONFIG 8
#define FECH__TIMER 1
#define FECH__QUAD 3
#define FECH__PWM_SEL 7

#define FECH__COUNT_UP 0
#define FECH__COUNT_DOWN 1
#define FECH__COUNT_UPDOWN0 2
#define FECH__COUNT_UPDOWN1 3


/* Prescaler */
#define FECH_PRESCALE_DIVBY1                ((uint32)(0u << FECH_PRESCALER_SHIFT))
#define FECH_PRESCALE_DIVBY2                ((uint32)(1u << FECH_PRESCALER_SHIFT))
#define FECH_PRESCALE_DIVBY4                ((uint32)(2u << FECH_PRESCALER_SHIFT))
#define FECH_PRESCALE_DIVBY8                ((uint32)(3u << FECH_PRESCALER_SHIFT))
#define FECH_PRESCALE_DIVBY16               ((uint32)(4u << FECH_PRESCALER_SHIFT))
#define FECH_PRESCALE_DIVBY32               ((uint32)(5u << FECH_PRESCALER_SHIFT))
#define FECH_PRESCALE_DIVBY64               ((uint32)(6u << FECH_PRESCALER_SHIFT))
#define FECH_PRESCALE_DIVBY128              ((uint32)(7u << FECH_PRESCALER_SHIFT))

/* TCPWM set modes */
#define FECH_MODE_TIMER_COMPARE             ((uint32)(FECH__COMPARE         <<  \
                                                                  FECH_MODE_SHIFT))
#define FECH_MODE_TIMER_CAPTURE             ((uint32)(FECH__CAPTURE         <<  \
                                                                  FECH_MODE_SHIFT))
#define FECH_MODE_QUAD                      ((uint32)(FECH__QUAD            <<  \
                                                                  FECH_MODE_SHIFT))
#define FECH_MODE_PWM                       ((uint32)(FECH__PWM             <<  \
                                                                  FECH_MODE_SHIFT))
#define FECH_MODE_PWM_DT                    ((uint32)(FECH__PWM_DT          <<  \
                                                                  FECH_MODE_SHIFT))
#define FECH_MODE_PWM_PR                    ((uint32)(FECH__PWM_PR          <<  \
                                                                  FECH_MODE_SHIFT))

/* Quad Modes */
#define FECH_MODE_X1                        ((uint32)(FECH__X1              <<  \
                                                                  FECH_QUAD_MODE_SHIFT))
#define FECH_MODE_X2                        ((uint32)(FECH__X2              <<  \
                                                                  FECH_QUAD_MODE_SHIFT))
#define FECH_MODE_X4                        ((uint32)(FECH__X4              <<  \
                                                                  FECH_QUAD_MODE_SHIFT))

/* Counter modes */
#define FECH_COUNT_UP                       ((uint32)(FECH__COUNT_UP        <<  \
                                                                  FECH_UPDOWN_SHIFT))
#define FECH_COUNT_DOWN                     ((uint32)(FECH__COUNT_DOWN      <<  \
                                                                  FECH_UPDOWN_SHIFT))
#define FECH_COUNT_UPDOWN0                  ((uint32)(FECH__COUNT_UPDOWN0   <<  \
                                                                  FECH_UPDOWN_SHIFT))
#define FECH_COUNT_UPDOWN1                  ((uint32)(FECH__COUNT_UPDOWN1   <<  \
                                                                  FECH_UPDOWN_SHIFT))

/* PWM output invert */
#define FECH_INVERT_LINE                    ((uint32)(FECH__INVERSE         <<  \
                                                                  FECH_INV_OUT_SHIFT))
#define FECH_INVERT_LINE_N                  ((uint32)(FECH__INVERSE         <<  \
                                                                  FECH_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define FECH_TRIG_RISING                    ((uint32)FECH__TRIG_RISING)
#define FECH_TRIG_FALLING                   ((uint32)FECH__TRIG_FALLING)
#define FECH_TRIG_BOTH                      ((uint32)FECH__TRIG_BOTH)
#define FECH_TRIG_LEVEL                     ((uint32)FECH__TRIG_LEVEL)

/* Interrupt mask */
#define FECH_INTR_MASK_TC                   ((uint32)FECH__INTR_MASK_TC)
#define FECH_INTR_MASK_CC_MATCH             ((uint32)FECH__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define FECH_CC_MATCH_SET                   (0x00u)
#define FECH_CC_MATCH_CLEAR                 (0x01u)
#define FECH_CC_MATCH_INVERT                (0x02u)
#define FECH_CC_MATCH_NO_CHANGE             (0x03u)
#define FECH_OVERLOW_SET                    (0x00u)
#define FECH_OVERLOW_CLEAR                  (0x04u)
#define FECH_OVERLOW_INVERT                 (0x08u)
#define FECH_OVERLOW_NO_CHANGE              (0x0Cu)
#define FECH_UNDERFLOW_SET                  (0x00u)
#define FECH_UNDERFLOW_CLEAR                (0x10u)
#define FECH_UNDERFLOW_INVERT               (0x20u)
#define FECH_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define FECH_PWM_MODE_LEFT                  (FECH_CC_MATCH_CLEAR        |   \
                                                         FECH_OVERLOW_SET           |   \
                                                         FECH_UNDERFLOW_NO_CHANGE)
#define FECH_PWM_MODE_RIGHT                 (FECH_CC_MATCH_SET          |   \
                                                         FECH_OVERLOW_NO_CHANGE     |   \
                                                         FECH_UNDERFLOW_CLEAR)
#define FECH_PWM_MODE_ASYM                  (FECH_CC_MATCH_INVERT       |   \
                                                         FECH_OVERLOW_SET           |   \
                                                         FECH_UNDERFLOW_CLEAR)

#if (FECH_CY_TCPWM_V2)
    #if(FECH_CY_TCPWM_4000)
        #define FECH_PWM_MODE_CENTER                (FECH_CC_MATCH_INVERT       |   \
                                                                 FECH_OVERLOW_NO_CHANGE     |   \
                                                                 FECH_UNDERFLOW_CLEAR)
    #else
        #define FECH_PWM_MODE_CENTER                (FECH_CC_MATCH_INVERT       |   \
                                                                 FECH_OVERLOW_SET           |   \
                                                                 FECH_UNDERFLOW_CLEAR)
    #endif /* (FECH_CY_TCPWM_4000) */
#else
    #define FECH_PWM_MODE_CENTER                (FECH_CC_MATCH_INVERT       |   \
                                                             FECH_OVERLOW_NO_CHANGE     |   \
                                                             FECH_UNDERFLOW_CLEAR)
#endif /* (FECH_CY_TCPWM_NEW) */

/* Command operations without condition */
#define FECH_CMD_CAPTURE                    (0u)
#define FECH_CMD_RELOAD                     (8u)
#define FECH_CMD_STOP                       (16u)
#define FECH_CMD_START                      (24u)

/* Status */
#define FECH_STATUS_DOWN                    (1u)
#define FECH_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   FECH_Init(void);
void   FECH_Enable(void);
void   FECH_Start(void);
void   FECH_Stop(void);

void   FECH_SetMode(uint32 mode);
void   FECH_SetCounterMode(uint32 counterMode);
void   FECH_SetPWMMode(uint32 modeMask);
void   FECH_SetQDMode(uint32 qdMode);

void   FECH_SetPrescaler(uint32 prescaler);
void   FECH_TriggerCommand(uint32 mask, uint32 command);
void   FECH_SetOneShot(uint32 oneShotEnable);
uint32 FECH_ReadStatus(void);

void   FECH_SetPWMSyncKill(uint32 syncKillEnable);
void   FECH_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   FECH_SetPWMDeadTime(uint32 deadTime);
void   FECH_SetPWMInvert(uint32 mask);

void   FECH_SetInterruptMode(uint32 interruptMask);
uint32 FECH_GetInterruptSourceMasked(void);
uint32 FECH_GetInterruptSource(void);
void   FECH_ClearInterrupt(uint32 interruptMask);
void   FECH_SetInterrupt(uint32 interruptMask);

void   FECH_WriteCounter(uint32 count);
uint32 FECH_ReadCounter(void);

uint32 FECH_ReadCapture(void);
uint32 FECH_ReadCaptureBuf(void);

void   FECH_WritePeriod(uint32 period);
uint32 FECH_ReadPeriod(void);
void   FECH_WritePeriodBuf(uint32 periodBuf);
uint32 FECH_ReadPeriodBuf(void);

void   FECH_WriteCompare(uint32 compare);
uint32 FECH_ReadCompare(void);
void   FECH_WriteCompareBuf(uint32 compareBuf);
uint32 FECH_ReadCompareBuf(void);

void   FECH_SetPeriodSwap(uint32 swapEnable);
void   FECH_SetCompareSwap(uint32 swapEnable);

void   FECH_SetCaptureMode(uint32 triggerMode);
void   FECH_SetReloadMode(uint32 triggerMode);
void   FECH_SetStartMode(uint32 triggerMode);
void   FECH_SetStopMode(uint32 triggerMode);
void   FECH_SetCountMode(uint32 triggerMode);

void   FECH_SaveConfig(void);
void   FECH_RestoreConfig(void);
void   FECH_Sleep(void);
void   FECH_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define FECH_BLOCK_CONTROL_REG              (*(reg32 *) FECH_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define FECH_BLOCK_CONTROL_PTR              ( (reg32 *) FECH_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define FECH_COMMAND_REG                    (*(reg32 *) FECH_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define FECH_COMMAND_PTR                    ( (reg32 *) FECH_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define FECH_INTRRUPT_CAUSE_REG             (*(reg32 *) FECH_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define FECH_INTRRUPT_CAUSE_PTR             ( (reg32 *) FECH_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define FECH_CONTROL_REG                    (*(reg32 *) FECH_cy_m0s8_tcpwm_1__CTRL )
#define FECH_CONTROL_PTR                    ( (reg32 *) FECH_cy_m0s8_tcpwm_1__CTRL )
#define FECH_STATUS_REG                     (*(reg32 *) FECH_cy_m0s8_tcpwm_1__STATUS )
#define FECH_STATUS_PTR                     ( (reg32 *) FECH_cy_m0s8_tcpwm_1__STATUS )
#define FECH_COUNTER_REG                    (*(reg32 *) FECH_cy_m0s8_tcpwm_1__COUNTER )
#define FECH_COUNTER_PTR                    ( (reg32 *) FECH_cy_m0s8_tcpwm_1__COUNTER )
#define FECH_COMP_CAP_REG                   (*(reg32 *) FECH_cy_m0s8_tcpwm_1__CC )
#define FECH_COMP_CAP_PTR                   ( (reg32 *) FECH_cy_m0s8_tcpwm_1__CC )
#define FECH_COMP_CAP_BUF_REG               (*(reg32 *) FECH_cy_m0s8_tcpwm_1__CC_BUFF )
#define FECH_COMP_CAP_BUF_PTR               ( (reg32 *) FECH_cy_m0s8_tcpwm_1__CC_BUFF )
#define FECH_PERIOD_REG                     (*(reg32 *) FECH_cy_m0s8_tcpwm_1__PERIOD )
#define FECH_PERIOD_PTR                     ( (reg32 *) FECH_cy_m0s8_tcpwm_1__PERIOD )
#define FECH_PERIOD_BUF_REG                 (*(reg32 *) FECH_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define FECH_PERIOD_BUF_PTR                 ( (reg32 *) FECH_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define FECH_TRIG_CONTROL0_REG              (*(reg32 *) FECH_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define FECH_TRIG_CONTROL0_PTR              ( (reg32 *) FECH_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define FECH_TRIG_CONTROL1_REG              (*(reg32 *) FECH_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define FECH_TRIG_CONTROL1_PTR              ( (reg32 *) FECH_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define FECH_TRIG_CONTROL2_REG              (*(reg32 *) FECH_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define FECH_TRIG_CONTROL2_PTR              ( (reg32 *) FECH_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define FECH_INTERRUPT_REQ_REG              (*(reg32 *) FECH_cy_m0s8_tcpwm_1__INTR )
#define FECH_INTERRUPT_REQ_PTR              ( (reg32 *) FECH_cy_m0s8_tcpwm_1__INTR )
#define FECH_INTERRUPT_SET_REG              (*(reg32 *) FECH_cy_m0s8_tcpwm_1__INTR_SET )
#define FECH_INTERRUPT_SET_PTR              ( (reg32 *) FECH_cy_m0s8_tcpwm_1__INTR_SET )
#define FECH_INTERRUPT_MASK_REG             (*(reg32 *) FECH_cy_m0s8_tcpwm_1__INTR_MASK )
#define FECH_INTERRUPT_MASK_PTR             ( (reg32 *) FECH_cy_m0s8_tcpwm_1__INTR_MASK )
#define FECH_INTERRUPT_MASKED_REG           (*(reg32 *) FECH_cy_m0s8_tcpwm_1__INTR_MASKED )
#define FECH_INTERRUPT_MASKED_PTR           ( (reg32 *) FECH_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define FECH_MASK                           ((uint32)FECH_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define FECH_RELOAD_CC_SHIFT                (0u)
#define FECH_RELOAD_PERIOD_SHIFT            (1u)
#define FECH_PWM_SYNC_KILL_SHIFT            (2u)
#define FECH_PWM_STOP_KILL_SHIFT            (3u)
#define FECH_PRESCALER_SHIFT                (8u)
#define FECH_UPDOWN_SHIFT                   (16u)
#define FECH_ONESHOT_SHIFT                  (18u)
#define FECH_QUAD_MODE_SHIFT                (20u)
#define FECH_INV_OUT_SHIFT                  (20u)
#define FECH_INV_COMPL_OUT_SHIFT            (21u)
#define FECH_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define FECH_RELOAD_CC_MASK                 ((uint32)(FECH_1BIT_MASK        <<  \
                                                                            FECH_RELOAD_CC_SHIFT))
#define FECH_RELOAD_PERIOD_MASK             ((uint32)(FECH_1BIT_MASK        <<  \
                                                                            FECH_RELOAD_PERIOD_SHIFT))
#define FECH_PWM_SYNC_KILL_MASK             ((uint32)(FECH_1BIT_MASK        <<  \
                                                                            FECH_PWM_SYNC_KILL_SHIFT))
#define FECH_PWM_STOP_KILL_MASK             ((uint32)(FECH_1BIT_MASK        <<  \
                                                                            FECH_PWM_STOP_KILL_SHIFT))
#define FECH_PRESCALER_MASK                 ((uint32)(FECH_8BIT_MASK        <<  \
                                                                            FECH_PRESCALER_SHIFT))
#define FECH_UPDOWN_MASK                    ((uint32)(FECH_2BIT_MASK        <<  \
                                                                            FECH_UPDOWN_SHIFT))
#define FECH_ONESHOT_MASK                   ((uint32)(FECH_1BIT_MASK        <<  \
                                                                            FECH_ONESHOT_SHIFT))
#define FECH_QUAD_MODE_MASK                 ((uint32)(FECH_3BIT_MASK        <<  \
                                                                            FECH_QUAD_MODE_SHIFT))
#define FECH_INV_OUT_MASK                   ((uint32)(FECH_2BIT_MASK        <<  \
                                                                            FECH_INV_OUT_SHIFT))
#define FECH_MODE_MASK                      ((uint32)(FECH_3BIT_MASK        <<  \
                                                                            FECH_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define FECH_CAPTURE_SHIFT                  (0u)
#define FECH_COUNT_SHIFT                    (2u)
#define FECH_RELOAD_SHIFT                   (4u)
#define FECH_STOP_SHIFT                     (6u)
#define FECH_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define FECH_CAPTURE_MASK                   ((uint32)(FECH_2BIT_MASK        <<  \
                                                                  FECH_CAPTURE_SHIFT))
#define FECH_COUNT_MASK                     ((uint32)(FECH_2BIT_MASK        <<  \
                                                                  FECH_COUNT_SHIFT))
#define FECH_RELOAD_MASK                    ((uint32)(FECH_2BIT_MASK        <<  \
                                                                  FECH_RELOAD_SHIFT))
#define FECH_STOP_MASK                      ((uint32)(FECH_2BIT_MASK        <<  \
                                                                  FECH_STOP_SHIFT))
#define FECH_START_MASK                     ((uint32)(FECH_2BIT_MASK        <<  \
                                                                  FECH_START_SHIFT))

/* MASK */
#define FECH_1BIT_MASK                      ((uint32)0x01u)
#define FECH_2BIT_MASK                      ((uint32)0x03u)
#define FECH_3BIT_MASK                      ((uint32)0x07u)
#define FECH_6BIT_MASK                      ((uint32)0x3Fu)
#define FECH_8BIT_MASK                      ((uint32)0xFFu)
#define FECH_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define FECH_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define FECH_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(FECH_QUAD_ENCODING_MODES     << FECH_QUAD_MODE_SHIFT))       |\
         ((uint32)(FECH_CONFIG                  << FECH_MODE_SHIFT)))

#define FECH_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(FECH_PWM_STOP_EVENT          << FECH_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(FECH_PWM_OUT_INVERT          << FECH_INV_OUT_SHIFT))         |\
         ((uint32)(FECH_PWM_OUT_N_INVERT        << FECH_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(FECH_PWM_MODE                << FECH_MODE_SHIFT)))

#define FECH_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(FECH_PWM_RUN_MODE         << FECH_ONESHOT_SHIFT))
            
#define FECH_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(FECH_PWM_ALIGN            << FECH_UPDOWN_SHIFT))

#define FECH_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(FECH_PWM_KILL_EVENT      << FECH_PWM_SYNC_KILL_SHIFT))

#define FECH_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(FECH_PWM_DEAD_TIME_CYCLE  << FECH_PRESCALER_SHIFT))

#define FECH_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(FECH_PWM_PRESCALER        << FECH_PRESCALER_SHIFT))

#define FECH_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(FECH_TC_PRESCALER            << FECH_PRESCALER_SHIFT))       |\
         ((uint32)(FECH_TC_COUNTER_MODE         << FECH_UPDOWN_SHIFT))          |\
         ((uint32)(FECH_TC_RUN_MODE             << FECH_ONESHOT_SHIFT))         |\
         ((uint32)(FECH_TC_COMP_CAP_MODE        << FECH_MODE_SHIFT)))
        
#define FECH_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(FECH_QUAD_PHIA_SIGNAL_MODE   << FECH_COUNT_SHIFT))           |\
         ((uint32)(FECH_QUAD_INDEX_SIGNAL_MODE  << FECH_RELOAD_SHIFT))          |\
         ((uint32)(FECH_QUAD_STOP_SIGNAL_MODE   << FECH_STOP_SHIFT))            |\
         ((uint32)(FECH_QUAD_PHIB_SIGNAL_MODE   << FECH_START_SHIFT)))

#define FECH_PWM_SIGNALS_MODES                                                              \
        (((uint32)(FECH_PWM_SWITCH_SIGNAL_MODE  << FECH_CAPTURE_SHIFT))         |\
         ((uint32)(FECH_PWM_COUNT_SIGNAL_MODE   << FECH_COUNT_SHIFT))           |\
         ((uint32)(FECH_PWM_RELOAD_SIGNAL_MODE  << FECH_RELOAD_SHIFT))          |\
         ((uint32)(FECH_PWM_STOP_SIGNAL_MODE    << FECH_STOP_SHIFT))            |\
         ((uint32)(FECH_PWM_START_SIGNAL_MODE   << FECH_START_SHIFT)))

#define FECH_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(FECH_TC_CAPTURE_SIGNAL_MODE  << FECH_CAPTURE_SHIFT))         |\
         ((uint32)(FECH_TC_COUNT_SIGNAL_MODE    << FECH_COUNT_SHIFT))           |\
         ((uint32)(FECH_TC_RELOAD_SIGNAL_MODE   << FECH_RELOAD_SHIFT))          |\
         ((uint32)(FECH_TC_STOP_SIGNAL_MODE     << FECH_STOP_SHIFT))            |\
         ((uint32)(FECH_TC_START_SIGNAL_MODE    << FECH_START_SHIFT)))
        
#define FECH_TIMER_UPDOWN_CNT_USED                                                          \
                ((FECH__COUNT_UPDOWN0 == FECH_TC_COUNTER_MODE)                  ||\
                 (FECH__COUNT_UPDOWN1 == FECH_TC_COUNTER_MODE))

#define FECH_PWM_UPDOWN_CNT_USED                                                            \
                ((FECH__CENTER == FECH_PWM_ALIGN)                               ||\
                 (FECH__ASYMMETRIC == FECH_PWM_ALIGN))               
        
#define FECH_PWM_PR_INIT_VALUE              (1u)
#define FECH_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_FECH_H */

/* [] END OF FILE */
