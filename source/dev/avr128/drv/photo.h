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

#ifndef __PHOTO_H
#define __PHOTO_H

#include "fdlist.h"


/*----------------- EXTERNAL PARAMETER & FUNCTION----------------------------------------------------------------------*/
// 1. device identificated number
#define DEV_NUM_PHOTO 110

// 2. device insert module function 
int PHOTO_insmod(SYSCBlk* sysblk, nDEV numdev);
#if USE_RMMODE == ENABLED
int PHOTO_rmmod(nDEV numdev);
#endif

// 3. device command 
#define CMD_WD_SAMPLE_RATE 0x01 
#define CMD_DF_SAMPLE_RATE 0x02


/*----------------- INNER PARAMETER----------------------------------------------------------------------------------------*/

// sine 파가 생겨서 이렇게 평균을 구하면 안됨!! 평균도 sine파를 탐.. 
// hardware에서 수정하기 전까지는 주석 처리 할것 
#define NO_NOISE_MODE DISABLED
#define NOISE_MODE ENABLED

/*when you are change the max sampling value,
you should be cauful of sum-overflow*/
#define MAX_SAMPLING_VALUE 209 

/*적외선센서에서 sine 파가 발생.. 약.. 6msec의 주기를 갖는다.. 
 그래서 6msec의 배수로써 sampling을 기준으로 작성.. 
 -> 24msec를 맞추기 위해서 209로 sampling.. */
#define DEFAULT_SAMPLING_RATE 209

#define SIZE_PHOTO_DATA_OF_BUF 2


#endif
