#include "guia.h"
#include "GCODE.h"
#include "mcc_generated_files/mcc.h"
float pos_relativa_Z=0;
float pos_absoluta_Z=0;

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


void G_00(Comando_T* axis, int n){
   if(axis==NULL) return;
   float distancia;
   for(int i=0;i<n;i++){
      if(axis[i].code  =='Z' || axis[i].code == 'z'){
         TMR2_SetInterruptHandler(G00_TMR2_ISR);
         distancia = axis[i].number - pos_relativa_Z;
         //distancia = axis[i].number;
         pos_relativa_Z= axis[i].number;
         pos_absoluta_Z= pos_absoluta_Z + distancia;
         mover_2(distancia);
      }
   }
   return;
}
float feed;/*
void G_01(Comando_T* axis, int n){
   if(axis[n].code=='F'){
      feed=axis[n]->number;
   }
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
   
}*/

void G_53(Comando_T* axis, int n){
   for(int i=0;i<n;i++){
      if(axis[i].code  =='Z' || axis[i].code == 'z'){
         pos_relativa_Z=axis[i].number;
      }
   }
   return;
}
