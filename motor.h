/* 
 * File:   motor.h
 * Author: pedro
 *
 * Created on November 3, 2022, 12:25 PM
 */

#ifndef MOTOR_H
#define	MOTOR_H

#ifdef	__cplusplus
extern "C" {
#endif
 
#define EN_Rotor LATCbits.LATC6
#define Direccion_Rotor LATAbits.LATA7
#define ENCENDIDO 1
#define APAGADO 0
#define CCW 1
#define CW 0
    
void apagarRotor();
void encenderRotor();
void DireccionRotor(int dir);


#ifdef	__cplusplus
}
#endif

#endif	/* MOTOR_H */

