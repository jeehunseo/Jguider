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

#ifndef __UART1FR_H
#define __UART1FR_H

#include "uart.h"

#if USE_UART1 == ENABLED

#define DEV_NUM_UART1FR 101

#if USE_UART0 == ENABLED
	U8 GoThroughTxUart1fr(U8 *tx, int dataLen);
	extern U32 u1timetemp;
#else
	#define GoThroughTxUart0fr(a, b) (U8)0;
#endif

/*insmode & rmmode*/
int URT1_insmod(nDEV numdev);
#if USE_RMMODE == ENABLED
	int URT1_rmmod(nDEV numdev);
#endif

/*uart1 ioctl*/
IOCTL URT1_ioctl(FILED *filp, unsigned int cmd, unsigned long arg);


#endif
#endif
