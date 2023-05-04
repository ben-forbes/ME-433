/* 
 * File:   hw_10.c
 * Author: benjaminforbes
 *
 * Created on May 3, 2023, 6:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "ws2812b.h"
#include "nu32dip.h"

void main() {
    NU32DIP_Startup();
    ws2812b_setup();
    wsColor c[8];
    while (1){
// create the rainbow      
        int i = 0;
        for (i = 0; i < 3600; i++){
            float x = i*0.1; // the increment
            float x0 = x+0.0;
            if (x0 > 360){
                x0 = 0;
            }
            float x1 = x+5.0;
            if (x1 > 360){
                x1 = 0;
            }
            float x2 = x+10.0;
            if (x2 > 360){
                x2 = 0;
            }
            float x3 = x+15.0;
            if (x3 > 360){
                x3 = 0;
            }
            float x4 = x+20.0;
            if (x4 > 360){
                x4 = 0;
            }
            float x5 = x+25.0;
            if (x5 > 360){
                x5 = 0;
            }
            float x6 = x+30.0;
            if (x6 > 360){
                x6 = 0;
            }
            float x7 = x+35.0;
            if (x7 > 360){
                x7 = 0;
            }

            c[0] = HSBtoRGB(x0, 1.0, 0.25);
            c[1] = HSBtoRGB(x1, 1.0, 0.25);
            c[2] = HSBtoRGB(x2, 1.0, 0.25);
            c[3] = HSBtoRGB(x3, 1.0, 0.25);
            c[4] = HSBtoRGB(x4, 1.0, 0.25);
            c[5] = HSBtoRGB(x5, 1.0, 0.25);
            c[6] = HSBtoRGB(x6, 1.0, 0.25);
            c[7] = HSBtoRGB(x7, 1.0, 0.25);
            ws2812b_setColor(c,8);
        }
    }
}

