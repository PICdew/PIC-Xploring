/*
 * File:   main.c
 * Author: Mallon
 *
 * Created on 27 de Julho de 2014, 14:09
 */

#include <p18f4550.h>

#pragma config MCLRE = ON // HABILITA O MCLR
#pragma config FOSC = HS // OSCILADOR PRIM�RIO � EXTERNO, DE ALTA FREQU�NCIA E PLL DESABILITADO
#pragma config CPUDIV = OSC1_PLL2 // CLOCK DO SISTEMA VEM DO OSCILADOR EXTERNO
#pragma config PWRT = ON // HABILITA O POWER-UP-TIMER
#pragma config BOR = ON // HABILITA O BROWN-OUT-RESET
#pragma config BORV = 1 // SETA COMO 4.33v A TENS�O M�NIMA PARA O BOR
#pragma config WDT = OFF // DESABILITA WATCH-DOG-TIMER
#pragma config LVP = OFF // DASABILITA O LOW-VOLTAGE-PROGRAM
#pragma config PBADEN = OFF // SETA OS PINOS RB0, RB1, RB2, RB3 e RB4 COMO I/O

/** SETA ROTINAS PARA INTERRUP��O GERADA */
#pragma interrupt interruptRoutine

void interruptRoutine(void) {
    if(PIR1bits.TMR2IF){
        PORTD = ~LATD;
        PIR1bits.TMR2IF = 0;
    }
}

/** SETA ENDERE�O DE MEM�RIA PARA ROTINA DE INTERRUP��O */
#pragma code setInterruptAddr = 0x08

void setInterruptAddr(void) {
    _asm GOTO interruptRoutine _endasm
}
#pragma code

/** CONFIGURA��O DE INTERRUP��O */
void configsInterrupt(void) {
    RCONbits.IPEN = 0; // DESABILITA N�VEL DE PRIORIDADE DE INTERRUP��O
    INTCONbits.GIE = 1; // HABILITA INTERRUP��ES
    INTCONbits.PEIE = 1; // HABILITA INTERRUP��O DE PERIF�RICOS
    T2CONbits.TMR2ON = 1; // STARTA INCREMENTO DE TIMER2
}

/** CONFIGURA��ES DO TIMER */
void configsTimer(void) {
    T2CON = 0B01111011; // SETA POSTSCALE COMO 16, INCREMENTO DESLIGADO E PRESCALE COMO 16
    PR2 = 50; // SETA PER�ODO PARA INTERRUP��O DO TIMER2
    PIE1bits.TMR2IE = 1; // HABILITA INTERRUP��O PARA ESTOUR DE TIMER2
    PIR1bits.TMR2IF = 0; // LIMPA FLAG DE ESTOURO DE TIMER2
}

/** CONFIGURA��ES GERAIS */
void configs(void) {
#ifdef P18F45K22
    ANSELD = 0; // SETA PINOS DO PORTD COMO I/O
#else
    ADCON1 = 0B00001111; // SETA TODOS OS PINOS A/D COMO I/O
#endif
    TRISD = 0; // SETA PINOS DO PORTD COMO SA�DA
    PORTD = 0b010101; // SETA N�VEL L�GICO DOS PINOS DO PORTD COMO 0
}

/** FUN��O PRINCIPAL */
void main(void) {
    configs();
    configsTimer();
    configsInterrupt();
    while (1);
}
