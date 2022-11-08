#include <xc.h>
#include "mcc_generated_files/mcc.h"

uint16_t current=0;

void medir_corriente(){
   
   ADC_StartConversion();
   while(ADC_IsConversionDone()==0);
   current = ADC_GetConversionResult();
   return;
}
