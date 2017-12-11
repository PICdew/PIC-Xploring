/*
 * File:   main.c
 * Author: Thiago Mallon
 *
 * Created on 1 de Janeiro de 2015, 21:52
 */

#include <xc.h>
#include "o-codestyle.h"

#pragma config FOSC = INTOSCIO // oscilador interno de 4Mhz; pinos RA6 e RA7 liberados para I/O
#pragma config MCLRE = ON // habilita pino de reset; pino RA5 funcionando como MASTER CLEAR RESET
#pragma config LVP = OFF // desabilita LOW VOLTAGE PROGRAMMING
#pragma config WDTE = OFF // desabilita WATCH DOG TIMER
#pragma config BOREN = ON // habilita BROWN OUT RESET
#pragma config PWRTE = ON // habilita POWER UP TIMER
#pragma config CPD = OFF // desabilita prote��o de c�digo para EEPROM
#pragma config CP = OFF // desabilita prote��o de c�digo para FLASH

#define _XTAL_FREQ  4000000UL

/* Quando utiliza-se o oscilador interno, o clock reservado ao timer1 � Fosc/4, ou seja, no caso do PIC16F628A,
que possui um oscilador interno de 4Mhz, o clock do timer1 ser� de 1Mhz. */

#define LED (1 << RA0) // define constante de pino que ser� usado como no led
static unsigned char timer1H = 0xF6;
static unsigned char timer1L = 0x3C; /* atribui valor de 63036 ao timer1, para gerar uma frequ�ncia de 50Hz
                                      * C�lculo:
                                      * Timer1 = Tamanho timer1 - ((((FOSC/4) / Prescaler) / Freq.) -1)
                                      * 63036 = 65535 - ((((4Mhz/4) / 8) / 50Hz) -1) */

void timer1Init(void) {
    PCON |= (1 << OSCF); // oscilador interno de 4Mhz - j� vem configurado por padr�o, por�m, adicionado aqui, para deixar expl�cita a configura��o
    T1CON &= ~(1 << TMR1CS); // seleciona clock interno
    T1CON |= (1 << T1SYNC); // n�o sincroniza com o clock externo
    T1CON |= (1 << T1CKPS1);
    T1CON |= (1 << T1CKPS0); // atribui prescaler de 1:8 ao timer1
    PIR1 &= ~(1 << TMR1IF); // limpa flag de estouro do timer1
    PIE1 |= (1 << TMR1IE); // habilita interrup��o por estouro do timer1
    TMR1H = timer1H; // seta valor no byte mais significativo do contador do timer1
    TMR1L = timer1L; // seta valor no byte menos significativo do contatdor do timer1
    T1CON |= (1 << TMR1ON); // inicializa o timer1
}

void interruptInit(void) {
    INTCON |= (1 << GIE); // habilita interrup��es globais
    INTCON |= (1 << PEIE); // habilita interrup��es de perif�ricos
}

int main(void) {
    CMCON |= (1 << CM2 | 1 << CM1 | 1 << CM0); // pinos do PORTA como I/O
    TRISA &= ~LED; // configura pino RB0 como sa�da digital
    interruptInit(); // chama fun��o que inicializa interrup��es
    timer1Init(); // chama fun��o que configura timer1
    while (1);
    return 1;
}

/** interrup��o de prioridade alta, j� que n�o possui a palavra-chave low_priority depois de interrupt */
void interrupt ISR(void) {
    if (PIR1 & (1 << TMR1IF)) { // verifica se flag de estouro do timer1 est� setada (ocorreu estouro)
        PIR1 &= ~(1 << TMR1IF); // limpa flag de estouro do timer1
        TMR1H = timer1H;
        TMR1L = timer1L; // reatribui valor ao timer1
        PORTA ^= LED; // inverte n�vel l�gico do pino
    }
}