/* 
 * File:   main.c
 * Author: Thiago Mallon
 *
 * Created on 6 de Janeiro de 2015, 14:22
 */

#include <xc.h>
#include "light-avr-codestyle.h" /** GRA�AS AS CONSTANTES, MACROS E TYPEDEFS DECLARADAS NO ARQUIVO, POSSO CODIFICAR O PIC DE UMA FORMA MAIS PARECIDA
                             COM A DO AVR */

#pragma config FOSC = INTOSCIO // utiliza oscilador interno, de 4Mhz
#pragma config MCLRE = ON // habilita o MASTER CLEAR RESET
#pragma config PWRTE = ON // habilita o POWER UP TIMER
#pragma config BOREN = ON // habilita o BROWN OUT RESET
#pragma config WDTE = OFF // desabilita o WATCH DOG TIMER
#pragma config CPD = OFF // desabilita prote��o de c�digo da mem�ria EEPROM
#pragma config CP = OFF // desabilita prote��o de c�digo da mem�ria FLASH
#pragma config LVP = OFF // desabilita LOW VOLTAGE PROGRAM

/** defini��es da USART */
#define _XTAL_FREQ 4000000UL // informa a frequ�ncia do oscilador
#define BAUD 9600 // define o valor de BAUDRATE desejado
#define BAUDRATE ((_XTAL_FREQ / (BAUD * 16UL)) -1) // faz c�lculo do valor do BAUDRATE

/** defini��es dos LEDS */
#define LED_AZUL (1 << RA0)
#define LED_VERDE (1 << RA7)
#define LED_VERMELHO (1 << RA1)

/** defini��o do bot�o */
#define BUTTON (1 << RB3)

/** propriedades */
static uint16_t timerCounter = 0; // vari�vel em que � armazenado valor a ser comparado com o par�metro passado � fun��o setInterval(uint16_t time);
static uint8_t tmr1High = 0xFF;
static uint8_t tmr1Low = 0x83; // valor a ser atribu�do ao timer1, para que seja gerado delay de 1ms

/** prot�tipos das fun��es que ser�o implementadas no arquivo */
void usartInit(void); // fun��o inicializa a USART
void usartSend(unsigned char data); // fun��o envia um char para a USART
void usartPutString(unsigned char* dataPtr); // fun��o envia char's de ponteiro � USART
void usartPutStringConst(const unsigned char* dataPtr); // imprime string const
void timer1Init(void); // fun��o configura e inicializa timer1
void setTimeOut(uint16_t time); // fun��o implementa intervalo de tempo em milisegundos
void ledsConfig(void); // fun��o configura pinos de leds
void ledsEnviando(void); // configura os leds para luz de enviando mensagem
void ledsEnviado(void); // configura os leds para luz de mensagem enviada
void ledsStandBy(void); // configura os leds para luz de stand-by
void pullUpConfig(void); // habilita pullup

int main(void) {
    CMCON |= (1 << CM2 | 1 << CM1 | 1 << CM0); // pinos do PORTA como I/O
    usartInit(); // inicializa a USART
    timer1Init(); // inicializa o TIMER1
    ledsConfig(); // configura pinos de LED
    pullUpConfig(); // habilita pull-up
    while (1) {
        if (!(PORTB & (BUTTON))) { // verifica se o bot�o foi clicado
            setTimeOut(20); // chama fun��o passando o valor de 20ms de intervalo
            ledsEnviando();
            usartPutStringConst("Tu cujo nome � Jeov�, somente Tu �s o Altissimo sobre toda a terra.\n"); // envia mensagem para a USART
            setTimeOut(200);
            ledsEnviado();
            setTimeOut(200);
            ledsStandBy(); // configura os leds para luz de stand-by
        }
        setTimeOut(200); // chama fun��o passando o valor de 200ms de intervalo
    }
    return 1;
}

/** fun��o inicializa a USART */
void usartInit(void) {
    SPBRG = BAUDRATE; // informa valor do baudrate
    // configura transmiss�o
    TXSTA |= (1 << BRGH | 1 << TXEN); // transmiss�o de alta velocidade - habilita transmiss�o
    TXSTA &= ~(1 << SYNC | 1 << TX9); // modo ass�ncrono - transmiss�o de 8 bits

    // configura recep��o
    RCSTA &= ~(1 << ADEN | 1 << RX9); // desabilita auto detec��o de endere�o - recep��o de 8 bits
    RCSTA |= (1 << SPEN | 1 << CREN); // habilita portas seriais, ou seja, habilita configura pinos RB2 e RB1 como portas seriais - habilita recep��o
}

/** fun��o envia dados para o buffer de transmiss�o da USART */
void usartSend(uint8_t data) {
    while (!(PIR1 & (1 << TXIF))); // verifica e permanece no loop se flag de envio de dados da USART est� setado, sinalizando que existem dados serem enviados
    TXREG = data; // atribui dado recebido por par�metro ao buffer de transmiss�o da USART
}

/** fun��o envia valores das posi��es de mem�ria de um ponteiro */
void usartPutStringConst(const char *dataPtr) {
    while (*dataPtr != '\0') {
        usartSend(*dataPtr);
        dataPtr++;
    }
}

/** fun��o configura e inicializa timer1 */
void timer1Init(void) {
    PCON |= (1 << OSCF); // oscilador interno de 4Mhz - j� est� configurado por padr�o - escrito para deixar expl�cia a configura��o
    T1CON &= ~(1 << TMR1CS); // seleciona oscilador interno
    PIR1 &= ~(1 << TMR1IF); // limpa flag de interrup��o do timer 1
    PIE1 |= (1 << TMR1IE); // habilita interrup��o por estouro no timer1
    TMR1H = tmr1High;
    TMR1L = tmr1Low;
    T1CON |= (1 << T1CKPS1 | 1 << T1CKPS0 | 1 << T1SYNC); // atribui prescaler de 1:8; seleciona modo ass�ncrono
    INTCON |= (1 << GIE); // habilita interrup��es globais
    INTCON |= (1 << PEIE); // habilita interup��es de perif�ricos     
}

/** fun��o implementa intervalo em milisegundos com base no valor passado via par�metro */
void setTimeOut(uint16_t interval) {
    T1CON |= (1 << TMR1ON); // inicializa timer1
    TMR1H = tmr1High;
    TMR1L = tmr1Low; // atribui valor ao timer1
    timerCounter = 0; // zera timerCounter
    T1CON |= (1 << TMR1ON); // inicializa timer 1
    while (timerCounter < interval); // espera timerCounter atingir valor da vari�vel interval;
    T1CON &= ~(1 << TMR1ON); // desliga timer 1
    PIR1 &= ~(1 << TMR1IF); // limpa flag de interrup��o do timer1
}

/** fun��o configura os pinos de led */
void ledsConfig(void) {
    TRISA &= ~(LED_VERDE | LED_AZUL | LED_VERMELHO); // configura pinos como sa�da
    PORTA &= ~(LED_VERDE | LED_VERMELHO); // atribui n�vel l�gico 0 aos pinos
    PORTA |= LED_AZUL; // atribui n�vel l�gico 1 ao pino
}

/** configura leds para luz de enviando mensagem */
void ledsEnviando(void) {
    PORTA &= ~(LED_VERDE | LED_AZUL); // atribui n�vel l�gico 0 aos pinos
    PORTA |= LED_VERMELHO; // atribui n�vel l�gico 1 ao pino
}

/** configura leds para luz de enviado */
void ledsEnviado(void) {
    PORTA &= ~(LED_VERMELHO | LED_AZUL); // atribui n�vel l�gico 0 aos pinos
    PORTA |= LED_VERDE; // atribui n�vel l�gico 1 ao pino
}

/** configura leds para luz de stand-by */
void ledsStandBy(void) {
    PORTA &= ~(LED_VERDE | LED_VERMELHO); // atribui n�vel l�gico 0 aos pinos
    PORTA |= LED_AZUL; // atribui n�vel l�gico 1 ao pino
}

/** habilita e configura pull-up */
void pullUpConfig(void) {
    OPTION_REG &= ~(1 << RBPU); // habilita pullups no PORTB
    TRISB |= BUTTON; // configura pino como sa�da
    PORTB |= BUTTON; // atribui n�vel l�gico 1 ao pino
}

/** fun��o de interrup��o - INTERRUPT SERVICE ROUTINE */
void interrupt ISR(void) {
    if (PIR1 & (1 << TMR1IF)) { // verifica se flag de interrup��o do timer1 est� setada
        PIR1 &= ~(1 << TMR1IF); // limpa flag de interrup��o do timer1
        TMR1H = tmr1High;
        TMR1L = tmr1Low; // reatribui valor ao timer1
        timerCounter++; // incrementa timerCounter;
    }
}