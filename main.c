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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC18F45K40
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"

void play(char message);
void touchISR(void);

char scanButtons(void);


/*
                         Main application
 */
void main(void) {
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    /*
     * Interrupt on Change
     * Must have a handler set for each pin.
     * page 290 of datasheet
     */
     
    IOCCF1_SetInterruptHandler(touchISR);

    
    
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

 

    PORTAbits.RA0 = 0; // sensitivity
    PORTAbits.RA1 = 0;
    char    message;
    while (1) {

        if (BUSY_GetValue() == 0) { // not currently playing
            message = scanButtons();
            if (message != 0x99) {
                play(message);
                message = 0x99; // don't repeat message
            }
        }

        // after time set lastbutton=0

    }
}

/*Interrupt for buttons
 * 
 * Will wake from sleep and action appropriate button
 * Idealy, the frame button will be detected first
 */

void touchISR(){
    
    // clear flag
    IOCIF=0;
    // which button
    //check for each port IOCxP or IOCxN  for high or low
       if (IOCCNbits.IOCCN0==1){
 
    }
       
   

    // action event
}

}

/*
 * Look for a button pressed in the first group on PORTC
 * Return the button number
 */
 char scanButtons() {
    static uint16_t lastButton;
    uint16_t currentButton;
    char messageID = 0x99;
    currentButton = PORTD; // Buttons on PORTD = 01111111 when all off
    currentButton =  currentButton<< 8;
    currentButton = currentButton + PORTC;// Buttons on PORTC = 01111111 when all off
    // Reads as PORTD PORTC

   
    if (currentButton != lastButton && currentButton != 0b01111111) { // stop repeat triggers
        lastButton = currentButton;
        switch(currentButton){
            case 0b0111111101111110:
                messageID = 0x1;
                break;
            case 0b0111111101111101:
                messageID = 0x2;
                break;
            case 0b0111111101111011:
                messageID = 0x3;
                break;
            case 0b0111111101110111:
                messageID = 0x4;
                break;
            case 0b0111111101101111:
                messageID = 0x5;
                break;
            case 0b0111111101011111:
                messageID = 0x6;
                break;
            case 0b0111111100111111:
                messageID = 0x7;
                break;
             case 0b0111111001111111:
                messageID = 0x8;
                break;
            case 0b0111110101111111:
                messageID = 0x9;
                break;
            case 0b0111101101111111:
                messageID = 0x0A;
                break;
            case 0b0111011101111111:
                messageID = 0x0B;
                break;
            case 0b0110111101111111:
                messageID = 0x0C;
                break;
            case 0b0101111101111111:
                messageID = 0x0D;
                break;
            case 0b0011111101111111:
                messageID = 0x0E;
                break;    
            default:
                messageID = 0x99;
        }
     
 
    }
   
    return messageID;
}
 

/*
 * Play the message by sending serial to DFR0534
 */
void play(char message) {
    unsigned char play[6] = {0xAA, 0x07, 0x02, 0x00, message, message + 0xB3};

    for (int a = 0; a < 6; a++) {
        EUSART1_Write(play[a]);
    }
}

/**
 End of File
 */