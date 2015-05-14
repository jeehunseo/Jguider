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

#ifndef __RECORD_TASK_H_
#define __RECORD_TASK_H_

#include "reg.h"

/***************** TASK MENDATORY DATA ***********************/
/* TASK ID*/
#define TID_RECORD 0x02

/* TASK MANDATORIAL PROTOTYPE */
void recordingTaskInit(Dbts* sysblk, Trdata* tr);
extern TaskContrBlk recordingTask;


/***************** TASK MENDATORY DATA ***********************/
// NULL 


/******************** MESSAGE BUFFER **************************/
// 1. message buffer structure
typedef struct _RECORD_BUFF_{
	/* MANDATORY INFOMATION OF MESSAGE BUFFER*/
	U8 cmd;
	U8 opt;

	/*----------- USER VARIALBE --------------*/
	// user variable	
	unsigned long data;

}RecordBuff;

// 2. message buffer size
#define SIZE_REC_BUFF		5 

// 3. message buffer command 
#define BCMD_HI				0x01
#define BCMD_HELLO_WORLD 	0x02
#define BCMD_WHO_ARE_YOU	0x03
/**************************************************************/

#endif

