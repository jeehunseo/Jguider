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

#include "reg.h"

void CheckReg(void){
	// check for validate of device's driver
	static int test= -1;
	
	test |= registerDEV(DEV_NUM_EEPROM); //<--
	test |= registerDEV(DEV_NUM_UART0FR);
	test |= registerDEV(DEV_NUM_SERVO);
	test |= registerDEV(DEV_NUM_MOTION);
	test |= registerDEV(DEV_NUM_SONIC);
	test |= registerDEV(DEV_NUM_PHOTO);
	
	test=test;

#if KERNEL_INIT_VIEW == ENABLED
	xprintf("K>Reg check ... OK\n");
#endif

}


