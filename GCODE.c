#include "guia.h"
#include "GCODE.h"
float pos_relativa_Z=0;
float pos_absoluta_Z=0;


void G_00(Comando_T* axis, int n){
   float distancia;
   for(int i=0;i<n;i++){
      if(axis[i].code  =='Z' || axis[i].code == 'z'){
         distancia = axis[i].number - pos_relativa_Z;
         pos_relativa_Z+=distancia;
         pos_absoluta_Z+=distancia;
         mover_2(distancia);
      }
   }
   return;
}
void G_53(Comando_T* axis, int n){
   for(int i=0;i<n;i++){
      if(axis[i].code  =='Z' || axis[i].code == 'z'){
         pos_relativa_Z=axis[i].number;
      }
   }
   return;
}
