#include "nu32dip.h" // constants, functions for startup and UART
#include <math.h>
#include "spi.h"
#include <xc.h>      // processor SFR definitions
#include <stdio.h>

signed short make_voltageA(unsigned short v);
signed short make_voltageB(unsigned short v);

int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    initSPI();
    int t = 1;
    char up = 1;
    int counter = 0;
    float v2 = 0;
    
    while(1){
        // math to make sinewave 0 to 1023 with 2Hz 
        float v1 = 510*sin(2*M_PI*t/100)+510;
        // make binary number (16 bits) [a or b 1 1 1 [10 bit voltage] 0 0]
        if (up == 1) {
            v2 = v2 + 1023/100;
            counter = counter + 1;
            if (counter == 100){
                up = up-1;
                counter = 0;
            }
        }
        
        if (up == 0) {
            v2 = v2 - 1023/100;
            counter = counter + 1;
            if (counter == 100){
                up = up+1;
                counter = 0;
            }
        }
        
        unsigned short v11 = v1;
        unsigned short v22 = v2;
        
        signed short va = make_voltageA(v11);
        signed short vb = make_voltageB(v22);
        
        unsigned short c1a = va>>8, c2a = va, c1b = vb>>8, c2b = vb;
        // send the voltage with spi
        LATBbits.LATB6 = 0; //CS = 0;
        spi_io(c1a);
        spi_io(c2a);
        LATBbits.LATB6 = 1; //CS = 1;
       
       
        // VoutB
        LATBbits.LATB6 = 0;
        spi_io(c1b);
        spi_io(c2b);
        LATBbits.LATB6 = 1;
        
        
        _CP0_SET_COUNT(0);
        while( _CP0_GET_COUNT() < 120000){}
             
        t = t + 1 ;
    }
}

signed short make_voltageA(unsigned short v) {
    signed short a = 0;
    a = 0b0111<<12;
    a = a | (0b0 << 15);
    a = a | (v << 2);
    return a;
}

signed short make_voltageB(unsigned short v) {
    signed short b = 0;
    b = 0b0111<<12;
    b = b | (0b1 << 15);
    b = b | (v << 2);
    return b;
}


