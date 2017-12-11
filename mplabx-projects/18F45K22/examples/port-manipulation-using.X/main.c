/*
 * File:   main.c
 * Author: Thiago Mallon
 *
 * Created on 9 de Janeiro de 2015, 18:35
 */

#include <xc.h>
#include "../configs.h"

int main(void) {

    TRISA = 0; // pinos como saída
    PORTA = 0; // pinos com nível lógico baixo. Caso altere-se, a expressão do loop infinito, relativa a essa porta, não funcionará

    TRISB = 0; // pinos como saída
    PORTB = 0xFF; // pinos com nível lógico alto. Caso altere-se, a expressão do loop infinito, relativa a essa porta, não funcionará

    TRISC = 0; // pinos como saída
    PORTC = 0x00; // pinos com nível lógico baixo. Caso altere-se, a expressão do loop infinito, relativa a essa porta, não funcionará

    TRISD = 0; // pinos como saída
    PORTD = 0x00; // independentemente do nível lógico que se atribui nos pinos, a expressão relativa a essa porta, no loop infinito, funcionará

    do {
        PORTB &= ~(0b11 << 0 | 0b11 << 4) | (0b11 << 2 | 0b11 << 6); // expressão funciona somente se todos pinos estiverem previamente com nível lógico alto
        PORTC |= ~(0b11 << 0 | 0b11 << 4) | (0b11 << 2 | 0b11 << 6); // expressão funciona somente se todos pinos estiverem previamente com nível lógico baixo
        PORTD |= ((PORTD&~(0b11 << 0 | 0b11 << 4)) | ((0b11 << 2 | 0b11 << 6))); // expressão funciona independentemente de qual seja o estado lógico dos pinos anteriormente
    } while (1); // Endless loop
    return 1;
}
