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

#ifndef __TCBLIST_H_
#define __TCBLIST_H_

#include "timelist.h"
#include "csched.h"


#define MAX_NUM_FAST_THREAD 5

#define TID U8 // task ID  0~ 255

typedef  void TransferData ;

typedef struct _TASK_TRANS_DATA Trdata, *pTrdata;// 이런식으로도 사용 가능 
typedef struct _FAST_THREAD_TRNAS_DATA FastTransDat;

typedef void (*pfunctNext)(Dbts*, Trdata*);
typedef void (*FastThrNext)(Dbts*, FastTransDat*);
typedef void (*pfSendMsg)(U8*, U32, U8);

struct _TASK_TRANS_DATA
{
	// *** This structure is designed for sharing data ****
	
	// test valuable
	U8 status;

	/*task identification number*/
	TID tid;

	/* the pointer of common data */
	TransferData *pdata;
	
	/*next step function pointer*/
	pfunctNext pNext;
	
	int *pfd;
	
};

struct _FAST_THREAD_TRNAS_DATA
{
	U8 status;

	/* RFU */
	TransferData *pdata;

	/*next step function pointer*/
	FastThrNext pNext;
		
};


typedef struct _TASK_CTRL_BLK
{
	/* 같은 task 안에서 전달 받거나 컨트롤 되어지는 data */

	/*TCB linked list*/
	ListNode	node;

	/*the function pointer of the step in user task*/
	pfunctNext func;

	/*the pointer of transfered info*/
	Trdata* trdata ;

	/*the pointer of system variable*/
	SYSCBlk* SysVar;

	/*the pointer of data between task*/
	Dbts* pDbts;
		
}TaskContrBlk;


typedef struct _FAST_THREAD_BLK
{

	/*TCB linked list*/
	ListNode	node;

	/*the function pointer of the step in user task*/
	FastThrNext func;

	/*the pointer of transfered info*/
	FastTransDat* ftdata ;

	/*the pointer of system variable*/
	SYSCBlk* SysVar;

	/*the pointer of data between task*/
	Dbts* pDbts;

}FastThreadBlk;


typedef struct _FAST_THREAD_ARRAY{

	FastThrNext pNext;
	
}FastThreadArray;


#define nextFunct(a) a->pNext


BOOL TCB_Init(SYSCBlk* sysblk);
void FTCB_Init(SYSCBlk* sysblk);
void CreateTask(SYSCBlk* sysblk, TaskContrBlk* tcb, pfunctNext pf);
void DeleteTask(TaskContrBlk* tcb);

BOOL RegFastThread(SYSCBlk* sysblk, FastThrNext fp);
	
void TCB_processor(SYSCBlk* sysblk);
void Fast_processor(SYSCBlk* sysblk);

#endif


