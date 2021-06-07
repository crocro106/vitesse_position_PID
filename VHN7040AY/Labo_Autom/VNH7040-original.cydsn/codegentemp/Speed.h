/*******************************************************************************
* File Name: Speed.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the Speed
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

#if !defined(CY_TCPWM_Speed_H)
#define CY_TCPWM_Speed_H


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
} Speed_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  Speed_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define Speed_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define Speed_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define Speed_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define Speed_QUAD_ENCODING_MODES            (0lu)
#define Speed_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define Speed_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define Speed_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define Speed_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define Speed_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define Speed_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define Speed_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define Speed_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define Speed_TC_RUN_MODE                    (0lu)
#define Speed_TC_COUNTER_MODE                (0lu)
#define Speed_TC_COMP_CAP_MODE               (2lu)
#define Speed_TC_PRESCALER                   (0lu)

/* Signal modes */
#define Speed_TC_RELOAD_SIGNAL_MODE          (0lu)
#define Speed_TC_COUNT_SIGNAL_MODE           (0lu)
#define Speed_TC_START_SIGNAL_MODE           (0lu)
#define Speed_TC_STOP_SIGNAL_MODE            (0lu)
#define Speed_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define Speed_TC_RELOAD_SIGNAL_PRESENT       (1lu)
#define Speed_TC_COUNT_SIGNAL_PRESENT        (1lu)
#define Speed_TC_START_SIGNAL_PRESENT        (0lu)
#define Speed_TC_STOP_SIGNAL_PRESENT         (0lu)
#define Speed_TC_CAPTURE_SIGNAL_PRESENT      (1lu)

/* Interrupt Mask */
#define Speed_TC_INTERRUPT_MASK              (0lu)

/* PWM Mode */
/* Parameters */
#define Speed_PWM_KILL_EVENT                 (0lu)
#define Speed_PWM_STOP_EVENT                 (0lu)
#define Speed_PWM_MODE                       (4lu)
#define Speed_PWM_OUT_N_INVERT               (0lu)
#define Speed_PWM_OUT_INVERT                 (0lu)
#define Speed_PWM_ALIGN                      (0lu)
#define Speed_PWM_RUN_MODE                   (0lu)
#define Speed_PWM_DEAD_TIME_CYCLE            (0lu)
#define Speed_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define Speed_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define Speed_PWM_COUNT_SIGNAL_MODE          (3lu)
#define Speed_PWM_START_SIGNAL_MODE          (0lu)
#define Speed_PWM_STOP_SIGNAL_MODE           (0lu)
#define Speed_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define Speed_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define Speed_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define Speed_PWM_START_SIGNAL_PRESENT       (0lu)
#define Speed_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define Speed_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Speed_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define Speed_TC_PERIOD_VALUE                (65535lu)
#define Speed_TC_COMPARE_VALUE               (65535lu)
#define Speed_TC_COMPARE_BUF_VALUE           (65535lu)
#define Speed_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define Speed_PWM_PERIOD_VALUE               (65535lu)
#define Speed_PWM_PERIOD_BUF_VALUE           (65535lu)
#define Speed_PWM_PERIOD_SWAP                (0lu)
#define Speed_PWM_COMPARE_VALUE              (65535lu)
#define Speed_PWM_COMPARE_BUF_VALUE          (65535lu)
#define Speed_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Speed__LEFT 0
#define Speed__RIGHT 1
#define Speed__CENTER 2
#define Speed__ASYMMETRIC 3

#define Speed__X1 0
#define Speed__X2 1
#define Speed__X4 2

#define Speed__PWM 4
#define Speed__PWM_DT 5
#define Speed__PWM_PR 6

#define Speed__INVERSE 1
#define Speed__DIRECT 0

#define Speed__CAPTURE 2
#define Speed__COMPARE 0

#define Speed__TRIG_LEVEL 3
#define Speed__TRIG_RISING 0
#define Speed__TRIG_FALLING 1
#define Speed__TRIG_BOTH 2

#define Speed__INTR_MASK_TC 1
#define Speed__INTR_MASK_CC_MATCH 2
#define Speed__INTR_MASK_NONE 0
#define Speed__INTR_MASK_TC_CC 3

#define Speed__UNCONFIG 8
#define Speed__TIMER 1
#define Speed__QUAD 3
#define Speed__PWM_SEL 7

#define Speed__COUNT_UP 0
#define Speed__COUNT_DOWN 1
#define Speed__COUNT_UPDOWN0 2
#define Speed__COUNT_UPDOWN1 3


/* Prescaler */
#define Speed_PRESCALE_DIVBY1                ((uint32)(0u << Speed_PRESCALER_SHIFT))
#define Speed_PRESCALE_DIVBY2                ((uint32)(1u << Speed_PRESCALER_SHIFT))
#define Speed_PRESCALE_DIVBY4                ((uint32)(2u << Speed_PRESCALER_SHIFT))
#define Speed_PRESCALE_DIVBY8                ((uint32)(3u << Speed_PRESCALER_SHIFT))
#define Speed_PRESCALE_DIVBY16               ((uint32)(4u << Speed_PRESCALER_SHIFT))
#define Speed_PRESCALE_DIVBY32               ((uint32)(5u << Speed_PRESCALER_SHIFT))
#define Speed_PRESCALE_DIVBY64               ((uint32)(6u << Speed_PRESCALER_SHIFT))
#define Speed_PRESCALE_DIVBY128              ((uint32)(7u << Speed_PRESCALER_SHIFT))

/* TCPWM set modes */
#define Speed_MODE_TIMER_COMPARE             ((uint32)(Speed__COMPARE         <<  \
                                                                  Speed_MODE_SHIFT))
#define Speed_MODE_TIMER_CAPTURE             ((uint32)(Speed__CAPTURE         <<  \
                                                                  Speed_MODE_SHIFT))
#define Speed_MODE_QUAD                      ((uint32)(Speed__QUAD            <<  \
                                                                  Speed_MODE_SHIFT))
#define Speed_MODE_PWM                       ((uint32)(Speed__PWM             <<  \
                                                                  Speed_MODE_SHIFT))
#define Speed_MODE_PWM_DT                    ((uint32)(Speed__PWM_DT          <<  \
                                                                  Speed_MODE_SHIFT))
#define Speed_MODE_PWM_PR                    ((uint32)(Speed__PWM_PR          <<  \
                                                                  Speed_MODE_SHIFT))

/* Quad Modes */
#define Speed_MODE_X1                        ((uint32)(Speed__X1              <<  \
                                                                  Speed_QUAD_MODE_SHIFT))
#define Speed_MODE_X2                        ((uint32)(Speed__X2              <<  \
                                                                  Speed_QUAD_MODE_SHIFT))
#define Speed_MODE_X4                        ((uint32)(Speed__X4              <<  \
                                                                  Speed_QUAD_MODE_SHIFT))

/* Counter modes */
#define Speed_COUNT_UP                       ((uint32)(Speed__COUNT_UP        <<  \
                                                                  Speed_UPDOWN_SHIFT))
#define Speed_COUNT_DOWN                     ((uint32)(Speed__COUNT_DOWN      <<  \
                                                                  Speed_UPDOWN_SHIFT))
#define Speed_COUNT_UPDOWN0                  ((uint32)(Speed__COUNT_UPDOWN0   <<  \
                                                                  Speed_UPDOWN_SHIFT))
#define Speed_COUNT_UPDOWN1                  ((uint32)(Speed__COUNT_UPDOWN1   <<  \
                                                                  Speed_UPDOWN_SHIFT))

/* PWM output invert */
#define Speed_INVERT_LINE                    ((uint32)(Speed__INVERSE         <<  \
                                                                  Speed_INV_OUT_SHIFT))
#define Speed_INVERT_LINE_N                  ((uint32)(Speed__INVERSE         <<  \
                                                                  Speed_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define Speed_TRIG_RISING                    ((uint32)Speed__TRIG_RISING)
#define Speed_TRIG_FALLING                   ((uint32)Speed__TRIG_FALLING)
#define Speed_TRIG_BOTH                      ((uint32)Speed__TRIG_BOTH)
#define Speed_TRIG_LEVEL                     ((uint32)Speed__TRIG_LEVEL)

/* Interrupt mask */
#define Speed_INTR_MASK_TC                   ((uint32)Speed__INTR_MASK_TC)
#define Speed_INTR_MASK_CC_MATCH             ((uint32)Speed__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define Speed_CC_MATCH_SET                   (0x00u)
#define Speed_CC_MATCH_CLEAR                 (0x01u)
#define Speed_CC_MATCH_INVERT                (0x02u)
#define Speed_CC_MATCH_NO_CHANGE             (0x03u)
#define Speed_OVERLOW_SET                    (0x00u)
#define Speed_OVERLOW_CLEAR                  (0x04u)
#define Speed_OVERLOW_INVERT                 (0x08u)
#define Speed_OVERLOW_NO_CHANGE              (0x0Cu)
#define Speed_UNDERFLOW_SET                  (0x00u)
#define Speed_UNDERFLOW_CLEAR                (0x10u)
#define Speed_UNDERFLOW_INVERT               (0x20u)
#define Speed_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define Speed_PWM_MODE_LEFT                  (Speed_CC_MATCH_CLEAR        |   \
                                                         Speed_OVERLOW_SET           |   \
                                                         Speed_UNDERFLOW_NO_CHANGE)
#define Speed_PWM_MODE_RIGHT                 (Speed_CC_MATCH_SET          |   \
                                                         Speed_OVERLOW_NO_CHANGE     |   \
                                                         Speed_UNDERFLOW_CLEAR)
#define Speed_PWM_MODE_ASYM                  (Speed_CC_MATCH_INVERT       |   \
                                                         Speed_OVERLOW_SET           |   \
                                                         Speed_UNDERFLOW_CLEAR)

#if (Speed_CY_TCPWM_V2)
    #if(Speed_CY_TCPWM_4000)
        #define Speed_PWM_MODE_CENTER                (Speed_CC_MATCH_INVERT       |   \
                                                                 Speed_OVERLOW_NO_CHANGE     |   \
                                                                 Speed_UNDERFLOW_CLEAR)
    #else
        #define Speed_PWM_MODE_CENTER                (Speed_CC_MATCH_INVERT       |   \
                                                                 Speed_OVERLOW_SET           |   \
                                                                 Speed_UNDERFLOW_CLEAR)
    #endif /* (Speed_CY_TCPWM_4000) */
#else
    #define Speed_PWM_MODE_CENTER                (Speed_CC_MATCH_INVERT       |   \
                                                             Speed_OVERLOW_NO_CHANGE     |   \
                                                             Speed_UNDERFLOW_CLEAR)
#endif /* (Speed_CY_TCPWM_NEW) */

/* Command operations without condition */
#define Speed_CMD_CAPTURE                    (0u)
#define Speed_CMD_RELOAD                     (8u)
#define Speed_CMD_STOP                       (16u)
#define Speed_CMD_START                      (24u)

/* Status */
#define Speed_STATUS_DOWN                    (1u)
#define Speed_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   Speed_Init(void);
void   Speed_Enable(void);
void   Speed_Start(void);
void   Speed_Stop(void);

void   Speed_SetMode(uint32 mode);
void   Speed_SetCounterMode(uint32 counterMode);
void   Speed_SetPWMMode(uint32 modeMask);
void   Speed_SetQDMode(uint32 qdMode);

void   Speed_SetPrescaler(uint32 prescaler);
void   Speed_TriggerCommand(uint32 mask, uint32 command);
void   Speed_SetOneShot(uint32 oneShotEnable);
uint32 Speed_ReadStatus(void);

void   Speed_SetPWMSyncKill(uint32 syncKillEnable);
void   Speed_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   Speed_SetPWMDeadTime(uint32 deadTime);
void   Speed_SetPWMInvert(uint32 mask);

void   Speed_SetInterruptMode(uint32 interruptMask);
uint32 Speed_GetInterruptSourceMasked(void);
uint32 Speed_GetInterruptSource(void);
void   Speed_ClearInterrupt(uint32 interruptMask);
void   Speed_SetInterrupt(uint32 interruptMask);

void   Speed_WriteCounter(uint32 count);
uint32 Speed_ReadCounter(void);

uint32 Speed_ReadCapture(void);
uint32 Speed_ReadCaptureBuf(void);

void   Speed_WritePeriod(uint32 period);
uint32 Speed_ReadPeriod(void);
void   Speed_WritePeriodBuf(uint32 periodBuf);
uint32 Speed_ReadPeriodBuf(void);

void   Speed_WriteCompare(uint32 compare);
uint32 Speed_ReadCompare(void);
void   Speed_WriteCompareBuf(uint32 compareBuf);
uint32 Speed_ReadCompareBuf(void);

void   Speed_SetPeriodSwap(uint32 swapEnable);
void   Speed_SetCompareSwap(uint32 swapEnable);

void   Speed_SetCaptureMode(uint32 triggerMode);
void   Speed_SetReloadMode(uint32 triggerMode);
void   Speed_SetStartMode(uint32 triggerMode);
void   Speed_SetStopMode(uint32 triggerMode);
void   Speed_SetCountMode(uint32 triggerMode);

void   Speed_SaveConfig(void);
void   Speed_RestoreConfig(void);
void   Speed_Sleep(void);
void   Speed_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define Speed_BLOCK_CONTROL_REG              (*(reg32 *) Speed_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Speed_BLOCK_CONTROL_PTR              ( (reg32 *) Speed_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Speed_COMMAND_REG                    (*(reg32 *) Speed_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Speed_COMMAND_PTR                    ( (reg32 *) Speed_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Speed_INTRRUPT_CAUSE_REG             (*(reg32 *) Speed_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Speed_INTRRUPT_CAUSE_PTR             ( (reg32 *) Speed_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Speed_CONTROL_REG                    (*(reg32 *) Speed_cy_m0s8_tcpwm_1__CTRL )
#define Speed_CONTROL_PTR                    ( (reg32 *) Speed_cy_m0s8_tcpwm_1__CTRL )
#define Speed_STATUS_REG                     (*(reg32 *) Speed_cy_m0s8_tcpwm_1__STATUS )
#define Speed_STATUS_PTR                     ( (reg32 *) Speed_cy_m0s8_tcpwm_1__STATUS )
#define Speed_COUNTER_REG                    (*(reg32 *) Speed_cy_m0s8_tcpwm_1__COUNTER )
#define Speed_COUNTER_PTR                    ( (reg32 *) Speed_cy_m0s8_tcpwm_1__COUNTER )
#define Speed_COMP_CAP_REG                   (*(reg32 *) Speed_cy_m0s8_tcpwm_1__CC )
#define Speed_COMP_CAP_PTR                   ( (reg32 *) Speed_cy_m0s8_tcpwm_1__CC )
#define Speed_COMP_CAP_BUF_REG               (*(reg32 *) Speed_cy_m0s8_tcpwm_1__CC_BUFF )
#define Speed_COMP_CAP_BUF_PTR               ( (reg32 *) Speed_cy_m0s8_tcpwm_1__CC_BUFF )
#define Speed_PERIOD_REG                     (*(reg32 *) Speed_cy_m0s8_tcpwm_1__PERIOD )
#define Speed_PERIOD_PTR                     ( (reg32 *) Speed_cy_m0s8_tcpwm_1__PERIOD )
#define Speed_PERIOD_BUF_REG                 (*(reg32 *) Speed_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Speed_PERIOD_BUF_PTR                 ( (reg32 *) Speed_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Speed_TRIG_CONTROL0_REG              (*(reg32 *) Speed_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Speed_TRIG_CONTROL0_PTR              ( (reg32 *) Speed_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Speed_TRIG_CONTROL1_REG              (*(reg32 *) Speed_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Speed_TRIG_CONTROL1_PTR              ( (reg32 *) Speed_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Speed_TRIG_CONTROL2_REG              (*(reg32 *) Speed_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Speed_TRIG_CONTROL2_PTR              ( (reg32 *) Speed_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Speed_INTERRUPT_REQ_REG              (*(reg32 *) Speed_cy_m0s8_tcpwm_1__INTR )
#define Speed_INTERRUPT_REQ_PTR              ( (reg32 *) Speed_cy_m0s8_tcpwm_1__INTR )
#define Speed_INTERRUPT_SET_REG              (*(reg32 *) Speed_cy_m0s8_tcpwm_1__INTR_SET )
#define Speed_INTERRUPT_SET_PTR              ( (reg32 *) Speed_cy_m0s8_tcpwm_1__INTR_SET )
#define Speed_INTERRUPT_MASK_REG             (*(reg32 *) Speed_cy_m0s8_tcpwm_1__INTR_MASK )
#define Speed_INTERRUPT_MASK_PTR             ( (reg32 *) Speed_cy_m0s8_tcpwm_1__INTR_MASK )
#define Speed_INTERRUPT_MASKED_REG           (*(reg32 *) Speed_cy_m0s8_tcpwm_1__INTR_MASKED )
#define Speed_INTERRUPT_MASKED_PTR           ( (reg32 *) Speed_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define Speed_MASK                           ((uint32)Speed_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define Speed_RELOAD_CC_SHIFT                (0u)
#define Speed_RELOAD_PERIOD_SHIFT            (1u)
#define Speed_PWM_SYNC_KILL_SHIFT            (2u)
#define Speed_PWM_STOP_KILL_SHIFT            (3u)
#define Speed_PRESCALER_SHIFT                (8u)
#define Speed_UPDOWN_SHIFT                   (16u)
#define Speed_ONESHOT_SHIFT                  (18u)
#define Speed_QUAD_MODE_SHIFT                (20u)
#define Speed_INV_OUT_SHIFT                  (20u)
#define Speed_INV_COMPL_OUT_SHIFT            (21u)
#define Speed_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define Speed_RELOAD_CC_MASK                 ((uint32)(Speed_1BIT_MASK        <<  \
                                                                            Speed_RELOAD_CC_SHIFT))
#define Speed_RELOAD_PERIOD_MASK             ((uint32)(Speed_1BIT_MASK        <<  \
                                                                            Speed_RELOAD_PERIOD_SHIFT))
#define Speed_PWM_SYNC_KILL_MASK             ((uint32)(Speed_1BIT_MASK        <<  \
                                                                            Speed_PWM_SYNC_KILL_SHIFT))
#define Speed_PWM_STOP_KILL_MASK             ((uint32)(Speed_1BIT_MASK        <<  \
                                                                            Speed_PWM_STOP_KILL_SHIFT))
#define Speed_PRESCALER_MASK                 ((uint32)(Speed_8BIT_MASK        <<  \
                                                                            Speed_PRESCALER_SHIFT))
#define Speed_UPDOWN_MASK                    ((uint32)(Speed_2BIT_MASK        <<  \
                                                                            Speed_UPDOWN_SHIFT))
#define Speed_ONESHOT_MASK                   ((uint32)(Speed_1BIT_MASK        <<  \
                                                                            Speed_ONESHOT_SHIFT))
#define Speed_QUAD_MODE_MASK                 ((uint32)(Speed_3BIT_MASK        <<  \
                                                                            Speed_QUAD_MODE_SHIFT))
#define Speed_INV_OUT_MASK                   ((uint32)(Speed_2BIT_MASK        <<  \
                                                                            Speed_INV_OUT_SHIFT))
#define Speed_MODE_MASK                      ((uint32)(Speed_3BIT_MASK        <<  \
                                                                            Speed_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define Speed_CAPTURE_SHIFT                  (0u)
#define Speed_COUNT_SHIFT                    (2u)
#define Speed_RELOAD_SHIFT                   (4u)
#define Speed_STOP_SHIFT                     (6u)
#define Speed_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define Speed_CAPTURE_MASK                   ((uint32)(Speed_2BIT_MASK        <<  \
                                                                  Speed_CAPTURE_SHIFT))
#define Speed_COUNT_MASK                     ((uint32)(Speed_2BIT_MASK        <<  \
                                                                  Speed_COUNT_SHIFT))
#define Speed_RELOAD_MASK                    ((uint32)(Speed_2BIT_MASK        <<  \
                                                                  Speed_RELOAD_SHIFT))
#define Speed_STOP_MASK                      ((uint32)(Speed_2BIT_MASK        <<  \
                                                                  Speed_STOP_SHIFT))
#define Speed_START_MASK                     ((uint32)(Speed_2BIT_MASK        <<  \
                                                                  Speed_START_SHIFT))

/* MASK */
#define Speed_1BIT_MASK                      ((uint32)0x01u)
#define Speed_2BIT_MASK                      ((uint32)0x03u)
#define Speed_3BIT_MASK                      ((uint32)0x07u)
#define Speed_6BIT_MASK                      ((uint32)0x3Fu)
#define Speed_8BIT_MASK                      ((uint32)0xFFu)
#define Speed_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define Speed_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define Speed_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(Speed_QUAD_ENCODING_MODES     << Speed_QUAD_MODE_SHIFT))       |\
         ((uint32)(Speed_CONFIG                  << Speed_MODE_SHIFT)))

#define Speed_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(Speed_PWM_STOP_EVENT          << Speed_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(Speed_PWM_OUT_INVERT          << Speed_INV_OUT_SHIFT))         |\
         ((uint32)(Speed_PWM_OUT_N_INVERT        << Speed_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(Speed_PWM_MODE                << Speed_MODE_SHIFT)))

#define Speed_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(Speed_PWM_RUN_MODE         << Speed_ONESHOT_SHIFT))
            
#define Speed_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(Speed_PWM_ALIGN            << Speed_UPDOWN_SHIFT))

#define Speed_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(Speed_PWM_KILL_EVENT      << Speed_PWM_SYNC_KILL_SHIFT))

#define Speed_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(Speed_PWM_DEAD_TIME_CYCLE  << Speed_PRESCALER_SHIFT))

#define Speed_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(Speed_PWM_PRESCALER        << Speed_PRESCALER_SHIFT))

#define Speed_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(Speed_TC_PRESCALER            << Speed_PRESCALER_SHIFT))       |\
         ((uint32)(Speed_TC_COUNTER_MODE         << Speed_UPDOWN_SHIFT))          |\
         ((uint32)(Speed_TC_RUN_MODE             << Speed_ONESHOT_SHIFT))         |\
         ((uint32)(Speed_TC_COMP_CAP_MODE        << Speed_MODE_SHIFT)))
        
#define Speed_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(Speed_QUAD_PHIA_SIGNAL_MODE   << Speed_COUNT_SHIFT))           |\
         ((uint32)(Speed_QUAD_INDEX_SIGNAL_MODE  << Speed_RELOAD_SHIFT))          |\
         ((uint32)(Speed_QUAD_STOP_SIGNAL_MODE   << Speed_STOP_SHIFT))            |\
         ((uint32)(Speed_QUAD_PHIB_SIGNAL_MODE   << Speed_START_SHIFT)))

#define Speed_PWM_SIGNALS_MODES                                                              \
        (((uint32)(Speed_PWM_SWITCH_SIGNAL_MODE  << Speed_CAPTURE_SHIFT))         |\
         ((uint32)(Speed_PWM_COUNT_SIGNAL_MODE   << Speed_COUNT_SHIFT))           |\
         ((uint32)(Speed_PWM_RELOAD_SIGNAL_MODE  << Speed_RELOAD_SHIFT))          |\
         ((uint32)(Speed_PWM_STOP_SIGNAL_MODE    << Speed_STOP_SHIFT))            |\
         ((uint32)(Speed_PWM_START_SIGNAL_MODE   << Speed_START_SHIFT)))

#define Speed_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(Speed_TC_CAPTURE_SIGNAL_MODE  << Speed_CAPTURE_SHIFT))         |\
         ((uint32)(Speed_TC_COUNT_SIGNAL_MODE    << Speed_COUNT_SHIFT))           |\
         ((uint32)(Speed_TC_RELOAD_SIGNAL_MODE   << Speed_RELOAD_SHIFT))          |\
         ((uint32)(Speed_TC_STOP_SIGNAL_MODE     << Speed_STOP_SHIFT))            |\
         ((uint32)(Speed_TC_START_SIGNAL_MODE    << Speed_START_SHIFT)))
        
#define Speed_TIMER_UPDOWN_CNT_USED                                                          \
                ((Speed__COUNT_UPDOWN0 == Speed_TC_COUNTER_MODE)                  ||\
                 (Speed__COUNT_UPDOWN1 == Speed_TC_COUNTER_MODE))

#define Speed_PWM_UPDOWN_CNT_USED                                                            \
                ((Speed__CENTER == Speed_PWM_ALIGN)                               ||\
                 (Speed__ASYMMETRIC == Speed_PWM_ALIGN))               
        
#define Speed_PWM_PR_INIT_VALUE              (1u)
#define Speed_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_Speed_H */

/* [] END OF FILE */
