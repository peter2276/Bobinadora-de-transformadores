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
#include "CommandHandler.h"



extern uint8_t writeBuffer[32];
extern uint8_t numBytesRead=0;
extern uint8_t busy;
extern float S;
extern uint8_t angulo;
extern uint8_t largo;
extern uint16_t current;
extern float feed;

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
      sprintf(writeBuffer,"%.6f %d %d ",S,angulo,current);
      MCC_USB_WRITE(writeBuffer,30);
       CDCTxService();
       memset(writeBuffer,0,sizeof(writeBuffer));
       __delay_ms(1);

    }
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