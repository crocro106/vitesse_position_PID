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

#include "State_machine.h"
#include "UART_XG.h"

int32 N=4;

void systick_delayms(uint32 attente)
{
    uint32 temp;
    temp=time;
    while(time-temp<attente);
}

void init(){
    CySysTickStart();
    CySysTickSetReload(NUMBER_OF_TICKS);
    CySysTickSetCallback(0, SYSTICK_ISR);
    UART_Start();
 //   ADC_SetChanMask(0x0003); // seulement voie 0 et 1 ( on a besoin que de val1 et val2 tout le reste c'est du calcul
 //   ADC_Start();
 //   ADC_StartConvert();
    param_ok=false;
    Clock_2_Start();
    isr_fech_StartEx(FECH_ISR);
    FECH_Start(); //on initialise le timer pour FECH
    FECH_Stop(); // on le disable, mais la config reste
    // debut recherche pt origine
 /*   param.cons_per_den=100;
    param.cons_per_num=100;
    param.cons_initiale=0;
    param.cons_finale=15;
    gain_idac=((param.cons_finale-param.cons_initiale)/100.0)*256/1000;
    offset_idac=(uint32)(param.cons_initiale*256/100);//(uint32)(((param.cons_initiale+param.cons_finale)>>1)*250/100);
    gain_pwm1=((param.cons_finale-param.cons_initiale)/100.0)*PWM_PERIOD/1000;
    offset_pwm1=(uint32)(param.cons_initiale*PWM_PERIOD/100);
    IDAC_Start(); */
    PWM_Start();
    PWM_WritePeriod(PWM_PERIOD);
    PWM_WriteCompare(0); // on met 0 de rapport cyclique en sortie
    //PWM_WriteCompare2(0); // on met 0 de rapport cyclique en sortie
    // Ok config terminée
    statefunc=arret; //arret;
    //debug
/*    offset_pwm1=0;
    gain_pwm1=1;
    FECH_Start();
    param.Tech=20;
    param.cons_per_num=20;
    param.cons_per_den=1;
    param.Kd1_den=100;
    param.Kd1_num=30;
    param.Kd2_den=1;
    param.Kd2_num=0;
    param.Ki1_den=1;
    param.Ki1_num=0;
    param.Ki2_den=1;
    param.Ki2_num=0;
    param.Kp1_den=1;
    param.Kp1_num=0;
    param.Kp2_den=1;
    param.Kp2_num=0;
    param.nb_boucles='3';
    param.type_consigne='C';
    pointeur_gen=carree;
    FECH_WritePeriod((param.Tech<<2)-1); */
}

void arret() {
    if(!DI_ATU_Read()) //ATU ?
    {
        statefunc = arret_urg;
        marche_bool=false;
        send_control_frame(ATU);
        return;
    }
    // ATTENTE Données du PC
    LED_Write(0);
    // CyDelay(100);
    systick_delayms(100);
    LED_Write(1);
    //CyDelay(100);
    systick_delayms(100);
    LED_Write(0);
    //CyDelay(100);
    systick_delayms(100);
    LED_Write(1);
    //CyDelay(500);
    systick_delayms(500);
    LED_Write(0);
    param_ok=Get_trame();
    if(param_ok)
    {
        if(marche_bool==true) //APPUIE btn M/A
        {
       /*     CyDelay(10); // debounce bouton M/A
            while(DI_7_Read()); // Attente Bouton M/A plus appuye
            CyDelay(10); // debounce bouton M/A  */
            statefunc =marche; // on change d'état
            // calcul coefficient
           /* gain_pwm1=(((float)param.cons_finale-(float)param.cons_initiale)/100.0)*PWM_PERIOD/1000;
            offset_pwm1=((int32)param.cons_initiale*PWM_PERIOD/100); */
            gain_pwm1=(((float)param.cons_finale-(float)param.cons_initiale)/100.0)*PWM_PERIOD/1000;
            offset_pwm1=((int32)param.cons_initiale*PWM_PERIOD/100);
            switch (param.type_consigne)
            {
                case 'A':
                // Carree
                    pointeur_gen=carree;
                break;
                case 'B':
                // triangle
                    pointeur_gen=triangle;
                break;
                case 'C':
                // Sinus
                    pointeur_gen=sinus;
                break;
                case 'D':
                // Dent de scie
                    pointeur_gen=dent_de_scie;
                break;
                case 'E':
                // Echellon
                    pointeur_gen=carree;
                break;
                case 'F':
                // Rampe
                    pointeur_gen=dent_de_scie;
                break;
                default:
                // default case
                    pointeur_gen=sinus;
                break;
            }
            // demarrage acquisition
            erreur_int_pid1=0;
            erreur_int_pid2=0;
            erreur_av_pid1=0;
            out_deriv_av1=0;
            QuadDec_WriteCounter(0);
            QuadDec_Start();
            QuadDec_WriteCounter(32767);
            Speed_Start();
            FECH_WritePeriod((param.Tech<<2)-1);
        IN1_L298_Write(0);
        IN2_L298_Write(0);
        PWM_WriteCompare(0);
            FECH_Start(); // on demarre le timer des ISR pour acquisition signaux
            //FECH_WriteCompare((param.Tech<<2)-2);
            val1=0;
            Speed_WriteCompare(0);
            Speed_WriteCompareBuf(0);
            val2=0;
            time=0;
            index_gen=0;          
        }
     }
    else
    {
        statefunc=arret;
    }
}

    bool test=false;
int32 erreur_temp;
void marche()
{
    int32 out_deriv=0;
    uint32 temp;

    if(!DI_ATU_Read()) // ATU ?
    {
        statefunc = arret_urg;
        marche_bool=false;
        send_control_frame(ATU);
        FECH_Stop();
        return;
    }
    LED_Write(1);
    param_ok=false;
    temp=UART_UartGetChar();
    if( temp=='S')//!DI_Stop_Read()) //APPUIE btn M/A
    {
      //  CyDelay(10); // debounce bouton M/A
      //  while(DI_Stop_Read()); // Attente Bouton M/A plus appuye
        statefunc =arret; // on change d'état
        send_control_frame(AT);
        marche_bool=false;
        FECH_Stop();
        IN1_L298_Write(0);
        IN2_L298_Write(0);
        PWM_WriteCompare(0);
    }    
    if(sent==1) // FECH Interrupt has happend so : faut calculer mon vieux...
    {
        // Generation PWM  Calcul PID...
        if(param.nb_boucles=='1') // une boucle de Reg vitesse
        {
            // Calcul de la consigne purement en interne car PID numerique !!!
            consigne=(offset_pwm1+(int32)(gain_pwm1*(float)(*(pointeur_gen+index_gen))))/10;
            epsilon=consigne-(val1);
            erreur_int_pid1+=epsilon;
            out_deriv=(((epsilon-erreur_av_pid1)+out_deriv_av1/N)*((int32)param.Kd1_num))/((((((int32)param.Kd1_den*(int32)param.Tech)/1000)+(int32)param.Kd1_num/N))); //+1);
            spid1=((int32)param.Kp1_num*epsilon)/(int32)param.Kp1_den+((int32)param.Ki1_num*erreur_int_pid1*(int32)param.Tech)/((int32)param.Ki1_den*1000)+out_deriv;
            spid2=spid1;
            erreur_av_pid1=epsilon;
            out_deriv_av1=out_deriv;
            
            if (spid1<0) spid1=0;
            if (spid1>1000) spid1=1000;
            pwm1_valeur=spid1;
        }
        else if(param.nb_boucles=='2') //une boucle Position
        {   
            // Calcul de la consigne purement en interne car PID numerique !!!
            consigne=(offset_pwm1+(gain_pwm1*(float)(*(pointeur_gen+index_gen))))/10;
            epsilon=consigne-val2;
            erreur_int_pid2+=epsilon;
            out_deriv=(((epsilon-erreur_av_pid2)+out_deriv_av2/N)*((int32)param.Kd2_num))/((((((int32)param.Kd2_den*(int32)param.Tech)/1000)+(int32)param.Kd2_num/N))); // +1 si periode trop petite
            spid2=(((int32)param.Kp2_num*epsilon)/(int32)param.Kp2_den+((int32)param.Ki2_num*erreur_int_pid2*(int32)param.Tech)/((int32)param.Ki2_den*1000)+out_deriv)+500;
            if (spid2<0) spid2=0;
            if (spid2>1000) spid2=1000;
            spid1=spid2;
            erreur_av_pid2=epsilon;
            out_deriv_av2=out_deriv;
            pwm1_valeur=spid1;
        }
        else if(param.nb_boucles=='3') //deux boucles de Reg imbriquees Position
        {   
            // Calcul de la consigne purement en interne car PID numerique !!!
            consigne=(offset_pwm1+(gain_pwm1*(float)(*(pointeur_gen+index_gen))))/10;
            epsilon=consigne-val2;
            erreur_int_pid2+=epsilon;
            out_deriv=(((epsilon-erreur_av_pid2)+out_deriv_av2/N)*((int32)param.Kd2_num))/((((((int32)param.Kd2_den*(int32)param.Tech)/1000)+(int32)param.Kd2_num/N)));
            spid2=((int32)param.Kp2_num*epsilon)/(int32)param.Kp2_den+((int32)param.Ki2_num*erreur_int_pid2*(int32)param.Tech)/((int32)param.Ki2_den*1000)+out_deriv;
            //spid1=spid1/100;
            erreur_av_pid2=epsilon;
            out_deriv_av2=out_deriv;            
           // spid2=((param.Kp2_num*epsilon)/param.Kp2_den+(param.Ki2_num*erreur_int_pid2*param.Tech)/(param.Ki2_den*1000)+(param.Kd2_num*(epsilon-erreur_av_pid2))/((param.Kd2_den*param.Tech/1000)+1));
            if(spid2>5000) spid2=5000;
            else if(spid2<-5000) spid2 = -5000;          
            erreur_temp=+spid2-val1;
            erreur_int_pid1+=erreur_temp;
            out_deriv=(((erreur_temp-erreur_av_pid1)+out_deriv_av1/N)*((int32)param.Kd1_num))/((((((int32)param.Kd1_den*(int32)param.Tech)/1000)+(int32)param.Kd1_num/N)));
            spid1=((int32)param.Kp1_num*erreur_temp)/(int32)param.Kp1_den+((int32)param.Ki1_num*erreur_int_pid1*(int32)param.Tech)/((int32)param.Ki1_den*1000)+out_deriv;
            //spid1=spid1/100;
            erreur_av_pid1=erreur_temp;
            out_deriv_av1=out_deriv;
            
            if (spid1<0) spid1=0;
            if (spid1>1000) spid1=1000;
            pwm1_valeur=spid1;
        }
        else if(param.nb_boucles=='5')
        {
            pwm1_valeur=Get_trame_matlab();
        }
        else  // En boucle ouverte
        {
            // on met epsilon = consigne, car pas de soustracteur
            consigne=(offset_pwm1+(int32)(gain_pwm1*(float)(*(pointeur_gen+index_gen))))/100;
            erreur_int_pid1+=consigne;
            out_deriv=(((consigne-erreur_av_pid1)+out_deriv_av1/N)*((int32)param.Kd1_num))/((((((int32)param.Kd1_den*(int32)param.Tech)/1000)+(int32)param.Kd1_num/N))+1); //+1);
            spid1=((int32)param.Ki1_num*erreur_int_pid1*(int32)param.Tech)/((int32)param.Ki1_den*1000);
            spid2=out_deriv;
            erreur_av_pid1=consigne;
            out_deriv_av1=out_deriv;
            epsilon=(consigne>>1)+500; 
            if (epsilon<0) epsilon=0;
            if (epsilon>1000) epsilon=1000;
            pwm1_valeur=epsilon;      
        }

    // Debut transmission donnée    
        UART_UartPutChar('P'); //debut trame envoie de donnee
        UART_UartPutChar('P');
        UART_UartPutChar((DI_Fdd_Read()|DI_Fdg_Read())<<2); // mot de controle fin de course actifs ?? signale comme dfaut sur l'app
        UART_UartPutChar(param.Tech>>8); //envoie Tech
        UART_UartPutChar(param.Tech);
        // ensuite envoi consigne,epsilon,spid1,spid2,val1,val2
        UART_UartPutChar(consigne>>8); //envoie consigne
        UART_UartPutChar(consigne);
        UART_UartPutChar(epsilon>>8);
        UART_UartPutChar(epsilon);
        UART_UartPutChar(spid1>>8);
        UART_UartPutChar(spid1);
        UART_UartPutChar(spid2>>8);
        UART_UartPutChar(spid2);
        UART_UartPutChar(val1>>8);
        UART_UartPutChar(val1);
        UART_UartPutChar(val2>>8);
        UART_UartPutChar(val2);
        sent=0;
    }
    else
    {
    }
}

void arret_urg() {
    LED_Write(0);
            IN1_L298_Write(0);
        IN2_L298_Write(0);
        PWM_WriteCompare(0);
    if(DI_ATU_Read())
    {
        statefunc = arret;
        send_control_frame(AT);
    }
    else
    {
        statefunc=arret_urg;
    }
}

void send_control_frame(uint32 state)
{
        UART_UartPutChar('P'); //debut trame envoie de donnee
        UART_UartPutChar(state); // modifier pour envoie mot de controle (etat)
        UART_UartPutChar(param.Tech>>8); //envoie Tech
        UART_UartPutChar(param.Tech);
        // ensuite envoi consigne,epsilon,spid1,spid2,val1,val2
        UART_UartPutChar(0); //envoie dummy values
        UART_UartPutChar(0);
        UART_UartPutChar(0);
        UART_UartPutChar(0);
        UART_UartPutChar(0);
        UART_UartPutChar(0);
        UART_UartPutChar(0);
        UART_UartPutChar(0);
        UART_UartPutChar(0);
        UART_UartPutChar(0);
        UART_UartPutChar(0);
        UART_UartPutChar(0);
}
/* [] END OF FILE */
