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

#ifndef __APP_H
#define __APP_H

#include "dev.h"
#include "csched.h"
#include "msg.h"

#if KERNEL_DEBUG == DISABLED
// don't change this value 
#define DEVICE_DEBUG KERNEL_DEBUG;
#else
// YOU CAN CHANGE THIS VALUE TO SEE KERNEL_DEVICE_DEBUG INFO
#define DEVICE_DEBUG DISABLED;
//#define DEVICE_DEBUG ENABLED;
#endif

void DevInit(SYSCBlk* sysblk);
int registerDEV(nDEV numdev);
int open(nDEV numdev,nOPT option);
int read(int fd, void *buf, unsigned int count);
int write(int fd, void *buf, unsigned int count);
IOCTL ioctl(int fd, unsigned int cmd, unsigned long arg);
int close(nDEV numdev, nOPT option);

int getfd(nDEV numdev);

#endif
