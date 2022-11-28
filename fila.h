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
void Fila_Init(void);


#ifdef	__cplusplus
}
#endif

#endif	/* FILA_H */

