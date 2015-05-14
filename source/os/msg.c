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

#include "msg.h"
#include "error.h"

// message buffer structure
Msg msgbox[SIZE_MAX_MSG];


BOOL initMsg(void){
	U8 cnt;
	Msg *pmsgbox;
	
	for(cnt = 0; cnt < SIZE_MAX_MSG; cnt++){
		pmsgbox = &(msgbox[cnt]);
		oMemSet((U8*)pmsgbox, 0, sizeof(Msg));
		pmsgbox->bufinfo.rbuf_lock = BUF_LOCK;
		pmsgbox->bufinfo.rbuf_end = -1; 
		pmsgbox->bufinfo.rbuf_start = -1;	
	}
	
#if KERNEL_INIT_VIEW == ENABLED
	xprintf("K>Msg Init ... OK\n");
#endif

	return TRUE;
}

BOOL insertMsgBox(TID tid, MsgBUF *pbuf, SizeBUF bufsize){
	U8 cnt;
	Msg *pmsgbox;
	
	for(cnt = 0 ; cnt < SIZE_MAX_MSG; cnt++){
		pmsgbox = &(msgbox[cnt]);
		if(pmsgbox->tid == 0){
			pmsgbox->tid = tid;
			pmsgbox->bufsize = bufsize;
			pmsgbox->pbuf= pbuf;
			return TRUE;
		}
	}

	return FALSE;
}

void writeBuff(U8 *recv, U32 len, Msg* msg){
	MsgBUF *precbuf = msg->pbuf;
	BUFINFO *binfo = &(msg->bufinfo);
	int cnt;

	// lock buffer
	binfo->rbuf_lock = BUF_LOCK;

	for(cnt = 0; cnt < len ; cnt++){
		if(++(binfo->rbuf_end) > ((msg->bufsize)- 1) ) 
			binfo->rbuf_end = 0;
		
		// make 'buff data'
		precbuf[binfo->rbuf_end] = recv[cnt];
	}
	
	// unlock buffer
	binfo->rbuf_lock = BUF_UNLOCK;

}


int readBuff(U8* rec, U32 tlen, Msg* msg){
	MsgBUF *precbuf = msg->pbuf;
	BUFINFO *binfo = &(msg->bufinfo);
	int size = 0;
	int trbuf_start;
	
	while (binfo->rbuf_lock == BUF_LOCK)
		return 0;

	while(binfo->rbuf_end !=binfo->rbuf_start){

		if(++(binfo->rbuf_start) > ((msg->bufsize) -1) )
			(binfo->rbuf_start) =0;

		trbuf_start = binfo->rbuf_start;
		rec[size] = precbuf[trbuf_start];
		
		if(tlen <= ++size){
			binfo->rbuf_lock = BUF_UNLOCK;
			return size;
		}

	}
		
	binfo->rbuf_lock = BUF_LOCK;
	return size;
}



int SendMsg(TID sender, TID receiver, U8* data, U32 len){
	int cnt;
	Msg *pmsgbox;
	
	for(cnt =0 ; cnt < SIZE_MAX_MSG; cnt++){
		pmsgbox = &(msgbox[cnt]);
		
		if(pmsgbox->tid == 0)
			return FALSE;
		
		if(receiver == pmsgbox->tid){
			if((pmsgbox->sbuf_used + len) > pmsgbox->bufsize)
				return err(ERR_MSG_BUFF_OVERFLOW,WHR_SENDMSG);
			pmsgbox->sbuf_used += len;
			pmsgbox->source = sender;
			writeBuff(data, len, pmsgbox);
			return TRUE;
		}
	}
	return FALSE;
}


int RecvMsg(TID receiver, U8* data, U32 tlen){
	int cnt, size;
	Msg *pmsgbox;

	for(cnt =0 ; cnt < SIZE_MAX_MSG; cnt++){
		pmsgbox = &(msgbox[cnt]);
		
		if(pmsgbox->tid == 0)
			return 0;
		if(receiver == pmsgbox->tid){
			size = readBuff(data, tlen, pmsgbox);
			pmsgbox->sbuf_used -= size;
			return size;
		}
	}

	return 0;
}


