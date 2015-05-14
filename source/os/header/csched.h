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

#ifndef __CSCHED_H
#define __CSCHED_H

#include "override.h"
#include "intr.h"

#define rTIME U32
#define rYEAR U16

typedef struct _DATA_BETWEEN_TASKS_ Dbts;
typedef struct _SYSTEM_CONTROL_BLOCK_ {
	U8 reset; // RFU

	U8 taskCount; // the number of task
	U8 ftaskCount; // the number of fast task

	U32 chgDay;
	
	rTIME rtime; 
	rYEAR year; 

	/*
	>> content of 'rTIME' (32bits)
		  U32		: xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx
		  ----------------------------------------------------------------
		  sec(6)		: xxxx xxxx xxxx xxxx xxxx xxxx xx00 0000 (0)
		  min(6)		: xxxx xxxx xxxx xxxx xxxx 0000 00xx xxxx (6)
		 hour(5)		: xxxx xxxx xxxx xxx0 0000 xxxx xxxx xxxx (12)
		  day(5)		: xxxx xxxx xx00 000x xxxx xxxx xxxx xxxx (17)
		month(4)		: xxxx xx00 00xx xxxx xxxx xxxx xxxx xxxx (22)
		year indicator	: xxxx x0xx xxxx xxxx xxxx xxxx xxxx xxxx : (26)// it can make us know changing year
		RFU			: 0000 0xxx xxxx xxxx xxxx xxxx xxxx xxxx 

	>>content of 'year' (16bits)
		  U16	: xxxx xxxx xxxx xxxx
		  ------------------------------------
		  year(7)	: xxxx xxxx x000 0000 (0) : ex) 2009 -> 20xx : only 'xx' is used to describe about J-guider's Year
		  days(3)	: xxxx xx00 0xxx xxxx (7)
		  RFU	: 0000 00xx xxxx xxxx

	>> everything value in J-guider is maked as the type of accessing memory is 'Big-endian'.
	
	*/
	
	/*THE POINTER OF THE DATA BETWEEN TASKS*/
	Dbts *pDbts;

}SYSCBlk;

void SystemSched(SYSCBlk* sysblk);

#endif

