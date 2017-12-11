/*
 * File:   main.c
 * Author: Mallon
 *
 * Created on 10 de Agosto de 2014, 12:18
 */


#include <xc.h>

#pragma config FOSC = HS // OSCILADOR PRIMÁRIO EXTERNO, DE ALTA FREQUÊNCIA E SEM PLL
#pragma config CPUDIV = OSC1_PLL2 // CLOCK DO SISTEMA VIRÁ DO OSCILADOR PRIMÁRIO
#pragma config MCLRE = ON // HABILITA O MASTER CLEAR RESET
#pragma config WDT = OFF // DESABILITA O WATCH-DOG-TIMER
#pragma config PWRT = ON // HABILITA O POWER-UP-TIMER
#pragma config BOR = ON // HABILITA O BROWN-OUT-RESET
#pragma config BORV = 1 // SETA VOLTAGEM LIMITE DE BOR, COMO 4.33v
#pragma config LVP = OFF // DESABILITA O LOW-VOLTAGE-PROGRAM
#pragma config PBADEN = OFF // PINOS RB0, RB1, RB2, RB3 e RB4 COMO DIGITAIS

#define _XTAL_FREQ 8000000

/** DEFINIÇÃO DOS PINOS QUE SERÃO UTILIZADOS PELO O LCD */
#define D4 PORTBbits.RB0
#define D5 PORTBbits.RB1
#define D6 PORTBbits.RB2
#define D7 PORTBbits.RB3
#define RS PORTBbits.RB4
#define E PORTBbits.RB5

/** CONSTANTES DE VALOR PARA O TIMER0 */
const unsigned char highT0Value = 0xc2;
const unsigned char lowT0Value = 0xf7;

/** CONFIGURAÇÕES INICIAIS DO TIMER0 */
void timer0Configs(void) {
    INTCONbits.TMR0IF = 0;
    TMR0H = highT0Value;
    TMR0L = lowT0Value;
}

/** CONFIGURAÇÕES INICIAIS DOS TIMERS */
void timerConfigs(void) {
    T0CON = 0B00000100;
    timer0Configs();
}

/** CONFIGURAÇÕES INICIAIS DO PORTB */
void portbConfigs(void) {
    TRISB = 0B00000000;
    PORTB = 0B00000000;
}

/** CONFIGURAÇÕES GERAIS */
void configs(void) {
    ADCON1 = 0X0F; // SETA PINOS A/D, COMO I/O
    portbConfigs(); // CONFIGURAÇÕES DO PORTB
    timerConfigs(); // CONFIGURAÇÕES DO TIMER0
    T0CONbits.TMR0ON = 1;
}

/** FUNÇÃO PRINCIPAL */
void main(void) {
    configs();
    while (1) {
        if (INTCONbits.TMR0IF) {
            D4 = ~LATBbits.LATB0;
            timer0Configs();
        }
    }
}
