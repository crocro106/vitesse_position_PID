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

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
//variable    
extern volatile uint8 param_ok,sent;
extern volatile const int32 *pointeur_gen;
extern volatile uint32 time;
extern volatile int32 val1,val2; 
extern volatile float gain_idac,gain_pwm1;
extern volatile int32 offset_idac,offset_pwm1,pwm1_valeur;
extern volatile int32 consigne,epsilon,spid1,spid2;
extern volatile int32 erreur_int_pid1,erreur_av_pid1,erreur_int_pid2,erreur_av_pid2,out_deriv_av1,out_deriv_av2;
extern  void (*statefunc)();
extern volatile uint32 index_gen;

// States
void init();
void arret();
void marche();
void arret_urg();
void send_control_frame(uint32 state);
#endif

/* [] END OF FILE */
