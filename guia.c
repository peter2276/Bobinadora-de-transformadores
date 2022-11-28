/*
 Funciones para el movimiento del motor guia
 */

#include "mcc_generated_files/mcc.h"
#include <xc.h>
#include "guia.h"
#include "GCODE.h"
#include "encoder.h"


extern float S;
uint8_t ustep=1;
uint8_t busy=0; //
volatile int pasos; //Numero de pasos a realizar
bool flag; //Toggle flag
extern float feed;
extern double inverse_time_feed;
extern float inverse_S;


//#define feedtoTMR2 46665*60/(2*STEPS_PER_MM)
//#define feedtoTMR2 15625*60/(2*STEPS_PER_MM)
#define MM_PER_STEP (float)1/STEPS_PER_MM
feed_state_t feed_state;

extern float pos_relativa_Z;
extern float objetivo_Z;
extern bool S_CHANGE;
double distanciaRestante;
void G01_TMR2_ISR(void){
   uint16_t period;
   STEP_PIN = ~STEP_PIN;
   if(S_CHANGE){
      switch(feed_state){
         case g95:
            ustep=1;
            period=feedtoTMR2*inverse_S*inverse_time_feed;
            while((uint16_t)(period/ustep)>255){
               ustep=ustep<<1;
               if(ustep>16){
                  ustep=16;
                  break;
               }
            }
            pasos =(int) (distanciaRestante* STEPS_PER_MM* ustep);
            setMicroStep(ustep);
            TMR2_LoadPeriodRegister((uint8_t)(period/ustep));

            break;
         default:
            break;
      }
      S_CHANGE=0;
   }
   if(flag == 0) flag = 1;
   else{
      if(DIRECTION_PIN==DIRECCION_POSITIVA){
         pos_relativa_Z=pos_relativa_Z+(float)(MM_PER_STEP/ustep);
         distanciaRestante=objetivo_Z-pos_relativa_Z;
      }
      else{
         pos_relativa_Z=(float)pos_relativa_Z-(float)(MM_PER_STEP/ustep);
         distanciaRestante=pos_relativa_Z-objetivo_Z;
      }
      pasos = pasos - 1; 
      flag=0;
      if(pasos==0){ 
         busy=0;
         EN_PIN=DISABLE;
         TMR2_StopTimer(); 
         pos_relativa_Z=objetivo_Z;
      }
   }
}

/*
void G95_TMR2_ISR(void){
   STEP_PIN = ~STEP_PIN;
   //TMR2_WriteTimer((uint8_t)(feed*feedtoTMR2));
   //TMR2_WriteTimer(254);
   
   if(flag == 0) flag = 1;
   else{
      pasos = pasos - 1; 
      flag=0;
      if(pasos==0){ 
         busy=0;
         EN_PIN=DISABLE;
         TMR2_StopTimer(); 
      }
   }
}
 * */

/**
   Function:
      void mover(float,int)
    
   Description:
      Esta funcion mueve el eje cierta distancia
                
   Precondition:
      None
        
   Parameters:
      float distancia - distancia a moverse expresada en milimetros. 
      int direccion - Establece la direccion del eje 
      * 1:Positiva
      * 0:Negativa
     
   Return Values:
      None
 */
/*
void mover(float distancia, int direccion){
   
   while(busy==1);
   busy=1;
   TMR2_LoadPeriodRegister((uint8_t)(feedtoTMR2*ustep/feed));
   EN_PIN=ENABLE;
   pasos = (distancia * STEPS_PER_MM) * uSTEP;
   DIRECTION_PIN = direccion;
   //PREPARACION Y HABILITACION EL TMR3
   flag=0;
   TMR2_WriteTimer(0);
   TMR2_StartTimer();
   
   return;
}
*/


/**
   Function:
      void mover_2(float)
    
   Description:
      Esta funcion mueve el eje cierta distancia
                
   Precondition:
      None
        
   Parameters:
      float distancia - distancia a moverse expresada en milimetros. El signo 
      establece la direccion
     
   Return Values:
      None
 */
void mover_2(float distancia){
   while(busy==1){}; //Espera a que termine ultima operacion
   if(distancia==0)return; 
   busy=1;
   EN_PIN=ENABLE;
   if(distancia<0){
      DIRECTION_PIN=DIRECCION_NEGATIVA;
      distancia = -distancia;
   }
   else {DIRECTION_PIN=DIRECCION_POSITIVA;}
   
   //Seleccion de uSTEP
   switch(feed_state){
      case g01:
         ustep=1;
         //S=(((feedtoTMR2*ustep)*inverse_time_feed));
         while(((feedtoTMR2*inverse_time_feed/ustep)>255)){
            ustep=ustep<<1;
            if(ustep>16){
               ustep=16;
               break;
            }
         }
         pasos =(int) (distancia * STEPS_PER_MM * ustep);
         setMicroStep(ustep);
         TMR2_LoadPeriodRegister((uint8_t)(feedtoTMR2*inverse_time_feed/ustep));
         break;
      case g95:
         /*
         ustep=1;
         inverse_S=0.01;
         while((uint16_t)(feedtoTMR2*inverse_S*inverse_time_feed/ustep)>255){
            ustep=ustep<<1;
            if(ustep>16){
               ustep=16;
               break;
            }
         }
         pasos =(int) (distancia * STEPS_PER_MM * ustep);
         setMicroStep(ustep);
         TMR2_LoadPeriodRegister((uint8_t)(feedtoTMR2*inverse_S*inverse_time_feed/ustep));
          * */
         
         TMR2_LoadPeriodRegister(255);
      break;
      default:
         break;
   }
   
   
   //setMicroStep(16);
   
   //PREPARACION Y HABILITACION EL TMR3
   flag=0;
   TMR2_WriteTimer(0);
   //TMR2_LoadPeriodRegister(255);
   
   TMR2_StartTimer();
   return;
}

void setMicroStep(uint8_t ustep){
   //uSTEP_PIN1=(bool)(ustep&0x1B);
   //uSTEP_PIN2=(bool)(ustep&0x1A);
   //uSTEP_PIN3=(bool)(ustep&0x10);
   
   switch(ustep){
      case 1:
         uSTEP_PIN1=0;
         uSTEP_PIN2=0;
         uSTEP_PIN3=0;
         break;
      case 2:
         uSTEP_PIN1=1;
         uSTEP_PIN2=0;
         uSTEP_PIN3=0;
         break;
      case 4:
         uSTEP_PIN1=0;
         uSTEP_PIN2=1;
         uSTEP_PIN3=0;
         break;
      case 8:
         uSTEP_PIN1=1;
         uSTEP_PIN2=1;
         uSTEP_PIN3=0;
         break;
      case 16:
         uSTEP_PIN1=1;
         uSTEP_PIN2=1;
         uSTEP_PIN3=1;
         break;
      default:
         uSTEP_PIN1=1;
         uSTEP_PIN2=1;
         uSTEP_PIN3=1;
         break;
   }
}