/*
 Funciones para el movimiento del motor guia
 */

#include "mcc_generated_files/mcc.h"
#include <xc.h>
#include "guia.h"
#include "GCODE.h"


uint8_t busy=0; //
volatile int pasos; //Numero de pasos a realizar
bool flag; //Toggle flag
extern float feed;
/*
void G00_TMR2_ISR(void){
   STEP_PIN = ~STEP_PIN;
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

#define feedtoTMR2 46665*60/(2*STEPS_PER_MM)

void G01_TMR2_ISR(void){
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
void mover(float distancia, int direccion){
   
   while(busy==1);
   busy=1;
   
   EN_PIN=ENABLE;
   pasos = (distancia * STEPS_PER_MM) * uSTEP;
   DIRECTION_PIN = direccion;
   //PREPARACION Y HABILITACION EL TMR3
   flag=0;
   TMR2_WriteTimer(0);
   TMR2_StartTimer();
   
   return;
}

void setMicroStep(int ustep){
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
   uint8_t ustep=1;
   //Seleccion de uSTEP
   while(((uint16_t)((feedtoTMR2*ustep)/feed))>255){
      ustep=ustep<<1;
      if(ustep>16){
         ustep=16;
         break;
      }
   }
   pasos =(int) (distancia * STEPS_PER_MM * ustep);
   //setMicroStep(16);
   setMicroStep(ustep);
   //PREPARACION Y HABILITACION EL TMR3
   flag=0;
   TMR2_WriteTimer(0);
   //TMR2_LoadPeriodRegister(255);
   TMR2_LoadPeriodRegister((uint8_t)(feedtoTMR2*ustep/feed));
   TMR2_StartTimer();
   return;
}
/*
int Linear_Feed(int nbits){
   FCLOCK;
   
}*/
