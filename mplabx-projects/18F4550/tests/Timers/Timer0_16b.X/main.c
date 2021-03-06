/*
 * File:   main.c
 * Author: Mallon
 *
 * Created on 22 de Julho de 2014, 21:36
 */

#include <p18f4550.h>

#pragma config MCLRE = ON // HABILITA O MASTER-CLEAR-RESET
#pragma config FOSC = HS // OSCILADOR EXTERNO, DE ALTA FREQU�NCIA E SEM PLL
#pragma config CPUDIV = OSC1_PLL2 // CLOCK DO SISTEMA SER� DO OSCILADOR PRIM�RIO
#pragma config PWRT = ON // HABILITA O POWER-UP-TIMER
#pragma config BOR = ON // HABILITA BROWN-OUT-RESET
#pragma config BORV = 1 // SETA VOLTAGEM M�NIMA DO BOR, COMO 4.33v
#pragma config WDT = OFF // DESABILITA O WATCH-DOG-TIMER
#pragma config LVP = OFF // DESABILITA LOW-VOLTAGE-PROGRAM
#pragma config PBADEN = OFF // SETA PINOS RB0, RB1, RB2, RB3 e RB4 COMO I/O

/** CONSTANTES ARMAZENAM O VALOR DO BYTE ALTO E BAIXO DE TIMER0*/
const unsigned char highValue = 0xFD;
const unsigned char lowValue = 0xE9;

void configsTimer(void) {
    T0CON = 0B00000111; // CONFIGURA T0CON
    TMR0H = highValue; // ATRIBUI VALOR AO BYTE ALTO DE TIMER0
    TMR0L = lowValue; // ATRIBUI VALOR AO BYTE BAIXO DE TIMER0
    T0CONbits.TMR0ON = 1; // STARTA INCREMENTO DE TIMER0
    INTCONbits.TMR0IF = 0; // LIMPA FLAG DE ESTOURO DE TIMER0
}

void configs(void) {
#ifdef P18F45K22
    ANSELD = 0; // SETA PINOS DO PORTD COMO DIGITAIS
#else
    ADCON1 = 0B00001111; // CONFIGURA ADCON1 - VOLTAGEM DE REFER�NCIA COMO VSS E VDD E TODOS OS PINOS COMO I/O
#endif
    TRISD = 0; // SETA PINOS DO PORTD COMO SA�DA
    PORTD = 0B01010101; // CONFIGURA N�VEL L�GICO DOS PINOS DO PORTD
}

void main(void) {
    configs();
    configsTimer();
    while (1) {
        if (INTCONbits.TMR0IF) { // VERIFICA SE FLAG DE ESTOURO DE TIMER 0, EST� SETADA
            PORTD = ~LATD; // INVERTE N�VEL L�GICO DOS PINOS DO PORTD
            TMR0H = highValue; // ATRIBUI VALOR AO BYTE ALTO DE TIMER0
            TMR0L = lowValue; // ATRIBUI VALOR AO BYTE BAIXO DE TIMER0
            INTCONbits.TMR0IF = 0; // LIMPA FLAG DE ESTOURO DE TIMER0
        }
    }
}
