//
// PIC18F4620 1kHz PWM example program
// Written by Ted Burke (http://batchloaf.com)
// Last updated 4-4-2013
//
// To compile with XC8:
//     xc8 --chip=18F4620 main.c
//
/*

#include <xc.h>

#pragma config FOSC = HS
#pragma config MCLRE=OFF,
#pragma config WDT=OFF
#pragma config LVP=OFF
#pragma config PBADEN = OFF

#define _XTAL_FREQ 8000000

int main(void) {
    ADCON1 = 0X0F;
    // Set up PWM (see section 15.4 of the PIC18F4620 datasheet)    
    CCP1CON = 0b00001100; // Enable PWM on CCP1
    TRISC = 0b11111001; // Make pin 17 (RC1/CCP2) an output
    //T2CON = 0b00000100; // Enable TMR2 with prescaler = 1
    T2CON = 0b00000111; // Enable TMR2 with prescaler = 16
    //PR2 = 249; // PWM period = (PR2+1) * prescaler * Tcy = 1ms
    PR2 = 124; // PWM period = (PR2+1) * prescaler * Tcy = 1ms
    CCPR1L = 250; // pulse width = CCPR1L * prescaler * Tcy = 100us

    while (1) {
        /*
        // 50% duty cycle for 500ms

        CCPR1L = 125;
        _delay(125);

        // 10% duty cycle for 500ms
        CCPR1L = 250;
        _delay(125);

        // 0% duty cycle for 500ms
        CCPR1L = 100;
        _delay(125);
    }
}
         */
