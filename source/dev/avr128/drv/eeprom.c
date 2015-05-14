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

	// initialize address
	gAddr = 0;  
	
	return 0;
}

ssize_t EEP_write(FILED *filp, unsigned char *buf, unsigned int count)
{
	ssize_t size;
	unsigned int tmpAddr = gAddr;

	// address is started at 'gAddr'(global variable)
	// so, if you want to change eeprom address, first of all, you have to change 'gAddr' with 'ioctl()'. 
	for(size = 0; size< count ; size++){
		__EEPUT(tmpAddr++, buf[size]);
	} 

	return size;
}

ssize_t EEP_read(FILED *filp, unsigned char *buf, unsigned int count)
{
	ssize_t size;
	unsigned int tmpAddr = gAddr;

	// address is started at 'gAddr'(global variable)
	// so, if you want to change eeprom address, first of all, you have to change 'gAddr' with 'ioctl()'. 
	for(size = 0; size< count ; size++)
		__EEGET(buf[size], tmpAddr++); 

	return size;
}

IOCTL EEP_ioctl(FILED *filp, unsigned int cmd, unsigned long arg)
{
	IOCTL ret = 0;
	
	switch(cmd){
	case CMD_SET_ADDR:
		gAddr = (arg)&(0xFFFF);// change the value of 'gAddr' 
		break;
	case CMD_ADD_ADDR:
		gAddr += (arg)&(0xFFFF); // add some value into the value of 'gAddr'
		break;
	default:
		ret = -1;
		break;
	}

	return ret;
}


int EEP_close(nDEV numdev, nOPT option){
  
	return TRUE;
  
}

#if USE_RMMODE == ENABLED
int EEP_rmmod(nDEV numdev){

	return deletefdlist(numdev);		
}
#endif

