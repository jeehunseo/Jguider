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

#include "actiontask.h"


/*STRUCTURE FOR MAKING TASK*/
// 1. TCB: task control block
TaskContrBlk actingTask;
// 2. TRANSFER DATA: common data among the same task
Trdata acting_data;
// 3. COMMON DATA: common data which is used only in one task
ActionData adat;

unsigned long count =0;

/*DECLARE PROTOTYPE OF SEGMENT FUNCTION*/
void actingBase(Dbts* ts, Trdata* trd);
void A_2(Dbts* ts, Trdata* trd);
void A_3(Dbts* ts, Trdata* trd);

int drv_num[2]; 

void actingTaskInit(Dbts* ts, Trdata *tr){
	Trdata *pActing_data = &acting_data;
	
	/*INITIALIZATION OF THE TRANSFER DATA*/
	oMemSet((U8*)pActing_data, 0, sizeof(Trdata));
	pActing_data->status = 0xFF;
	pActing_data->pNext = actingBase;
	pActing_data->tid = TID_ACTION;
	pActing_data->pdata = &adat;

	
	/*TRDATA IS LINKED UP WITH TCB*/
	actingTask.trdata = pActing_data;

	// 1. driver initialization
	pActing_data->pfd = drv_num;
	pActing_data->pfd[0] = open(DEV_NUM_EEPROM,0);

}

void actingBase(Dbts* ts, Trdata* trd){

#if (_MSG_SEND_TEST_ == ENABLED)
	nextFunct(trd) = A_2;
#endif

}


void A_2(Dbts* ts, Trdata* trd){
#if (_MSG_SEND_TEST_ == ENABLED)
	RecordBuff tmpRcbuf;

	// ---- SEND TEST1 ----
	tmpRcbuf.cmd = BCMD_HI;
	tmpRcbuf.data = count;
	SendMsg(trd->tid, TID_RECORD, (U8*)&tmpRcbuf, sizeof(RecordBuff));
	
	xprintf("(a(%ld):  hi)\n",count);
	count++;

	nextFunct(trd) = A_3;
#endif
}

void A_3(Dbts* ts, Trdata* trd){
#if (_MSG_SEND_TEST_ == ENABLED)
	RecordBuff tmpRcbuf;

	// ---- SEND TEST2 ----	
	tmpRcbuf.cmd = BCMD_HELLO_WORLD;
	tmpRcbuf.data = count;
	SendMsg(trd->tid, TID_RECORD, (U8*)&tmpRcbuf, sizeof(RecordBuff));
	
	xprintf("(a(%ld): hello world)\n",count);
	count++;

	// ---- SEND TEST3 ----
	tmpRcbuf.cmd = BCMD_WHO_ARE_YOU;
	tmpRcbuf.data = count;
	SendMsg(trd->tid, TID_RECORD, (U8*)&tmpRcbuf, sizeof(RecordBuff));
	
	xprintf("(a(%ld):  who are you)\n",count);
	count++;
	
	nextFunct(trd) = actingBase;
#endif
}

