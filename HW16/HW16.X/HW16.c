/* 
 * File:   HW16.c
 * Author: benjaminforbes
 *
 * Created on May 23, 2023, 11:29 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "nu32dip.h"
#include "uart2.h" // include the library

void main() {
    NU32DIP_Startup();
    UART2_Startup();
// for one DC motor
    TRISBbits.TRISB14 = 0;    // set B14 to a digital output for the control of DC motors
    LATBbits.LATB14 = 0;      // set B14 to output low for the control of DC motors
    
    TRISBbits.TRISB12 = 0;    // set B12 to a digital output for the control of DC motors
    LATBbits.LATB12 = 0;      // set B12 to output low for the control of DC motors
    
    RPB15R = 0b0101;         // Set B15 to OC1
    T2CONbits.TCKPS = 1;     // Timer2 prescaler N=1 (1:4)
    PR2 = 2399;              // period = (PR2+1) * N * (1/48000000) = 20 KHz
    TMR2 = 0;                // initial TMR2 count is 0
    OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC1CONbits.OCTSEL = 0;   // Use timer2
    OC1RS = 2000;            // duty cycle = OC1RS/(PR2+1) = 1.0ms
    OC1R = 2000;             // initialize before turning OC1 on; afterward it is read-only
    
    RPB13R = 0b0101;         // Set B13 to OC4
    OC4CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC4CONbits.OCTSEL = 0;   // Use timer2
    OC4RS = 2000;            // duty cycle = OC4RS/(PR3+1) = 1.0ms
    OC4R = 2000;             // initialize before turning OC1 on; afterward it is read-only
    
    T2CONbits.ON = 1;        // turn on Timer2
    OC1CONbits.ON = 1;       // turn on OC1
    OC4CONbits.ON = 1;       // turn on OC4
    
    LATBbits.LATB14 = 1;   // forward direction
    LATBbits.LATB12 = 0;   // forward direction
    
//    
        while (1){
            int com = 0;
            //uart2_flag() is 1 when uart2 has rx a message and sprintf'd it into a value
            if(get_uart2_flag()){
                set_uart2_flag(0); // set the flag to 0 to be ready for the next message
                char message2[100];
                com = get_uart2_value();
                sprintf(message2,"%d\n",com);
                NU32DIP_WriteUART1(message2);
                
            if (com > 35) {
                OC1RS = 1000; //OC1 is the left motor
                OC4RS = 750; //OC4 is the right motor
            }
            else if (com < 25) {
                OC1RS = 750; 
                OC4RS = 1000;
            }
            else {
                OC1RS = 1000;
                OC4RS = 1000;
            }
         }

            
            // code to run in case the robot is not reading camera it goes in a square
//            OC1RS = 2000;
//            OC4RS = 2000;
//            _CP0_SET_COUNT(0);
//            while (_CP0_GET_COUNT() < 50000000) {}   
//            OC1RS = 0;
//            OC4RS = 2000;
//            _CP0_SET_COUNT(0);
//            while (_CP0_GET_COUNT() < 20000000) {} 
//             
        }
    }


