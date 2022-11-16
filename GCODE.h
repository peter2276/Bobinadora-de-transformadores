/* 
 * File:   GCODE.h
 * Author: pedro
 *
 * Created on September 1, 2022, 11:46 AM
 */

#ifndef GCODE_H
#define	GCODE_H

#ifdef	__cplusplus
extern "C" {
#endif
    typedef struct Comando_T{
       char code;
       float number;
    }Comando_T;
    typedef enum{
        g00=0,
        g01=1,
        g95=95
    }feed_state_t;
    feed_state_t feed_state;
    void G_00(Comando_T* axis, int n);
    void G_01(Comando_T* axis, int n);
    void G_53(Comando_T* axis, int n);
    void G_95(Comando_T* axis, int n);
    void G_97(Comando_T* axis, int n);
    void M_3(Comando_T* axis, int n);
    void M_4(Comando_T* axis, int n);
    void M_5(Comando_T* axis, int n);
    void ParadaEmergencia(void);
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* GCODE_H */

