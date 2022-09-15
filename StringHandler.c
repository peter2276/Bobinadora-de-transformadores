
#include <stdlib.h>
#include <string.h>

#include "GCODE.h"

int getTokens(char** token,char* str){
   char s[2]=" ";
   //strcpy(str,buffer);
   token[0] = strtok(str, s);
   int i=0;
   /* walk through other tokens */
   while( token[i] != NULL) {
      //if(token[i][strlen(token[i])]=='\n') token[i][strlen(token[i])]=0;
      i++;
      token[i] = strtok(NULL, s);
   }
   return i;
}

void getComands(Comando_T* comandos, char** tokens, int size){
   char buff[10];
   for(int i=0;i<size;i++){
      comandos[i].code=tokens[i][0];
      strcpy(buff, &tokens[i][1]);
	comandos[i].number=strtof(buff,NULL);
   }
   return;
}