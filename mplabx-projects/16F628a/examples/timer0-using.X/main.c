/*
 * File:   main.c
 * Author: Thiago Mallon
 *
 * Created on 30 de Dezembro de 2014, 19:55
 */

#include <xc.h>

#pragma config FOSC = INTOSCIO // oscilador interno de 4Mhz; pinos RA6 e RA7 liberados para I/O
#pragma config MCLRE = ON // habilita pino de reset; pino RA5 funcionando como MASTER CLEAR RESET
#pragma config LVP = OFF // desabilita LOW VOLTAGE PROGRAMMING
#pragma config WDTE = OFF // desabilita WATCH DOG TIMER
#pragma config BOREN = ON // habilita BROWN OUT RESET
#pragma config PWRTE = ON // habilita POWER UP TIMER
#pragma config CPD = OFF // desabilita prote��o de c�digo para EEPROM
#pragma config CP = OFF // desabilita prote��o de c�digo para FLASH

/* Quando utiliza-se o oscilador interno, o clock reservado ao timer0 � Fosc/4, ou seja, no caso do PIC16F628A,
que possui um oscilador interno de 4Mhz, o clock do timer0 ser� de 1Mhz. */

#define LED PORTBbits.RB0 // define pino que ser� usado para o led
static unsigned char timer0Value = 178; /* atribui valor de 178 ao timer0, para gerar uma frequ�ncia de 50Hz
                                      * C�lculo:
                                      * Timer0 = Tamanho timer0 - ((((FOSC/4) / Prescaler) / Freq.) -1)
                                      * 178,9 = 255 - ((((4Mhz/4) / 256) / 50Hz) -1) */

void timer0Init(void) {
    PCONbits.OSCF = 1; // oscilador interno de 4Mhz - j� vem configurado por padr�o, por�m, adicionado aqui, para deixar expl�cita a configura��o
    OPTION_REGbits.T0CS = 0; // timer0 atuar� como temporizador
    OPTION_REGbits.PSA = 0; // permite atribui��o de prescaler ao timer0
    OPTION_REGbits.PS2 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 1; // configura prescaler do timer0 em 1:256
    TMR0 = timer0Value; // atribui valor ao timer1

    INTCONbits.T0IE = 1; // habilita interrup��o por estouro do contador do timer0
    INTCONbits.T0IF = 0; // limpa flag de estouro do timer0
}

void interruptInit(void) {
    INTCONbits.GIE = 1; // habilita interrup��es globais
}

int main(void) {
    TRISB0 = 0; // configura pino 0 do portb como sa�da
    timer0Init(); // inicializa timer0
    interruptInit(); // inicializa interrup��es
    while (1);
    return 1;
}

void interrupt ISR(void) {
    if (INTCONbits.T0IF) { // verifica se flag de estouro do timer0 est� setada
        INTCONbits.T0IF = 0; // limpa flag de estouro do timer0
        TMR0 = timer0Value; // reatribui valor ao timer0
        PORTB = ~LED; // inverte n�vel l�gico do pino
    }
}