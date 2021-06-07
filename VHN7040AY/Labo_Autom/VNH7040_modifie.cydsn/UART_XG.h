/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "proj_types.h"

#ifndef UART_XG_H
#define UART_XG_H

#define UART_TIMEOUT 1000
#define FRAME_SIZE 42
#define FRAME_SIZE_MATLAB 4
    
extern volatile config param;
extern volatile uint32 time;
    
uint8 Get_trame(); //uint8 *rxdata);
int32 Get_trame_matlab();

#endif
/* [] END OF FILE */
