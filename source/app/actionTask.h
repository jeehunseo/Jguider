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

#ifndef __ACTIONTASK_H
#define __ACTIONTASK_H

#include "reg.h"


/***************** TASK MENDATORY DATA ***********************/
/* TASK ID*/
#define TID_ACTION 0x01

/* TASK MANDATORIAL PROTOTYPE */
void actingTaskInit(Dbts* sysblk, Trdata* tr);
extern TaskContrBlk actingTask;



/****************** TASK COMMON DATA ************************/
typedef struct _ACTION_DATA_{
	U8 test[10];
	
}ActionData;



/******************** MESSAGE BUFFER **************************/
// 1. message buffer structure
typedef struct _ACTION_FORM_ {
	/* MANDATORY INFOMATION OF MESSAGE BUFFER*/
	U8 cmd;
	U8 opt;

	/*----------- USER VARIALBE --------------*/
	rTIME rtime;

	NUM_CID cid;
	NUM_EID eid; // Example: NUM_CID & NUM_EID are defined in 'Taskdefine.h' file

	U8 sdata[20];
	U16 slength;
	
}ActionForm;

// 2. message buffer size
#define SIZE_ACT_BUFF 5 

// 3. message buffer command 
#define BCMD_REHI 0x01
#define BCMD_NICE_TO_MEET 0x02
/**************************************************************/


#endif

