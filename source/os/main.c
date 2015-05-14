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
#include "reg.h"


/*SYSTEM MEMORY BLOCK INITIALIZATION*/
void InitSysBlk(SYSCBlk* sysblk);

/*MAIN*/
void main(void){
	/*THE STRUCTURE OF SYSTEM CONTROL BLOCK*/
	SYSCBlk SysCtrlBlk;
	
	
	/*HDWARE INITIALIZATION*/	
	InitPort();

	/*INITIALIZE SYSTEM BLOCK*/
	InitSysBlk(&SysCtrlBlk);
	
	/*SOFTWARE INITIALIZATION*/
	InitOS(&SysCtrlBlk);

	/*TASK THREAD START & LOOP*/
	while(1){

		/*SCHEDLUE FOR USER TASK*/
		Tasksched(&SysCtrlBlk);

		/*SCHEDULE FOR COMMON(SYSTEM) TASK*/ 
		SystemSched(&SysCtrlBlk); 

		/*RESET WATCHDOG*/
		RstWatchdog();

	}

}

void InitSysBlk(SYSCBlk* sysblk){
	/*INITALIZE SYSTEM BLOCK*/
	sysblk->reset = FALSE;
	oMemSet((U8*)sysblk,0x00, sizeof(SYSCBlk));

}

