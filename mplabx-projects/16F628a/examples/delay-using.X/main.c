/* 
 * File:   main.c
 * Author: Thiago Mallon
 *
 * Created on 2 de Janeiro de 2015, 11:51
 */

#include <xc.h>
#include "o-codestyle.h"

#pragma config FOSC = INTOSCIO // oscilador interno de 4Mhz; pinos RA6 e RA7 liberados para I/O
#pragma config MCLRE = ON // habilita pino de reset; pino RA5 funcionando como MASTER CLEAR RESET
#pragma config LVP = OFF // desabilita LOW VOLTAGE PROGRAMMING
#pragma config WDTE = OFF // desabilita WATCH DOG TIMER
#pragma config BOREN = ON // habilita BROWN OUT RESET
#pragma config PWRTE = ON // habilita POWER UP TIMER
#pragma config CPD = OFF // desabilita proteção de código para EEPROM
#pragma config CP = OFF // desabilita proteção de código para FLASH

/** Observe que declaramos o valor inteiro da frequência do oscilador interno. Não ocorre com o delay, o que
 ocorre com os timers, quando utiliza-se o oscillador interno, à saber, quando utiliza-se timers com o oscilador
 interno, a frequência do mesmo tem que ser dividida por 4. */
#define _XTAL_FREQ 4000000UL // informa ao sistema qual a frequência utilizada pela CPU, nesse caso, para posterior uso da função __delay_ms();
#define LED (1 << 1) // define LED

void configLed(void) {
    CMCON |= (0b111 << CM0); // pinos do PORTA como I/O digitais - desloca 0b111 uma vez de CM0, afetanto os CM1 e CM2 também
    TRISB &= ~LED; // configura pino RB0 como saída digital
    PORTB |= LED; // atribui nível lógico 1 ao pino RB0 (LED)
}

int main(void) {
    configLed(); // chama função que configura pino
    while (1) {
        PORTB ^= LED; // inverte nível lógico do pino
        __delay_ms(1000); // aplica delay de 500ms
    }
    return 1;
}

