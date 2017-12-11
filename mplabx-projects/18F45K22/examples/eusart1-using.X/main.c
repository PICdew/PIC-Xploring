/* 
 * File:   main.c
 * Author: Thiago Mallon
 *
 * Created on 12 de Janeiro de 2015, 11:47
 */

#include <xc.h>
#include "../configs.h"

/* frequ�ncia do clock */
#define _XTAL_FREQ 16000000UL

/* defini��es da eusart1 */
#define BAUD 9600
#define BAUDRATE ((_XTAL_FREQ / (BAUD * 16UL)) -1)

void eusart1Init(void); // fun��o inicializa a eusart1

int main(void) {
    while (1);
    return 1;
}

/** fun��o inicializa a eusart1 */
void eusart1Init(void) {
    SPBRG1 = BAUDRATE;
    // configura transmiss�o
    TXSTA1 |= (1 << 5 | 1 << 2); // TXEN - BRGH
    TXSTA1 &= ~(1 << 6 | 1 << 4); // TX9 - SYNC
    // configura recep��o
    RCSTA1 |= (1 << 7);
}
