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

#include "osapi.h"
#include "timertick.h"
#include "timelist.h"
#include "init.h"
#include "app.h"

static  TIMET   skipTime;
static U16     randSeed;

BOOL oInit(SYSCBlk* sysblk)
{
	randSeed = (U16)oTimerGet1MsTick();
	
	oSysTimerInit(sysblk);
	JG_TimerInit();

	/*INITIALIZE SYSTEM VARIABLE FOR DEVICE*/
	DevInit(sysblk);
	
	skipTime = 0;

#if KERNEL_INIT_VIEW == ENABLED
	xprintf("K>System Init ... OK\n");
#endif	

	return TRUE;    
}

TIMET oGetSystemTime(void)
{
	return (TIMET)(oTimerGet1MsTick() + skipTime);
}

U16 oRand(void)
{
	randSeed = 25173 * randSeed + 13849;
	return randSeed;
}


/* oMemCopy:
	oMemCopy is designed to using generally, so it is not effcient at some times.
	if you can make memory-copy function faster than the function in this kernel, 
	you can code in here by youself such as using 'memcpy()' in compiler lib*/
void oMemCopy(U8 *dest, const U8 *source, U32 numBytes)
{
	while (numBytes--)
		*dest++ = *source++;    
}

/* this is used to copy memory with reverse access*/
void oRevMemCopy(U8 *dest, U8 *source, U32 numBytes)
{
	
	U8 *end = (source+numBytes-1);
	
	while (numBytes--)
		*dest++ = *end--;    

}

BOOL oMemCmp(const U8 *buffer1, U16 len1, const U8 *buffer2, U16 len2)
{
	if (len1 == len2) {
		while (len1--) {
			if (*buffer1++ != *buffer2++)
				return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

/*oMemSet : 
	oMemSet is designed to using generally, so it is not effcient at some times.
	If you can make memory-copy function faster than the function in this kernel, 
	you can code in here by youself such as using 'memset()' in compiler lib*/
void oMemSet(U8 *dest, U8 byte, U32 len)
{
	while (len--)
		*dest++ = byte;

}

U8 oStrCmp(const char *Str1, const char *Str2)
{
	while (*Str1 == *Str2) {
		if (*Str1 == 0 || *Str2 == 0) {
			break;
		}
		Str1++;
		Str2++;
	}

	if (*Str1 == *Str2)
		return 0;

	return 1;
}

U16 oStrLen(const char *Str)
{
	const char  *cp = Str;

	while (*cp != 0)
		cp++;

	return (U16)(cp - Str);
}


void oTimerDelay(U32 count)
{
	U32		start_tmp;

	start_tmp = oTimerGet1MsTick();

	while((oTimerGet1MsTick() - start_tmp)  <= count ){
	#if WATCH_DOG == ENABLED
		RstWatchdog();
	#endif
	}
	
}

void oForDelay(U32 count, U32 value){
	//0x09C0 : 1msec
	U32 j,k;
	
	for(j=0;j<count;j++){
		#if WATCH_DOG == ENABLED
			RstWatchdog();
		#endif
		for(k=0;k<value;k++){
		}
	}
	
}

U32 o4to32(U8 *ch){
	U32 temp;
	//big endian
#if 0
	//temp = *ch;

#else
	temp = ch[1]|(ch[0]<<8);
	temp = (temp<<16)|(U16)((ch[3])|(ch[2]<<8));
#endif	
	return temp;
}

#if USE_GET5usTICK == ENABLED
void oTimerDelay5us(U32 count)
{	
	U32 start_tmp;
	
	start_tmp = oTimerGet5usTick();

	while((oTimerGet5usTick() - start_tmp)  <= count ){
	#if WATCH_DOG == ENABLED
		RstWatchdog();
	#endif
	}

}
#endif

#if KERNEL_DEBUG == ENABLED
void oAssert(const char *expression, const char *file, U16 line){

}
#endif

