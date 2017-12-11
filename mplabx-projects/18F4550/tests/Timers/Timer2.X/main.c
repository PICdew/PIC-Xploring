/*
 * File:   main.c
 * Author: Mallon
 *
 * Created on 27 de Julho de 2014, 16:34
 */

#include <p18f4550.h>
#include <delays.h>

#pragma config MCLRE = ON // HABILITA O MCLR
#pragma config FOSC = HS // OSCILADOR PRIMÁRIO É EXTERNO, DE ALTA FREQUÊNCIA E O PLL ESTÁ DESATIVADO
#pragma config CPUDIV = OSC1_PLL2 // CLOCK DO SISTEMA VEM DO OSCILADOR PRIMÁRIO
#pragma config PWRT = ON // HABILITA O POWER-UP-TIMER
#pragma config BOR = ON // HABILITA O BROWN-OUT-RESET
#pragma config BORV = 1 // SETA COMO 4.33v A TENSÃO MÍNIMA PARA O BOR
#pragma config WDT = OFF // DESABILITA O WATCH-DOG-TIMER
#pragma config LVP = OFF // DESABILITA O LOW-VOLTAGE-PROGRAM
#pragma config PBADEN = OFF // PINOS RB0, RB1, RB2, RB3 e RB4 COMO I/0

/** FUNÇÃO IMPLEMENTA CONFIGURAÇÕES INICIAIS PARA O MÓDULO TIMER2 */
void configsTimer(void) {
    T2CON = 0B01111011; // CONFIGURA T2CON
    PR2 = 255; // CONFIGURA VALOR PARA O PR2 (PERÍODO DO TIMER2)
    PIR1bits.TMR2IF = 0; // LIMPA FLAG DE ESTOURO DO TIMER2;
    T2CONbits.TMR2ON = 1; // START INCREMENTO DE TIMER2
}

/** FUNÇÃO IMPLEMENTA CONFIGURAÇÕES GERAIS, INICIAIS */
void configs(void) {
#ifdef
    ANSELD = 0;
#else
    ADCON1 = 0X0F; // CONFIGURA VCFG1 COMO VSS, VCFG0 COMO VDD E SETA TODOS OS PINOS A/D COMO I/O

    TRISD = 0; // CONFIGURA PINOS DO PORTD COMO SAÍDA
    PORTD = 0; // SETA NÍVEL LÓGICO DOS PINOS DO PORTD COMO 0

#endif
}

void main(void) {
    configs();
    configsTimer();
    while (1) {
        if (PIR1bits.TMR2IF) {
            PORTD = ~LATD;
            PIR1bits.TMR2IF = 0;
        }
    }
}
