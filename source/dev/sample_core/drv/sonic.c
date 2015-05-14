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

#include "sonic.h"


// function prototype 
int SONIC_open(nDEV numdev, nOPT option);
ssize_t SONIC_read(FILED *filp, unsigned char *buf, unsigned int count);
IOCTL SONIC_ioctl(FILED *filp, unsigned int cmd, unsigned long arg);

OS_FOP SONIC_fop;

int SONIC_insmod(SYSCBlk* sysblk, nDEV numdev){
	int ret;  
	OS_FOP *tSONIC_fop = &SONIC_fop;
	
	tSONIC_fop->open = SONIC_open;
	tSONIC_fop->read = SONIC_read;
	tSONIC_fop->write = 0;
	tSONIC_fop->ioctl = SONIC_ioctl;
	tSONIC_fop->close = 0;

	ret = addfdlist(numdev,tSONIC_fop);

	return ret;
}

int SONIC_open(nDEV numdev, nOPT option){
	/*when it is initialized, sensor is activated  */
	return 0;
}

ssize_t SONIC_read(FILED *filp, unsigned char *buf, unsigned int count)
{
	return count;
}

IOCTL SONIC_ioctl(FILED *filp, unsigned int cmd, unsigned long arg)
{
	return 0;
}

#if USE_RMMODE == ENABLED
int SONIC_rmmod(nDEV numdev){
	return deletefdlist(numdev);		
}
#endif
