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
    
    void G_00(Comando_T* axis, int n);
    void G_01(Comando_T* axis, int n);
    void G_53(Comando_T* axis, int n);
    void G_97(Comando_T* axis, int n);
    void M_3(Comando_T* axis, int n);
    void M_4(Comando_T* axis, int n);
    void M_5(Comando_T* axis, int n);
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* GCODE_H */

