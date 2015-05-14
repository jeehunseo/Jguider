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

// sine �İ� ���ܼ� �̷��� ����� ���ϸ� �ȵ�!! ��յ� sine�ĸ� Ž.. 
// hardware���� �����ϱ� �������� �ּ� ó�� �Ұ� 
#define NO_NOISE_MODE DISABLED
#define NOISE_MODE ENABLED

/*when you are change the max sampling value,
you should be cauful of sum-overflow*/
#define MAX_SAMPLING_VALUE 209 

/*���ܼ��������� sine �İ� �߻�.. ��.. 6msec�� �ֱ⸦ ���´�.. 
 �׷��� 6msec�� ����ν� sampling�� �������� �ۼ�.. 
 -> 24msec�� ���߱� ���ؼ� 209�� sampling.. */
#define DEFAULT_SAMPLING_RATE 209

#define SIZE_PHOTO_DATA_OF_BUF 2


#endif
