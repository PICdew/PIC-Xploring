/* 
 * File:   main.c
 * Author: Thiago Mallon
 *
 * Created on 3 de Janeiro de 2015, 22:52
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

int main(void) {
    while (1);
    return 1;
}

/** abaixo, utilizando a palavra chave 'interrupt', temos uma interrup��o de alta prioridade */
void interrupt highISR(void) {

}

/** abaixo, utilizando as palavras chave 'interrupt' seguida de 'low_priority', temos uma interrup��o de baixa prioridade */
void interrupt low_priority lowISR(void) {

}