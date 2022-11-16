#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "Ventana.h"
#include "encoder.h"
#include "guia.h"
#include "GCODE.h"

#define nsPERCLOCK 2667
#define msPERCLOCK 0.002667
#define NBITSTMR0 16
#define NRANURAS 72
#define encoder PORTCbits.RC2
uint8_t prescaler; //Variable para prescaler del TMR0 por software
//extern float S;
double S; //Velocidad luego del filtro
double inverse_S;
void Timing_TMR0_ISR(){
   
   TMR0_WriteTimer(0);
   prescaler++;
   if(prescaler>=10){ //Si pasa mucho tiempo
      //rtU.Input= 0;
      //Ventana_step();
      S=0;
      //inverse_S=1000000;
      prescaler=0;
   }
}

#define FILTER_LENGTH 50
#define UMBRAL 2
uint8_t index=0;
uint8_t angulo=0;
/*
void Encoder_ISR(){
   //TMR0_StopTimer();
   
   //Reading PORTC to fix mismatch of IOCIF
   //Read INTCON register notes for more information
   int a = PORTB;
   a=PORTC;
   int tmr0 = TMR0_ReadTimer();
   TMR0_WriteTimer(0);
   //Calculo de velocidad instantanea y paso por el filtro
   int tics = tmr0 + prescaler*(2^NBITSTMR0);
   float promedio[5];
   if(tics>200){
      //angulo++;
      //angulo = angulo%100;
      //rtU.Input= 1000000000*60/(nsPERCLOCK*tics*NRANURAS);
      rtU.Input=(60*1000/nsPERCLOCK)*(1000/tics)*(1000/NRANURAS);
      if(rtU.Input<UMBRAL){
         //rtU.Input=tics;
         Ventana_step();
         index++;
         index=index%5;
         promedio[index]=rtY.Output;
         S=(promedio[0]+promedio[1]+promedio[2]+promedio[3]+promedio[4])/5;
         S=rtU.Input;
      }
   }
   //Reseteo de prescaler
   prescaler=0;
   //TMR0_StartTimer();
}*/

#define TICS_TO_REVSEC 1000000000*60/(nsPERCLOCK*NRANURAS)
#define TICS_TO_SECREV (double)(nsPERCLOCK*NRANURAS)/(1000000000*60)*65536
bool S_CHANGE;
extern feed_state_t feed_state;
extern float feed;
extern double inverse_time_feed;
extern uint8_t ustep;
void Encoder_ISR(){
   //TMR0_StopTimer();
   
   //Reading PORTC to fix mismatch of IOCIF
   //Read INTCON register notes for more information
   int a = PORTB;
   a=PORTC;
   int tmr0 = TMR0_ReadTimer();
   TMR0_WriteTimer(0);
   //Calculo de velocidad instantanea y paso por el filtro
   double tics = tmr0 + prescaler*(2^NBITSTMR0);
   double y[3];
   double salida;
   
   if(tics>400){
      y[0]=(double)0.02008*tics+1.56101*y[1]-(double)0.64135*y[2];
      salida = y[0]+2*y[1]+y[2];
      y[2]=y[1];
      y[1]=y[0];
      S=(1000000*60/salida)*((double)1000/((double)nsPERCLOCK*NRANURAS));
      inverse_S=1/S;
      S_CHANGE=1;
      Actualizar_angulo();
   }
   //Reseteo de prescaler
   prescaler=0;
}

bool flag_angulo=0;
void Actualizar_angulo(){
   if(encoder==1){
      if(flag_angulo==0){
         flag_angulo=1;
         angulo++;
         angulo = angulo%NRANURAS;
      }
   }else{
      if(flag_angulo==1){
         flag_angulo=0;
         angulo++;
         angulo = angulo%NRANURAS;
      }
   }
}