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

#ifndef __MOTION_H
#define __MOTION_H

#include "fdlist.h"


/*----------------- EXTERNAL PARAMETER & FUNCTION----------------------------------------------------------------------*/
// 1. device identificated number
#define DEV_NUM_MOTION 150

// 2. device insert module function 
int MOT_insmod(SYSCBlk* sysblk, nDEV numdev);
#if USE_RMMODE == ENABLED
int MOT_rmmod(nDEV numdev);
#endif

// 3. device command 
#define CMD_SENSOR_ON 0x01
#define CMD_SENSOR_OFF 0x02
#define CMD_WR_SENSITIVITY 0x03
#define CMD_CHANGE_FILTER 0x04
#define CMD_LOOP_CHECK 0x05
#define CMD_RD_CURRENT_MOVEMENT 0x06
#define CMD_FREQ_CLEAR 0x07


/*----------------- INNER PARAMETER----------------------------------------------------------------------------------------*/
#define SIZE_MOT_DATA_OF_BUF 8  /* 6 bytes로 구성 (4byte : time , 4bytes : Freq time)*/
#define MOTION_BUFF_SIZE 5 // 최악의 경우 5초 동안 read 되어지지 않을 수 없다고 봄  
#define DEFAULT_SENSITIVITY 0 //0x100

/*degree of sensing time*/
#define FILTER_1MIN 6
#define FILTER_1SEC 0

#define MASK_1MIN rMinRMASK
#define MASK_1SEC rSecMASK


#endif

