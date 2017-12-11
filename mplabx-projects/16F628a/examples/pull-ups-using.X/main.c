/* 
 * File:   main.c
 * Author: Thiago Mallon
 *
 * Created on 2 de Janeiro de 2015, 12:20
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

#define _XTAL_FREQ 4000000UL // define frequência do oscilador da CPU
#define LED (1 << 1) // define pino de LED
#define BUTTON (1 << 0) // define pino utilizado como botão - implementado como pull-up

/* Os pinos com pull-ups, no PIC16F628A, são os pinos do PORTB. Todos os pinos do PORTB possuem função pullup. */

void pullupConfig(void) {
    OPTION_REGbits.nRBPU = 0; // habilita pull-ups do PORTB
    TRISB |= BUTTON; // atribui nível lógico 1 ao pino RB1, configurando o pino como entrada (necessário para que possa utilizar o pullup)
    PORTB |= BUTTON; // coloca o pino em nível lógico 1, quando utilizado como pull-up, está é a abordagem correta
}

void ledConfig(void) {
    TRISB &= ~LED; // coloca pino como saída
    PORTB |= LED; // atribui nível lógico 0 ao pino (led desligado)
}

int main(void) {
    pullupConfig();
    ledConfig();
    while (1) {
        if (!(PORTB & (BUTTON))) { // verifica se nível lógico do pino utilizado como botão, está em 0, ou seja, se fechou conexão do circuito
            __delay_ms(25);
            PORTB ^= LED; // inverte nível lógico do pino, fazendo toggle no led
        }
        __delay_ms(150);
    }
    return 1;
}

