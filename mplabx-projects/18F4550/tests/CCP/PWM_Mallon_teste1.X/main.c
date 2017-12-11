/*
 * File:   main.c
 * Author: Mallon
 *
 * Created on 29 de Julho de 2014, 21:50
 */



#include <xc.h>

#pragma config MCLRE = ON // HABILITA MCLR
#pragma config FOSC = HS // OSCILADOR PRIMÁRIO EXTERNO, DE ALTA FREQUÊNCIA, PLL DESABILITADO
#pragma config PWRT = ON // HABILITA O POWER-UP-TIMER
#pragma config WDT = OFF // DESABILITA O WATCH-DOG-TIMER
#pragma config BOR = ON // HABILITA O BROWN-OUT-RESET
#pragma config BORV = 1 // SETA COMO 4.33v A TENSÃO MÍNIMA PARA O BOR
#pragma config LVP = OFF // DESABILITA O LOW-VOLTAGE-PROGRAM
#pragma config PBADEN = OFF // SETA PINOS RB0, RB1, RB2, RB3 e RB4 COMO I/O
#pragma config CCP2MX = OFF // SETA PINO DE SINAL DO PWM O RB3

#define _XTAL_FREQ 8000000 //The speed of your internal(or)external oscillator

void configs(void) {
    TRISA = 0x00; //PORTA saída
    TRISB = 0x01; //RB0 como entrada e demais pinos do PORTB como saída
    TRISC = 0x00; //PORTC saída
    TRISD = 0x00; //PORTD saída
    TRISE = 0x00; //PORTE saída
    ADCON1 = 0x0F; //configura pinos dos PORTA e PORTE como digitais
    PORTA = 0; //limpa PORTA
    PORTB = 0; //limpa PORTB
    PORTC = 0; //limpa PORTC
    PORTD = 0x00; //apaga displays
    PORTE = 0; //limpa PORTE
}

void configsPWM(void) {
    PR2 = 150; //período do sinal PWM = 15625Hz
    CCPR1L = 0b01000000;
    CCP1CONbits.DC1B1 = 0;
    CCP1CONbits.DC1B0 = 0; //bits de controle = 256
    TRISCbits.RC2 = 0; //configura pino de saída do sinal PWM como saída

    T2CON = 0b00000111; //fator de postscaler de 1:1 <6:3>
    //fator de prescaler de 1:1<1:0>
    TMR2 = 0; //inicializa TMR2

    CCP1CON *= 0b00110000;
    CCP1CON += 0b00001100; //ativa modo PWM
}

void main(void) {
    configs();
    configsPWM();
    while (1);
}
 