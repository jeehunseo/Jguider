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

#include "eeprom.h"

unsigned int gAddr=0;

// function prototype 
int EEP_open(nDEV numdev, nOPT option);
ssize_t EEP_write(FILED *filp, unsigned char *buf, unsigned int count);
ssize_t EEP_read(FILED *filp, unsigned char *buf, unsigned int count);
IOCTL EEP_ioctl(FILED *filp, unsigned int cmd, unsigned long arg);
int EEP_close(nDEV numdev, nOPT option);

OS_FOP eep_fop;

int EEP_insmod(SYSCBlk* sysblk, nDEV numdev){
	int ret;  
	OS_FOP *teep_fop =&eep_fop;
	
	teep_fop->open = EEP_open;
	teep_fop->read = EEP_read;
	teep_fop->write = EEP_write;
	teep_fop->ioctl = EEP_ioctl;
	teep_fop->close = EEP_close;

	ret = addfdlist(numdev,teep_fop);// give the pointer of 'fop_struct' for kernel to add fdlist

	return ret;
}

int EEP_open(nDEV numdev, nOPT option){
	return 0;
}

ssize_t EEP_write(FILED *filp, unsigned char *buf, unsigned int count)
{
	return count;
}

ssize_t EEP_read(FILED *filp, unsigned char *buf, unsigned int count)
{
	return count;
}

IOCTL EEP_ioctl(FILED *filp, unsigned int cmd, unsigned long arg)
{
	return TRUE;
}


int EEP_close(nDEV numdev, nOPT option){
  
	return TRUE;
  
}

#if USE_RMMODE == ENABLED
int EEP_rmmod(nDEV numdev){

	return deletefdlist(numdev);		
}
#endif

