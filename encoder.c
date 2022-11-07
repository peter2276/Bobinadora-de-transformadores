#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "Ventana.h"

#define nsPERCLOCK 2667
#define NBITSTMR0 16
#define NRANURAS 100
int prescaler; //Variable para prescaler del TMR0 por software
float S; //Velocidad luego del filtro

void Timing_TMR0_ISR(){
   
   TMR0_WriteTimer(0);
   prescaler++;
   if(prescaler>=10){ //Si pasa mucho tiempo
      rtU.Input= 0;
      Ventana_step();
      S=0;
      prescaler=0;
   }
}

#define FILTER_LENGTH 50
#define UMBRAL 2
uint8_t index=0;
uint8_t angulo=0;

void Encoder_ISR(){
   //TMR0_StopTimer();
   
   //Reading PORTC to fix mismatch of IOCIF
   //Read INTCON register notes for more information
   int a = PORTB;
   a=PORTC;
   int tmr0 = TMR0_ReadTimer();
   TMR0_WriteTimer(0);
   //Calculo de velocidad instantanea y paso por el filtro
   float tics = tmr0 + prescaler*(2^NBITSTMR0);
   float promedio[5];
   if(tics>200){
      angulo++;
      angulo = angulo%100;
      rtU.Input= 1000000000/(nsPERCLOCK*tics*NRANURAS);
      if(rtU.Input<UMBRAL){
         //rtU.Input=tics;
         Ventana_step();
         index++;
         index=index%5;
         promedio[index]=rtY.Output;
         S=(promedio[0]+promedio[1]+promedio[2]+promedio[3]+promedio[4])/5;
      }
   }
   //Reseteo de prescaler
   prescaler=0;
   //TMR0_StartTimer();
}

void Encoder_Init(){
   Ventana_initialize();
   return;
}