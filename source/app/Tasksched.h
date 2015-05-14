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

#ifndef __TASKSCHED_H
#define __TASKSCHED_H

#include "csched.h"
#include "reg.h"

/* data structure which is used to transfer between tasks*/
struct _DATA_BETWEEN_TASKS_{

	rTIME *pRtime;
	rYEAR *pYear;

	U8 istatus;// kernel status

	U8 CallTime; // temp timer

	U32 DCmd; // temp comand

};

void Tasksched(SYSCBlk* sysblk);
void taskschedInit(SYSCBlk* sysblk);

#endif
