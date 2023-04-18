int main()
//nu32startup()
//init the i2c pins
//init the init the chip, GP0 is input, GP7 is output. also build the button to input and LED to output from chip

while(1)
// blink the yellow LED on the pic
// blink GP7 to make sure it works (do this first to make sure the write function to the chip works)
    // turn on GP7
    // delay
    // turn off GP7
    // delay

    r = read_from_GPO
    if (r)
    turnOn_GP7
    else
    turnOff_GP7

    // might be good to write a function for each of these functions 

    void turnOn_GP7(){
        // send start bit 12c master start
        // send the address of the chip
        // 0b01000000 or 0b01000001 for read or write address
        // send the register name
        // write to 0x0A OLAT
        // send the value to turn on GP7
        // 0b10000000
        // send stop bit 12c master stop
    }

    // can make this a more generic function

    void generic_i2c_write(unsigned char address, unsigned char reg, unsigned char value){
        // send start bit 12c master start
        // send the address of the chip
        // 0b01000000 or 0b01000001 for read or write address
        // send the register name
        // write to 0x0A OLAT
        // send the value to turn on GP7
        // 0b10000000
        // send stop bit 12c master stop
    }

    //once we have that we have to read from gp0

    int read_Gp0(){
        // send start bit
        // send address with write bit
        // send register you want to read from
        // restart
        // send address with read bit
        unsigned char r = recv()
        // send the ack bit
        // send the stop bit
        return (r&0b00000001)
    }
    
// 


