/* 
 * File:   main.c
 * Author: Thiago Mallon
 *
 * Created on 5 de Janeiro de 2015, 18:29
 */

#include <xc.h>

#pragma config FOSC = INTOSCIO // uso do oscilador interno de 4Mhz
#pragma config MCLRE = ON // habilita MASTER CLEAR RESET
#pragma config PWRTE = ON // habilita POWER UP TIMER
#pragma config BOREN = ON // habilita BROWN OUT RESET
#pragma config WDTE = OFF // desabilita WATCH DOG TIMER
#pragma config CPD = OFF // desabilita proteção de código da memória EEPROM
#pragma config CP = OFF // desabilita proteção de código da memória FLASH
#pragma config LVP = OFF // desabilita LOW VOLTAGE PROGRAMM

#define LED PORTBbits.RB0; // define constante para pino que será utilizado para o led

static unsigned int compareValue = 2499; // atribui valor para frequência de 50Hz

void timer1Init(void); // função inicializa timer1
void ccpCompareInit(void); // função inicializa e configura modo Compare do módulo CCP
void interruptInit(void); // função inicializa interrupções

int main(void) {
    timer1Init(); // chama função que inicializa e configura timer1
    ccpCompareInit(); // chama função que inicializa e configura modo Compare do módulo CCP
    interruptInit(); // chama função que inicializa interrupções
    TRISB0 = 0; // configura pino RB0 como saída
    while (1); // loop infinito
    return 1;
}

void ccpCompareInit(void) {
    CCPR1L = compareValue; // atribui valor para comparação
    CCP1CONbits.CCP1M3 = 1;
    CCP1CONbits.CCP1M2 = 0;
    CCP1CONbits.CCP1M1 = 1;
    CCP1CONbits.CCP1M0 = 0; // 3º modo Compare do módulo CCP - CCP1IF é setado, porém, nada ocorre no pino CCP1
    PIE1bits.CCP1IE = 1; // habilita interrupção no módulo CCP
    PIR1bits.CCP1IF = 0; // limpa flag de interrupção do módulo CCP
}

void timer1Init(void) {
    PCONbits.OSCF = 1; // oscilador interno de 4Mhz - já vem configurado por padrão, porém, adicionado aqui, para tornar explícita a configuração
    T1CONbits.TMR1CS = 0; // seleciona clock interno
    T1CONbits.nT1SYNC = 1; // não sincroniza com o clock externo
    T1CONbits.T1CKPS1 = 1;
    T1CONbits.T1CKPS0 = 1; // atribui prescaler de 1:8 ao timer1
    TMR1H = 0x00;
    TMR1L = 0x00;
    T1CONbits.TMR1ON = 1; // inicializa o timer1
}

void interruptInit(void) {
    INTCONbits.GIE = 1; // habilita interrupções globais
    INTCONbits.PEIE = 1; // habilita interrupções de periféricos
}

void interrupt ISR(void) {
    if (PIR1bits.CCP1IF) { // verifica se flag de interrupção do módulo CCP está setada
        PIR1bits.CCP1IF = 0; // limpa flag de interrupção do módulo CCP        
        TMR1H = 0x00;
        TMR1L = 0x00;
        CCPR1L = compareValue; // reatribui valor para comparação
        PORTB = ~LED; // inverte nível lógico do pino
    }
}