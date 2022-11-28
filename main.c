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

#define FIN_CARRERA PORTCbits.RC1

extern uint8_t writeBuffer[32];
extern uint8_t numBytesRead=0;
extern uint8_t busy;
extern float S;
//extern double inverse_S;
extern uint8_t angulo;
extern uint8_t largo;
extern uint16_t current;
extern float feed;
extern float pos_relativa_Z;
uint8_t error=0;

void inicializar_Sistema(void); 
   
void main(void)
{
    inicializar_Sistema();
    while (1)
    {
      USBCommandFetch();
      executeCommand();
      
      medir_corriente();
      error=(~FIN_CARRERA)&0x01;
      sprintf(writeBuffer,"%.3f %.3f %d %d %d ",S,pos_relativa_Z,angulo,current,error);
      
      MCC_USB_WRITE(writeBuffer,30);
      CDCTxService();
      memset(writeBuffer,0,sizeof(writeBuffer));
      
      __delay_ms(1);
    }
}

void inicializar_Sistema(){
   // Initialize the device
    SYSTEM_Initialize();
    IOCC2_SetInterruptHandler(Encoder_ISR);
    TMR0_SetInterruptHandler(Timing_TMR0_ISR);
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
   TMR3_StopTimer();
   TMR2_StopTimer();
   TMR0_StartTimer();
   Fila_Init();
   PORTBbits.RB0=0;
   PORTBbits.RB4=1;
   PORTBbits.RB5=1;
   LATBbits.LATB1=1;
   LATBbits.LATB2=1;
   LATBbits.LATB3=1;
   numBytesRead=0; 
   EN_PIN=DISABLE;
   RESET_PIN=1;
   ADC_SelectChannel(channel_AN19);
   
}




