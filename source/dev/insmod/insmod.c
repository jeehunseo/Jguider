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

#include "insmod.h"

void InitDrv(SYSCBlk* sysblk){
	oStopHardware();

	// kernel require URT0 insmod!
	URT0_insmod(sysblk, DEV_NUM_UART0FR); //100

	/*insert all drv that is included in this module*/
	
	EEP_insmod(sysblk, DEV_NUM_EEPROM); //240
	SERVO_insmod(sysblk, DEV_NUM_SERVO); //50
	MOT_insmod(sysblk, DEV_NUM_MOTION); //150
	SONIC_insmod(sysblk, DEV_NUM_SONIC); //121
	PHOTO_insmod(sysblk, DEV_NUM_PHOTO); //209
	
	oResumeHardware();
	
}



