/* 
 * File:   CommandHandler.h
 * Author: pedro
 *
 * Created on November 10, 2022, 2:40 PM
 */

#ifndef COMMANDHANDLER_H
#define	COMMANDHANDLER_H

#ifdef	__cplusplus
extern "C" {
#endif


void USBCommandFetch();
void executeCommand();
void MCC_USB_WRITE(char* str, int nBytes);
void MCC_USB_READ(void);

#ifdef	__cplusplus
}
#endif

#endif	/* COMMANDHANDLER_H */

