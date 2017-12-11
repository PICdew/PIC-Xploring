/*
 * File:   main.c
 * Author: Mallon
 *
 * Created on 22 de Julho de 2014, 20:35
 */

#include <p18f4550.h>
#include <delays.h>

#pragma config MCLRE = ON // HABILITA O MASTER CLEAR RESET
#pragma config FOSC = HS // OSCILADOR EXTERNO DE ALTA FREQU�NCIA, SEM PLL
#pragma config CPUDIV = OSC1_PLL2 // CLOCK DO SISTEMA VEM DO OSCILADOR PRIM�RIO
#pragma config PWRT = ON // HABILITA O POWER-UP-TIMER
#pragma config BOR = ON // HABILITA O BROWN-OUT-RESET
#pragma config BORV = 1 // CONFIGURA LIMITE DE TENS�O DO BOR, COMO 4.33v
#pragma config WDT = OFF // DESABILITA O WATCH-DOG-TIMER
#pragma config LVP = OFF // DESABILITA O LOW-VOLTAGE-PROGRAM
#pragma config PBADEN = OFF // SETA PINO RB0, RB1, RB2, RB3 e RB4 COMO DIGITAIS

/** CONSTANTE DE VALOR DO TMR0L */
unsigned char lowTimerValue = 235;
unsigned char count = 0;
/** */
#pragma interrupt highIntRoutine

void highIntRoutine(void) {
   // if(count == 10){
        PORTD = ~LATD; // INVERTE N�VEL L�GICO DOS PINOS DO PORTD
      //  count = 0;
    //}
    TMR0L = lowTimerValue;
    INTCONbits.TMR0IF = 0;
    //count++;
}

/** */
#pragma code highInterruption = 0x08

void highInterruption(void) {
    _asm GOTO highIntRoutine _endasm
}
#pragma code

/** */
void configsInterrupt(void) {
    RCONbits.IPEN = 1; // HABILITA N�VEL DE PRIORIDADE DE INTERRU��ES
    INTCONbits.GIEH = 1; // HABILITA INTERRUP��ES DE ALTA PRIORIDADE
    INTCONbits.TMR0IE = 1; // HABILITA INTERRUP��O PARA TIMER0
    INTCON2bits.TMR0IP = 1; // SETA ESTOURO DE TIMER0 COMO INTERRUP��O DE ALTA PRIORIDADE
    INTCONbits.TMR0IF = 0; // LIMPA FLAG DE ESTOURO DO TIMER0
    T0CONbits.TMR0ON = 1; // STARTA INCREMENTO DE
}

/** FUN��O DE CONFIGURA��O DO TIMER */
void configsTimer(void) {
    T0CON = 0B01000111; // CONFIGURA T0CON

    TMR0L = lowTimerValue;
}

/** FUN��O DE CONFIGURA��O GERAL */
void configs(void) {
#ifdef P18F45K22
    ANSELD = 0;
#else
    ADCON1 = 0B00001111; // CONFIGURA ADCON1
#endif
    TRISB = 0B00000011; // SETA PINOS RB0 E RB1 COMO ENTRADA E OS DEMAIS COMO SA�DA
    PORTB = 0; // SETA N�VEL L�GICO 0, PARA TODOS OS PINOS DO PORTB

    TRISC = 0; // SETA PINOS DO PORTC COMO SA�DA
    PORTC = 0; // SETA N�VEL L�GICO 0 PARA TODOS OS PINOS DO PORTC

    TRISD = 0; // SETA PINOS DO PORTD COMO SA�DA
    PORTD = 0B01010101; // CONFIGURA N�VEL L�GICO DOS PINOS DE PORTD
}

unsigned char aux = 0;

/** FUN��O PRINCIPAL */
void main(void) {
    configs();
    configsTimer();
    configsInterrupt();
    while (1) {
        if (PORTBbits.RB0 == 0 && lowTimerValue < 255) {
            PORTCbits.RC0 = 1;
            lowTimerValue += 1;
            Delay10KTCYx(50);
        } else {
            PORTCbits.RC0 = 0;
        }

        if (PORTBbits.RB1 == 0 && lowTimerValue > 235) {
            PORTCbits.RC1 = 1;
            lowTimerValue -= 1;
            Delay10KTCYx(50);
        } else {
            PORTCbits.RC1 = 0;
        }
    }
}