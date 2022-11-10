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
#include "motor.h"
#include "Ventana.h"
#include "torque.h"



uint8_t readBuffer[32];
uint8_t writeBuffer[32];
uint8_t numBytesRead=0;
extern uint8_t busy;
extern float S;
extern uint8_t angulo;
extern uint16_t current;
extern float feed;
void MCC_USB_WRITE(char* str, int nBytes);
void MCC_USB_READ(void);
void executeCommand();
void USBCommandFetch();
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
    
    //Fila_T CommandList;
    Fila_Init();
    PORTBbits.RB0=0;
    PORTBbits.RB4=1;
    PORTBbits.RB5=1;
    LATBbits.LATB1=1;
    LATBbits.LATB2=1;
    LATBbits.LATB3=1;
           //mover_2(2);
           //PORTBbits.RB0=1; 
    numBytesRead=0; 
  
    EN_PIN=DISABLE;
    RESET_PIN=1;
    int a=0;
    bool flag_angulo;
    Encoder_Init();
    ADC_SelectChannel(channel_AN19);
    //PORTCbits.RC6=1;
    while (1)
    {
      // __delay_ms(2000);
      USBCommandFetch();
      __delay_ms(1);
      executeCommand();
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
      Actualizar_angulo();
       //USB service function
      //sprintf(writeBuffer,"\n %.4f",S);
      medir_corriente();
      sprintf(writeBuffer,"\n %.5f|%d|%d",S,angulo,current);
      MCC_USB_WRITE(writeBuffer,30);
       CDCTxService();
       memset(writeBuffer,0,sizeof(writeBuffer));
       __delay_ms(1);

    }
}


char lastToken[30]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
extern uint8_t largo;
void USBCommandFetch(){
   char* readTokens[30];
   char s[2]="\n";
   int i=0;
   int lastTokenFlag=0;
   if(largo<5){
         MCC_USB_READ();
         //Command fetch
         
         if(numBytesRead>0){
            memset(readTokens,0,sizeof(readTokens));
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