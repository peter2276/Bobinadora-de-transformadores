/* 
 * File:   StringHandler.h
 * Author: pedro
 *
 * Created on August 29, 2022, 10:47 AM
 */

#ifndef STRINGHANDLER_H
#define	STRINGHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "GCODE.h"
uint8_t getTokens(char** token,char* str);
void getComands(Comando_T* comandos, char** tokens, uint8_t size);

#ifdef	__cplusplus
}
#endif

#endif	/* STRINGHANDLER_H */

