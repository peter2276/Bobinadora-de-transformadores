#include <xc.h>
#include "mcc_generated_files/mcc.h"

#define nsPERCLOCK 2667
#define NBITSTMR0 16
#define NRANURAS 100
int prescaler; //Variable para prescaler del TMR0 por software
float S; //Velocidad luego del filtro

void Timing_TMR0_ISR(){
   
   TMR0_WriteTimer(0);
   prescaler++;
   if(prescaler>=10){
      S=20;
      prescaler=0;
   }
}

#define FILTER_LENGTH 50
float filter[FILTER_LENGTH]={0,0,0,0,0,0};
uint8_t index=0;

void Encoder_ISR(){
   //TMR0_StopTimer();
   
   //Reading PORTC to fix mismatch of IOCIF
   //Read INTCON register notes for more information
   int a = PORTB;
   a=PORTC;
   //if(PORTCbits.RC2==0) return;
    
   int tmr0 = TMR0_ReadTimer();
   TMR0_WriteTimer(0);
   float tics = tmr0 + prescaler*(2^NBITSTMR0);
   if(tics>200){
      index++;
      index=index%FILTER_LENGTH;
      filter[index] = 1000000000/(nsPERCLOCK*tics*NRANURAS);
      S=0;
      for(int i=0;i<FILTER_LENGTH;i++){
         S=S+filter[i];
      }
      S=S/FILTER_LENGTH;
      //S=30;
   }
   prescaler=0;
   //TMR0_StartTimer();
}
