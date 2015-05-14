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

#ifndef __SERVO_H
#define __SERVO_H

#include "fdlist.h"


/*----------------- EXTERNAL PARAMETER & FUNCTION----------------------------------------------------------------------*/
// 1. device identificated number
#define DEV_NUM_SERVO 50

// 2. device insert module function 
int SERVO_insmod(SYSCBlk* sysblk, nDEV numdev);
#if USE_RMMODE == ENABLED
int SERVO_rmmod(nDEV numdev);
#endif

// 3. device command 
#define CMD_SET_DEGREE 0x01



/*----------------- INNER PARAMETER----------------------------------------------------------------------------------------*/
#define MAX_DEGREE_VALUE 125
#define MIN_DEGREE_VALUE 28


#endif
