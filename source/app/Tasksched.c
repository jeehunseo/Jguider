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

#include "Tasksched.h"

/*This struct is used for offering communication-info between tasks in a scheduler*/
Dbts dbts;

void taskschedInit(SYSCBlk* sysblk){
	Dbts *pdbts = &dbts;

	/*LINKING TASK WITH DBTS(DATA BETWEEN TASKS)*/
	oMemSet((U8*)pdbts, 0,sizeof(Dbts));
		
	/*LINKED SYSTEMBLOCK WITH CSDT*/
	pdbts->pRtime = &(sysblk->rtime);
	pdbts->pYear = &(sysblk->year);
	sysblk->pDbts = pdbts;


	/*---------------------- USER TASK INITIALICATION -----------------------*/
	// 'recordingTask' & 'actingTask' are just some example in a kernel.
	// User can code here.
	
	CreateTask(sysblk,&recordingTask, recordingTaskInit); // example 1 task
	CreateTask(sysblk,&actingTask, actingTaskInit); // example 2 task



	/*---------------------- Mandotary Task Initialication ----------------------*/
	
	CreateTask(sysblk,&serialTask, serialTaskInit);
	
#if KERNEL_INIT_VIEW == ENABLED
	xprintf("K>TaskSched Init ... OK\n");
	xprintf("     - %d Tasks are running!\n",sysblk->taskCount);

	xprintf("K>FastThread Init ... OK\n");
	if(sysblk->ftaskCount != 0)
		xprintf("     - %d Fast tasks are running!\n",sysblk->ftaskCount);
#endif

}


void Tasksched(SYSCBlk* sysblk){	
	TCB_processor(sysblk);
	
#if KERNEL_SPEED_LOW == ENABLED
	 // kernel low speed set for deguging : Next task will be begin 200 msec after ending previous task.
	oTimerDelay(100);
#endif

}



