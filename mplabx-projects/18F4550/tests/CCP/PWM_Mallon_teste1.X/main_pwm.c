/*
 *                          usando PWM no MPlab XC8
 *
 * Compilador : MPlabXC8
 * Microcontrolador: 16F877A
 * Autor: aguivone
 * Versão: 1
 * Data :  12 de março de 2013
 */
/*
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 8000000    // cristal de 4 Mhz
#include <xc.h>

/////////////////////////////////////////////////////////configuraçôes//////////////////////////////////////////////////

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)



///////////////////////////////////////////////////interrupção//////////////////////////////////////////////////////////////

void interrupt interrupcao(void) {//vetor de interrupção
    if (TMR2IF) {//interrupção do timer2
        TMR2IF = 0; //não será usado
    }
    if (CCP1IF) {//interrupção do ccp1
        CCP1IF = 0; //não será usado
    }
}

void inicializa_PWM1(char prescaler, char pr2, char postcaler) {//prescaler / PR2 / postcaler
    switch (prescaler) {
        case 1:
            prescaler = 0;
            break;
        case 4:
            prescaler = 1;
            break;
        case 16:
            prescaler = 3;
            break;
    }
    T2CON = (postcaler - 1) << 3;
    T2CON = T2CON + 4 + prescaler; //o 4 é para habilitar o timer 2
    PR2 = pr2;
    CCP1CON = 0X0F; //habilita pwm
    CCP1IE = 1; //habilita modulo ccp1
    TMR2IE = 1; //habilita timer 2
}

void duty_cicle(int valor) {
    int baixo = (valor << 4) | 0X0C; //assim mantem os 4 bits mais baixo como 1100 - modo pwm
    CCPR1L = valor >> 2;
    CCP1CON = baixo;
}
//////////////////////////////////////////////////////Rotina principal///////////////////////////////////////////////////////////////

void main(void) {
    TRISC = 0; //configura como saida
    PORTC = 0; // limpar as portas que estão configuradas como saidas
    inicializa_PWM1(4, 250, 1); //1khz veja no comentario abaixo "SUGESTÃO DE DEFINES :"
    PEIE = 1; //habilita interrupção de perifericos do pic
    GIE = 1; //GIE: Global Interrupt Enable bit
    // N = (Fosc/(Fpwm * 4 * prescaler))
    //N = (4.000.000/(1000*4*1)) = 1000 incrementos
    duty_cicle(500); //1000 passos ,supondo que se queira 50% basta por a metade deste valor = 500.
    while (1);
}

 */


/*calculos para pwm
 *
 * periodo do pwm
 *
 *  Tpwm = [PR2+1]*4*Tosc*prescaler(do timer2)
 *
 * duty cycle
 *             <bits 5e4>
 * D = (CCPR1L + CCP1CON) * Tosc * prescaler (do timer2)
 *
 * numero de passos do pwm
 *
 * N = (Fosc/(Fpwm * 4 * prescaler))
 */

/*
 SUGESTÃO DE DEFINES :
 * use estes valores como referencia
 *
//clock de 4mhz
#define PWM_250HZ_CLK4         inicializa_PWM1(16, 250, 1) //
#define PWM_500HZ_CLK4         inicializa_PWM1(16, 125, 1) //
#define PWM_1KHZ_CLK4          inicializa_PWM1(4, 250, 1)  //
#define PWM_1K25HZ_CLK4        inicializa_PWM1(16, 50, 1)  //
#define PWM_2KHZ_CLK4          inicializa_PWM1(4, 125, 1)  //
#define PWM_2K5HZ_CLK4         inicializa_PWM1(4, 100, 1)  //
#define PWM_4KHZ_CLK4          inicializa_PWM1(1, 250, 1)  //
#define PWM_5KHZ_CLK4          inicializa_PWM1(1, 200, 1)  //
#define PWM_8KHZ_CLK4          inicializa_PWM1(1, 125, 1)  //
#define PWM_10KHZ_CLK4         inicializa_PWM1(1, 100, 1)  //
#define PWM_20KHZ_CLK4         inicializa_PWM1(1,  50, 1)  //
#define PWM_25KHZ_CLK4         inicializa_PWM1(1,  40, 1)  //
#define PWM_100KHZ_CLK4        inicializa_PWM1(1, 10, 1)   //
//clock de 8mhz
#define PWM_500HZ_CLK8         inicializa_PWM1(16, 250, 1) //
#define PWM_1KHZ_CLK8          inicializa_PWM1(16, 125, 1) //
#define PWM_2KHZ_CLK8          inicializa_PWM1(4, 250, 1)  //
#define PWM_2K5HZ_CLK8         inicializa_PWM1(16, 50, 1)  //
#define PWM_4KHZ_CLK8          inicializa_PWM1(4, 125, 1)  //
#define PWM_5KHZ_CLK8          inicializa_PWM1(4, 100, 1)  //
#define PWM_8KHZ_CLK8          inicializa_PWM1(1, 250, 1)  //
#define PWM_10KHZ_CLK8         inicializa_PWM1(1, 200, 1)  //
#define PWM_16KHZ_CLK8         inicializa_PWM1(1, 125, 1)  //
#define PWM_20KHZ_CLK8         inicializa_PWM1(1, 100, 1)  //
#define PWM_40KHZ_CLK8         inicializa_PWM1(1,  50, 1)  //
#define PWM_50KHZ_CLK8         inicializa_PWM1(1,  40, 1)  //
#define PWM_200KHZ_CLK8        inicializa_PWM1(1, 10, 1)   //
//clock de 16mhz
#define PWM_1KHZ_CLK16         inicializa_PWM1(16, 250, 1) //
#define PWM_2KHZ_CLK16         inicializa_PWM1(16, 125, 1) //
#define PWM_4KHZ_CLK16         inicializa_PWM1(4, 250, 1)  //
#define PWM_5KHZ_CLK16         inicializa_PWM1(16, 50, 1)  //
#define PWM_8KHZ_CLK16         inicializa_PWM1(4, 125, 1)  //
#define PWM_10KHZ_CLK16        inicializa_PWM1(4, 100, 1)  //
#define PWM_16KHZ_CLK16        inicializa_PWM1(1, 250, 1)  //
#define PWM_20KHZ_CLK16        inicializa_PWM1(1, 200, 1)  //
#define PWM_32KHZ_CLK16        inicializa_PWM1(1, 125, 1)  //
#define PWM_40KHZ_CLK16        inicializa_PWM1(1, 100, 1)  //
#define PWM_80KHZ_CLK16        inicializa_PWM1(1,  50, 1)  //
#define PWM_100KHZ_CLK16       inicializa_PWM1(1,  40, 1)  //
#define PWM_400KHZ_CLK16       inicializa_PWM1(1, 10, 1)   //

 */