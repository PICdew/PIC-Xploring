/*
 * File:   main.c
 * Author: Thiago Mallon
 *
 * Created on 9 de Janeiro de 2015, 18:35
 */

#include <xc.h>
#include "../configs.h"

#define _XTAL_FREQ 64000000UL // (utilizando um cristal de 16MHz, porém, com o PLL ativado, o que gera o valor de 64MHz)

void delayGenerate(unsigned int miliseconds);

int main(void) {

    TRISA = 0; // set direction to be output
    TRISB = 0; // set direction to be output
    TRISC = 0; // set direction to be output
    TRISD = 0; // set direction to be output
    TRISE = 0; // set direction to be output

    PORTA = 0; // set direction to be output
    PORTB = 0; // set direction to be output
    PORTC = 0; // set direction to be output
    PORTD = 0; // set direction to be output
    PORTE = 0; // set direction to be output

    do {
        LATA = ~LATA; // Turn OFF LEDs on LATA
        LATB = ~LATB; // Turn OFF LEDs on LATB
        LATC = ~LATC; // Turn OFF LEDs on LATC
        LATD = ~LATD; // Turn OFF LEDs on LATD
        LATE = ~LATE; // Turn OFF LEDs on LATE
        delayGenerate(1000);
    } while (1); // Endless loop
    return 1;
}

void delayGenerate(unsigned int miliseconds) {
    while (miliseconds-- > 0) {
        __delay_ms(1); // 1 second delay
    }
}

