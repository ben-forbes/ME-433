/* 
 * File:   HW14.c
 * Author: benjaminforbes
 *
 * Created on May 23, 2023, 11:29 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "nu32dip.h"

void main() {
    NU32DIP_Startup();
// for the servo motor
    TRISBbits.TRISB0 = 0;    // set B0 to a digital output for the control of DC motors
    LATBbits.LATB0 = 0;      // set B0 to output low for the control of DC motors
    
    RPB15R = 0b0101;         // Set B15 to OC1
    T2CONbits.TCKPS = 4;     // Timer2 prescaler N=16 (1:4)
    PR2 = 59999;              // period = (PR2+1) * N * (1/48000000) = 50 Hz
    TMR2 = 0;                // initial TMR2 count is 0
    OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
    OC1CONbits.OCTSEL = 0;   // Use timer2
    OC1RS = 6000;             // duty cycle = OC1RS/(PR2+1) = 1.0ms
    OC1R = 6000;              // initialize before turning OC1 on; afterward it is read-only
    T2CONbits.ON = 1;        // turn on Timer2
    OC1CONbits.ON = 1;       // turn on OC1
    
    LATBbits.LATB0 = 1;       // reset the B0 pin for the control of DC motors
    while (1){
        OC1RS = 2000;
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT() < 50000000) {}   
        OC1RS = 8000;
        _CP0_SET_COUNT(0);
        while (_CP0_GET_COUNT() < 50000000) {}   
        }
    }


