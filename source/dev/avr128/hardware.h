/****************************************************************************
 *                                                JeeLab J-Guider ver Zero
 *--------------------------------------------------------------------------------------------------------*
 *
 *  - lisence -
 * 'JeeLab J-Guider' represents the best 'FREE Guider' for tiny microcomputer currently available on the market.
 * This code is 'FREE OF CHARGE' for non-commercial & individual developer only. Both of these conditions should be met!
 * If you are not a individual developer or if you want to use your computer for business purposes,
 * we offer a wide range of more suitable verison providing higher speed and more efficient processing.
 * If you use more infomation, contact us using e-mail or visit our site.
 *
 * e-mail: 
 *              info@jeelab.com
 *  
 * web site:    
 *               http://www.jeelab.com
 *               http://jeelab.tistory.com
 *
 ****************************************************************************/

#ifndef __HARDWARE_H
#define __HARDWARE_H

#include "osapi.h"
#include "intr.h"

#include <inavr.h>
#include <iom128.h>
#include <string.h>

/* SETTING FOR KERNEL ***************************************************************************
	: you have to connect your value depending on you hardware or compiler.
	  If you don't put on this, kernel is possible not to execute correctly.

	env: IAR compiler/ avr128(ATMEL)
	
*/

/* SYSTEM PARAMETER FOR AVR ************************************************************************/
// interrupt enable/ disable setting
#define oStopHardware()		__disable_interrupt() 
#define oResumeHardware()	__enable_interrupt() 

// main clock setting
#define CPU_CLOCK	14745600L
#define PRE_SCL		16	

/* SYSTEM TIME FOR AVR ************************************************************************/
// timer setting
#define TIMER_INIT()	TIMSK = 0x00;\
					TCNT0 = 0x00;\
					OCR0 = 0x72;\
					TCCR0 = 0x05;\
					TIMSK = 0x02
					
#define rTIMER_COUNT TCNT0
#define TIMER_COUNT_CLEAR()	rTIMER_COUNT = 0x00


/* UART FOR AVR *************************************************************************************/
#define UART_CALC_BAUD(b) ((( CPU_CLOCK / PRE_SCL ) / b ) - 1)

#define UART0_SETTING()	UCSR0B  |= ( 1<<TXEN0 );\
												UCSR0C  |= (3<<UCSZ00)

#define UART1_SETTING()	UCSR1B  |= (1<<TXCIE1 );\
												UCSR1C  |= (3<<UCSZ10) 

#define TX0_ENABLE_INTR(enable)	(enable == TRUE) ? (UCSR0B |= (1<<TXCIE0)) : (UCSR0B &= ~(1<<TXCIE0))
#define RX0_ENABLE_INTR(enable)	(enable == TRUE) ? (UCSR0B |= ( (1<<RXCIE0) |(1<<RXEN0) )) \
													: (UCSR0B &= ~( (1<<RXCIE0) | (1<<RXEN0) ))
#define TX1_ENABLE_INTR(enable) (enable == TRUE) ? (UCSR1B |= (1<<TXCIE1)) : (UCSR1B &= ~(1<<TXCIE1))
#define RX1_ENABLE_INTR(enable)	(enable == TRUE) ? (UCSR1B |= ( (1<<RXCIE1) |(1<<RXEN1) )) \
													: (UCSR1B &= ~( (1<<RXCIE1) | (1<<RXEN1) ))

#define UART0_SEND(aByte) while(!(UCSR0A & (1<<UDRE0)));\
													UDR0 = aByte
#define UART1_SEND(aByte)	while(!(UCSR1A & (1<<UDRE1)));\
													UDR1 = aByte

#define UART0_SET_BAUDRATE(value)	UBRR0H  = ( value >> 8 ) & 0xFF;	UBRR0L  = value & 0xFF
#define UART1_SET_BAUDRATE(value)	UBRR1H  = ( value >> 8 ) & 0xFF;	UBRR1L  = value & 0xFF
                            
#define UART0GetRxByte()		(UDR0)
#define UART0RxAvail()		(UCSR0A & 0x80)
#define UART0TxEmpty()		(UCSR0A & 0x20)
#define UART0TxShiftNotDone()	((UCSR0A & 0x40) == 0)

#define UART1GetRxByte()		(UDR1)
#define UART1RxAvail()			(UCSR1A & 0x80)
#define UART1TxEmpty()			(UCSR1A & 0x20)
#define UART1TxShiftNotDone()	((UCSR1A & 0x40) == 0)




/* DEVICE DRIVER FOR AVR ************************************************************************************/

/* COMMON FOR AVR DRV ------------------------------------------------------------------------------------*/
#define POUT 1// port direction: in / out
#define PIN 0
#define rEXTERNAL_INT_MASK EIMSK // 0000 0011 -> rising edge detect !


/* SONIC FOR AVR------------------------------------------------------------------------------------*/
#define SONIC_PORT_OPEN()	DDRE_Bit7  = 0;	PORTE_Bit7 = 1
#define rEXTERNAL_INT_MOD_B EICRB


/* MOTION SENSOR FOR AVR ------------------------------------------------------------------------------------*/
#define rEXTERNAL_INT_MOD EICRA // 0000 1110 -> INT0: falling edge detect & INT1: rising edge
#define MOTION_PORT_OPEN()	DDRD &= ~0x03;	PORTD |= 0x03 //portD 0,1


/* SERVO MOTOR FOR AVR ------------------------------------------------------------------------------------*/
/* FastPWM 10bit mode setting */
#define TIMER_MODE_ENABLE()	TCCR1A |= (1<<WGM11) | (1<<WGM10); TCCR1B |= (0<<WGM13) | (1<<WGM12)
#define TIMER_MODE_DISABLE()	TCCR1A = 0; TCCR1B = 0
/* prescaler 256-prescaler */
#define TIMER_PRESCALER()	TCCR1B |= (1<<CS12) | (0<<CS11) | (0<<CS10)

#define DUTY_RATE(a) OCR1A = a;
#define OUTPORT(a) DDRB_Bit5 = a
/* initialize timer register*/
#define TIMERVAL_INIT()	TCNT1H = 0x00; 	TCNT1L = 0x00
/* FastPWM mode inverting setting Channel A/B */
#define TIMER_OUT_SEL() TCCR1A |= (1<<COM1A1) | (0<<COM1A0) | (1<<COM1B1) | (0<<COM1B0)


#endif
