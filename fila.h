/* 
 * File:   fila.h
 * Author: pedro
 *
 * Created on August 27, 2022, 12:36 PM
 */

#ifndef FILA_H
#define	FILA_H

#ifdef	__cplusplus
extern "C" {
#endif

    
int FilaPop(char* str);
int Fila_Agregar(char* comando, int nBytes);
void Fila_Init();
/*
    
typedef struct NodoComando_T{
   char comando[30];
   struct NodoComando_T* next;
}NodoComando_T;

typedef struct Fila_T{
   NodoComando_T* cabeza;
   NodoComando_T* cola;
   int size;
}Fila_T;
void Fila_Init(Fila_T* fila);
int Fila_Agregar(Fila_T* fila, char* comando,int);
int FilaPop(char* str,Fila_T* CommandList);

*/

#ifdef	__cplusplus
}
#endif

#endif	/* FILA_H */

