/*
 * File:   mainservo.c
 * Author: Mallon
 *
 * Created on 31 de Julho de 2014, 20:20
 */

/*
#include <xc.h>

#pragma config FOSC = INTOSC_XT
#pragma config MCLRE = OFF
#pragma config WDT = OFF
#pragma config LVP = OFF

void main(void) {
    // Set Fosc = 8MHz, which gives Tcy = 0.5us
    OSCCON = 0b01110000;

    // Set up PWM (section 15 of the PIC18F4620 Data Sheet)
    CCP1CON = 0b00001100; // PWM on CCP1
    TRISC = 0b11111011; // CCP1 (pin 17) as output
    T2CON = 0b10010110; // Enable TMR2 with prescale=16, postscale=10
    PR2 = 255; // period = (PR2+1) * prescale * postscale * Tcy = 20.48ms
    CCPR1L = 18; // pulse width = CCPR1L * prescale * postscale * Tcy = 1.52ms

    // Every time you press the button, the servo angle
    // will increase by 15 degrees until you get to 180
    // at which point it will reset to 0.
    while (1) {
        // Wait for button press
        while (PORTDbits.RD0 == 0);
        Delay10KTCYx(2); // 10ms debounce delay

        // Change servo angle
        if (CCPR1L < 24) CCPR1L += 1; // Increment angle
        else CCPR1L = 12; // Set angle back to zero

        // Wait for button to be released
        while (PORTDbits.RD0 == 1);
        Delay10KTCYx(2); // 10ms debounce delay
    }
}
  */