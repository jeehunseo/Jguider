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

#ifndef __TYPES_H
#define __TYPES_H

/* BOOLEAN DEFINE */
#ifndef TRUE
	#define TRUE  (1==1)
#endif
#ifndef FALSE
	#define FALSE (0==1)  
#endif
#ifndef true
	#define true  (1==1)
#endif
#ifndef false
	#define false (0==1)  
#endif


/* COMMON DEFINES*/
#define ENABLED		true
#define DISABLED	false
#define NONE			0


/* BOOL DEFINE*/
#ifndef BOOL_DEFINED
typedef unsigned char	BOOL;
// typedef int BOOL;
#endif

/* UNSIGNED DEFINE*/
typedef unsigned long	U32;
typedef unsigned short	U16;
typedef unsigned char	U8;

/* SIGNED DEFINE*/
typedef long			S32;
typedef short			S16;
typedef char			S8;


#define INTEGER_SIZE 2 // <-- user setting 
/* INTEGER SIZE DEFINES*/
typedef unsigned long	I32;
#if INTEGER_SIZE == 4
	typedef unsigned long  I16;
	typedef unsigned long  I8;
#elif INTEGER_SIZE == 2
	typedef unsigned short I16;
	typedef unsigned short I8;
#elif INTEGER_SIZE == 1
	typedef unsigned short I16;
	typedef unsigned char  I8;
#else
	#error NO INTEGER_SIZE specified!!! You have to set it up in "types.h"
#endif

/* FUNCTION POINTER DEFINE*/
typedef void (*pFunctVoid) (void);

/* ETC */
typedef U32 TIMET;
typedef int IOCTL;

#endif
