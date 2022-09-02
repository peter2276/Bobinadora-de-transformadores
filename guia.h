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

#define STEPS_PER_MM 33
#define DIRECTION_PIN PORTBbits.RB7
#define STEP_PIN LATBbits.LATB6
#define EN_PIN LATBbits.LATB0
#define uSTEP_PIN1 LATBbits.LATB1
#define uSTEP_PIN2 LATBbits.LATB2
#define uSTEP_PIN3 LATBbits.LATB3
#define uSTEP 1
#define DIRECCION_POSITIVA 1
#define DIRECCION_NEGATIVA 0
    void MY_TMR3_ISR(void);
    void mover(int distancia, int direccion);
    void mover_2(int distancia);
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* GUIA_H */

