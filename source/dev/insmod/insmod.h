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

#ifndef __INSMOD_H
#define __INSMOD_H

/* 
	If you want to insert your driver, you should add your header file to this "insmod.h".
*/

#include "uart0fr.h"
#include "uart1fr.h"
#include "eeprom.h"
#include "servo.h"
#include "motion.h"
#include "sonic.h"
#include "photo.h"

void InitDrv(SYSCBlk* sysblk);

#endif
