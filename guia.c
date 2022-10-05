/*
 Funciones para el movimiento del motor guia
 */

#include "mcc_generated_files/mcc.h"
#include <xc.h>
#include "guia.h"


uint8_t busy=0; //
volatile int pasos; //Numero de pasos a realizar
bool flag; //Toggle flag

void G00_TMR2_ISR(void){
   STEP_PIN = ~STEP_PIN;
   TMR2_WriteTimer(127);
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

void G01_TMR2_ISR(void){
   STEP_PIN = ~STEP_PIN;
    TMR2_WriteTimer(127);
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
   pasos =(int) (distancia * STEPS_PER_MM * uSTEP);
   //PREPARACION Y HABILITACION EL TMR3
   flag=0;
   TMR2_WriteTimer(0);
   TMR2_StartTimer();
   return;
}
/*
int Linear_Feed(int nbits){
   FCLOCK;
   
}*/
