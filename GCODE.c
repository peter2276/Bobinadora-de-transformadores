#include "guia.h"
#include "GCODE.h"
#include "mcc_generated_files/mcc.h"
#include "motor.h"
#include "fila.h"
float pos_relativa_Z=0;
float pos_absoluta_Z=0;
float objetivo_Z=0;

/*
 Puntero a Funcion FEED
 * Depende de la configuracion del feed a que funcion apunta
 * G93: Linear feed
 * G94: Inverse time feed
 * G95: Revolutional feed  
 * Recive 
 */
int (*F)(int feed,int nbits); //Retorna valor para setear el timer de pasos
extern int pasos;
extern uint8_t busy;
/**
   Function:
      void MY_TMR2_ISR(void)
    
   Description:
      Interrupcion del timer 2. Realiza los pasos solicitados en el eje
 *    Configurada solamente por las funciones mover
                
   Precondition:
      None
        
   Parameters:
      None
     
   Return Values:
      None
 */
float feed;
double inverse_time_feed;
/*
void G_00(Comando_T* axis, int n){
   if(axis==NULL) return;
   feed_state=g00;
   float distancia;
   feed=400;
   inverse_time_feed=1/feed;
   for(int i=0;i<n;i++){
      if(axis[i].code  =='Z' || axis[i].code == 'z'){
         TMR2_SetInterruptHandler(G01_TMR2_ISR);
         distancia = axis[i].number - pos_relativa_Z;
         //distancia = axis[i].number;
         pos_relativa_Z= axis[i].number;
         pos_absoluta_Z= pos_absoluta_Z + distancia;
         mover_2(distancia);
      }
   }
   return;
}
*/



void G_01(Comando_T* axis, int n){
   if(axis==NULL)return;
   TMR2_SetInterruptHandler(G01_TMR2_ISR);
   float distancia;
   for(int i=0;i<n;i++){
      if(axis[i].code=='F'){
         feed=axis[i].number;
      }
   }
   inverse_time_feed=1/feed;
   for(int i=0;i<n;i++){
      if(axis[i].code  =='Z' || axis[i].code == 'z'){
         distancia = axis[i].number - pos_relativa_Z;
         objetivo_Z=axis[i].number;
         //distancia = axis[i].number;
         //pos_relativa_Z= axis[i].number;
         //pos_absoluta_Z= pos_absoluta_Z + distancia;
         mover_2(distancia);
      }
   }  
}
/*
void G_95(Comando_T* axis, int n){
   if(axis==NULL)return;
   TMR2_SetInterruptHandler(G01_TMR2_ISR);
   float distancia;
   for(int i=0;i<n;i++){
      if(axis[i].code=='F'){
         feed=axis[i].number; 
         inverse_time_feed=1/feed;
      }
   }
   for(int i=0;i<n;i++){
      if(axis[i].code  =='Z' || axis[i].code == 'z'){
         distancia = axis[i].number - pos_relativa_Z;
         objetivo_Z=axis[i].number;
         //distancia = axis[i].number;
         //pos_relativa_Z= axis[i].number;
         //pos_absoluta_Z= pos_absoluta_Z + distancia;
         mover_2(distancia);
      }
   }  
}*/
 
extern uint8_t angulo;
void G_53(Comando_T* axis, int n){
   for(int i=0;i<n;i++){
      if(axis[i].code  =='Z' || axis[i].code == 'z'){
         pos_relativa_Z=axis[i].number;
      }
   }
   angulo=0;
   return;
}

void G_97(Comando_T* axis, int n){
   if(n==0) return;
   if(n>1){
      if(axis[1].code == 'M'){
         if(axis[1].number==3) M_3(NULL,0);
         if(axis[1].number==4) M_4(NULL,0);
         __delay_ms(1);
      }
   }
   if(axis[0].code == 'S'){
      encenderRotor();
   }
   return;
}
void M_3(Comando_T* axis, int n){
   DireccionRotor(CW);
   return;
}
void M_4(Comando_T* axis, int n){
   DireccionRotor(CCW);
   return;
}
void M_5(Comando_T* axis, int n){
   apagarRotor();
   return;
}

void ParadaEmergencia(){
   EN_PIN=DISABLE;
   TMR2_StopTimer();
   Fila_Init();
   busy=0;
   pos_relativa_Z=0;
   apagarRotor();
}
