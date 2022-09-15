
#include "fila.h"
#include <stdlib.h>
#include <string.h>

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
