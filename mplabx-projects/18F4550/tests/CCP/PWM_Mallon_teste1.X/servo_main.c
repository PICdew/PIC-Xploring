/*
 * File:   servo_main.c
 * Author: Mallon
 *
 * Created on 31 de Julho de 2014, 20:12
 */

/*
#include <xc.h>

#pragma config FOSC=INTOSCIO_EC
#pragma config MCLRE=OFF
#pragma config WDT=OFF
#pragma config LVP=OFF
#pragma config PBADEN = OFF

int main(void) {
    // Set clock frequency to 500kHz, therefore Tcy = 8us
    OSCCONbits.IRCF = 0b01100000;

    // Set up PWM
    CCP1CON = 0b00001100; // Enable PWM on CCP1
    TRISC = 0b11011111; // Make CCP1 an output
    T2CON = 0b00000110; // Enable TMR2 with prescaler = 16
    PR2 = 155; // PWM period = (PR2+1) * prescaler * Tcy = 19.968ms
    CCPR1L = 8; // pulse width = CCPR1L * prescaler * Tcy = 1.024ms

    while (1) {
        if (PORTCbits.RC4) CCPR1L = 12; // 1.536ms pulses, i.e. 90 degrees
        else CCPR1L = 8; // 1.024ms pulses, i.e. 0 degrees
    }

    return 0;
}
*/