/*******************************************************************************
* File Name: Speed.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the Speed
*  component
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

#include "Speed.h"

uint8 Speed_initVar = 0u;


/*******************************************************************************
* Function Name: Speed_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default Speed configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Speed_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (Speed__QUAD == Speed_CONFIG)
        Speed_CONTROL_REG = Speed_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Speed_TRIG_CONTROL1_REG  = Speed_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        Speed_SetInterruptMode(Speed_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        Speed_SetCounterMode(Speed_COUNT_DOWN);
        Speed_WritePeriod(Speed_QUAD_PERIOD_INIT_VALUE);
        Speed_WriteCounter(Speed_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (Speed__QUAD == Speed_CONFIG) */

    #if (Speed__TIMER == Speed_CONFIG)
        Speed_CONTROL_REG = Speed_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Speed_TRIG_CONTROL1_REG  = Speed_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Speed_SetInterruptMode(Speed_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        Speed_WritePeriod(Speed_TC_PERIOD_VALUE );

        #if (Speed__COMPARE == Speed_TC_COMP_CAP_MODE)
            Speed_WriteCompare(Speed_TC_COMPARE_VALUE);

            #if (1u == Speed_TC_COMPARE_SWAP)
                Speed_SetCompareSwap(1u);
                Speed_WriteCompareBuf(Speed_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == Speed_TC_COMPARE_SWAP) */
        #endif  /* (Speed__COMPARE == Speed_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (Speed_CY_TCPWM_V2 && Speed_TIMER_UPDOWN_CNT_USED && !Speed_CY_TCPWM_4000)
            Speed_WriteCounter(1u);
        #elif(Speed__COUNT_DOWN == Speed_TC_COUNTER_MODE)
            Speed_WriteCounter(Speed_TC_PERIOD_VALUE);
        #else
            Speed_WriteCounter(0u);
        #endif /* (Speed_CY_TCPWM_V2 && Speed_TIMER_UPDOWN_CNT_USED && !Speed_CY_TCPWM_4000) */
    #endif  /* (Speed__TIMER == Speed_CONFIG) */

    #if (Speed__PWM_SEL == Speed_CONFIG)
        Speed_CONTROL_REG = Speed_CTRL_PWM_BASE_CONFIG;

        #if (Speed__PWM_PR == Speed_PWM_MODE)
            Speed_CONTROL_REG |= Speed_CTRL_PWM_RUN_MODE;
            Speed_WriteCounter(Speed_PWM_PR_INIT_VALUE);
        #else
            Speed_CONTROL_REG |= Speed_CTRL_PWM_ALIGN | Speed_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (Speed_CY_TCPWM_V2 && Speed_PWM_UPDOWN_CNT_USED && !Speed_CY_TCPWM_4000)
                Speed_WriteCounter(1u);
            #elif (Speed__RIGHT == Speed_PWM_ALIGN)
                Speed_WriteCounter(Speed_PWM_PERIOD_VALUE);
            #else 
                Speed_WriteCounter(0u);
            #endif  /* (Speed_CY_TCPWM_V2 && Speed_PWM_UPDOWN_CNT_USED && !Speed_CY_TCPWM_4000) */
        #endif  /* (Speed__PWM_PR == Speed_PWM_MODE) */

        #if (Speed__PWM_DT == Speed_PWM_MODE)
            Speed_CONTROL_REG |= Speed_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (Speed__PWM_DT == Speed_PWM_MODE) */

        #if (Speed__PWM == Speed_PWM_MODE)
            Speed_CONTROL_REG |= Speed_CTRL_PWM_PRESCALER;
        #endif  /* (Speed__PWM == Speed_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        Speed_TRIG_CONTROL1_REG  = Speed_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Speed_SetInterruptMode(Speed_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (Speed__PWM_PR == Speed_PWM_MODE)
            Speed_TRIG_CONTROL2_REG =
                    (Speed_CC_MATCH_NO_CHANGE    |
                    Speed_OVERLOW_NO_CHANGE      |
                    Speed_UNDERFLOW_NO_CHANGE);
        #else
            #if (Speed__LEFT == Speed_PWM_ALIGN)
                Speed_TRIG_CONTROL2_REG = Speed_PWM_MODE_LEFT;
            #endif  /* ( Speed_PWM_LEFT == Speed_PWM_ALIGN) */

            #if (Speed__RIGHT == Speed_PWM_ALIGN)
                Speed_TRIG_CONTROL2_REG = Speed_PWM_MODE_RIGHT;
            #endif  /* ( Speed_PWM_RIGHT == Speed_PWM_ALIGN) */

            #if (Speed__CENTER == Speed_PWM_ALIGN)
                Speed_TRIG_CONTROL2_REG = Speed_PWM_MODE_CENTER;
            #endif  /* ( Speed_PWM_CENTER == Speed_PWM_ALIGN) */

            #if (Speed__ASYMMETRIC == Speed_PWM_ALIGN)
                Speed_TRIG_CONTROL2_REG = Speed_PWM_MODE_ASYM;
            #endif  /* (Speed__ASYMMETRIC == Speed_PWM_ALIGN) */
        #endif  /* (Speed__PWM_PR == Speed_PWM_MODE) */

        /* Set other values from customizer */
        Speed_WritePeriod(Speed_PWM_PERIOD_VALUE );
        Speed_WriteCompare(Speed_PWM_COMPARE_VALUE);

        #if (1u == Speed_PWM_COMPARE_SWAP)
            Speed_SetCompareSwap(1u);
            Speed_WriteCompareBuf(Speed_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == Speed_PWM_COMPARE_SWAP) */

        #if (1u == Speed_PWM_PERIOD_SWAP)
            Speed_SetPeriodSwap(1u);
            Speed_WritePeriodBuf(Speed_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == Speed_PWM_PERIOD_SWAP) */
    #endif  /* (Speed__PWM_SEL == Speed_CONFIG) */
    
}


/*******************************************************************************
* Function Name: Speed_Enable
********************************************************************************
*
* Summary:
*  Enables the Speed.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Speed_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    Speed_BLOCK_CONTROL_REG |= Speed_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (Speed__PWM_SEL == Speed_CONFIG)
        #if (0u == Speed_PWM_START_SIGNAL_PRESENT)
            Speed_TriggerCommand(Speed_MASK, Speed_CMD_START);
        #endif /* (0u == Speed_PWM_START_SIGNAL_PRESENT) */
    #endif /* (Speed__PWM_SEL == Speed_CONFIG) */

    #if (Speed__TIMER == Speed_CONFIG)
        #if (0u == Speed_TC_START_SIGNAL_PRESENT)
            Speed_TriggerCommand(Speed_MASK, Speed_CMD_START);
        #endif /* (0u == Speed_TC_START_SIGNAL_PRESENT) */
    #endif /* (Speed__TIMER == Speed_CONFIG) */
    
    #if (Speed__QUAD == Speed_CONFIG)
        #if (0u != Speed_QUAD_AUTO_START)
            Speed_TriggerCommand(Speed_MASK, Speed_CMD_RELOAD);
        #endif /* (0u != Speed_QUAD_AUTO_START) */
    #endif  /* (Speed__QUAD == Speed_CONFIG) */
}


/*******************************************************************************
* Function Name: Speed_Start
********************************************************************************
*
* Summary:
*  Initializes the Speed with default customizer
*  values when called the first time and enables the Speed.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Speed_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time Speed_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the Speed_Start() routine.
*
*******************************************************************************/
void Speed_Start(void)
{
    if (0u == Speed_initVar)
    {
        Speed_Init();
        Speed_initVar = 1u;
    }

    Speed_Enable();
}


/*******************************************************************************
* Function Name: Speed_Stop
********************************************************************************
*
* Summary:
*  Disables the Speed.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Speed_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_BLOCK_CONTROL_REG &= (uint32)~Speed_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the Speed. This function is used when
*  configured as a generic Speed and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the Speed to operate in
*   Values:
*   - Speed_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - Speed_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - Speed_MODE_QUAD - Quadrature decoder
*         - Speed_MODE_PWM - PWM
*         - Speed_MODE_PWM_DT - PWM with dead time
*         - Speed_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_CONTROL_REG &= (uint32)~Speed_MODE_MASK;
    Speed_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - Speed_MODE_X1 - Counts on phi 1 rising
*         - Speed_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - Speed_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_CONTROL_REG &= (uint32)~Speed_QUAD_MODE_MASK;
    Speed_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - Speed_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - Speed_PRESCALE_DIVBY2    - Divide by 2
*         - Speed_PRESCALE_DIVBY4    - Divide by 4
*         - Speed_PRESCALE_DIVBY8    - Divide by 8
*         - Speed_PRESCALE_DIVBY16   - Divide by 16
*         - Speed_PRESCALE_DIVBY32   - Divide by 32
*         - Speed_PRESCALE_DIVBY64   - Divide by 64
*         - Speed_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_CONTROL_REG &= (uint32)~Speed_PRESCALER_MASK;
    Speed_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the Speed runs
*  continuously or stops when terminal count is reached.  By default the
*  Speed operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_CONTROL_REG &= (uint32)~Speed_ONESHOT_MASK;
    Speed_CONTROL_REG |= ((uint32)((oneShotEnable & Speed_1BIT_MASK) <<
                                                               Speed_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetPWMMode(uint32 modeMask)
{
    Speed_TRIG_CONTROL2_REG = (modeMask & Speed_6BIT_MASK);
}



/*******************************************************************************
* Function Name: Speed_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_CONTROL_REG &= (uint32)~Speed_PWM_SYNC_KILL_MASK;
    Speed_CONTROL_REG |= ((uint32)((syncKillEnable & Speed_1BIT_MASK)  <<
                                               Speed_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_CONTROL_REG &= (uint32)~Speed_PWM_STOP_KILL_MASK;
    Speed_CONTROL_REG |= ((uint32)((stopOnKillEnable & Speed_1BIT_MASK)  <<
                                                         Speed_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_CONTROL_REG &= (uint32)~Speed_PRESCALER_MASK;
    Speed_CONTROL_REG |= ((uint32)((deadTime & Speed_8BIT_MASK) <<
                                                          Speed_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - Speed_INVERT_LINE   - Inverts the line output
*         - Speed_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_CONTROL_REG &= (uint32)~Speed_INV_OUT_MASK;
    Speed_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: Speed_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void Speed_WriteCounter(uint32 count)
{
    Speed_COUNTER_REG = (count & Speed_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Speed_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 Speed_ReadCounter(void)
{
    return (Speed_COUNTER_REG & Speed_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Speed_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - Speed_COUNT_UP       - Counts up
*     - Speed_COUNT_DOWN     - Counts down
*     - Speed_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - Speed_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_CONTROL_REG &= (uint32)~Speed_UPDOWN_MASK;
    Speed_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void Speed_WritePeriod(uint32 period)
{
    Speed_PERIOD_REG = (period & Speed_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Speed_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 Speed_ReadPeriod(void)
{
    return (Speed_PERIOD_REG & Speed_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Speed_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_CONTROL_REG &= (uint32)~Speed_RELOAD_CC_MASK;
    Speed_CONTROL_REG |= (swapEnable & Speed_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void Speed_WritePeriodBuf(uint32 periodBuf)
{
    Speed_PERIOD_BUF_REG = (periodBuf & Speed_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Speed_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 Speed_ReadPeriodBuf(void)
{
    return (Speed_PERIOD_BUF_REG & Speed_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Speed_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_CONTROL_REG &= (uint32)~Speed_RELOAD_PERIOD_MASK;
    Speed_CONTROL_REG |= ((uint32)((swapEnable & Speed_1BIT_MASK) <<
                                                            Speed_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void Speed_WriteCompare(uint32 compare)
{
    #if (Speed_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Speed_CY_TCPWM_4000) */

    #if (Speed_CY_TCPWM_4000)
        currentMode = ((Speed_CONTROL_REG & Speed_UPDOWN_MASK) >> Speed_UPDOWN_SHIFT);

        if (((uint32)Speed__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)Speed__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (Speed_CY_TCPWM_4000) */
    
    Speed_COMP_CAP_REG = (compare & Speed_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Speed_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 Speed_ReadCompare(void)
{
    #if (Speed_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Speed_CY_TCPWM_4000) */

    #if (Speed_CY_TCPWM_4000)
        currentMode = ((Speed_CONTROL_REG & Speed_UPDOWN_MASK) >> Speed_UPDOWN_SHIFT);
        
        regVal = Speed_COMP_CAP_REG;
        
        if (((uint32)Speed__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Speed__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Speed_16BIT_MASK);
    #else
        return (Speed_COMP_CAP_REG & Speed_16BIT_MASK);
    #endif /* (Speed_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Speed_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void Speed_WriteCompareBuf(uint32 compareBuf)
{
    #if (Speed_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Speed_CY_TCPWM_4000) */

    #if (Speed_CY_TCPWM_4000)
        currentMode = ((Speed_CONTROL_REG & Speed_UPDOWN_MASK) >> Speed_UPDOWN_SHIFT);

        if (((uint32)Speed__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)Speed__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (Speed_CY_TCPWM_4000) */
    
    Speed_COMP_CAP_BUF_REG = (compareBuf & Speed_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Speed_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 Speed_ReadCompareBuf(void)
{
    #if (Speed_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Speed_CY_TCPWM_4000) */

    #if (Speed_CY_TCPWM_4000)
        currentMode = ((Speed_CONTROL_REG & Speed_UPDOWN_MASK) >> Speed_UPDOWN_SHIFT);

        regVal = Speed_COMP_CAP_BUF_REG;
        
        if (((uint32)Speed__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Speed__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Speed_16BIT_MASK);
    #else
        return (Speed_COMP_CAP_BUF_REG & Speed_16BIT_MASK);
    #endif /* (Speed_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Speed_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 Speed_ReadCapture(void)
{
    return (Speed_COMP_CAP_REG & Speed_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Speed_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 Speed_ReadCaptureBuf(void)
{
    return (Speed_COMP_CAP_BUF_REG & Speed_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Speed_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Speed_TRIG_LEVEL     - Level
*     - Speed_TRIG_RISING    - Rising edge
*     - Speed_TRIG_FALLING   - Falling edge
*     - Speed_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_TRIG_CONTROL1_REG &= (uint32)~Speed_CAPTURE_MASK;
    Speed_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Speed_TRIG_LEVEL     - Level
*     - Speed_TRIG_RISING    - Rising edge
*     - Speed_TRIG_FALLING   - Falling edge
*     - Speed_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_TRIG_CONTROL1_REG &= (uint32)~Speed_RELOAD_MASK;
    Speed_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Speed_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Speed_TRIG_LEVEL     - Level
*     - Speed_TRIG_RISING    - Rising edge
*     - Speed_TRIG_FALLING   - Falling edge
*     - Speed_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_TRIG_CONTROL1_REG &= (uint32)~Speed_START_MASK;
    Speed_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Speed_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Speed_TRIG_LEVEL     - Level
*     - Speed_TRIG_RISING    - Rising edge
*     - Speed_TRIG_FALLING   - Falling edge
*     - Speed_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_TRIG_CONTROL1_REG &= (uint32)~Speed_STOP_MASK;
    Speed_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Speed_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Speed_TRIG_LEVEL     - Level
*     - Speed_TRIG_RISING    - Rising edge
*     - Speed_TRIG_FALLING   - Falling edge
*     - Speed_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_TRIG_CONTROL1_REG &= (uint32)~Speed_COUNT_MASK;
    Speed_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Speed_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - Speed_CMD_CAPTURE    - Trigger Capture/Switch command
*     - Speed_CMD_RELOAD     - Trigger Reload/Index command
*     - Speed_CMD_STOP       - Trigger Stop/Kill command
*     - Speed_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void Speed_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Speed_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Speed_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the Speed.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - Speed_STATUS_DOWN    - Set if counting down
*     - Speed_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 Speed_ReadStatus(void)
{
    return ((Speed_STATUS_REG >> Speed_RUNNING_STATUS_SHIFT) |
            (Speed_STATUS_REG & Speed_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: Speed_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - Speed_INTR_MASK_TC       - Terminal count mask
*     - Speed_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetInterruptMode(uint32 interruptMask)
{
    Speed_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: Speed_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - Speed_INTR_MASK_TC       - Terminal count mask
*     - Speed_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Speed_GetInterruptSourceMasked(void)
{
    return (Speed_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: Speed_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - Speed_INTR_MASK_TC       - Terminal count mask
*     - Speed_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Speed_GetInterruptSource(void)
{
    return (Speed_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: Speed_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - Speed_INTR_MASK_TC       - Terminal count mask
*     - Speed_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Speed_ClearInterrupt(uint32 interruptMask)
{
    Speed_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: Speed_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - Speed_INTR_MASK_TC       - Terminal count mask
*     - Speed_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Speed_SetInterrupt(uint32 interruptMask)
{
    Speed_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
