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

#ifndef __DEV_H
#define __DEV_H

#include "hardware.h"
#include "types.h"
#include "config.h"
#include "error.h"
#include "override.h"

typedef int nDEV;
typedef char nFD;
typedef int nOPT;
typedef int ssize_t;

typedef struct _FILED_{
	// common information between drivers
	U8 test1;
	U8 test2;
	
	SYSCBlk* sysinfo;
	
}FILED;


typedef int (*PointerOpCl)(nDEV numdev,nOPT option);
typedef ssize_t (*PointerRdWr)(FILED *filp, unsigned char *buf, unsigned int count);
typedef IOCTL (*PointerIoctl)( FILED *filp, unsigned int cmd, unsigned long arg);

typedef struct _OS_FOP_ {
	PointerOpCl open;
	PointerRdWr read;
	PointerRdWr write;
	PointerIoctl ioctl;
	PointerOpCl close;
	int 	TID;
}OS_FOP;



#endif

