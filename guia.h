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
#define SLEEP_PIN LATBbits.LATB5
#define RESET_PIN LATBbits.LATB4
#define uSTEP 1
#define DIRECCION_POSITIVA 1
#define DIRECCION_NEGATIVA 0
#define DISABLE 1
#define ENABLE 0
    void G00_TMR2_ISR(void);
    void G01_TMR2_ISR(void);
    void mover(float distancia, int direccion);
    void mover_2(float distancia);
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* GUIA_H */

