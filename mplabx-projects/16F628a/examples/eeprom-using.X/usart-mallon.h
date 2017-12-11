/* 
 * File:   usart-mallon.h
 * Author: Thiago Mallon
 *
 * Created on 4 de Janeiro de 2015, 19:43
 */

#ifndef USART_MALLON_H
#define	USART_MALLON_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000UL
#endif

#ifndef BAUD
#define BAUD 9600
#define BAUDRATE ((_XTAL_FREQ / (BAUD * 16UL)) -1)
#endif

    /** prot�tipos das fun��es que ser�o implementadas no arquivo */
    void usartInit(void); // fun��o inicializa a USART
    void usartSend(unsigned char data); // fun��o envia um char para a USART
    void usartPutString(unsigned char* dataPtr); // fun��o envia char's de ponteiro � USART

    /** fun��o inicializa a USART */
    void usartInit(void) {
        SPBRG = BAUDRATE; // informa valor do baudrate
        // configura transmiss�o
        TXSTAbits.BRGH = 1; // transmiss�o de alta velocidade
        TXSTAbits.SYNC = 0; // modo ass�ncrono
        TXSTAbits.TX9 = 0; // transmiss�o de 8 bits
        TXSTAbits.TXEN = 1; // habilita transmiss�o
        // configura recep��o
        RCSTAbits.ADEN = 0; // desabilita auto detec��o de endere�o
        RCSTAbits.RX9 = 0; // recep��o de 8 bits
        RCSTAbits.SPEN = 1; // habilita portas seriais, ou seja, habilita configura pinos RB2 e RB1 como portas seriais
        RCSTAbits.CREN = 1; // habilita recep��o
    }

    /** fun��o envia dados para o buffer de transmiss�o da USART */
    void usartSend(const unsigned char data) {
        while (!PIR1bits.TXIF); // verifica e permanece no loop se flag de envio de dados da USART est� setado, sinalizando que existem dados serem enviados
        TXREG = data; // atribui dado recebido por par�metro ao buffer de transmiss�o da USART
    }

    /** fun��o envia um a um, os caracteres de um array, para o buffer de transmiss�o da USART */
    void usartPutString(const char* dataPtr) {
        while (*dataPtr != '\0') {
            usartSend(*dataPtr);
            dataPtr++;
        }
    }


#ifdef	__cplusplus
}
#endif

#endif	/* USART_MALLON_H */

