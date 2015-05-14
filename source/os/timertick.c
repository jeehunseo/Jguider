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

#include "types.h"
#include "osapi.h"
#include "timertick.h"


/*SYSTEM TICK VALIABLE*/
static U32 tick;
#if USE_GET5usTICK == ENABLED
static U32 fastTick;
#endif


/*The value that is used to caculate Kernel's time*/
rTIME sync_real_time;
U32 sync_tick = 0;
#if TIME_COMPENSATE == ENABLED
U8 saveTime;
#endif
U32 *pDAYchange;


void oSysTimerInit(SYSCBlk* sysblk)
{
	oStopHardware();
#if USE_GET5usTICK == ENABLED
	fastTick = 0;
#endif
	tick = 0;
	__TimerInit();

	pDAYchange = &(sysblk->chgDay);
	*pDAYchange =1;
	
	oResumeHardware();
}

U32 oTimerGet1MsTick(void)
{
	U32 tmp;

	oStopHardware();
	tmp  = tick;
	oResumeHardware();

	return tmp;  
}

/**** HARDWARE INTERRUPT CALL FUNCTION *********
     -> This function is called in system interrput 
************************************************/
void __IntrCall_SystemTimer(void){

	tick++;
#if USE_GET5usTICK == ENABLED
	fastTick += 200;
#endif

}


#if USE_GET5usTICK == ENABLED
U32 oTimerGet5usTick(void)
{
	U32 temp1;
	U32 temp2;
	U32 t1Cnt;
	U32 i;

	for (i = 0; i < 5; i++) {
		oStopHardware();
		temp1 = fastTick;
		t1Cnt = (U32)rTIMER_COUNT;
		temp2 = fastTick;
		oResumeHardware();

		if (temp1 == temp2) {
			break;
		}
	}
	return (temp1+t1Cnt);
}
#endif

void TimeInit(SYSCBlk*sysblk){
	RYearStruct ryearStr;
	RTimeStruct rtimeStr;

	ryearStr.year = 8;
	ryearStr.days = 1; 
	
	rtimeStr.month = 10;
	rtimeStr.day = 20;
	rtimeStr.hour = 11;
	rtimeStr.mi = 59;
	rtimeStr.sec = 50;
	
	SynchRYear(&(sysblk->year),&ryearStr);
	SynchRTime(&(sysblk->rtime),&rtimeStr);

#if KERNEL_INIT_VIEW == ENABLED
	xprintf("K>Time Set ... OK\n");
#endif

}

void SynchRYear(rYEAR* pYear, RYearStruct *yds){
	U16 temp=0;

	temp = ((yds->days)<<7)|((0xEF)&(yds->year));
	*pYear = temp;
}

BOOL CalDayCarrier(U8 year, U8 month, U8 cday){
	U32 totalyear;


	// dapted Y2K algorism
	if(year>50){
		//1900 year
		totalyear = 1900 + year;
	}else{
		// 2000 year
		totalyear = 2000 + year;
	}

	if(month == 2){
		// cacluate a leap year
		if(((totalyear%4)==0 && (totalyear%100)!=0) || (totalyear%400)==0){
			if(cday > 29)
				return TRUE;
		}else{
			if(cday >28)
				return TRUE;
		}
	}else if((month == 4)||(month == 6)||(month == 9)||(month == 11)){
		// cacluate a month which have 30 days 
		if(cday > 30 )
			return TRUE;
	}else{
		// caculate a month which have 31 days 
		if(cday > 31)
			return TRUE;
	}
	
	return FALSE;
}

void CalYMDs(SYSCBlk* sysblk, U8 ret){
	U8 day;
	U8 month;
	U8 year;
	U8 days;
	U32 month_day=0;
	
	day = getrDay(sysblk->rtime);
	month = getrMonth(sysblk->rtime);
	year = getrYear(sysblk->year);
	days = getrDays(sysblk->year);
	
	if(ret == TRUE){
	#if KERNEL_DEBUG == ENABLED
		xprintf("\nK>----CalYMDs----\n");
	#endif

		// 1. A day of the week
		if(days == 6){
			days = 0;
		}else
			days++;

		// 2. Day, month
		if(CalDayCarrier(year, month, (day + 1)) == TRUE){
			// when it passed through a month
			month++;
			day = 1;
		}else{
			// when it doesn't passed through a month
			day++;
		}

		if(month > 12){
			year++;
			month = 1;
		}

		//* we suppose that the type of this memory access is Big-endian.
		month_day = (month<<5)|((0x1F)&(day));
		month_day = month_day<<17;
		
		sysblk->year = (rYEAR)((days<<7)|((0x7F)&(year)));
		sysblk->rtime = ((rMD_OTHER_MASK)&(sysblk->rtime)) |((rMD_MASK)&(month_day));
		
	}
	
}

void SynchRTime(rTIME* pRtime, RTimeStruct* rhms){
	rTIME ntsht = 0;

	sync_tick = tick;
	
	ntsht = ((rhms->month)<<5)|((0x1F)&(rhms->day));
	ntsht = (ntsht <<5)|((0x1F)&(rhms->hour));
	ntsht = (ntsht <<6 )|((0x3F)&(rhms->mi));
	ntsht = (ntsht <<6)|((0x3F)&(rhms->sec));
	*pRtime = ntsht;

#if TIME_COMPENSATE == ENABLED
	saveTime =(rMinRMASK)&(rhms->mi);
#endif
	sync_real_time = ntsht;

	*pDAYchange = 1;
}


U8 CalCarrier(U32 csec, U8 div){
	U8 carrier;
	
	// this algorism is using two condition to avoid a delay 
	// which occurs in divide-processing.
	if(csec >= div){
		if(csec >= (div*2)){
			carrier = csec/div;
		}else
			carrier = 1;
	}else 
		carrier = 0;

	return carrier;
}

U8 TickTocSynchRtime(SYSCBlk* sysblk){
	U32 gap;
	U8 min,hour,sec ;
	U16 cmin,csec,chour;// minutes variable with own carrier
	rTIME tempRtime;
	U8 ret = FALSE;
	rTIME ntsht = sync_real_time;

#if TIME_DEBUG2 == ENABLED
	rTIME ggg;
	static rTIME prev_time = 0;
#endif
	gap = (U32)(tick - sync_tick);

	// (occur delay time. It'll be changed)
	sec = (gap /1000)%60;
	min = (gap / 60000) % 60;
	hour =  (gap/ 3600000)%24;

	// 1. csec result
	csec = getrSec(ntsht) + sec;

	// 2. cmin result
	cmin = getrMin(ntsht) + min + CalCarrier(csec,60);

	// 3. chour result
	chour = getrHour(ntsht) + hour + CalCarrier(cmin,60);

	// 4. carry the value of day-carrier 
	//ret = CalCarrier(chour,24);
	if(chour/24 == (sysblk->chgDay)){
		(sysblk->chgDay)++;
		ret = TRUE;
	}
	
	// 5. hour/min/sec result 
	// (occur delay time. It'll be changed.)
	csec = csec%60;
	cmin = cmin%60;
	chour = chour%24;
	
	/*  6. carry to system timer 
	5bits : hour 
	6bits : minutes
	6bits : sec 
	*/
	tempRtime =  (chour<<6)|((rMinRMASK)&cmin);
	tempRtime = (tempRtime<<6)|((rSecMASK)&csec);
	
	sysblk->rtime = ((sysblk->rtime)&(0xFFFE0000))|((tempRtime)&(0x0001FFFF));

#if TIME_DEBUG2 == ENABLED
	ggg = tempRtime;
	if(prev_time != ggg){
		prev_time = ggg;
		xprintf("K>REAL: Y:20%02d M:%d D:%d ",(U8)getrYear(sysblk->year),(U8)getrMonth(sysblk->rtime),(U8)getrDay(sysblk->rtime));
		xprintf("-- H:%d M:%d S:%d\n",(U8)getrHour(sysblk->rtime),(U8)getrMin(sysblk->rtime),(U8)getrSec(sysblk->rtime));
	}
#endif
	
	sync_real_time = ntsht;		
	
	return ret;
}

U16 Rtime2Min(rTIME rtime){
	U8 hour;
	U8 min;

	hour = getrHour(rtime);
	min = getrMin(rtime);

	return (hour*60) + min;
}

U32 Rtime2Sec(rTIME rtime){
	U8 day;
	U8 hour;
	U8 min;
	U8 sec;
	
	day = getrDay(rtime);
	hour = getrHour(rtime);
	min = getrMin(rtime);
	sec = getrSec(rtime);

	return (day*24*360) + (hour*360) + (min*60)+sec;
}


