/*
 * File:   main.c
 * Author: Mallon
 *
 * Created on 22 de Julho de 2014, 20:35
 */

#include <p18f4550.h>

#pragma config MCLRE = ON // HABILITA O MASTER CLEAR RESET
#pragma config FOSC = HS // OSCILADOR EXTERNO DE ALTA FREQUÊNCIA, SEM PLL
#pragma config CPUDIV = OSC1_PLL2 // CLOCK DO SISTEMA VEM DO OSCILADOR PRIMÁRIO
#pragma config PWRT = ON // HABILITA O POWER-UP-TIMER
#pragma config BOR = ON // HABILITA O BROWN-OUT-RESET
#pragma config BORV = 1 // CONFIGURA LIMITE DE TENSÃO DO BOR, COMO 4.33v
#pragma config WDT = OFF // DESABILITA O WATCH-DOG-TIMER
#pragma config LVP = OFF // DESABILITA O LOW-VOLTAGE-PROGRAM
#pragma config PBADEN = OFF // SETA PINO RB0, RB1, RB2, RB3 e RB4 COMO DIGITAIS

/** CONSTANTE DE VALOR DO TMR0L */
const unsigned char timerValue = 0x01;

/** FUNÇÃO DE CONFIGURAÇÃO DO TIMER */
void configsTimer(void) {
    T0CON = 0B01000111; // CONFIGURA T0CON    
    TMR0L = timerValue;
    INTCONbits.TMR0IF = 0;
    T0CONbits.TMR0ON = 1;
}

/** FUNÇÃO DE CONFIGURAÇÃO GERAL */
void configs(void) {
#ifdef P18F45K22
    ANSELD = 0;
#else
    ADCON1 = 0B00001111;
    /** SETA VSS COMO VOLTAGEM DE REFERÊNCIA NEGATIVA,
     * VDD COMO VOLTAGEM DE REFERÊNCIA POSITIVA E
     * TODOS OS PINOS A/D COMO I/O */
#endif
    TRISD = 0; // SETA PINOS DO PORTD COMO SAÍDA
    PORTD = 0B01010101; // CONFIGURA NÍVEL LÓGICO DOS PINOS DE PORTD
}

volatile unsigned char timerCount = 0;

/** FUNÇÃO PRINCIPAL */
void main(void) {
    configs();
    configsTimer();
    while (1) {
        if (INTCONbits.TMR0IF && timerCount == 2) { // VERIFICA SE A FLAG DE ESTOURO DE TIMER0 ESTÁ SETADA
            PORTD = ~LATD; // INVERTE NÍVEL LÓGICO DOS PINOS DO PORTD            
            TMR0L = timerValue;
            timerCount = 0;
            INTCONbits.TMR0IF = 0;
        } else if (INTCONbits.TMR0IF) {
            TMR0L = timerValue;
            timerCount++;
            INTCONbits.TMR0IF = 0;
        }
    }
}
