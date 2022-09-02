/*
 Funciones para el movimiento del motor guia
 */

#include "mcc_generated_files/mcc.h"
#include <xc.h>
#include "guia.h"

int flag;
int end_flag=0;
int pasos;


void MY_TMR3_ISR(void){
   STEP_PIN = ~STEP_PIN;
    TMR3_WriteTimer(127);
   if(flag == 0) flag = 1;
   else{
      pasos = pasos - 1; 
      flag=0;
      if(pasos==0){ 
         TMR3_StopTimer(); 
         end_flag=0;
      }
   }
}

void mover(int distancia, int direccion){
   
   while(end_flag==1);
   pasos = (distancia * STEPS_PER_MM) * uSTEP;
   DIRECTION_PIN = direccion;
   //PREPARACION Y HABILITACION EL TMR3
   end_flag=1;
   flag=0;
   TMR3_WriteTimer(0);
   TMR3_StartTimer();
   
   return;
}

void mover_2(int distancia){
   while(end_flag==1);
   end_flag=1;
   if(distancia<0){
      DIRECTION_PIN=DIRECCION_NEGATIVA;
      distancia = distancia*(-1);
   }
   else DIRECTION_PIN=DIRECCION_POSITIVA;
   pasos = (distancia * STEPS_PER_MM) * uSTEP;
   
   //PREPARACION Y HABILITACION EL TMR3
   flag=0;
   TMR3_WriteTimer(0);
   TMR3_StartTimer();
   
   return;
}
