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
 TIMER 3 reservado para el movimiento rapido del eje Z
 * Probablemente halla que cambiar al timer 0 por ser de 16 bits
 * Dependera de la frecuencia de pasos minima
 */

#include "mcc_generated_files/mcc.h"
#include "fila.h"
#include <string.h>
#include "StringHandler.h"
#include "guia.h"
#include "GCODE.h"



static uint8_t readBuffer[64];
static uint8_t writeBuffer[64];
uint8_t numBytesRead=0;
extern uint8_t busy;
void MCC_USB_WRITE(char* str, int nBytes);
void MCC_USB_READ(void);
 void (*G[100])(Comando_T* axis, int n);
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    G[0]=G_00;
    G[53]=G_53;
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

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
    TMR2_SetInterruptHandler(MY_TMR2_ISR);
    char* send;
    char* TokensCom[10];
    int numTokens=0;
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
    Comando_T comando[10];
    char buffer[10];
    char str[200];
    char comandoLista[30];
    char* readTokens[10];
    char s[2]="\n";
    int i=0;
    while (1)
    {
       if(CommandList.size<5){
         MCC_USB_READ();
         //Command fetch
         if(numBytesRead>0){
            sprintf(str,"XX");
            readTokens[0]=strtok(readBuffer,s);
            i=0;
            while(readTokens[i]!=NULL){
               Fila_Agregar(&CommandList,readTokens[i],strlen(readBuffer));
               sprintf(str,"%s %s",str,readTokens[i]);
               readTokens[i]=NULL;
               i++;
            }
            __delay_ms(10);
            //sprintf(str,"%s",readBuffer);
             //__delay_ms(100);
            numBytesRead=0;

            for(int i=0; i<sizeof(readBuffer);i++){
               readBuffer[i]=0;
            }
            MCC_USB_WRITE(str,50);
          }
         
       }
      __delay_ms(10);
      //Command processing
      if(!busy){
         if(CommandList.size>0){
            //sprintf(str,"XX");

            FilaPop(comandoLista,&CommandList);
            //sprintf(str,"%s %d",str,CommandList.size);
            numTokens=getTokens(TokensCom,comandoLista);
            getComands(comando,TokensCom,numTokens);
            comando[0].code=TokensCom[0][0];
            if(comando[0].code=='G'){
               G[(int)comando[0].number](&comando[1],1);
            }
            numTokens=0;
            TokensCom[0]=NULL;
            
         }
      }
       //USB service function
       CDCTxService();
       __delay_ms(100);
    }
}


void MCC_USB_WRITE(char* str, int nBytes){
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
      //if(readBuffer[0]==0)numBytesRead=0;
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