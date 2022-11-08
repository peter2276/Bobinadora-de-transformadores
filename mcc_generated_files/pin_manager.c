/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F25K50
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB             :  MPLAB X 6.00

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "pin_manager.h"




void (*IOCC2_InterruptHandler)(void);


void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATA = 0x00;
    LATB = 0x3E;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISA = 0x7F;
    TRISB = 0x00;
    TRISC = 0x87;

    /**
    ANSELx registers
    */
    ANSELC = 0x80;
    ANSELB = 0x00;
    ANSELA = 0x2F;

    /**
    WPUx registers
    */
    WPUB = 0x00;
    INTCON2bits.nRBPU = 1;



    /**
    IOCx registers 
    */
    //interrupt on change for group IOCC - flag
    IOCCbits.IOCC2 = 1;



    // register default IOC callback functions at runtime; use these methods to register a custom function
    IOCC2_SetInterruptHandler(IOCC2_DefaultInterruptHandler);
   
    // Enable IOCI interrupt 
    INTCONbits.IOCIE = 1; 
    
}
  
void PIN_MANAGER_IOC(void)
{   
	// interrupt on change for pin IOCC2
    if(IOCCbits.IOCC2 == 1)
    {
        IOCC2_ISR();  
    }	
	// Clear global Interrupt-On-Change flag
    INTCONbits.IOCIF = 0;
}

/**
   IOCC2 Interrupt Service Routine
*/
void IOCC2_ISR(void) {

    // Add custom IOCC2 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCC2_InterruptHandler)
    {
        IOCC2_InterruptHandler();
    }
}

/**
  Allows selecting an interrupt handler for IOCC2 at application runtime
*/
void IOCC2_SetInterruptHandler(void (* InterruptHandler)(void)){
    IOCC2_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCC2
*/
void IOCC2_DefaultInterruptHandler(void){
    // add your IOCC2 interrupt custom code
    // or set custom function using IOCC2_SetInterruptHandler()
}

/**
 End of File
*/