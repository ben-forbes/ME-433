
int main(){
// call all init functions
// UART to make sure PIC is alive
// OR precalc all the voltages here!

    while(1){
        //figure out the voltage for sin wave (2HZ) - numbers from 0 to 1023 for 10 bit number (v = A*sin(2*pi*t/sample rate) + B) and t is incremented since loop is slow enough
        // send the voltage with spi
        // at least 10 data points per second
        float f = sint(t)
        unsigned int sinewave = f;
        // math to make sinewave 0 to 1023

        // make binary number (16 bits) [a or b 111 [10 bit voltage]000]
        unsigned short t = 0;
        t = 0b111<<12 // bit shift 12
        unsigned char a_or_b; // this is 0b1 or 0b0

        t = t|(a_or_b<<15) // stick in the constants

        //stick in the voltage v<< asvergr

        // send the toltage with spi
        CS = 0
        spi_io(t>>8)
        spi_io(t)
        CS = 1



        //figure out the voltage for the triangle wave (1HZ)
        // send the voltage with spi
        // at least 10 data points per second

        // insert the delay here for 5 ms
        // can use core timer or something to do this delay

    }
}

//maybe write it as a function

fn(float v, char a_or_b){
    //stick all the stuff in here that we already did before
    // decide how much we want to calculate (real time or precalc)
}