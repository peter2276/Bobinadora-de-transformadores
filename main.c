/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F25K50
        Driver Version    :  2.00
*/

/*
 TIMER 2 reservado para el movimiento rapido del eje Z
 * Probablemente halla que cambiar al timer 0 por ser de 16 bits
 * Dependera de la frecuencia de pasos minima
 */

#include "mcc_generated_files/mcc.h"
#include "fila.h"
#include <string.h>
#include "StringHandler.h"
#include "guia.h"
#include "GCODE.h"
#include "encoder.h"



uint8_t readBuffer[64];
uint8_t writeBuffer[64];
uint8_t numBytesRead=0;
extern uint8_t busy;
extern float S;
void MCC_USB_WRITE(char* str, int nBytes);
void MCC_USB_READ(void);
void executeCommand(Fila_T* CommandList);
void USBCommandFetch(Fila_T* CommandList);
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:
    
    //Encoder interrupt handler for IOC interruption
    IOCC2_SetInterruptHandler(Encoder_ISR);
    TMR0_SetInterruptHandler(Timing_TMR0_ISR);
    //INTCONbits.IOCIE = 0;
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    TMR3_StopTimer();
    TMR2_StopTimer();
    TMR0_StartTimer();
    
    Fila_T CommandList;
    Fila_Init(&CommandList);
    PORTBbits.RB0=0;
    PORTBbits.RB4=1;
    PORTBbits.RB5=1;
    PORTBbits.RB1=0;
    PORTBbits.RB2=0;
    PORTBbits.RB3=0;
           //mover_2(2);
           //PORTBbits.RB0=1; 
    numBytesRead=0; 
  
    EN_PIN=DISABLE;
    int a=0;
    S=0;
    while (1)
    {
      // __delay_ms(2000);
      //USBCommandFetch(&CommandList);
      //__delay_ms(10);
      //Command processing
       /*
       if(a==0){
          sprintf(buf,"N01");
          Fila_Agregar(&CommandList,buf,strlen(buf));
          sprintf(buf,"N02");
          Fila_Agregar(&CommandList,buf,strlen(buf));
          sprintf(buf,"N03");
          Fila_Agregar(&CommandList,buf,strlen(buf));
          a=1;
       }
       FilaPop(writeBuffer,&CommandList);
      */
      if(a==4){
         //executeCommand(&CommandList);
         a=0;
      }
      else a++;
       //USB service function
      sprintf(writeBuffer,"\n %.4f",S);
      MCC_USB_WRITE(writeBuffer,10);
       CDCTxService();
       memset(writeBuffer,0,sizeof(writeBuffer));
       S=10;
       __delay_ms(100);
    }
}


char lastToken[30]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
void USBCommandFetch(Fila_T* CommandList){
   char* readTokens[30];
   char s[2]="\n";
   int i=0;
   int lastTokenFlag=0;
   if(CommandList->size<5){
         MCC_USB_READ();
         //Command fetch
         
         if(numBytesRead>0){
            memset(readTokens,0,sizeof(readTokens));
            for(int i=0; i<sizeof(writeBuffer);i++){
               writeBuffer[i]=0;
            } 
            //sprintf(str,"%s",readBuffer);
            //MCC_USB_WRITE(readBuffer,50);
            //Fila_Agregar(CommandList,readBuffer,strlen(readBuffer));
            //sprintf(writeBuffer,"XX");
            //sprintf(writeBuffer,"%s%s",writeBuffer,readBuffer);
            
            if(readBuffer[numBytesRead-1]!=0x0A){
               lastTokenFlag=1;
            }
            else{
               lastTokenFlag=0;
            }
            
            readTokens[0]=strtok(readBuffer,s);
            sprintf(lastToken,"%s%s",lastToken,readTokens[0]);
            Fila_Agregar(CommandList,lastToken,strlen(lastToken));
            //sprintf(writeBuffer,"%s%sX",writeBuffer,lastToken);
            readTokens[1]=strtok(NULL,s);
            i=1;
            while(readTokens[i]!=NULL){
               readTokens[i+1]=strtok(NULL,s);
               if(readTokens[i+1]!=NULL||lastTokenFlag==0){
                  //sprintf(writeBuffer,"%s%sX",writeBuffer,readTokens[i]);
                  Fila_Agregar(CommandList,readTokens[i],strlen(readTokens[i]));     
               }
               else strcpy(lastToken,readTokens[i]);
               i++;
            }                    
            if(lastTokenFlag==0){
               memset(lastToken,0,sizeof(lastToken));
            }
            //sprintf(writeBuffer,"%sXX%d",writeBuffer,i);
            numBytesRead=0;
            memset(readBuffer,0,sizeof(readBuffer));
            //MCC_USB_WRITE(writeBuffer,sizeof(writeBuffer));
          }
       }
}

void executeCommand(Fila_T* CommandList){
   char strCommand[30];
   int numTokens=0;
   Comando_T comando[20];
   char* TokensCom[20];
   if(busy==0){
         if(CommandList->size>0){
            //sprintf(writeBuffer,"");
            memset(comando,0,sizeof(comando));
            memset(strCommand,0,sizeof(strCommand));
            FilaPop(strCommand,CommandList);
            for(int i=0;i<20;i++){
               TokensCom[i]=NULL;
            }
            
            numTokens=getTokens(TokensCom,strCommand);
            //sprintf(writeBuffer,"%s%sXX%d\n",writeBuffer,strCommand,numTokens);
            getComands(comando,TokensCom,numTokens);
            
            comando[0].code=TokensCom[0][0];
            
            if(comando[0].code=='G'){
               switch((int)comando[0].number){
                  case 0:
                     G_00(&comando[1],1);
                     break;
                  case 53:
                     G_53(&comando[1],1);
                     break;
                  default:
                     break;         
               }
            }
             
            numTokens=0;
            //MCC_USB_WRITE(writeBuffer,strlen(writeBuffer));
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

//USB interruption
//Read command 
//save in a FIFO queue
//out

//Next angle interrupt (external interrupt)
//read timer
//clear timer
//recalculate speed
//out



/**
 End of File
*/