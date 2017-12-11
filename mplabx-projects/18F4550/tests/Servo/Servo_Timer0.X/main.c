/*
 * File:   main.c
 * Author: Mallon
 *
 * Created on 17 de Agosto de 2014, 10:43
 */


#include <xc.h>

#pragma config FOSC = HS
#pragma config MCLRE = ON
#pragma config CPUDIV = OSC1_PLL2
#pragma config WDT = OFF
#pragma config BOR = ON
#pragma config BORV = 1
#pragma config PWRT = ON
#pragma config LVP = OFF
#pragma config PBADEN = OFF

#define _XTAL_FREQ 8000000
#define timerH 100
#define timerL 0

void timerOn(void) {
    INTCONbits.TMR0IF = 0; // LIMPA FLAG DO TIMER0
    //TMR0H = timerH; // CONFIGURA VALOR PARA O TIMER0
    TMR0L = timerL; // CONFIGURA VALOR PARA O TIMER0
}

void cicloAtivo(void) {

}

void interrupt intRoutine(void) {
    if (INTCONbits.TMR0IF) {
        PORTDbits.RD0 = ~LATD0;
        PORTDbits.RD1 = ~LATD1;
        __delay_us(1000);
        PORTDbits.RD0 = ~LATD0;

        //cicloAtivo();
        timerOn();
    }
}

void intConfigs(void) {
    RCONbits.IPEN = 0; // DESABILITA MODO DE PRIORIDADE DE INTERRUPÇÃO
    INTCONbits.GIE = 1; // HABILITA TODAS AS INTERRUPÇÕES
}

void timerConfigs(void) {
    T0CON = 0B00000111; // 7:TMR0ON, 6:T08BIT, 5:T0CS, 4:T0SE, 3:PSA, 2:T0PS0, 1:T0PS1, 0:T0PS0
    timerOn();
    T0CONbits.TMR0ON = 1; // STARTA TIMER0
    INTCONbits.TMR0IE = 1; // HABILITA INTERRUPÇÃO PARA TIMER0
}

void configs(void) {
    ADCON1 = 0X0F;
    TRISD = 0B00000000;
    PORTD = 0B000000000;
}

void main(void) {
    configs();
    timerConfigs();
    intConfigs();

    do {
        //        if (TMR0L == 100) {
        //            PORTDbits.RD0 = ~LATD0;
        //        }
    } while (1);
}
