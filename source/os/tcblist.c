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

#include "tcblist.h"
#include "error.h"
#include "msg.h"

ListNode TCBList;

/*INITIALIZATION FOR FAST THREAD*/
ListNode FTCBList;
FastThreadBlk fThreadBlk;
FastTransDat fastTrd;
FastThreadArray Fta[MAX_NUM_FAST_THREAD];
static U8 Fast_cnt =0;

#define BlkTr(e) e

void CreateFastThread(SYSCBlk* sysblk, FastThrNext pf);


BOOL RegFastThread(SYSCBlk* sysblk, FastThrNext fp){

	if(Fast_cnt >= MAX_NUM_FAST_THREAD)
		return FALSE;
	
	Fta[Fast_cnt++].pNext = fp;
	sysblk->ftaskCount++;
	
	return TRUE;
}

void NullFunctT(Dbts* ts, Trdata* trd){
	err(ERR_NULL_FUNCTION_CALL_IN_TASK,WHR_NULLFUNCTT);
}

void NullFunctFT(Dbts* ts, FastTransDat* trd){
	err(ERR_NULL_FUNCTION_CALL_IN_FASTTASK,WHR_NULLFUNCTFT);
}

FastThrNext CallNextFastThread(void){
	FastThrNext p;
	static U8 innerCnt=0;

	if(Fast_cnt == 0)
		return 0;
	
	p = Fta[innerCnt].pNext;
	if(innerCnt+1 >= Fast_cnt)
		innerCnt = 0 ;
	else
		innerCnt++;
	
	return p;
}
	
void FastThreadInit(Dbts* ts, FastTransDat *tr){
	
	/*INITIALIZATION OF THE TRANSFER DATA*/
	oMemSet((U8*)&fastTrd, 0, sizeof(FastTransDat));
	
	fastTrd.status = 0xFF;
	
	/*TRDATA IS LINKED UP WITH TCB*/
	fThreadBlk.ftdata = &fastTrd;
}



BOOL TCB_Init(SYSCBlk* sysblk)
{
	U8 cnt;
	
	/*linked list of the TCB and the FastTCB is install*/
	InitializeListHead(&BlkTr(TCBList));
	InitializeListHead(&BlkTr(FTCBList));
	
	/* initialize fast thread block */
	oMemSet((U8*)&fThreadBlk,0,sizeof(FastThreadBlk));

	/*INITIALIZATION OF THE FAST THREAD ARRAY DATA*/
	for(cnt = 0; cnt <MAX_NUM_FAST_THREAD; cnt++)
		oMemSet((U8*)&Fta[cnt], 0, sizeof(FastThreadArray));
	
#if KERNEL_INIT_VIEW == ENABLED
	xprintf("K>TCB Init ... OK\n");
#endif
	return TRUE;
}


void FTCB_Init(SYSCBlk* sysblk){
	
	CreateFastThread(sysblk, FastThreadInit);
}
	
void CreateTask(SYSCBlk* sysblk, TaskContrBlk* tcb, pfunctNext pf)
{
	oStopHardware();
	
	oMemSet((U8*)tcb, 0, sizeof(TaskContrBlk));

	tcb->func = pf;

	 // you have to seperate between kernel user and application.
	tcb->SysVar = sysblk;
	tcb->pDbts = tcb->SysVar->pDbts;
	
	/*ADD NEW TCB TO THE TCBLIST IN THE REAR(*/
	if (!IsNodeOnList(&BlkTr(TCBList), &tcb->node))
		InsertHeadList(&BlkTr(TCBList), &tcb->node);        

	sysblk->taskCount++;
	
	oResumeHardware();
}

void DeleteTask(TaskContrBlk* tcb)
{
	TaskContrBlk   *curTcb;
	ListNode  *node;
	ListNode *tcbList=&BlkTr(TCBList) ;
	
	oStopHardware();
	
	if (!IsListEmpty(tcbList)) {
		
		node = GetHeadList(tcbList);        
		while (node != tcbList) {
			curTcb = (TaskContrBlk*) node;
			node = node->Flink;
			
			if (curTcb == tcb) {
				RemoveEntryList(&curTcb->node);
				break;
			}
		}
	}
	oResumeHardware();
}

static void TCBScheduler(void)
{
	TaskContrBlk *ttcb;
	ListNode *node;
	ListNode *tcbList=&BlkTr(TCBList) ;
	
	oStopHardware();
	if (!IsListEmpty(tcbList)) {
		
		node = GetHeadList(tcbList);
		while (node != tcbList){            
			ttcb = (TaskContrBlk*) node;            
			
			oResumeHardware();       
			/* CALL THE FUNCTION BE IN SELECTED TASK*/
			if(ttcb->func == 0)
				ttcb->func = NullFunctT;

			// link the function which will be used in next time.
			ttcb->func(ttcb->pDbts, ttcb->trdata); 
			
			ttcb->func = ttcb->trdata->pNext;
			
			oStopHardware();
			
			/*CALL NEXT NODE(FLINKED) */            
			node = node->Flink; 
		}
	}
	oResumeHardware();
}

void TCB_processor(SYSCBlk* sysblk){
	
	TCBScheduler();
}

void CreateFastThread(SYSCBlk* sysblk, FastThrNext pf)
{
	FastThreadBlk* ftb= &fThreadBlk;

	oStopHardware();
	
	ftb->func = pf;
	// you have to restrict to access in the kernel.
	ftb->SysVar = sysblk; 
	ftb->pDbts = sysblk->pDbts;
	
	/*ADD NEW TCB TO THE TCBLIST IN THE REAR(*/
	if (!IsNodeOnList(&BlkTr(FTCBList), &ftb->node))
		InsertHeadList(&BlkTr(FTCBList), &ftb->node);        

	oResumeHardware();
}


static void FastThreadScheduler(void){
	FastThreadBlk *tftb;
	ListNode *node;
	ListNode *fastList=&BlkTr(FTCBList) ;
	
	oStopHardware();
	if (!IsListEmpty(fastList)) {
		
		node = GetHeadList(fastList);
		while (node != fastList){            
			tftb = (FastThreadBlk*) node;
			oResumeHardware();       
			/* CALL THE FUNCTION BE IN SELECTED TASK*/

			if(tftb->func == 0)
				tftb->func = NullFunctFT;
			
			tftb->func(tftb->pDbts, tftb->ftdata); 

			tftb->func = CallNextFastThread(); 
			
			oStopHardware();
			
			/*CALL NEXT NODE(FLINKED) */            
			node = node->Flink; 
		}
	}
	oResumeHardware();

}

void Fast_processor(SYSCBlk* sysblk){
	FastThreadScheduler();
}

