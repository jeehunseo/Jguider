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


#include "photo.h"

/*GLOBAL VARIABLE*/

/*FUNCTION PROTOTYPE*/
int PHOTO_open(nDEV numdev, nOPT option);
ssize_t PHOTO_write(FILED *filp, unsigned char *buf, unsigned int count);
ssize_t PHOTO_read(FILED *filp, unsigned char *buf, unsigned int count);
IOCTL PHOTO_ioctl(FILED *filp, unsigned int cmd, unsigned long arg);
int PHOTO_close(nDEV numdev, nOPT option);

/*DRIVER STRUCTURE*/
OS_FOP PHOTO_fop;


int PHOTO_insmod(SYSCBlk* sysblk, nDEV numdev){
	int ret;  
	OS_FOP* tPHOTO_fop = &PHOTO_fop;
	
	tPHOTO_fop->open = PHOTO_open;
	tPHOTO_fop->read = PHOTO_read;
	tPHOTO_fop->write = 0;
	tPHOTO_fop->ioctl = PHOTO_ioctl;
	tPHOTO_fop->close = PHOTO_close;

	ret = addfdlist(numdev,tPHOTO_fop);

	return ret;
}

int PHOTO_open(nDEV numdev, nOPT option){
	return 0;
}

ssize_t PHOTO_read(FILED *filp, unsigned char *buf, unsigned int count)
{
	return count;
}

IOCTL PHOTO_ioctl(FILED *filp, unsigned int cmd, unsigned long arg)
{
	int ret = 0;
	
	switch(cmd){
	case CMD_WD_SAMPLE_RATE:
		break;
	case CMD_DF_SAMPLE_RATE:
		break;
	default:
		ret = -1;
		break;
	}
	return ret;
}


int PHOTO_close(nDEV numdev, nOPT option){
	return TRUE;  
}

#if USE_RMMODE == ENABLED
int PHOTO_rmmod(nDEV numdev){

	return deletefdlist(numdev);		
}
#endif
