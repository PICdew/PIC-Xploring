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

    /** protótipos das funções que serão implementadas no arquivo */
    void usartInit(void); // função inicializa a USART
    void usartSend(unsigned char data); // função envia um char para a USART
    void usartPutString(unsigned char* dataPtr); // função envia char's de ponteiro à USART

    /** função inicializa a USART */
    void usartInit(void) {
        SPBRG = BAUDRATE; // informa valor do baudrate
        // configura transmissão
        TXSTAbits.BRGH = 1; // transmissão de alta velocidade
        TXSTAbits.SYNC = 0; // modo assíncrono
        TXSTAbits.TX9 = 0; // transmissão de 8 bits
        TXSTAbits.TXEN = 1; // habilita transmissão
        // configura recepção
        RCSTAbits.ADEN = 0; // desabilita auto detecção de endereço
        RCSTAbits.RX9 = 0; // recepção de 8 bits
        RCSTAbits.SPEN = 1; // habilita portas seriais, ou seja, habilita configura pinos RB2 e RB1 como portas seriais
        RCSTAbits.CREN = 1; // habilita recepção
    }

    /** função envia dados para o buffer de transmissão da USART */
    void usartSend(const unsigned char data) {
        while (!PIR1bits.TXIF); // verifica e permanece no loop se flag de envio de dados da USART está setado, sinalizando que existem dados serem enviados
        TXREG = data; // atribui dado recebido por parâmetro ao buffer de transmissão da USART
    }

    /** função envia um a um, os caracteres de um array, para o buffer de transmissão da USART */
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

