/* 
 * File:   main.c
 * Author: Thiago Mallon
 *
 * Created on 5 de Janeiro de 2015, 15:25
 */

#include <xc.h>

#pragma config FOSC = INTOSCIO // faz uso do oscilador interno de 4Mhz
#pragma config MCLRE = ON // habilita o MASTER CLEAR RESET
#pragma config PWRTE = ON // habilita o POWER UP TIMER
#pragma config BOREN = ON // habilita o BROWN OUT RESET
#pragma config WDTE = OFF // desabilita o WATCH DOG TIMER
#pragma config CPD = OFF // desabilita prote��o de c�digo da mem�ria EEPROM
#pragma config CP = OFF // desabilita prote��o de c�digo da mem�ria FLASH
#pragma config LVP = OFF // desabilita LOW VOLTAGE PROGRAMM

#define _XTAL_FREQ 4000000UL // declara constante com valor do oscilador, para a fun��o de delay

/** No m�dulo CCP, para o recurso PWM utiliza-se obrigat�riamente, via hardware, o timer2 
 *
 * Quando utiliza-se o oscilador interno, o clock reservado ao timer2 � Fosc/4, ou seja, no caso do PIC16F628A,
 * que possui um oscilador interno de 4Mhz, o clock do timer2 ser� de 1Mhz. */

void ccpPwmConfig(void);
void timer2Init(void);
void oscillate(void);

int main(void) {
    ccpPwmConfig(); // chama fun��o que configura o modo PWM no m�dulo CCP
    timer2Init(); // inicializa timer2
    while (1) {
        oscillate();
    }
    return 1;
}

void oscillate(void) {
    static unsigned int x = 0;
    for (; x < 255; x++) { // navega x, para passar por todos os valores poss�veis da resolu��o m�xima do dutty cycle
        CCPR1L = x; // atribui valor de x ao registrador que implementa duty cycle
        __delay_ms(5); // delay de 5ms
    }
    for (; x > 0; x--) { // navega x, para passar por todos os valores poss�veis da resolu��o m�xima do dutty cycle
        CCPR1L = x; // atribui valor de x ao registrador que implementa duty cycle
        __delay_ms(5); // delay de 5ms
    }
}

void ccpPwmConfig(void) { // fun��o habilita e configura modo PWM
    TRISB3 = 0; // configura pino RB3 como sa�da - este � o pino CCP1 no PIC16F628A

    CCP1CONbits.CCP1M3 = 1;
    CCP1CONbits.CCP1M2 = 1;
    CCP1CONbits.CCP1M1 = 0;
    CCP1CONbits.CCP1M0 = 0; // habilita modo PWM, no m�dulo CCP

    CCPR1L = 1023; // atribui valor do dutty cycle ao registrador
}

/* Para calcular-se o per�odo do PWM, usa-se a seguinte f�rmula:
 * Per�odo do PWM = (((PR2) + 1) * 4 * TOSC * prescaler)
 * 0,016384s = (((255) + 1) * 4 * (1/(FOSC/4)) * 16) - S� ocorre a divis�o (FOSC/4), quando utiliza-se o oscilador interno
 * Para determinar a frequ�ncia que ser� gerada, ent�o divide-se de 1, o valor encontrado, ou seja:
 * Freq. = 1/0,016384 = 61Hz
 *
 * Para calcular-se o valor a ser colocado em PR2, para uma determinada frequ�ncia desejada (15625KHz), utiliza-se a seguinte f�rmula:
 * PR2 = ((FOSC/4) / ((Freq. Desejada) * 4 * prescaler)) -1  - S� ocorre a divis�o (FOSC/4), quando utiliza-se o oscilador interno
 * 255 = (1000000 / (61Hz * 4 * 16)) -1
 *
 * Para calcular-se o Dutty Cycle, utiliza-se a seguinte f�rmula:
 * Duty Cycle = ((CCPR1L:CCP1CON<5:4>) / ((PR2+1)*4)) * Tens�o m�xima
 * 2,5v = ((512) / ((255+1)*4)) * 5v
 *
 */
void timer2Init(void) { // fun��o inicializa e configura timer2
    PCONbits.OSCF = 1; // oscilador interno de 4Mhz - j� vem configurado por padr�o, por�m, adicionado aqui, para deixar expl�cita a configura��o
    T2CONbits.T2CKPS1 = 1; // configura prescaler de 1:16
    PR2 = 255; // frequ�ncia de 61Hz
    T2CONbits.TMR2ON = 1; // inicializa timer2
}


