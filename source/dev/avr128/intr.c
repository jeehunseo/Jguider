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
 
#include "csched.h"
#include "timertick.h"
#include "types.h"
#include "osapi.h"
#include "insmod.h"


/* INTERRUPT SETTING FOR AVR(IAR)*/

#pragma vector=TIMER0_COMP_vect
__interrupt void TIMER0_COMP_interrupt(void) 
{
	TIMER_COUNT_CLEAR();
	__IntrCall_SystemTimer();
	
}

#pragma vector = USART0_RXC_vect
__interrupt void USART0_RXC_interrupt(void){

	while (UART0RxAvail()) {
		__IntrCall_Uart0(UART0GetRxByte());
	}
}

void __TimerInit(void){
	
	TIMER_INIT();

}

void __UartInit(void){
	
	UART0_SETTING();
	
}

U16 __CalBaud(U32 baud){
	return (UART_CALC_BAUD(baud));
}


