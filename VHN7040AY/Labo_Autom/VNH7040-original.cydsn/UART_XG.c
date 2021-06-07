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
#include "UART_XG.h"
int32 Get_trame_matlab()
{
    uint8 indexe,*tmp8;
    uint8 rxdata[FRAME_SIZE-2];
    uint32 tmp32,debut;
    tmp8 =(uint8*) &tmp32;
    indexe=0;
    debut=time;
    while((indexe<FRAME_SIZE_MATLAB)&&((time-debut)<UART_TIMEOUT))
    {
      tmp32 = UART_UartGetByte();
      if (tmp32>255)
      {
      //   UART_UartPutString("Buffer eror ok\r\n");
       // indexe=0;
      }    
      else 
      {
        if ((*tmp8=='M') && (indexe==0))
        {
            indexe++;
        }
        else if ((*tmp8=='M') && (indexe==1))
        {
            indexe++;
        }
        else if((indexe>1)&&(indexe<FRAME_SIZE_MATLAB)) // ??? 
        {
            rxdata[indexe-2]=*tmp8; 
            indexe++;
        }
        else
        {
            indexe=0;
        }  
       } 
    }
    if(indexe==3) return (rxdata[0]<<8)+rxdata[1];
    else return 0;
}

uint8 Get_trame() // uint8 *rxdata)
{

    uint8 indexe,*tmp8,ok;
    uint8 rxdata[FRAME_SIZE-4];
    uint16 CRCcalc;
    uint32 tmp32,debut;
    tmp8 =(uint8*) &tmp32;
    ok=false;
    indexe=0;
    debut=time;
//    txdata=rxdata;
    while((indexe<FRAME_SIZE)&&((time-debut)<UART_TIMEOUT))
    {
      tmp32 = UART_UartGetByte();
      if (tmp32>255)
      {
      //   UART_UartPutString("Buffer eror ok\r\n");
       // indexe=0;
      }    
      else 
      {
        if ((*tmp8=='P') && (indexe==0))
        {
            indexe++;
        }
        else if ((*tmp8=='A') && (indexe==1))
        {
            indexe++;
        }
        else if ((*tmp8=='R') && (indexe==2))
        {
            indexe++;
        }
        else if ((*tmp8=='.') && (indexe==3))
        {
            indexe++;
        }
        else if((indexe>3)&&(indexe<FRAME_SIZE)) // ??? 
        {
            rxdata[indexe-4]=*tmp8; 
            indexe++;
        }
        else
        {
            indexe=0;
        }  
       } 
    }
    param.Tech=(rxdata[0]<<8)+rxdata[1];
    param.nb_boucles=rxdata[2];
    param.Kp1_num=(rxdata[3]<<8)+rxdata[4];
    param.Kp1_den=(rxdata[5]<<8)+rxdata[6];
    param.Kp2_num=(rxdata[7]<<8)+rxdata[8];
    param.Kp2_den=(rxdata[9]<<8)+rxdata[10];
    param.Kd1_num=(rxdata[11]<<8)+rxdata[12];
    param.Kd1_den=(rxdata[13]<<8)+rxdata[14];
    param.Kd2_num=(rxdata[15]<<8)+rxdata[16];
    param.Kd2_den=(rxdata[17]<<8)+rxdata[18];
    param.Ki1_num=(rxdata[19]<<8)+rxdata[20];
    param.Ki1_den=(rxdata[21]<<8)+rxdata[22];
    param.Ki2_num=(rxdata[23]<<8)+rxdata[24];
    param.Ki2_den=(rxdata[25]<<8)+rxdata[26];
    param.type_consigne=rxdata[27];
    param.cons_initiale=(rxdata[28]<<8)+rxdata[29];
    param.cons_finale=(rxdata[30]<<8)+rxdata[31];
    param.cons_per_num=(rxdata[32]<<8)+rxdata[33];
    param.cons_per_den=(rxdata[34]<<8)+rxdata[35];
    param.CRC=(rxdata[36]<<8)+(rxdata[37]);
    CRCcalc= param.Tech^param.Kp1_num^param.Kp1_den^param.Kp2_num^param.Kp2_den^ \
            param.Ki1_num^param.Ki1_den^param.Ki2_num^param.Ki2_den^param.Kd1_num^param.Kd1_den^ \
            param.Kd1_num^param.Kd1_den^param.Kp2_num^param.cons_initiale^   \
            param.cons_finale^param.cons_per_den^param.cons_per_num^((param.nb_boucles<<8)+param.type_consigne);
    if(CRCcalc==param.CRC)
            {
                ok=true;
                if(param.nb_boucles>=128) 
                {
                    param.nb_boucles-=128;
                    marche_bool=true;
                }
                else 
                {
                    marche_bool=false;
                }
            }
            else
            {
                ok=false;
            }
    return ok;
}

/* [] END OF FILE */
