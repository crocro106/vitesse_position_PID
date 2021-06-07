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

#ifndef PROJ_TYPES_H
#define PROJ_TYPES_H

typedef enum { false, true } bool;
    
#define NUMBER_OF_TICKS   (CYDEV_BCLK__SYSCLK__HZ/1000) /* Syclk / freq pour le calcul du temps desirée ici 1000, un tick toute les 1ms */    
#define PWM_PERIOD 1000 // nbr de coup horloge (11.5 MHz ) pour les freq de sortie des PWMs

#define ATU 2
#define AT 1    
#define PB 4    
#define PT_CONS 512
    
extern const int32 carree[PT_CONS];
extern const int32 rampe[PT_CONS];
extern const int32 echelon[PT_CONS];
extern const int32 triangle[PT_CONS];
extern const int32 sinus[PT_CONS];
extern const int32 dent_de_scie[PT_CONS];
extern bool marche_bool;
extern volatile uint32 time;
/* ISR prototype declaration */
CY_ISR_PROTO(SYSTICK_ISR);
CY_ISR_PROTO(FECH_ISR);    
    
typedef struct{
    uint16 Tech; // Temps echantillonnage en multiple de 1ms
    char nb_boucles; // nb boucles '0' boucle ouverte, '1' une boucle, '2' 2 boucles imbriquées , '3' boucle ouvert avec signal du PC
    uint16 Kp1_num; // numerateur KP 1 - Proportionnel  - si 1 boucle alors seule la boucle 1 est active
    uint16 Kp1_den; // Denominateur KP 1
    uint16 Kp2_num; // numerateur KP 2
    uint16 Kp2_den; // Denominateur KP 2
    uint16 Kd1_num; // numerateur Kd 1 - Dérivée
    uint16 Kd1_den; // Denominateur Kd 1
    uint16 Kd2_num; // numerateur Kd 2
    uint16 Kd2_den; // Denominateur Kd 2
    uint16 Ki1_num; // numerateur Ki 1 - Intégral
    uint16 Ki1_den; // Denominateur Ki 1
    uint16 Ki2_num; // numerateur Ki 2
    uint16 Ki2_den; // Denominateur Ki 2
    char type_consigne; // 'E' Echellon, 'R' Rampe, 'S' Sinus, 'T' triangle, C'carrée, 'W' dent de scie
    int16 cons_initiale; //100 * pourcentage initial
    int16 cons_finale; //100 * pourcentage final
    uint16 cons_per_num; // numerateur Kd 1 - Dérivée
    uint16 cons_per_den; // Denominateur Kd 1
    uint16 CRC;
} config;

#endif

/* [] END OF FILE */
