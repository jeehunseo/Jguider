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

#include "recordTask.h"

/*STRUCTURE FOR MAKING TASK*/
// 1. TCB: task control block
TaskContrBlk recordingTask;
// 2. TRANSFER DATA: common data among the same task
Trdata recording_data;
// 3. MESSAGE BUFFER : 
RecordBuff recbuf[SIZE_REC_BUFF];

/*DECLARE PROTOTYPE OF SEGMENT FUNCTION*/
void recordingBase(Dbts* ts, Trdata* trd);

void recordingTaskInit(Dbts* ts, Trdata *tr){
	Trdata *pRecording_data = &recording_data;
	
	/*INITIALIZATION OF THE TRANSFER DATA*/
	oMemSet((U8*)pRecording_data, 0, sizeof(Trdata));
	pRecording_data->status = 0xFF;
	pRecording_data->pNext = recordingBase;
	pRecording_data->tid = TID_RECORD;
	
	/*TRDATA IS LINKED UP WITH TCB*/
	recordingTask.trdata = pRecording_data;

	insertMsgBox(pRecording_data->tid,(U8*)&recbuf, sizeof(recbuf));
}

void recordingBase(Dbts* ts, Trdata* trd){
#if (_MSG_SEND_TEST_ == ENABLED)
	int tlen;
	RecordBuff recvFrom;
	U8 senddata[20];
	
	/*PROCESS OF THE RXDATA*/
	do{
		oMemSet((U8*)&recvFrom, 0, sizeof(RecordBuff));
		tlen = RecvMsg(trd->tid, (U8*)&recvFrom, sizeof(RecordBuff));
		if(tlen >0){
			oMemSet((U8*)&senddata, 0, sizeof(senddata));
			switch(recvFrom.cmd){
			case BCMD_HI:
				xprintf("\t\t>>recordTask(%ld): HI\n",recvFrom.data);
				break;
				
			case BCMD_HELLO_WORLD:
				xprintf("\t\t>>recordTask(%ld): GLAD TO MEET YOU\n",recvFrom.data);
				break;

			case BCMD_WHO_ARE_YOU:
				xprintf("\t\t>>recordTask(%ld): J_GUIDER\n",recvFrom.data);
				break;

			default:
				break;
			}			
		}
	}while(tlen >0);
#endif

}

