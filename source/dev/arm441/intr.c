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
 
#include "override.h"
#include "csched.h"
#include "timertick.h"
#include "types.h"
#include "osapi.h"
#include "insmod.h"

#include "hardware.h"

/* INTERRUPT SETTING FOR ARM(SDT)*/

__irq void TIMER_interrupt(void) 
{
	__IntrCall_SystemTimer();
	TIMER_PENDING_CLEAR();	
}

__irq void USART0_RX_interrupt(void){
	while (UART0RxAvail()) {
		__IntrCall_Uart0(UART0GetRxByte());
	}
	UART0_PENDING_CLEAR();
}

void __TimerInit(void){
	
	TIMER_INIT();	
	pISR_T1MC=(unsigned)TIMER_interrupt;
	TIMER_START();
}

void __UartInit(void){
	
	UART0_SETTING();
	
	oStopHardware();
	
	pISR_URXD=(unsigned)USART0_RX_interrupt;			
	RX0_ENABLE_INTR(TRUE);
	
	oResumeHardware();

}

U16 __CalBaud(U32 baud){
	switch(baud) {
		case 2400:
			return 1041;
		case 9600:
			return 259;
		case 19200:
			return 129;
		case 38400:
			return 64;
		case 57600:
			return 42;
		case 115200:
			return 21;
		default:
			return 0;
	}
}

