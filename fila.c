
#include <xc.h>
#include "fila.h"
#include <stdlib.h>
#include <string.h>
#define MaxNumCommands 20
#define MaxLength 32
char fila[MaxNumCommands][MaxLength];
uint8_t largo=0;
uint8_t cabeza=0;
uint8_t cola=0;
void Fila_Init(){
   cabeza=0;
   cola=0;
   largo=0;
   memset(fila,0,sizeof(char)*MaxLength*MaxNumCommands);
}
int Fila_Agregar(char* comando, int nBytes){
   if(largo<MaxNumCommands){
      if(nBytes<MaxLength){
         memcpy(fila[cabeza],comando,nBytes);
         cabeza++;
         cabeza=cabeza%MaxNumCommands;
         largo++;
         return 0;
      }
   }
   return 1;
}
int FilaPop(char* str){
   if(largo>0){
         memcpy(str,fila[cola],MaxLength);
         cola++;
         cola=cola%MaxNumCommands;
         largo--;
         return 1;
   }
   return 0;
}
