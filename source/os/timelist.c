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

#include "timelist.h"

/*TIME LIST STRUCTURE*/
ListNode          timerList;

#define BlkTr(e) e

BOOL JG_TimerInit(void)
{
	InitializeListHead(&BlkTr(timerList));
	return TRUE;
}

void JG_CancelTimer(JgTimer* timer)
{
	JgTimer   *curTimer;
	ListNode  *node;
	ListNode *timeList=&BlkTr(timerList) ;

	oStopHardware();

	if (!IsListEmpty(timeList)) {

		node = GetHeadList(timeList);        
		while (node != timeList) { 
			curTimer = (JgTimer*) node;
			node = node->Flink;

			if (curTimer == timer) {
				RemoveEntryList(&curTimer->node);
				break;
			}
		}
	}

	oResumeHardware();
}

void JgStartTimer(JgTimer* timer, TIMET ticks)
{


	oStopHardware();

	timer->startTime = oGetSystemTime();
	timer->time = ticks;

	if (!IsNodeOnList(&BlkTr(timerList), &timer->node)) {
		InsertHeadList(&BlkTr(timerList), &timer->node);        
	}

	oResumeHardware();

}

static void CheckTimers(void)
{
	JgTimer   *timer;
	ListNode  *node;
	TIMET       curTime;
	TIMET       timeExpired;
	ListNode *timeList=&BlkTr(timerList) ;

	oStopHardware();


	/* CHECK FOR EXPIRATION OF TIMERS*/
	if (!IsListEmpty(timeList)) {

		curTime = oGetSystemTime();

		node = GetHeadList(timeList);
		while (node != timeList) {            
			timer = (JgTimer*) node;            
			node = node->Flink;
			timeExpired = curTime - timer->startTime;

			if (timeExpired >= timer->time) {
				RemoveEntryList(&timer->node);
				oResumeHardware();

				timer->func(timer);
	
				oStopHardware();

				node = GetHeadList(timeList);
				curTime = oGetSystemTime();
			}
		}

	}

	oResumeHardware();
    
}


void Time_Process(void){
	CheckTimers();
}


