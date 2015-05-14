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

#ifndef __UART0FR_H
#define __UART0FR_H
#include "uart.h"

#if USE_UART0 == ENABLED

#define DEV_NUM_UART0FR 100
#define RD_FB 0x00

void __IntrCall_Uart0(U8 rx);

#if USE_UART1 == ENABLED
	U8 GoThroughTxUart0fr(U8 *tx, int dataLen);
	extern U32 u0timetemp;
#else
	#define GoThroughTxUart1fr(a, b) (U8)0
#endif

/*insmode & rmmode*/
int URT0_insmod(SYSCBlk* sysblk, nDEV numdev);
#if USE_RMMODE == ENABLED
	int URT0_rmmod(nDEV numdev);
#endif

/*uart1 ioctl*/
IOCTL URT0_ioctl(FILED *filp, unsigned int cmd, unsigned long arg);

#endif
#endif

