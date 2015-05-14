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

/* SETTING FOR KERNEL ***************************************************************************
	: you have to connect your value depending on you hardware or compiler.
	  If you don't put on this, kernel is possible not to execute correctly.
	
*/

/* SYSTEM PARAMETER ************************************************************************/
// interrupt enable/ disable setting
#define oStopHardware()  // ADD YOUR CODE HERE FOR STOPPING ALL INTERRPUT (OR DESIGNATED INTERRPUT).
#define oResumeHardware() // ADD YOUR CODE HERE FOR STARTING ALL INTERRPUT (OR DESIGNATED INTERRPUT).

// main clock setting
#define CPU_CLOCK	// ADD YOUR CODE HERE FOR CALCULATE SERIAL BAUDRATE OR OTHER DEVICE.


/* SYSTEM TIME ************************************************************************/
// timer setting
#define TIMER_INIT()	// ADD YOUR CODE HERE FOR INITIALIZING SYSTEM-TIMER.
#define TIMER_PENDING_CLEAR()	// ADD YOUR CODE HERE FOR CLEARING PENDING_BIT OF TIMER_INTERRUPT.
#define TIMER_START()	// ADD YOUR CODE HERE FOR STARTING TIMER_INTERRUPT PROCESS.

#define rTIMER_COUNT // ADD YOUR CODE HERE FOR THE ADDRESS OF 'TIMER_COUNT_REGISTER'.
#define TIMER_COUNT_CLEAR()	rTIMER_COUNT = 0x00


/* SRIAL SETTING *************************************************************************************/

#define UART0_SETTING()	// ADD YOUR CODE HERE FOR SETTING SERIAL VALUE.
#define UART0_PENDING_CLEAR()	// ADD YOUR CODE HERE FOR CLEARING PENDING_BIT OF SERIAL_INTERRUPT.

#define TX0_ENABLE_INTR(enable)	// ADD YOUR CODE HERE FOR SERIAL_TX_INTERRUPT.
#define RX0_ENABLE_INTR(enable)	// ADD YOUR CODE HERE FOR SERIAL_RX_INTERRUPT.

#define UART0_SEND(aByte)	// ADD YOUR CODE HERE FOR SENDING YOUR DATA('aByte') TO PC (OR OTHER DEVICE).

#define UART0_SET_BAUDRATE(value) // ADD	YOUR REGISTER-ADDRESS HERE TO SET APPROPRATE VALE('value'). 

#define UART0GetRxByte()		// ADD YOUR REGISTER-ADDRESS HERE TO GET RX_DATA FROM PC(OR OTHER DEVICE).
#define UART0RxAvail()		// ADD YOUR CODE IN ORDER TO KNOW WHETHER RECEVICE PROCESS IS READ FOR GETTING NEXT VALUE.
                                       // True: It is ready to get data
                                       // False: Not yet.
                                       // ex) (rUSSR & 0x20)

#define UART0TxEmpty()		// ADD YOUR CODE IN ORDER TO KNOW WHETHER SEND PROCESS IS READ FOR SENDING NEXT VALUE.
                                       // True: It is ready to send data
                                       // False: Not yet.
                                       // ex) (rUSSR & 0x40)

// double uart setting 
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
