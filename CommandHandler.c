#include "mcc_generated_files/mcc.h"
#include "fila.h"
#include "GCODE.h"
#include "StringHandler.h"
#include "CommandHandler.h"

uint8_t readBuffer[32];
uint8_t writeBuffer[32];
uint8_t numBytesRead=0;
extern uint8_t busy;

char lastToken[30]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
extern uint8_t largo;
#define sizeofReadTokens 32
void USBCommandFetch(){
   char* readTokens[sizeofReadTokens];
   char s[2]="\n";
   int i=0;
   int lastTokenFlag=0;
   if(largo<15){
         MCC_USB_READ();
         //Command fetch
         if(readBuffer[0]=='E'){
            ParadaEmergencia();
         }
         if(numBytesRead>0){
            memset(readTokens,0,sizeofReadTokens);
            if(readBuffer[numBytesRead-1]!=0x0A){
               lastTokenFlag=1;
            }
            else{
               lastTokenFlag=0;
            }
            
            readTokens[0]=strtok(readBuffer,s);
            sprintf(lastToken,"%s%s",lastToken,readTokens[0]);
            Fila_Agregar(lastToken,strlen(lastToken));
            readTokens[1]=strtok(NULL,s);
            i=1;
            while(readTokens[i]!=NULL){
               readTokens[i+1]=strtok(NULL,s);
               if(readTokens[i+1]!=NULL||lastTokenFlag==0){
                  Fila_Agregar(readTokens[i],strlen(readTokens[i]));     
               }
               else strcpy(lastToken,readTokens[i]);
               i++;
            }                    
            if(lastTokenFlag==0){
               memset(lastToken,0,sizeof(lastToken));
            }
            numBytesRead=0;
            memset(readBuffer,0,sizeof(readBuffer));
          }
       }
}

void executeCommand(){
   char strCommand[30];
   int numTokens=0;
   Comando_T comando[20];
   char* TokensCom[20];
   if(busy==0){
         if(largo>0){
            //Inicializacion
            memset(comando,0,sizeof(comando));
            memset(strCommand,0,sizeof(strCommand));
            for(int i=0;i<20;i++){
               TokensCom[i]=NULL;
            }
            
            //Recupera el string de la fina
            FilaPop(strCommand);
            //recupera el numero de tokens del strings
            numTokens=getTokens(TokensCom,strCommand);
            //Recupera cada comando del string
            getComands(comando,TokensCom,numTokens);
            sprintf(writeBuffer,"%c \n",(int)comando[1].code);
            if(comando[0].code=='G'){
               switch((int)comando[0].number){
                  case 0:
                     //G_00(&comando[1],numTokens);
                     //feed=400;
                     G_01(&comando[1],numTokens);
                     break;
                  case 1:
                     G_01(&comando[1],numTokens);
                     break;
                  case 53:
                     G_53(&comando[1],numTokens);
                     break;
                  case 95:
                     G_95(&comando[1],numTokens);
                     break;
                  case 97:
                     G_97(&comando[1],numTokens);
                  break;
                  default:
                     break;         
               }
            }
            if(comando[0].code=='M'){
               switch((int)comando[0].number){
                  case 3:
                     M_3(NULL,0);
                     break;
                  case 4:
                     M_4(NULL,0);
                     break;
                  case 5:
                     M_5(NULL,0);
                     break;
                  default:
                     break;
               }
            }
            numTokens=0;
            //MCC_USB_WRITE(writeBuffer,10);
         }
      }
   return;
}


void MCC_USB_WRITE(char* str, int nBytes){
   if( USBGetDeviceState() < CONFIGURED_STATE )
    {
        return;
    }
    if( USBIsDeviceSuspended()== true )
    {
        return;
    }
   if( USBUSARTIsTxTrfReady() == true)
    {
      putUSBUSART(str,nBytes);
   }
   //CDCTxService();
}
void MCC_USB_READ(void)
{
    if( USBGetDeviceState() < CONFIGURED_STATE )
    {
        return;
    }
    if( USBIsDeviceSuspended()== true )
    {
        return;
    }
      numBytesRead = getsUSBUSART(readBuffer, sizeof(readBuffer));
      //if(numBytesRead>0) MCC_USB_WRITE("command get \n",sizeof("command get \n"));
}