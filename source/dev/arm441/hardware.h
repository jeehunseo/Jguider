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

#include "s3f44xfx.h"
#include "osapi.h"

//#define MCLK_FREQ       (58982400)
//#define EXTCLK_FREQ     (58982400)

//#define DELAY_START_VAL         1000            //for external ROM

#define _RAM_STARTADDRESS 0x40000  
#define _ISR_STARTADDRESS 0x1ff1f80


/* SETTING FOR KERNEL ***************************************************************************
	: you have to connect your value depending on you hardware or compiler.
	  If you don't put on this, kernel is possible not to execute correctly.

	env: SDT compiler/ s3f44xfx(ARM)
	
*/

// interrupt enable/ disable setting
#define oStopHardware()	rSYSCON&=~0x100
#define oResumeHardware()	rSYSCON|=0x100

// main clock setting
#define CPU_CLOCK	40000000L // 40MHz.

// timer setting
#define TIMER_INIT()	rT1PRE  = (200-1); rT1DATA = (300-1); rT1CON  = 0xC0
					
#define TIMER_PENDING_CLEAR()	rINTPEND=~BIT_T1MC
#define TIMER_START()	rINTMASK|=BIT_T1MC

#define rTIMER_COUNT rT1CNT
#define TIMER_COUNT_CLEAR()	rTIMER_COUNT = 0x00

/*************************************************************************************************/


/* UART FOR ARM *************************************************************************************/

#define UART0_SETTING()	rUCON=0x0; \
						rLCON=0x43;\
						rUCON=0x09

#define UART0_PENDING_CLEAR()	rINTPEND=~BIT_URXD


#define TX0_ENABLE_INTR(enable)	(enable == TRUE) ? (rINTMASK |= BIT_UTXD) : (rINTMASK &= ~BIT_UTXD)
#define RX0_ENABLE_INTR(enable)	(enable == TRUE) ? (rINTMASK |= BIT_URXD) : (rINTMASK &= ~BIT_URXD)

#define UART0_SEND(aByte)	while(!(rUSSR & 0x40)); \
													rTBR=(unsigned char)aByte;\
													while(!(rUSSR & 0x80))

#define UART0_SET_BAUDRATE(value)	rUBRDR = value

#define UART0GetRxByte()		(rRBR)
#define UART0RxAvail()			(rUSSR & 0x20)
#define UART0TxEmpty()			(rUSSR & 0x40)


// ARM 441/443 have only one Uart channel
#define UART1_SETTING()	(void)0
#define UART1_PENDING_CLEAR()	(void)0
#define TX1_ENABLE_INTR(enable)	(void)0
#define RX1_ENABLE_INTR(enable)	(void)0
#define UART1_SEND(aByte)	(void)0
#define UART1_SET_BAUDRATE(value)	(void)0
#define UART1GetRxByte()	(void)0
#define UART1RxAvail()	(void)0
#define UART1TxEmpty()	(void)0

#endif
