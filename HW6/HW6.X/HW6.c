#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include <stdio.h>

void turnOn_GP7(void);
void turnOff_GP7(void);
void generic_i2c_write(unsigned char address, unsigned char reg, unsigned char value);
int read_GP0(void);

int main(void){
NU32DIP_Startup();
i2c_master_setup(); // init the i2c pins for the pic
generic_i2c_write(0b01000000,0x00,0b01111111); // make GP0 input and GP7 output
int r;
    while(1){
        NU32DIP_YELLOW = 0; // yellow LED on "heartbeat"
        _CP0_SET_COUNT(0);
        while( _CP0_GET_COUNT() < 12000000){}
        NU32DIP_YELLOW = 1; // yellow LED off
        
//        turnOn_GP7(); // test with the led THIS WORKS
//        _CP0_SET_COUNT(0);
//        while( _CP0_GET_COUNT() < 12000000){}
//        turnOff_GP7();
        
        r = read_GP0();
        if (r){
            turnOff_GP7();
        }

        else {
            turnOn_GP7();
        }
        
        _CP0_SET_COUNT(0);
        while( _CP0_GET_COUNT() < 1200){}
    }
}   


void turnOn_GP7(void){
        i2c_master_start(); // send start bit 12c master start
        i2c_master_send(0b01000000);// send the address of the chip
        // 0b01000000 or 0b01000001 for write or read address
        i2c_master_send(0x0A); // send the register name
        i2c_master_send(0b10000000); // send the value to turn on GP7
        i2c_master_stop();// send stop bit 12c master stop
}


void turnOff_GP7(void){
        i2c_master_start(); // send start bit 12c master start
        i2c_master_send(0b01000000);// send the address of the chip
        // 0b01000000 or 0b01000001 for read or write address
        i2c_master_send(0x0A); // send the register name
        i2c_master_send(0b00000000); // send the value to turn off GP7
        i2c_master_stop();// send stop bit 12c master stop
}

void generic_i2c_write(unsigned char address, unsigned char reg, unsigned char value){
        i2c_master_start(); // send start bit 12c master start
        i2c_master_send(address);// send the address of the chip
        // 0b01000000 or 0b01000001 for read or write address
        i2c_master_send(reg); // send the register name
        i2c_master_send(value); // send the value to turn on GP7
        i2c_master_stop();// send stop bit 12c master stop
}

int read_GP0(void){
        i2c_master_start();// send start bit
        i2c_master_send(0b01000000);// send address with write bit
        i2c_master_send(0x09); // send register GPIO
        //i2c_master_send(0b00000001); // send bit for GPIO
        i2c_master_restart();// restart
        i2c_master_send(0b01000001);// send address with read bit
        unsigned char r = i2c_master_recv();
        i2c_master_ack(1);// send the ack bit
        i2c_master_stop();// send the stop bit
        return (r&0b1);
}
    


