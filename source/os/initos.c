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

#include "initos.h"
#include "timertick.h"
#include "reg.h"

void InitOS(SYSCBlk* sysblk){
	
	/*DRIVER INITIALIZATION */
	InitDrv(sysblk);

	/*MSG INITIALIZATION*/
	initMsg();
	
	/*OS INITIALIZATION*/
	oInit(sysblk);
	
	/*TASK CONTROL BLOCK INITIALIZATION*/
	TCB_Init(sysblk);

	/*CHECK REGISTER DEVICE DRIVER*/
	CheckReg();

	/*INITIALIZE USER TASK AND REGISTER IN OS*/
	taskschedInit(sysblk);

	/*FAST THREAD THREAD INITIALIZATION*/
	FTCB_Init(sysblk);

	/*SETTING SYSTEM TIMER*/
	TimeInit(sysblk);

#if KERNEL_INIT_VIEW == ENABLED
	xprintf("\nK>J-guider ver.0 ... Launching\n");
#endif

}

