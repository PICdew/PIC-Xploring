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
#pragma config CPD = OFF // desabilita proteção de código para EEPROM
#pragma config CP = OFF // desabilita proteção de código para FLASH

#define BUTTON PORTBbits.RB5 // define pino que será utilizado para gerar a interrupção
#define LED PORTBbits.RB0 // define pino que será utilizado para o LED

/** A interrupção por mudança de nível lógico no pino, pode ocorrer nos pinos PORTB<7:4> */

void portChangeConfig(void) {
    TRISB5 = 1; // configura pino RB5 como entrada
    BUTTON = 1; // atribui nível lógico 1 ao pino RB5
    OPTION_REGbits.nRBPU = 0; // habilita-se pull-ups do PORTB
    INTCONbits.RBIE = 1; // habilita interrupção por mudança de nível lógico nos pinos
    INTCONbits.RBIF = 0; // limpa flag de interrupção por mudança de nível lógico nos pinos
}

void interruptConfig(void) {
    INTCONbits.GIE = 1; // habilita interrupções globais
}

int main(void) {
    TRISB0 = 0; // configura pino RB0 como saída
    LED = 0; // atribui nível lógico 0 ao pino do led
    portChangeConfig(); // chama função que habilita e configura interrupção por mudança de nível lógico no pino
    interruptConfig(); // chama função que habilita interrupções globais
    while (1);
    return 1;
}

void interrupt ISR(void) {
    if (INTCONbits.RBIF) { // verificamos se flag de interrupção por mudança de nível lógico no pino, está setada        
        LED = ~LED; // atribuímos nível lógico 1 ao pino, acendemos o led
        INTCONbits.RBIF = 0; // limpamos flag de interrupção por mudança de nível lógico no pino
    }
}