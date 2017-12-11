/*
 * File:   main.c
 * Author: Thiago Mallon
 *
 * Created on 9 de Janeiro de 2015, 18:35
 */

#include <xc.h>
#include "../configs.h"
#include "../arm-codestyle-18f45k22.h"

#define _XTAL_FREQ 16000000UL

#define LED_BLOCK (0xFF << RB0)

void ledBlockConfig(void); // função configura pinos dos leds
void generalConfig(void); // função realiza configurações gerais da aplicação
void interruptConfig(void); // função configura interrupções
void timer0Init(void); // função configura timer0

/** Interrupt Service Routine */
void interrupt ISR(void) {
    static uint16_t tmr0Counter = 1;
    if (INTCON & (1 << TMR0IF)) { // verifica se flag de interrupção do timer0 está setada
        if (tmr0Counter >= 31372) { // verifica se valor do contador atingiu valor alvo
            PORTB ^= (LED_BLOCK); // inverte nível lógico dos pinos dos leds
            tmr0Counter = 0; // zera contador do timer0
        }
        TMR0L = 0; // atribui valor ao contador do timer0
        INTCON &= ~(1 << TMR0IF); // limpa flag de interrupção do timer0
        tmr0Counter++; // incrementa contador
    }
}

/** função de configurações gerais da aplicação */
void generalConfig() {
    /*
    ANSELA &= ~(0xFF << ANSA0);
    ANSELB &= ~(0xFF << ANSB0);
    ANSELC &= ~(0b111111 << ANSC2);
     */
    OSCTUNE &= (1 << PLLEN); // habilita PLL 4x
    TRISA &= ~(0xFF << RA0);
    PORTA &= ~(0xFF << RA0);
    PORTB &= ~(0xFF << RB0);
    PORTC &= ~(0xFF << RC0);
    PORTD &= ~(0xFF << RD0);
    PORTE &= ~(0xFF << RE0);
}

/** configura pinos usados nos leds */
void ledBlockConfig(void) {
    TRISB &= ~(LED_BLOCK); // configura pinos como saída
    PORTB |= (LED_BLOCK); // atribui nível lógico alto aos pinos
}

/** função configura interrupções */
void interruptConfig(void) {
    RCON |= (1 << IPEN); // habilita níveis de prioridade para interrupções
    INTCON |= (1 << GIE | 1 << PEIE | 1 << TMR0IE); // habilita interrupções globais; habilita interrupções de periféricos; habilita interupção do timer0
    INTCON &= ~(1 << TMR0IF); // limpa flag de interrupção do timer0
    INTCON2 |= (1 << TMR0IP); // configura interrupção do timer0 como de alta prioridade
}

/** função configura timer0 */
void timer0Init(void) {
    /** liga timer0; modo 8 bits; modo temporizador; prescaler de 1:256 */
    T0CON |= (1 << T08BIT);
    T0CON &= ~(1 << PSA | 0b111 << T0PS0 | 1 << T0CS); // habilita prescaler do timer0
    TMR0L = 0; // atribui valor ao contador do timer0
    T0CON |= (1 << TMR0ON);
}

int main(void) {
    generalConfig();
    ledBlockConfig();
    interruptConfig();
    timer0Init();
    while (1);
    return 1;
}
