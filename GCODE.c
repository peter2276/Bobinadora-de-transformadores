#include "guia.h"
#include "GCODE.h"
#include "mcc_generated_files/mcc.h"
float pos_relativa_Z=0;
float pos_absoluta_Z=0;


void G_00(Comando_T* axis, int n){
   if(axis==NULL) return;
   float distancia;
   for(int i=0;i<n;i++){
      if(axis[i].code  =='Z' || axis[i].code == 'z'){
         distancia = axis[i].number - pos_relativa_Z;
         distancia = axis[i].number;
         pos_relativa_Z= axis[i].number;
         pos_absoluta_Z= pos_absoluta_Z + distancia;
         mover_2(distancia);
      }
   }
   return;
}

void G_01(Comando_T* axis, int n){
   
}

void G_53(Comando_T* axis, int n){
   for(int i=0;i<n;i++){
      if(axis[i].code  =='Z' || axis[i].code == 'z'){
         pos_relativa_Z=axis[i].number;
      }
   }
   return;
}
