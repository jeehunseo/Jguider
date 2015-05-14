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

#ifndef __CONFIG_H
#define __CONFIG_H

#include "override.h"

/*------------------SETTING OF COMMUNICATION------------------*/
/*ACTIVATE UART0 AND UART1*/
#define USE_UART0 ENABLED
#define USE_UART1 DISABLED

/*CHECK LRC*/
#define USE_LRC_CHK DISABLED

/*THE NUMBER OF RXBUFFER*/
// Don't change this value: The number that is more than 3 will be served in near future.
#define MAX_nTMP_BUF 2 

/*THE SIZE OF RXBUFFER*/
#define SERIAL_BUFFER_SIZE		512
#define UART0_RxBUFF_SIZE	(SERIAL_BUFFER_SIZE + 8) // 8: header size 
#define UART1_RxBUFF_SIZE	(SERIAL_BUFFER_SIZE + 8)

/*THE SIZE OF GOTHROUGH TMP BUFFER*/
#define GOTHROU_BUF_SIZE (UART0_RxBUFF_SIZE -8)

/*THE SPEED OF UART COMMUNICATION*/
#define DEFAULT_UART_SPEED 115200L

/*------------------SETTING OF SYSTEM------------------*/
/*ACTIVATE WATCH DOG */
#define WATCH_DOG ENABLED

/*ACTIVATE DEVICE RMMODE*/
#define USE_RMMODE DISABLED


#endif
