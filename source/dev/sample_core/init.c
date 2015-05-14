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

#if WATCH_DOG == ENABLED
void InitWatchdog(void)
{
	/* ADD YOUR CODE HERE FOR WATCHDOG-INITIALIZATION */
}
void RstWatchdog(void)
{
	/* ADD YOUR CODE HERE FOR WATCHDOG-RESET */
	
}

#endif 

void InitPort(void)
{
	/* ADD YOUR CODE HERE FOR PORT-INITIALIZATION 
	   This function is responsibled for initializing device-port and registers.
	   
	   ex)  rP0CON=0xff;	
	         rP0PUR=0x00;	
      	   rP0 = 0x78;
		   rEINTMOD = (1<<5)+(1<<4)+(0<<3)+(1<<2)+(0<<1)+(1<<0);
		   rEINTCON = (1<<2)+(0<<1)+(1<<0);
	*/

	InitWatchdog();
}

