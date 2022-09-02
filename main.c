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
//#include "GCODE.h"


void MCC_USB_CDC_DemoTasks(void);
/*
                         Main application
 */

static uint8_t readBuffer[64];
static uint8_t writeBuffer[64];
uint8_t numBytesRead=0;
void MCC_USB_WRITE(char* str, int nBytes);
void MCC_USB_READ(void);
 void (*G[100])(Comando_T* axis, int n);
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    G[0]=G_00;
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
    TMR3_SetInterruptHandler(MY_TMR3_ISR);
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
    while (1)
    {
       //guia.position=10;
       //G[0](&guia,1);
       //guia.position=-10;
       //__delay_ms(500);
       //G[0](&guia,1);
       
       MCC_USB_READ();
       //Fila_Agregar(&CommandList,"a casa",strlen("a casa"));
       //send=FilaPop(&CommandList);
       //if(send!=0) MCC_USB_WRITE(send,strlen(send));
       //free(send);
       
       if(numBytesRead>0){
         numTokens=getTokens(TokensCom,readBuffer);
         //MCC_USB_WRITE(TokensCom[0],strlen(TokensCom[0]));
         numBytesRead=0;
         getComands(comando,TokensCom,numTokens);
         //MCC_USB_WRITE(comando[0].code,1);
         if(comando[0].code=='G'){
            G[(int)comando[0].number](&comando[1],numTokens-1);
         }
       }
       numTokens=0;
       TokensCom[0]=NULL;
        
       __delay_ms(500);
       //Fetch next command
       //execute 
    }
}


void MCC_USB_WRITE(char* str, int nBytes){
   putUSBUSART(str,nBytes);
   CDCTxService();
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

    if( USBUSARTIsTxTrfReady() == true)
    {
        uint8_t i;
        //uint8_t numBytesRead;

        numBytesRead = getsUSBUSART(readBuffer, sizeof(readBuffer));

        for(i=0; i<numBytesRead; i++)
        {
            writeBuffer[i] = readBuffer[i];
        }

        if(numBytesRead > 0)
        {
            //putUSBUSART(writeBuffer,numBytesRead);
        }
    }
    CDCTxService();
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