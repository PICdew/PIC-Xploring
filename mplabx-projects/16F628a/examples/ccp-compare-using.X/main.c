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
#pragma config CPD = OFF // desabilita prote��o de c�digo da mem�ria EEPROM
#pragma config CP = OFF // desabilita prote��o de c�digo da mem�ria FLASH
#pragma config LVP = OFF // desabilita LOW VOLTAGE PROGRAMM

#define LED PORTBbits.RB0; // define constante para pino que ser� utilizado para o led

static unsigned int compareValue = 2499; // atribui valor para frequ�ncia de 50Hz

void timer1Init(void); // fun��o inicializa timer1
void ccpCompareInit(void); // fun��o inicializa e configura modo Compare do m�dulo CCP
void interruptInit(void); // fun��o inicializa interrup��es

int main(void) {
    timer1Init(); // chama fun��o que inicializa e configura timer1
    ccpCompareInit(); // chama fun��o que inicializa e configura modo Compare do m�dulo CCP
    interruptInit(); // chama fun��o que inicializa interrup��es
    TRISB0 = 0; // configura pino RB0 como sa�da
    while (1); // loop infinito
    return 1;
}

void ccpCompareInit(void) {
    CCPR1L = compareValue; // atribui valor para compara��o
    CCP1CONbits.CCP1M3 = 1;
    CCP1CONbits.CCP1M2 = 0;
    CCP1CONbits.CCP1M1 = 1;
    CCP1CONbits.CCP1M0 = 0; // 3� modo Compare do m�dulo CCP - CCP1IF � setado, por�m, nada ocorre no pino CCP1
    PIE1bits.CCP1IE = 1; // habilita interrup��o no m�dulo CCP
    PIR1bits.CCP1IF = 0; // limpa flag de interrup��o do m�dulo CCP
}

void timer1Init(void) {
    PCONbits.OSCF = 1; // oscilador interno de 4Mhz - j� vem configurado por padr�o, por�m, adicionado aqui, para tornar expl�cita a configura��o
    T1CONbits.TMR1CS = 0; // seleciona clock interno
    T1CONbits.nT1SYNC = 1; // n�o sincroniza com o clock externo
    T1CONbits.T1CKPS1 = 1;
    T1CONbits.T1CKPS0 = 1; // atribui prescaler de 1:8 ao timer1
    TMR1H = 0x00;
    TMR1L = 0x00;
    T1CONbits.TMR1ON = 1; // inicializa o timer1
}

void interruptInit(void) {
    INTCONbits.GIE = 1; // habilita interrup��es globais
    INTCONbits.PEIE = 1; // habilita interrup��es de perif�ricos
}

void interrupt ISR(void) {
    if (PIR1bits.CCP1IF) { // verifica se flag de interrup��o do m�dulo CCP est� setada
        PIR1bits.CCP1IF = 0; // limpa flag de interrup��o do m�dulo CCP        
        TMR1H = 0x00;
        TMR1L = 0x00;
        CCPR1L = compareValue; // reatribui valor para compara��o
        PORTB = ~LED; // inverte n�vel l�gico do pino
    }
}