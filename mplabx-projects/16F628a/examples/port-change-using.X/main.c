/* 
 * File:   main.c
 * Author: Thiago Mallon
 *
 * Created on 4 de Janeiro de 2015, 17:11
 */

#include <xc.h>

#pragma config FOSC = INTOSCIO // oscilador interno de 4Mhz; pinos RA6 e RA7 liberados para I/O
#pragma config MCLRE = ON // habilita pino de reset; pino RA5 funcionando como MASTER CLEAR RESET
#pragma config LVP = OFF // desabilita LOW VOLTAGE PROGRAMMING
#pragma config WDTE = OFF // desabilita WATCH DOG TIMER
#pragma config BOREN = ON // habilita BROWN OUT RESET
#pragma config PWRTE = ON // habilita POWER UP TIMER
#pragma config CPD = OFF // desabilita prote��o de c�digo para EEPROM
#pragma config CP = OFF // desabilita prote��o de c�digo para FLASH

#define BUTTON PORTBbits.RB5 // define pino que ser� utilizado para gerar a interrup��o
#define LED PORTBbits.RB0 // define pino que ser� utilizado para o LED

/** A interrup��o por mudan�a de n�vel l�gico no pino, pode ocorrer nos pinos PORTB<7:4> */

void portChangeConfig(void) {
    TRISB5 = 1; // configura pino RB5 como entrada
    BUTTON = 1; // atribui n�vel l�gico 1 ao pino RB5
    OPTION_REGbits.nRBPU = 0; // habilita-se pull-ups do PORTB
    INTCONbits.RBIE = 1; // habilita interrup��o por mudan�a de n�vel l�gico nos pinos
    INTCONbits.RBIF = 0; // limpa flag de interrup��o por mudan�a de n�vel l�gico nos pinos
}

void interruptConfig(void) {
    INTCONbits.GIE = 1; // habilita interrup��es globais
}

int main(void) {
    TRISB0 = 0; // configura pino RB0 como sa�da
    LED = 0; // atribui n�vel l�gico 0 ao pino do led
    portChangeConfig(); // chama fun��o que habilita e configura interrup��o por mudan�a de n�vel l�gico no pino
    interruptConfig(); // chama fun��o que habilita interrup��es globais
    while (1);
    return 1;
}

void interrupt ISR(void) {
    if (INTCONbits.RBIF) { // verificamos se flag de interrup��o por mudan�a de n�vel l�gico no pino, est� setada        
        LED = ~LED; // atribu�mos n�vel l�gico 1 ao pino, acendemos o led
        INTCONbits.RBIF = 0; // limpamos flag de interrup��o por mudan�a de n�vel l�gico no pino
    }
}