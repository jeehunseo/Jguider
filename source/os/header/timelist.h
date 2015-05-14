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

#ifndef __TIMELIST_H
#define __TIMELIST_H

#include "osapi.h"
#include "utils.h"
#include "types.h"


/* REFERNECE OF JgTimer*/
typedef struct _JgTimer JgTimer;

/*CALLBACK USED TO CHECK EXPIRATION OF TIMERS*/
typedef void (*JgTimerNotify)(JgTimer*);


 /*JgTimer STRICTURE */
struct _JgTimer
{
	ListNode		node;     
	void			*context;  
	JgTimerNotify	func;    

	TIMET		time;      
	TIMET		startTime;
};



/* THIS FUNCTION IS USED TO INITIALIZ JGTIMER*/
BOOL JG_TimerInit(void);

 /* CALL FOR CHECKING TIMER*/
void Time_Process(void);

/*CALL START A TIMER WITH SPECIFIED EXPIRED TIME (std: system tick)*/
void JgStartTimer(JgTimer* timer, TIMET ticks);

/*CALL START A TIMER WITH SPECIFIED EXPIRED TIME (std: milisecond)*/
void JG_StartTimer(JgTimer* timer, TIMET ms);

 /*CANCEL TIMER*/
void JG_CancelTimer(JgTimer* timer);

#endif

