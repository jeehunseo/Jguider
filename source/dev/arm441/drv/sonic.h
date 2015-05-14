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

#ifndef __SONIC_H
#define __SONIC_H

#include "fdlist.h"


/*----------------- EXTERNAL PARAMETER & FUNCTION----------------------------------------------------------------------*/
// 1. device identificated number
#define DEV_NUM_SONIC 121

// 2. device insert module function 
int SONIC_insmod(SYSCBlk* sysblk, nDEV numdev);
#if USE_RMMODE == ENABLED
int SONIC_rmmod(nDEV numdev);
#endif

// 3. device command 
#define CMD_1 0x01
#define CMD_2 0x02
#define CMD_3 0x03


/*----------------- INNER PARAMETER----------------------------------------------------------------------------------------*/


#endif
