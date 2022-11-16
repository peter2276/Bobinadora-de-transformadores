/* 
 * File:   guia.h
 * Author: pedro
 *
 * Created on September 1, 2022, 10:20 AM
 */

#ifndef GUIA_H
#define	GUIA_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <xc.h>
    
#define STEPS_PER_MM 31
#define feedtoTMR2 46665*60/(2*STEPS_PER_MM)
#define nsPERTMR2 1333
#define postscalerTMR2 16
#define DIRECTION_PIN PORTBbits.RB7
#define STEP_PIN LATBbits.LATB6
#define EN_PIN LATBbits.LATB0
#define uSTEP_PIN1 LATBbits.LATB1
#define uSTEP_PIN2 LATBbits.LATB2
#define uSTEP_PIN3 LATBbits.LATB3
#define SLEEP_PIN LATBbits.LATB5
#define RESET_PIN LATBbits.LATB4
#define uSTEP 1
#define DIRECCION_POSITIVA 1
#define DIRECCION_NEGATIVA 0
#define DISABLE 1
#define ENABLE 0
    void G01_TMR2_ISR(void);
    void mover_2(float distancia);
    void setMicroStep(uint8_t ustep);
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* GUIA_H */

