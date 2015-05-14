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

#ifndef __TIMERTICK_H
#define __TIMERTICK_H

#include "csched.h"

/* KERNEL TIMER SETTING ****************************************************

	We suppose that the type of this memory access is Big-endian!!
	If you want to change the type of endian, you have to convert all thing about 'shift-calculation'
	such as '(r)>>26'
	
	It'll be provided later.
***************************************************************************/

#define USE_GET5usTICK ENABLED

#define TIME_DEBUG DISABLED
#define TIME_DEBUG2 DISABLED

typedef struct _REAL_YEAR_STRUCT_{
	U8 year;
	U8 days;
}RYearStruct;

typedef struct _REAL_TIME_STRUCT_{
	U8 month;
	U8 day;
	U8 hour;
	U8 mi;
	U8 sec;
}RTimeStruct;

#define rDaysMASK 0x07 // 0000 0111 // 3bit
#define rYearMASK 0x7F // 0111 1111 // 7bit
#define rYIndMASK 0x01 // 0000 0001 // 1bit
#define rMonMASK  0x0F // 0000 1111 // 4bits
#define rdayMASK  0x1F // 0000 1111 // 5bits
#define rHourMASK  0x1F // 0001 1111 // 5bits
#define rMinRMASK 0x3F // 0011 1111 // 6bits
#define rSecMASK  0x3F // 0011 1111 // 6bits

// hour/min/sec 
#define rHMS_MASK 0x0001FFFF

// month day (// 0000 0011 1111 1110,  0x0 0x0-> 03 FE 00 00 
#define rMD_MASK 0x03FE0000
#define rMD_OTHER_MASK 0xFA01FFFF

// rYEAR
#define getrDays(y) ((rDaysMASK)&((y)>>7))
#define getrYear(y) ((rYearMASK)&(y))

// rTIME
#define getrYInd(r) ((rYIndMASK)&((r)>>26))
#define getrMonth(r) ((rMonMASK)&((r)>>22))
#define getrDay(r) ((rdayMASK)&((r)>>17))
#define getrHour(r) ((rHourMASK)&((r)>>12))
#define getrMin(r) ((rMinRMASK)&((r)>>6))
#define getrSec(r) ((rSecMASK)&(r))


/*32bits bigger time is changed to view and use easily*/

void TimeInit(SYSCBlk*sysblk);
void oSysTimerInit(SYSCBlk* sysblk);
U32 oTimerGet1MsTick(void);
void __IntrCall_SystemTimer(void);
#if USE_GET5usTICK == ENABLED
U32 oTimerGet5usTick(void);
#endif
void CalYMDs(SYSCBlk* sysblk,U8 ret);
U8 TickTocSynchRtime(SYSCBlk* sysblk);
void SynchRTime(rTIME* pRtime, RTimeStruct* rhms);
void SynchRYear(rYEAR* pYear, RYearStruct *yds);
U16 Rtime2Min(rTIME rtime);
U32 Rtime2Sec(rTIME rtime);

/*
	It is required to find correct 'system tick'(1msec) depending on main frequency,
	but, If you don't make correct tick required to your system, use TIME_COMPENSATE.
	we really recommand to adapt main frequency(hardware) to your device.
*/
#define TIME_COMPENSATE DISABLED

#endif
