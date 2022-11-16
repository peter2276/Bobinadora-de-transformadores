
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include "GCODE.h"

uint8_t getTokens(char** token,char* str){
   char s[2]=" ";
   token[0] = strtok(str, s);
   uint8_t i=0;
   /* walk through other tokens */
   while( token[i] != NULL) {
      i++;
      token[i] = strtok(NULL, s);
   }
   return i;
}

void getComands(Comando_T* comandos, char** tokens, uint8_t size){
   char buff[10];
   for(uint8_t i=0;i<size;i++){
      comandos[i].code=tokens[i][0];
      strcpy(buff, &tokens[i][1]);
	comandos[i].number=strtof(buff,NULL);
   }
   return;
}