/**
  CCP2 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    ccp2.c

  @Summary
    This is the generated driver implementation file for the CCP2 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for CCP2.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F25K50
        Driver Version    :  2.0.3
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
         MPLAB 	          :  MPLAB X 6.00
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "ccp2.h"


/**
  Section: Capture Module APIs:
*/


void CCP2_Initialize(void)
{
    // Set the CCP2 to the options selected in the User Interface
	
	// CCP2M Falling edge; DC2B 0; 
	CCP2CON = 0x04;    
	
	// CCPR2L 0; 
	CCPR2L = 0x00;    
	
	// CCPR2H 0; 
	CCPR2H = 0x00;    
    

	// Selecting Timer 1
	CCPTMRSbits.C2TSEL = 0x0;
    
}

bool CCP2_IsCapturedDataReady(void)
{
    // Check if data is ready to read from capture module by reading "CCPIF" flag.
    bool status = PIR2bits.CCP2IF;
    if(status)
        PIR2bits.CCP2IF = 0;
    return (status);
}

uint16_t CCP2_CaptureRead(void)
{
    CCP2_PERIOD_REG_T module;

    // Copy captured value.
    module.ccpr2l = CCPR2L;
    module.ccpr2h = CCPR2H;
    
    // Return 16bit captured value
    return module.ccpr2_16Bit;
}
/**
 End of File
*/