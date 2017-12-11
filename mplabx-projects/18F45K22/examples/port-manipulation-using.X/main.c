/*
 * File:   main.c
 * Author: Thiago Mallon
 *
 * Created on 9 de Janeiro de 2015, 18:35
 */

#include <xc.h>
#include "../configs.h"

int main(void) {

    TRISA = 0; // pinos como sa�da
    PORTA = 0; // pinos com n�vel l�gico baixo. Caso altere-se, a express�o do loop infinito, relativa a essa porta, n�o funcionar�

    TRISB = 0; // pinos como sa�da
    PORTB = 0xFF; // pinos com n�vel l�gico alto. Caso altere-se, a express�o do loop infinito, relativa a essa porta, n�o funcionar�

    TRISC = 0; // pinos como sa�da
    PORTC = 0x00; // pinos com n�vel l�gico baixo. Caso altere-se, a express�o do loop infinito, relativa a essa porta, n�o funcionar�

    TRISD = 0; // pinos como sa�da
    PORTD = 0x00; // independentemente do n�vel l�gico que se atribui nos pinos, a express�o relativa a essa porta, no loop infinito, funcionar�

    do {
        PORTB &= ~(0b11 << 0 | 0b11 << 4) | (0b11 << 2 | 0b11 << 6); // express�o funciona somente se todos pinos estiverem previamente com n�vel l�gico alto
        PORTC |= ~(0b11 << 0 | 0b11 << 4) | (0b11 << 2 | 0b11 << 6); // express�o funciona somente se todos pinos estiverem previamente com n�vel l�gico baixo
        PORTD |= ((PORTD&~(0b11 << 0 | 0b11 << 4)) | ((0b11 << 2 | 0b11 << 6))); // express�o funciona independentemente de qual seja o estado l�gico dos pinos anteriormente
    } while (1); // Endless loop
    return 1;
}
