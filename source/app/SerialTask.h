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

#ifndef __SERIALTASK_H_
#define __SERIALTASK_H_

#include "reg.h"


/***************** TASK MENDATORY DATA ***********************/
/* SERIAL TASK ID*/
#define TID_SERIAL			0x00

/* SERIAL TASK MANDATORIAL PROTOTYPE */
void serialTaskInit(Dbts* sysblk, Trdata* tr);
extern TaskContrBlk serialTask;


/******************** SERIAL MESSAGE BUFFER **************************/
// 1. message buffer structure
#define TX_BUFFER_SIZE		100
typedef struct _SERIAL_BUF_FORM_{
	// buffer mandatory
	U8 cmd;
	U8 opt;
	
	// user variable
	U16 len;
	U8 data[TX_BUFFER_SIZE];
}SerialBufForm;

// 2. message buffer size
#define SIZE_SERIAL_MSG_BUFF	5

// 3. message buffer command 
#define BCMD_SERIAL_SEND	0x01 // send some data to PC


/********************* inner parmaters ****************************/

typedef struct _YYMMDDS_{
	U8 year;		// year µÚ 2ÀÚ¸® 
	U8 month;
	U8 day;
	U8 days;		//0 ~ 6 : sunday ~ saturday
	U8 AM;
}yymmdds;

typedef struct _HHMMSS_{
	U8 hour;
	U8 mi;
	U8 sec;
}hhmmss;

/* serial device file */
#define SERIAL_FILE_SIZE	2
#define FILE_UART0			0x00
#define FILE_UART1			0x01

/* boot code */
#define BOOT_ON				0xCC

/*---------- ACOMMAND ----------*/
// USER DEFINE APP COMMAND
#define ACMD_HELLO_SERIALTASK	0xD4
#define ARSP_HELLO_SERIALTASK	0xD5

// SYSTEM DEFINE APP COMMAND
// next 0xC0 ~ 0xCF are reserved for system command
#define ACMD_SYNCH_SYSTEMTIME	0xCA
#define ACMD_ADMIN_USER_LOGIN	0xCB



#endif

