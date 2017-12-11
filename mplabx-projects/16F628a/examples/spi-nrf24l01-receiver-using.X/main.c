/* 
 * File:   main.c
 * Author: Thiago Mallon
 *
 * Created on 6 de Janeiro de 2015, 07:40
 */

#include <xc.h>
#include "o-codestyle.h" /* arquivo de constantes, typedefs e macros,
                                    para tornar possível uma codificação mais
                                    próxima do AVR e ARM */

#pragma config FOSC = INTOSCIO
#pragma config MCLRE = ON
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config WDTE = OFF
#pragma config CPD = OFF
#pragma config CP = OFF
#pragma config LVP = OFF

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000UL
#endif

// definições pinos SPI
#define MOSI (1 << RB2)    //Serial Slave Input.
#define MISO (1 << RB7)    //Serial Slave Output.
#define CE (1 << RB5)    //Chip Enable. Ativa modo TX ou RX
#define CSN (1 << RB3)    //Chip Select Not. Seleciona o chip zero
#define SCK (1 << RB6)    //SPI Clock.
#define IRQ (1 << RB0)    //Interrupçao de saída. Ativo baixo

// definições nRF24L01
#define CHANNEL 107 // 1 a 126
#define ENDTX 75  // 1 a 255
#define ENDRX 75  // 1 a 255
#define BUFFER 1

// variáveis armazenam buffer de envio e recebimento
volatile uint8_t receivedData[BUFFER];

#define LED (1 << RA1)
#define LED_VRM (1 << RA0)

void spiPinsConfig(void); // configura pinos para a comunicação SPI
uint8_t spiTransmit(uint8_t data); // envia bits
void setUpNrf24l01(void);
void spiReceiveData(void);
void interruptConfig(void); // função habilita interrupção externa
void spiTest(void);

int main(void) {
    CMCON |= (0b111 << CM0); // pinos do PORTA como I/O
    spiPinsConfig(); // configura pinos que serão usados pelo SPI
    setUpNrf24l01(); // configura módulo para recepção
    TRISA &= ~(LED | LED_VRM); // define pinos como saída
    PORTA |= LED;
    PORTA &= ~LED_VRM; // atribui nível lógico baixo ao pino
    while (1) {
        // Para receber
        spiReceiveData();
        if (receivedData[0] > 125) {
            PORTA |= LED_VRM;
        } else if (receivedData[0] < 125) {
            PORTA &= ~LED_VRM;
        }
    }
    return 1;
}

/** função configura os pinos utilizados para o SPI */
void spiPinsConfig(void) {
    TRISB &= ~(SCK | MOSI | CSN | CE); // configura pinos como saída
    TRISB |= (MISO | IRQ); // configura pinos como entrada
    PORTB |= IRQ; // atribui nível lógico 1 ao pino IRQ (usado para interrupção externa)

    PORTB |= CSN; // CSN em nível lógico 1, slave em stand-by
    PORTB &= ~CE; // CE em nível lógico 0, nRF24l01 desligado
}

/** função envida dados pela SPI */
uint8_t spiTransmit(uint8_t data) {
    uint8_t i, temp = 0;
    for (i = 0; i < 8; i++) { // saída de 8 bits
        ((data & 0x80) == 0x80) ? PORTB |= MOSI : PORTB &= ~MOSI;
        data = (data << 1); // desloca próximo bita para MSB..
        temp <<= 1;
        PORTB |= SCK; // coloca SCK em nível lógico alto
        if (PORTB & (MISO)) temp |= 1; // capture current MISO bit
        PORTB &= ~SCK; // coloca nível lógico 0 no SCK, novamente
    }
    return temp;
}

void setUpNrf24l01(void) {
    //RX_ADDR_P0 - configura endereço de recepção PIPE0
    PORTB &= ~CSN;
    spiTransmit(0x2A);
    spiTransmit(ENDRX);
    spiTransmit(0xC2);
    spiTransmit(0xC2);
    spiTransmit(0xC2);
    spiTransmit(0xC2);
    PORTB |= CSN;

    //TX_ADDR - configura endereço de transmissão
    PORTB &= ~CSN;
    spiTransmit(0x30);
    spiTransmit(ENDTX);
    spiTransmit(0xC2);
    spiTransmit(0xC2);
    spiTransmit(0xC2);
    spiTransmit(0xC2);
    PORTB |= CSN;

    //EN_AA - habilita autoACK no PIPE0
    PORTB &= ~CSN;
    spiTransmit(0x21);
    spiTransmit(0x01);
    PORTB |= CSN;

    //EN_RXADDR - ativa o PIPE0
    PORTB &= ~CSN;
    spiTransmit(0x22);
    spiTransmit(0x01);
    PORTB |= CSN;

    //SETUP_AW - define o endereço com tamanho de 5 Bytes
    PORTB &= ~CSN;
    spiTransmit(0x23);
    spiTransmit(0x03);
    PORTB |= CSN;

    //SETUP_RETR - configura para nao retransmitir pacotes
    PORTB &= ~CSN;
    spiTransmit(0x24);
    spiTransmit(0x00);
    PORTB |= CSN;

    //RF_CH - define o canal do modulo (TX e RX devem ser iguais)
    PORTB &= ~CSN;
    spiTransmit(0x05);
    spiTransmit(CHANNEL);
    PORTB |= CSN;

    //RF_SETUP - ativa LNA, taxa em 250K, e maxima potencia 0dbm
    PORTB &= ~CSN;
    spiTransmit(0x26);
    spiTransmit(0b00100110);
    PORTB |= CSN;

    //STATUS - reseta o resgistrador STATUS
    PORTB &= ~CSN;
    spiTransmit(0x27);
    spiTransmit(0x70);
    PORTB |= CSN;

    //RX_PW_P0 - tamanho do buffer PIPE0
    PORTB &= ~CSN;
    spiTransmit(0x31);
    spiTransmit(10);
    PORTB |= CSN;

    //CONFIG - coloca em modo de recepção, e define CRC de 2 Bytes
    PORTB &= ~CSN;
    spiTransmit(0x20);
    spiTransmit(0x0F);
    PORTB |= CSN;

    //tempo para sair do modo standby entrar em modo de recepçao
    PORTB |= CE;
    _delay_us(10);
}

void spiReceiveData() {
    // STATUS - clear register
    PORTB &= ~CSN;
    spiTransmit(0x27);
    spiTransmit(0x70);
    PORTB |= CSN;

    //R_RX_PAYLOAD - receive data from FIFO RX buffer
    PORTB &= ~CSN;
    spiTransmit(0x61);
    for (uint8_t i = 0; i < BUFFER; i++) {
        receivedData[i] = spiTransmit(0xFF);
    }
    PORTB |= CSN;

    // LIMPA FLUSH_RX
    PORTB &= ~CSN;
    spiTransmit(0xE2);
    PORTB |= CSN;

    _delay_us(10);
}

/** função habilita interrupção externa, para que seja capturado recebimento completo no pino IRQ (RB0) */
void interruptConfig(void) {
    INTCON |= (1 << GIE); // habilita interrupções globais
    INTCON |= (1 << INTE); // habilita interrupção externa
}

/** Interrupt Service Routine (ISR) */
void interrupt ISR(void) {
    if (INTCON & (1 << INTF)) { // verifica se flag de interrupção externa está setada
        INTCON &= ~(1 << INTF); // limpa flag de interrupção externa
    }
}