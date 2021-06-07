/*******************************************************************************
* File Name: QuadDec.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "QuadDec.h"

uint8 QuadDec_initVar = 0u;


/*******************************************************************************
* Function Name: QuadDec_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void QuadDec_Init(void) 
{
        #if (!QuadDec_UsingFixedFunction && !QuadDec_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!QuadDec_UsingFixedFunction && !QuadDec_ControlRegRemoved) */
        
        #if(!QuadDec_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 QuadDec_interruptState;
        #endif /* (!QuadDec_UsingFixedFunction) */
        
        #if (QuadDec_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            QuadDec_CONTROL &= QuadDec_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                QuadDec_CONTROL2 &= ((uint8)(~QuadDec_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                QuadDec_CONTROL3 &= ((uint8)(~QuadDec_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (QuadDec_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                QuadDec_CONTROL |= QuadDec_ONESHOT;
            #endif /* (QuadDec_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            QuadDec_CONTROL2 |= QuadDec_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            QuadDec_RT1 &= ((uint8)(~QuadDec_RT1_MASK));
            QuadDec_RT1 |= QuadDec_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            QuadDec_RT1 &= ((uint8)(~QuadDec_SYNCDSI_MASK));
            QuadDec_RT1 |= QuadDec_SYNCDSI_EN;

        #else
            #if(!QuadDec_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = QuadDec_CONTROL & ((uint8)(~QuadDec_CTRL_CMPMODE_MASK));
            QuadDec_CONTROL = ctrl | QuadDec_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = QuadDec_CONTROL & ((uint8)(~QuadDec_CTRL_CAPMODE_MASK));
            
            #if( 0 != QuadDec_CAPTURE_MODE_CONF)
                QuadDec_CONTROL = ctrl | QuadDec_DEFAULT_CAPTURE_MODE;
            #else
                QuadDec_CONTROL = ctrl;
            #endif /* 0 != QuadDec_CAPTURE_MODE */ 
            
            #endif /* (!QuadDec_ControlRegRemoved) */
        #endif /* (QuadDec_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!QuadDec_UsingFixedFunction)
            QuadDec_ClearFIFO();
        #endif /* (!QuadDec_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        QuadDec_WritePeriod(QuadDec_INIT_PERIOD_VALUE);
        #if (!(QuadDec_UsingFixedFunction && (CY_PSOC5A)))
            QuadDec_WriteCounter(QuadDec_INIT_COUNTER_VALUE);
        #endif /* (!(QuadDec_UsingFixedFunction && (CY_PSOC5A))) */
        QuadDec_SetInterruptMode(QuadDec_INIT_INTERRUPTS_MASK);
        
        #if (!QuadDec_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)QuadDec_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            QuadDec_WriteCompare(QuadDec_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            QuadDec_interruptState = CyEnterCriticalSection();
            
            QuadDec_STATUS_AUX_CTRL |= QuadDec_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(QuadDec_interruptState);
            
        #endif /* (!QuadDec_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void QuadDec_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (QuadDec_UsingFixedFunction)
        QuadDec_GLOBAL_ENABLE |= QuadDec_BLOCK_EN_MASK;
        QuadDec_GLOBAL_STBY_ENABLE |= QuadDec_BLOCK_STBY_EN_MASK;
    #endif /* (QuadDec_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!QuadDec_ControlRegRemoved || QuadDec_UsingFixedFunction)
        QuadDec_CONTROL |= QuadDec_CTRL_ENABLE;                
    #endif /* (!QuadDec_ControlRegRemoved || QuadDec_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: QuadDec_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  QuadDec_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void QuadDec_Start(void) 
{
    if(QuadDec_initVar == 0u)
    {
        QuadDec_Init();
        
        QuadDec_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    QuadDec_Enable();        
}


/*******************************************************************************
* Function Name: QuadDec_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void QuadDec_Stop(void) 
{
    /* Disable Counter */
    #if(!QuadDec_ControlRegRemoved || QuadDec_UsingFixedFunction)
        QuadDec_CONTROL &= ((uint8)(~QuadDec_CTRL_ENABLE));        
    #endif /* (!QuadDec_ControlRegRemoved || QuadDec_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (QuadDec_UsingFixedFunction)
        QuadDec_GLOBAL_ENABLE &= ((uint8)(~QuadDec_BLOCK_EN_MASK));
        QuadDec_GLOBAL_STBY_ENABLE &= ((uint8)(~QuadDec_BLOCK_STBY_EN_MASK));
    #endif /* (QuadDec_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void QuadDec_SetInterruptMode(uint8 interruptsMask) 
{
    QuadDec_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: QuadDec_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   QuadDec_ReadStatusRegister(void) 
{
    return QuadDec_STATUS;
}


#if(!QuadDec_ControlRegRemoved)
/*******************************************************************************
* Function Name: QuadDec_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   QuadDec_ReadControlRegister(void) 
{
    return QuadDec_CONTROL;
}


/*******************************************************************************
* Function Name: QuadDec_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    QuadDec_WriteControlRegister(uint8 control) 
{
    QuadDec_CONTROL = control;
}

#endif  /* (!QuadDec_ControlRegRemoved) */


#if (!(QuadDec_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: QuadDec_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void QuadDec_WriteCounter(uint16 counter) \
                                   
{
    #if(QuadDec_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (QuadDec_GLOBAL_ENABLE & QuadDec_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        QuadDec_GLOBAL_ENABLE |= QuadDec_BLOCK_EN_MASK;
        CY_SET_REG16(QuadDec_COUNTER_LSB_PTR, (uint16)counter);
        QuadDec_GLOBAL_ENABLE &= ((uint8)(~QuadDec_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(QuadDec_COUNTER_LSB_PTR, counter);
    #endif /* (QuadDec_UsingFixedFunction) */
}
#endif /* (!(QuadDec_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: QuadDec_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) The present value of the counter.
*
*******************************************************************************/
uint16 QuadDec_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(QuadDec_UsingFixedFunction)
		(void)CY_GET_REG16(QuadDec_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(QuadDec_COUNTER_LSB_PTR_8BIT);
	#endif/* (QuadDec_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(QuadDec_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(QuadDec_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(QuadDec_STATICCOUNT_LSB_PTR));
    #endif /* (QuadDec_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint16) Present Capture value.
*
*******************************************************************************/
uint16 QuadDec_ReadCapture(void) 
{
    #if(QuadDec_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(QuadDec_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(QuadDec_STATICCOUNT_LSB_PTR));
    #endif /* (QuadDec_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint16) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void QuadDec_WritePeriod(uint16 period) 
{
    #if(QuadDec_UsingFixedFunction)
        CY_SET_REG16(QuadDec_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(QuadDec_PERIOD_LSB_PTR, period);
    #endif /* (QuadDec_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) Present period value.
*
*******************************************************************************/
uint16 QuadDec_ReadPeriod(void) 
{
    #if(QuadDec_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(QuadDec_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(QuadDec_PERIOD_LSB_PTR));
    #endif /* (QuadDec_UsingFixedFunction) */
}


#if (!QuadDec_UsingFixedFunction)
/*******************************************************************************
* Function Name: QuadDec_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void QuadDec_WriteCompare(uint16 compare) \
                                   
{
    #if(QuadDec_UsingFixedFunction)
        CY_SET_REG16(QuadDec_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(QuadDec_COMPARE_LSB_PTR, compare);
    #endif /* (QuadDec_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: QuadDec_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint16) Present compare value.
*
*******************************************************************************/
uint16 QuadDec_ReadCompare(void) 
{
    return (CY_GET_REG16(QuadDec_COMPARE_LSB_PTR));
}


#if (QuadDec_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: QuadDec_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void QuadDec_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    QuadDec_CONTROL &= ((uint8)(~QuadDec_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    QuadDec_CONTROL |= compareMode;
}
#endif  /* (QuadDec_COMPARE_MODE_SOFTWARE) */


#if (QuadDec_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: QuadDec_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void QuadDec_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    QuadDec_CONTROL &= ((uint8)(~QuadDec_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    QuadDec_CONTROL |= ((uint8)((uint8)captureMode << QuadDec_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (QuadDec_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: QuadDec_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void QuadDec_ClearFIFO(void) 
{

    while(0u != (QuadDec_ReadStatusRegister() & QuadDec_STATUS_FIFONEMP))
    {
        (void)QuadDec_ReadCapture();
    }

}
#endif  /* (!QuadDec_UsingFixedFunction) */


/* [] END OF FILE */

