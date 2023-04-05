#include "nu32dip.h" // constants, functions for startup and UART
#include <math.h>

void blink(int, int); // blink the LEDs function

int main(void) {
  char message[100];
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  NU32DIP_WriteUART1("Hello\r\n");
  while (1) {
    int i = 0;
    if (NU32DIP_USER == 0){
        for (i = 0;i<100;i++){
            sprintf(message,"%f\r\n",sin((2*M_PI*i)/100));
            NU32DIP_WriteUART1(message); // send message back
            _CP0_SET_COUNT(0);
            while(_CP0_GET_COUNT()<24000){}
        }
    }
  }
}

		
