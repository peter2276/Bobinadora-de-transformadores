/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC18F25K50
        Driver Version    :  2.00
*/

#include "mcc_generated_files/mcc.h"
#include "fila.h"
#include <string.h>
void MCC_USB_CDC_DemoTasks(void);
/*
                         Main application
 */

static uint8_t readBuffer[64];
static uint8_t writeBuffer[64];
uint8_t numBytesRead=0;
void MCC_USB_WRITE(char* str, int nBytes);
void MCC_USB_READ(void);
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    char* send;
    Fila_T CommandList;
    Fila_Init(&CommandList);
    while (1)
    {
       //MCC_USB_READ();
       Fila_Agregar(&CommandList,"a casa",strlen("a casa"));
       send=FilaPop(&CommandList);
       //if(send!=0) MCC_USB_WRITE(send,strlen(send));
       MCC_USB_WRITE(send,strlen(send));
       __delay_ms(500);
       //Fetch next command
       //execute 
    }
}


void MCC_USB_WRITE(char* str, int nBytes){
   putUSBUSART(str,nBytes);
   CDCTxService();
}
void MCC_USB_READ(void)
{
    if( USBGetDeviceState() < CONFIGURED_STATE )
    {
        return;
    }
    if( USBIsDeviceSuspended()== true )
    {
        return;
    }

    if( USBUSARTIsTxTrfReady() == true)
    {
        uint8_t i;
        uint8_t numBytesRead;

        numBytesRead = getsUSBUSART(readBuffer, sizeof(readBuffer));

        for(i=0; i<numBytesRead; i++)
        {
            writeBuffer[i] = readBuffer[i];
        }

        if(numBytesRead > 0)
        {
            //putUSBUSART(writeBuffer,numBytesRead);
        }
    }
    CDCTxService();
}

//USB interruption
//Read command 
//save in a FIFO queue
//out

//Next angle interrupt (external interrupt)
//read timer
//clear timer
//recalculate speed
//out



/**
 End of File
*/