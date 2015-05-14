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

#ifndef __MSG_H_
#define __MSG_H_

#include "override.h"
#include "tcblist.h"

/***************** MESSAGE FUNCTION ***********************/
/* user setting value for kernel message */
#define SIZE_MAX_MSG	10 // This parameter will be removed near future

/* send, receive message function for kernel */
int SendMsg(U8 sender, U8 receiver, U8* data, U32 len);
int RecvMsg(TID tid, U8* recv, U32 tlen);

/* This initialization function is used to initialize message function in each task  */
BOOL insertMsgBox(TID tid, U8 *pbuf, U16 size);


/***************** MESSAGE INNER PARAMETERS ***********************/
#define BUF_LOCK		1
#define BUF_UNLOCK		0

#define MsgBUF U8
#define SizeBUF U16

typedef struct _BUFF_INFO_ {
	U8 rbuf_lock;
	int rbuf_end ;
	int rbuf_start;
}BUFINFO;


typedef struct _MSG_FORM_{
	// destination address ID
	TID tid;
	
	MsgBUF *pbuf;
	SizeBUF bufsize;
	BUFINFO bufinfo;
	U32 sbuf_used;
	
	// source address ID
	TID source; 
}Msg;
	
BOOL initMsg(void);

#endif

