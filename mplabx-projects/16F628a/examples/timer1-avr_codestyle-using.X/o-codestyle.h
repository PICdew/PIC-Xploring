/* 
 * File:   light-avr-codestyle.h
 * Author: Thiago Mallon
 *
 * Created on 6 de Janeiro de 2015, 13:40
 */

#ifndef LIGHT_AVR_CODESTYLE_H
#define	LIGHT_AVR_CODESTYLE_H

#define _delay_ms(x) (__delay_ms(x))

/** tipos de dados */
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed int int16_t;
typedef unsigned int uint16_t;
typedef signed long int int32_t;
typedef unsigned long int uint32_t;
typedef signed long long int int64_t;
typedef unsigned long long int uint64_t;

/** PORTA */
#define RA7 7
#define RA6 6
#define RA5 5
#define RA4 4
#define RA3 3
#define RA2 2
#define RA1 1
#define RA0 0

/** PORTB */
#define RB7 7
#define RB6 6
#define RB5 5
#define RB4 4
#define RB3 3
#define RB2 2
#define RB1 1
#define RB0 0

/** STATUS */
#define IRP 7
#define RP1 6
#define RP0 5
#define TO 4
#define PD 3
#define Z 2
#define DC 1
#define C 0

/** INTCON */
#define GIE 7
#define PEIE 6
#define T0IE 5
#define INTE 4
#define RBIE 3
#define T0IF 2
#define INTF 1
#define RBIF 0

/** PIR1 */
#define EEIF 7
#define CMIF 6
#define RCIF 5
#define TXIF 4
#define CCP1IF 2
#define TMR2IF 1
#define TMR1IF 0

/** T1CON */
#define T1CKPS1 5
#define T1CKPS0 4
#define T1OSCEN 3
#define T1SYNC 2
#define TMR1CS 1
#define TMR1ON 0

/** T2CON */
#define TOUTPS3 6
#define TOUTPS2 5
#define TOUTPS1 4
#define TOUTPS0 3
#define TMR2ON 2
#define T2CKPS1 1
#define T2CKPS0 0

/** RCSTA */
#define SPEN 7
#define RX9 6
#define SREN 5
#define CREN 4
#define ADEN 3
#define FERR 2
#define OERR 1
#define RX9D 0

/** CMCON */
#define C2OUT 7
#define C1OUT 6
#define C2INV 5
#define C1INV 4
#define CIS 3
#define CM2 2
#define CM1 1
#define CM0 0

/** OPTION */
#define RBPU 7
#define INTEDG 6
#define T0CS 5
#define T0SE 4
#define PSA 3
#define PS2 2
#define PS1 1
#define PS0 0

/** INTCON */
#define GIE 7
#define PEIE 6
#define T0IE 5
#define INTE 4
#define RBIE 3
#define T0IF 2
#define INTF 1
#define RBIF 0

/** PIE1 */
#define EEIE 7
#define CMIE 6
#define RCIE 5
#define TXIE 4
#define CCP1IE 2
#define TMR2IE 1
#define TMR1IE 0

/** PCON */
#define OSCF 3
#define POR 1
#define BOR 0

/** TXSTA */
#define CSRC 7
#define TX9 6
#define TXEN 5
#define SYNC 4
#define BRGH 2
#define TRMT 1
#define TX9D 0

/** EECON1 */
#define WRERR 3
#define WREN 2
#define WR 1
#define RD 0
/** VRCON */
#define VREN 7
#define VROE 6
#define VRR 5
#define VR3 3
#define VR2 2
#define VR1 1
#define VR0 0

/** CCP1CON */
#define CCP1X 5
#define CCP1Y 4
#define CCP1M3 3
#define CCP1M2 2
#define CCP1M1 1
#define CCP1M0 0

#endif	/* PIC16F628A_REGS_H */

