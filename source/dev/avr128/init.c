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

#include "dev.h"
#include "override.h"
#include "types.h"
#include "buzzer.h"

#if WATCH_DOG == ENABLED
void InitWatchdog(void)
{
	__disable_interrupt();
/* start watchdog 2.1msec*/  

  	WDTCR = 0x18;
  	WDTCR = 0x0F;
	__enable_interrupt(); 	

	__watchdog_reset();

}
void RstWatchdog(void)
{
	__watchdog_reset();
}

#endif 

void InitPort(void)
{

#if WATCH_DOG == ENABLED
	InitWatchdog();
#endif
	DDRD = 0xF3;	
	DDRE = 0xEC;
	
	// led 1 4 on 
	PORTD &= ~(0x80);
	PORTE &= ~(0x04);
	// led all 
	PORTE &= ~(0x04);
	PORTD &= ~(0xE0) ;

	//StartBuzzer();
	
}

