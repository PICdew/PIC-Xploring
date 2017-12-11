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
#pragma config CPD = OFF // desabilita proteção de código para EEPROM
#pragma config CP = OFF // desabilita proteção de código para FLASH

#define _XTAL_FREQ 4000000UL
#define BAUD 9600
#define BAUDRATE ((_XTAL_FREQ / (BAUD * 16UL)) -1)

void usartInit() {
    SPBRG = BAUDRATE;

    //TXSTA
    TXSTAbits.TX9 = 0; //8 bit transmission
    TXSTAbits.TXEN = 1; //Transmit enable
    TXSTAbits.SYNC = 0; //Async mode
    TXSTAbits.BRGH = 1; //High speed baud rate

    //RCSTA
    RCSTAbits.SPEN = 1; //Serial port enabled
    RCSTAbits.RX9 = 0; //8 bit mode
    RCSTAbits.CREN = 1; //Enable receive
    RCSTAbits.ADDEN = 0; //Disable address detection
}

void usartSend(char data) {
    while (!PIR1bits.TXIF);
    TXREG = data;
}

void usartPutString(const char *strPtr) {
    while (*strPtr != '\0') {
        usartSend(*strPtr);
        strPtr++;
    }
}

int main(void) {
    usartInit();
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    while (1) {
        usartPutString("Testando a USART no PIC16F628A.\n");
        __delay_ms(500);
    }
    return 1;
}