/* 
 * File:   hw8.c
 * Author: benjaminforbes
 *
 * Created on April 25, 2023, 11:16 AM
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include "mpu6050.h"
#include "ssd1306.h"
#include "font.h"
/*
 * 
 */

void blink(int, int); // blink the LEDs function
void drawchar(unsigned char letter, unsigned char x, unsigned char y);
void drawstring(unsigned char *m, unsigned char x, unsigned char y);

int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    init_mpu6050(); // initialize 12c
    ssd1306_setup(); // initialize OLED
    
    unsigned char m[100];
//    sprintf(m,"hey jeffrey"); // test to see if I can print to the screen
//    ssd1306_update();
   
    unsigned char d[14]; // char array for the raw data
	
    float ax, ay, az, gx, gy, gz, t; // floats to store the data
    unsigned char who; 
    who = whoami(); // read whoami
    
    char n[100];
    char m_in[100];
    sprintf(n,"%X\r\n", who); // print whoami
    NU32DIP_WriteUART1(n);
    if (who != 0x68){ // if whoami is not 0x68, stuck in loop with LEDs on
        blink(1,5);
    }
    
    while (1) {
        _CP0_SET_COUNT(0);
        //blink(1,5); // set heartbeat
        burst_read_mpu6050(d);         // read IMU
        ax = conv_xXL(d); 		// convert data
        sprintf(m,"Velocity in Z = %f",ax);         // print out the data
        drawstring(m,1,1);  // send the data to the LCD
        
        int x;
        x = _CP0_GET_COUNT(); // use core timer to get the "frame rate"
        sprintf(m,"Frame rate = %d",x);
        drawstring(m,1,2);
        ssd1306_update();
    } 
}

// blink the LEDs
void blink(int iterations, int time_ms) {
    int i;
    unsigned int t;
    for (i = 0; i < iterations; i++) {
        NU32DIP_GREEN = 0; // on
        NU32DIP_YELLOW = 1; // off
        t = _CP0_GET_COUNT(); // should really check for overflow here
        // the core timer ticks at half the SYSCLK, so 24000000 times per second
        // so each millisecond is 24000 ticks
        // wait half in each delay
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }

        NU32DIP_GREEN = 1; // off
        NU32DIP_YELLOW = 0; // on
        t = _CP0_GET_COUNT(); // should really check for overflow here
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }
    }
}

void drawchar(unsigned char letter, unsigned char x, unsigned char y){
    int i;
    int j;
    for (j = 0; j<5; j++) {
        char col = ASCII[letter - 0x20][j];
        for (i = 0; i<8; i++) {
            ssd1306_drawPixel(x+j,y+i, (col>>i)&0b1);
        }
    }
}

void drawstring(unsigned char *m, unsigned char x, unsigned char y){
    int k = 0;
    while (m[k]!=0){
        drawchar(m[k],x*5*k,y*8);
        k++;
    }
}
