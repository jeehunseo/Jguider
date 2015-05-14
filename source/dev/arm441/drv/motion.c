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


#include "motion.h"

// function prototype 
int MOT_open(nDEV numdev, nOPT option);
ssize_t MOT_write(FILED *filp, unsigned char *buf, unsigned int count);
ssize_t MOT_read(FILED *filp, unsigned char *buf, unsigned int count);
IOCTL MOT_ioctl(FILED *filp, unsigned int cmd, unsigned long arg);
int MOT_close(nDEV numdev, nOPT option);

OS_FOP MOT_fop;


int MOT_insmod(SYSCBlk* sysblk, nDEV numdev){
	int ret;  
	OS_FOP *tMOT_fop = &MOT_fop;
	
	tMOT_fop->open = MOT_open;
	tMOT_fop->read = MOT_read;
	tMOT_fop->write = MOT_write;
	tMOT_fop->ioctl = MOT_ioctl;
	tMOT_fop->close = MOT_close;

	ret = addfdlist(numdev,tMOT_fop);

	return ret;
}

int MOT_open(nDEV numdev, nOPT option){
	return 0;
}

ssize_t MOT_write(FILED *filp, unsigned char *buf, unsigned int count)
{
	return count;
}

ssize_t MOT_read(FILED *filp, unsigned char *buf, unsigned int count)
{
	return count;
}

IOCTL MOT_ioctl(FILED *filp, unsigned int cmd, unsigned long arg)
{
	int ret = 0;
	
	switch(cmd){
		case CMD_SENSOR_ON:
		break;
	case CMD_SENSOR_OFF:
		break;
	case CMD_WR_SENSITIVITY:
		break;
	case CMD_CHANGE_FILTER:
		break;
	case CMD_RD_CURRENT_MOVEMENT:
		break;
	case CMD_LOOP_CHECK:
		break;
	case CMD_FREQ_CLEAR:
		break;
	default:
		ret = -1;
		break;
	}
	return ret;
}


int MOT_close(nDEV numdev, nOPT option){
	return TRUE;
}

#if USE_RMMODE == ENABLED
int MOT_rmmod(nDEV numdev){

	return deletefdlist(numdev);		
}
#endif


