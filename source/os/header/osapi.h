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

#ifndef __OSAPI_H
#define __OSAPI_H


#include "hardware.h"
#include "timertick.h"
#if KERNEL_DEBUG == ENABLED
#include "printf.h"
#endif

BOOL oInit(SYSCBlk* sysblk);
TIMET oGetSystemTime(void);
U16 oRand(void);
void oMemCopy(U8 *dest, const U8 *source, U32 numBytes);
void oRevMemCopy(U8 *dest, U8 *source, U32 numBytes);
BOOL oMemCmp(const U8 *buffer1, U16 len1, const U8 *buffer2, U16 len2);
void oMemSet(U8 *dest, U8 byte, U32 len);
U8 oStrCmp(const char *Str1, const char *Str2);
U16 oStrLen(const char *Str);
void oTimerDelay(U32 count);
void oForDelay(U32 count, U32 value);
U32 o4to32(U8 *ch);

#if USE_GET5usTICK == ENABLED
	void oTimerDelay5us(U32 count);
#endif

#define REG_CLEAR(a,b) a &= ~b
#define REG_SET(a,b) a |= b

#define Assert(exp)  ((exp) ? (void)0 : oAssert(#exp,__FILE__,(U16)__LINE__))
#if KERNEL_DEBUG == ENABLED
	void oAssert(const char *expression, const char *file, U16 line);
#else
	#define oAssert(exp) (void)0
#endif


#endif
