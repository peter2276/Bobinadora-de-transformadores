#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "motor.h"

void encenderRotor(){
   EN_Rotor = ENCENDIDO;
}

void apagarRotor(){
   EN_Rotor=APAGADO;
}

void DireccionRotor(int dir){
   Direccion_Rotor = dir;
}