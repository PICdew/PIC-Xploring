/* 
 * File:   arm-codestyle.h
 * Author: Thiago Mallon
 *
 * Created on 8 de Janeiro de 2015, 21:02
 */

#ifndef ARM_CODESTYLE_18F4550_H
#define	ARM_CODESTYLE_18F4550_H

#ifdef	__cplusplus
extern "C" {
#endif

#define _delay_ms(x) (__delay_ms(x))
#define _delay_us(x) (__delay_us(x))

    /** tipos de dados */
    typedef signed char int8_t;
    typedef unsigned char uint8_t;
    typedef signed int int16_t;
    typedef unsigned int uint16_t;
    typedef signed long int int32_t;
    typedef unsigned long int uint32_t;
    typedef signed long long int int64_t;
    typedef unsigned long long int uint64_t;

    //STKPTR
#define STKFUL 7
#define STKUNF 6
#define SP4 4
#define SP3 3
#define SP2 2
#define SP1 1
#define SP0 0

    //INTCON 
#define GIE 7
#define GIEH 7
#define PEIE 6
#define GIEL 6
#define TMR0IE 5
#define INT0IE 4
#define RBIE 3
#define TMR0IF 2
#define INT0IF 1
#define RBIF 0

    //INTCON2 
#define RBPU 7
#define INTEDG0 6
#define INTEDG1 5
#define INTEDG2 4
#define TMR0IP 2
#define RBIP 0

    // INTCON3
#define INT2IP 7
#define INT1IP 6
#define INT2IE 4
#define INT1IE 3
#define INT2IF 1
#define INT1IF 0

    // STATUS
#define N 4
#define OV 3
#define Z 2
#define DC 1
#define C 0

    // T0CON
#define TMR0ON 7
#define T08BIT 6
#define T0CS 5
#define T0SE 4
#define PSA 3
#define T0PS2 2
#define T0PS1 1
#define T0PS0 0

    // OSCCON
#define IDLEN 7
#define IRCF2 6
#define IRCF1 5
#define IRCF0 4
#define OSTS 3
#define IOFS 2
#define SCS1 1
#define SCS0 0

    // HLVDCON
#define VDIRMAG 7
#define IRVST 5
#define HLVDEN 4
#define HLVDL3 3
#define HLVDL2 2
#define HLVDL1 1
#define HLVDL0 0

    // WDTCON
#define SWDTEN 0

    // RCON
#define IPEN 7
#define SBOREN 6
#define RI 4
#define TO 3
#define PD 2
#define POR 1
#define BOR 0

    // T1CON
#define RD16 7
#define T1RUN 6
#define T1CKPS1 5
#define T1CKPS0 4
#define T1OSCEN 3
#define T1SYNC 2
#define TMR1CS 1
#define TMR1ON 0

    // T2CON
#define T2OUTPS3 6
#define T2OUTPS2 5
#define T2OUTPS1 4
#define T2OUTPS0 3
#define TMR2ON 2
#define T2CKPS1 1
#define T2CKPS0 0

    // SSPSTAT
#define SMP 7
#define CKE 6
#define DA 5
#define P 4
#define S 3
#define RW 2
#define UA 1
#define BF 0

    // SSPCON1
#define WCOL 7
#define SSPOV 6
#define SSPEN 5
#define CKP 4
#define SSPM3 3
#define SSPM2 2
#define SSPM1 1
#define SSPM0 0

    // SSPCON2
#define GCEN 7
#define ACKSTAT 6
#define  ACKDT 5
#define ADMSK5 5
#define ACKEN 4
#define ADMSK4 4
#define RCEN 3
#define ADMSK3 3
#define PEN 2
#define ADMSK2 2
#define RSEN 1
#define ADMSK1 1
#define SEN 0

    // ADCON0
#define CHS3 5
#define CHS2 4
#define CHS1 3
#define CHS0 2
#define GODONE 1
#define ADON 0

    // ADCON1
#define VCFG1 5
#define VCFG0 4
#define PCFG3 3
#define PCFG2 2
#define PCFG1 1
#define PCFG0 0

    // ADCON2
#define ADFM 7
#define ACQT2 5
#define ACQT1 4
#define ACQT0 3
#define ADCS2 2
#define ADCS1 1
#define ADCS0 0

    // CCP1CON
#define P1M1 7
#define P1M0 6
#define DC1B1 5
#define DC1B0 4
#define CCP1M3 3
#define CCP1M2 2
#define CCP1M1 1
#define CCP1M0 0

    // CCP2CON
#define DC2B1 5
#define DC2B0 4
#define CCP2M3 3
#define CCP2M2 2
#define CCP2M1 1
#define CCP2M0 0

    // BAUDCON
#define ABDOVF 7
#define RCIDL 6
#define RXDTP 5
#define TXCKP 4
#define BRG16 3
#define WUE 1
#define ABDEN0 0

    // ECCP1DEL
#define PRSEN 7
#define PDC6 6
#define PDC5 5
#define PDC4 4
#define PDC3 3
#define PDC2 2
#define PDC1 1
#define PDC0 0

    // ECCP1AS
#define ECCPASE 7
#define ECCPAS2 6
#define ECCPAS1 5
#define ECCPAS0 4
#define PSSAC1 3
#define PSSAC0 2
#define PSSBD1 1
#define PSSBD0 0

    // CVRCON
#define CVREN 7
#define CVROE 6
#define CVRR 5
#define CVRSS 4
#define CVR3 3
#define CVR2 2
#define CVR1 1
#define CVR0 0

    // CMCON
#define C2OUT 7
#define C1OUT 6
#define C2INV 5
#define C1INV 4
#define CIS 3
#define CM2 2
#define CM1 1
#define CM0 0

    // T3CON
#define RD16 7
#define T3CCP2 6
#define T3CKPS1 5
#define T3CKPS0 4
#define T3CCP1 3
#define T3SYNC 2
#define TMR3CS 1
#define TMR3ON 0

    // TXSTA
#define CSRC 7
#define TX9 6
#define TXEN 5
#define SYNC 4
#define SENDB 3
#define BRGH 2
#define TRMT 1
#define TX9D 0

    // RCSTA
#define SPEN 7
#define RX9 6
#define SREN 5
#define CREN 4
#define ADDEN 3
#define FERR 2
#define OERR 1
#define RX9D 0

    // EECON1
#define EEPGD 7
#define CFGS 6
#define FREE 4
#define WRERR 3
#define WREN 2
#define WR 1
#define RD 0

    // IPR2
#define OSCFIP 7
#define CMIP 6
#define USBIP 5
#define EEIP 4
#define BCLIP 3
#define HLVDIP 2
#define TMR3IP 1
#define CCP2IP 0

    // PIR2
#define OSCFIF 7
#define CMIF 6
#define USBIF 5
#define EEIF 4
#define BCLIF 3
#define HLVDIF 2
#define TMR3IF 1
#define CCP2IF 0

    // PIE2
#define OSCFIE 7
#define CMIE 6
#define USBIE 5
#define EEIE 4
#define BCLIE 3
#define HLVDIE 2
#define TMR3IE 1
#define CCP2IE 0

    // IPR1
#define SPPIP 7
#define ADIP 6
#define RCIP 5
#define TXIP 4
#define SSPIP 3
#define CCP1IP 2
#define TMR2IP 1
#define TMR1IP 0

    // PIR1
#define SPPIF 7
#define ADIF 6
#define RCIF 5
#define TXIF 4
#define SSPIF 3
#define CCP1IF 2
#define TMR2IF 1
#define TMR1IF 0

    // PIE1
#define SPPIE 7
#define ADIE 6
#define RCIE 5
#define TXIE 4
#define SSPIE 3
#define CCP1IE 2
#define TMR2IE 1
#define TMR1IE 0

    // OSCTUNE 
#define INTSRC 7
#define TUN4 4
#define TUN3 3
#define TUN2 2
#define TUN1 1
#define TUN0 0

    // PORTA
#define RA6 6
#define RA5 5
#define RA4 4
#define RA3 3
#define RA2 2
#define RA1 1
#define RA0 0

    // PORTB
#define RB7 7
#define RB6 6
#define RB5 5
#define RB4 4
#define RB3 3
#define RB2 2
#define RB1 1
#define RB0 0

    // PORTC
#define RC7 7
#define RC6 6
#define RC5 5
#define RC4 4
#define RC2 2
#define RC1 1
#define RC0 0

    // PORTD
#define RD7 7
#define RD6 6
#define RD5 5
#define RD4 4
#define RD3 3
#define RD2 2
#define RD1 1
#define RD0 0

    // PORTE
#define RDPU 7
#define RE3 3
#define RE2 2
#define RE1 1
#define RE0 0

    // LATA
#define LATA6 6
#define LATA5 5
#define LATA4 4
#define LATA3 3
#define LATA2 2
#define LATA1 1
#define LATA0 0

    // LATB
#define LATB7 7
#define LATB6 6
#define LATB5 5
#define LATB4 4
#define LATB3 3
#define LATB2 2
#define LATB1 1
#define LATB0 0

    // LATC
#define LATC7 7
#define LATC6 6
#define LATC2 2
#define LATC1 1
#define LATC0 0

    // LATD
#define LATD7 7
#define LATD6 6
#define LATD5 5
#define LATD4 4
#define LATD3 3
#define LATD2 2
#define LATD1 1
#define LATD0 0

    // LATE
#define LATE2 2
#define LATE1 1
#define LATE0 0

    // UCFG
#define UTEYE 7
#define UOEMON 6
#define UPUEN 4
#define UTRDIS 3
#define FSEN 2
#define PPB1 1
#define PPB0 0

    // UADDR
#define ADDR6 6
#define ADDR5 5
#define ADDR4 4
#define ADDR3 3
#define ADDR2 2
#define ADDR1 1
#define ADDR0 0

    // UCON
#define PPBRST 6
#define SE0 5
#define PKTDIS 4
#define USBEN 3
#define RESUME 2
#define SUSPND 1

    // USTAT
#define ENDP3 6
#define ENDP2 5
#define ENDP1 4
#define ENDP0 3
#define DIR 2
#define PPBI 1

    // UEIE
#define BTSEE 7
#define BTOEE 4
#define DFN8EE 3
#define CRC16EE 2
#define CRC5EE 1
#define PIDEE 0

    // UEIR
#define BTSEF 7
#define BTOEF 4
#define DFN8EF 3
#define CRC16EF 2
#define CRC5EF 1
#define PIDEF 0

    // UIE
#define SOFIE 6
#define STALLIE 5
#define IDLEIE 4
#define TRNIE 3
#define ACTVIE 2
#define UERRIE 1
#define URSTIE 0

    // UIR
#define SOFIF 6
#define STALLIF 5
#define IDLEIF 4
#define TRNIF 3
#define ACTVIF 2
#define UERRIF 1
#define URSTIF 0

    // UFRMH
#define FRM10 2
#define FRM9 1
#define FRM8 0

    // UFRML
#define FRM7 7
#define FRM6 6
#define FRM5 5
#define FRM4 4
#define FRM3 3
#define FRM2 2
#define FRM1 1
#define FRM0 0

    // SPPCON
#define SPPOWN 1
#define SPPEN 0

    // SPPEPS
#define RDSPP 7
#define WRSPP 6
#define SPPBUSY 4
#define ADDR3 3
#define ADDR2 2
#define ADDR1 1
#define ADDR0 0

    // SPPCFG
#define CLKCFG1 7
#define CLKCFG0 6
#define CSEN 5
#define CLK1EN 4
#define WS3 3
#define WS2 2
#define WS1 1
#define WS0 0

    // SPPDATA
#define DATA7 7
#define DATA6 6
#define DATA5 5
#define DATA4 4
#define DATA3 3
#define DATA2 2
#define DATA1 1
#define DATA0 0

#ifdef	__cplusplus
}
#endif

#endif	/* ARM_CODESTYLE_H */

