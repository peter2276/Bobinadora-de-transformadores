
#include <xc.h>
#include "fila.h"
#include <stdlib.h>
#include <string.h>
#define MaxNumCommands 10
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

/*
void Fila_Init(Fila_T* fila){
   fila->cabeza=0;
   fila->cola=0;
   fila->size=0;
}

int Fila_Agregar(Fila_T* fila, char* comando, int nBytes){
   //Checking valid parameters
   if(comando==NULL)return 1;
   
   NodoComando_T* nuevo=NULL;
   while(nuevo==NULL){
      nuevo = (NodoComando_T*)malloc(sizeof(NodoComando_T));
   }
  
   
   strcpy(nuevo->comando,comando);
   //Adding new command in queue
   if(fila->size>0){
      fila->cola->next = nuevo;
      fila->cola= nuevo;
      nuevo->next=NULL;
   }
   else{
      fila->cola= nuevo;
      fila->cabeza=nuevo;
      nuevo->next=NULL;
   }
   fila->size=fila->size+1;
   return 0;
}

int FilaPop(char* str,Fila_T* fila){
   //char r[30];
   NodoComando_T* viejo;
   if(fila->size>0){
      fila->size=fila->size-1;
      strcpy(str,fila->cabeza->comando);
      viejo=fila->cabeza;
      if(fila->size==0){
         fila->cola=NULL;
         fila->cabeza=NULL;
      }
      else{
         fila->cabeza=fila->cabeza->next;
      }
      free(viejo);
      return 1;
   }
   else str[0]=0;
   return 0;
}
*/