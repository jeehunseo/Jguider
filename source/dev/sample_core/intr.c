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

/* INTERRUPT SETTING EXAMPLE*/


/* ADD YOUR CODE THERE('__ADDED_INTERRUPT_DEFINE__') FOR TIMER INTERRUPT 
    'TIMER_interrupt' function is not completed because we don't know your compiler and cpu. 
    It is depending on your compiler and CPU core.
    You have to complete next function('Timer_interrupt()') before compiling.
    And you must added the code that can make timer-tick.*/
__ADDED_INTERRUPT_DEFINE__ TIMER_interrupt(void) 
{
	/* ADD YOUR CODE HERE FOR TIMER-TIC 
	   you have to use '__IntrCall_SystemTimer()' in this function.
	
	   ex) __IntrCall_SystemTimer();
	       TIMER_PENDING_CLEAR();
	*/
}


/* ADD YOUR CODE THERE('__ADDED_INTERRUPT_DEFINE__') FOR SERIAL RECEIVE INTERRUPT 
    'USART0_RX_interrupt' function is not completed because we don't know your compiler and cpu. 
    It is depending on your compiler and CPU core.
    You have to complete next function('USART0_RX_interrupt()') before compiling
    And you must added the code that can receive data which is from PC (or other device).*/
__ADDED_INTERRUPT_DEFINE__ USART0_RX_interrupt(void){
	
	/* ADD YOUR CODE HERE FOR RECEIVING SERIAL DATA
	   you have to use '__IntrCall_Uart0(UART0GetRxByte())' in this function. 
	
	   ex)  while (UART0RxAvail()) {
		      __IntrCall_Uart0(UART0GetRxByte());
	         }
              UART0_PENDING_CLEAR();
	*/
}

void __TimerInit(void){
	
	/* ADD YOUR CODE HERE FOR INITIALIZING TIMER-INTERRUPT
	   You have to write appropriated code in here.
	   This function is responsibled for starting 'TIMER_interrupt()' timer. 
	   If you make 1msec-timer tick in this function, 'TIMER_interrupt()' function will be called every 1mesc.
	     - initialize timer-count-register.
	     - set and activate timer-interrupt.
	   
	   ex)  TIMER_INIT();
	        pISR_T1MC=(unsigned)TIMER_interrupt;
	        TIMER_START();
	*/
}

void __UartInit(void){
	
	/* ADD YOUR CODE HERE FOR INITIALIZING SERIAL-INTERRUPT
	   This function is responsibled for starting 'USART0_RX_interrupt()'. 
	   You have to set appropriate serial-parameters.
	     - initialize serial parameter.
	     - activate serial-interrupt.
	     
	   ex)  UART0_SETTING();	
	        oStopHardware();
	        pISR_URXD=(unsigned)USART0_RX_interrupt;			
	        RX0_ENABLE_INTR(TRUE);
	        oResumeHardware();
	*/
	

}

U16 __CalBaud(U32 baud){
	/* ADD YOUR CODE HERE FOR BAUDRATE(SERIAL SPEED)
	   This function return the appropriate register value depending on Device's clock or CPU register.
	   
	   ex)  switch(baud) {
			case 2400:
				return 1041;
			case 9600:
				return 259;
			...
			case 115200:
				return 21;
			default:
				return 0;
		}
	*/
	
}

