/*
 * File:   main.c
 * Author: Mallon
 *
 * Created on 29 de Julho de 2014, 21:41
 */

#include <p18f4550.h>
#include <timers.h>
#include <adc.h>
#include <stdio.h>
#include <pwm.h>
#include "biblioteca_lcd.h"

// Fosc = 20MHz
// Tciclo = 4/Fosc = 0,2us

#pragma config FOSC = HS
#pragma config CPUDIV = OSC1_PLL2

#pragma config WDT = OFF
#pragma config PWRT = ON
#pragma config BOR = 0N
#pragma config BORV = 1
#pragma config PBADEN = OFF
#pragma config LVP = OFF
#pragma config CCP2MX = OFF // SINAL DE PWM NO PINO RB3

// VARIÁVEIS GLOBAIS
unsigned int validade_tecla, cont_tecla;
unsigned char tecla, tecla_anterior;
unsigned char buffer[16];

#define B_DIMINUI PORTBbits.RB5
#define B_AUMENTA PORTBbits.RB6
#define B_CONTINUO PORTBbits.RB7

void main(void) {
    return;
}
