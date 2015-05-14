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
#include "timelist.h"
#include "uart.h"
#include "timertick.h"
#include "tcblist.h"

/*common Scheduler*/
void SystemSched(SYSCBlk* sysblk){
	U8 ret;

	Fast_processor(sysblk);

	ret = TickTocSynchRtime(sysblk);

	CalYMDs(sysblk,ret);

	Time_Process();
	Uart_Process();

}


