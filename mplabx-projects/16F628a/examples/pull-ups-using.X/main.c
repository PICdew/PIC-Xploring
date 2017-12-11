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
#pragma config CPD = OFF // desabilita prote��o de c�digo para EEPROM
#pragma config CP = OFF // desabilita prote��o de c�digo para FLASH

#define _XTAL_FREQ 4000000UL // define frequ�ncia do oscilador da CPU
#define LED (1 << 1) // define pino de LED
#define BUTTON (1 << 0) // define pino utilizado como bot�o - implementado como pull-up

/* Os pinos com pull-ups, no PIC16F628A, s�o os pinos do PORTB. Todos os pinos do PORTB possuem fun��o pullup. */

void pullupConfig(void) {
    OPTION_REGbits.nRBPU = 0; // habilita pull-ups do PORTB
    TRISB |= BUTTON; // atribui n�vel l�gico 1 ao pino RB1, configurando o pino como entrada (necess�rio para que possa utilizar o pullup)
    PORTB |= BUTTON; // coloca o pino em n�vel l�gico 1, quando utilizado como pull-up, est� � a abordagem correta
}

void ledConfig(void) {
    TRISB &= ~LED; // coloca pino como sa�da
    PORTB |= LED; // atribui n�vel l�gico 0 ao pino (led desligado)
}

int main(void) {
    pullupConfig();
    ledConfig();
    while (1) {
        if (!(PORTB & (BUTTON))) { // verifica se n�vel l�gico do pino utilizado como bot�o, est� em 0, ou seja, se fechou conex�o do circuito
            __delay_ms(25);
            PORTB ^= LED; // inverte n�vel l�gico do pino, fazendo toggle no led
        }
        __delay_ms(150);
    }
    return 1;
}

