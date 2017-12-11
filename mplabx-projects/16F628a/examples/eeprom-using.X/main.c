/* 
 * File:   main.c
 * Author: Thiago Mallon
 *
 * Created on 3 de Janeiro de 2015, 23:04
 */

#include <xc.h>

#pragma config FOSC = INTOSCIO // uso do oscilador interno, de 4Mhz
#pragma config MCLRE = ON // habilita MASTER CLEAR RESET
#pragma config PWRTE = ON // habilita POWER UP TIMER
#pragma config BOREN = ON // habilita BROWN OUT RESET
#pragma config WDTE = OFF // desabilita WATCH DOG TIMER
#pragma config LVP = OFF // desabilita LOW VOLTAGE PROGRAMM
#pragma config CPD = OFF // desabilita prote��o de c�digo da mem�ria EEPROM
#pragma config CP = OFF // desabilita prote��o de c�digo da mem�ria FLASH

#include "usart-mallon.h"

/** fun��o escreve dado na eeprom */
void eepromWrite(unsigned char address, unsigned char data) {
    EEDATA = data; // atribui dado � ser escrito, ao registrador - necess�rio escrever antes do endere�o - pode ir de 0x00 a 0x7F
    EEADR = address; // informa endere�o a ser escrito
    STATUSbits.RP0 = 1; // acessa banco de mem�ria 1
    EECON1bits.WREN = 1; // habilita escrita na eeprom
    INTCONbits.GIE = 0; // desabilite interrup��es globais - medida de seguran�a, conforma datasheet
    EECON2 = 0x55; // a��o requerida para habilitar escrita na eeprom, conforme datasheet
    EECON2 = 0xAA; // a��o requerida para habilitar escrita na eeprom, conforme datasheet
    EECON1bits.WR = 1; // inicia ciclo de escrita
    while (EECON1bits.WR); // espera t�rmino de qualquer poss�vel escrita � eeprom
    EECON1bits.WREN = 0; // desabilita escrita na eeprom - quest�o de seguran�a da mesma
    INTCONbits.GIE = 1; // reabilita interrup��es globais.
}

/** fun��o l� dado da eeprom */
char eepromRead(unsigned char address) {
    STATUSbits.RP0 = 1; // acessa banco de mem�ria 1
    EEADR = address; // informa endere�o que deve ser lido
    EECON1bits.RD = 1; // inicia ciclo de leitura    
    STATUSbits.RP0 = 0; // acessa banco de mem�ria 0
    return EEDATA; // retorna byte lido
}

int main(void) {
    usartInit(); // chama fun��o que inicializa a USART, no arquivo 'usart-mallon.h'
    eepromWrite(0x01, 'Y');
    eepromWrite(0x02, 'e');
    eepromWrite(0x03, 's');
    eepromWrite(0x04, 'h');
    eepromWrite(0x05, 'u');
    eepromWrite(0x06, 'a');
    eepromWrite(0x07, '!');
    eepromWrite(0x08, '\n'); // grava valores no endere�o de mem�ria setado, da eeprom
    while (1) {
        usartSend(eepromRead(0x01));
        usartSend(eepromRead(0x02));
        usartSend(eepromRead(0x03));
        usartSend(eepromRead(0x04));
        usartSend(eepromRead(0x05));
        usartSend(eepromRead(0x06));
        usartSend(eepromRead(0x07));
        usartSend(eepromRead(0x08)); // exibe valores que est�o gravados nos endere�os de mem�ria da eeprom
        __delay_ms(2000);
    }
    return 1;
}

