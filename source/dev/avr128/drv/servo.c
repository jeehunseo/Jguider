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

#include "servo.h"

// function prototype 
int SERVO_open(nDEV numdev, nOPT option);
IOCTL SERVO_ioctl(FILED *filp, unsigned int cmd, unsigned long arg);
int SERVO_close(nDEV numdev, nOPT option);

OS_FOP SERVO_fop;

int SERVO_insmod(SYSCBlk* sysblk, nDEV numdev){
	int ret;  
	OS_FOP *tSERVO_fop = &SERVO_fop;
	
	tSERVO_fop->open = SERVO_open;
	tSERVO_fop->read = 0;
	tSERVO_fop->write = 0;
	tSERVO_fop->ioctl = SERVO_ioctl;
	tSERVO_fop->close = SERVO_close;

	ret = addfdlist(numdev,tSERVO_fop);//���� ����ϰ� �ִ� fop struct�� pointer�� fdlist�� �����Ѵ� 

	return ret;
}

int SERVO_open(nDEV numdev, nOPT option){
  
	OUTPORT(POUT);
	TIMER_MODE_ENABLE();
	TIMER_OUT_SEL();
	TIMER_PRESCALER();
	TIMERVAL_INIT();
	
	return 0;
}

IOCTL SERVO_ioctl(FILED *filp, unsigned int cmd, unsigned long arg)
{
	IOCTL ret = 0;
	
	switch(cmd){
	case CMD_SET_DEGREE:
		if(arg <= 180){
			DUTY_RATE((U16)(MIN_DEGREE_VALUE + ((MAX_DEGREE_VALUE - MIN_DEGREE_VALUE)*arg)/180));
		}else{
			ret = -1;
		}
		break;

/*
	motor�� �����ϰ�
	���� �����Ѱ��� � �������� Ȯ�����ش� 
	or 
	OPEN ���� numdev�� �޾Ƽ� ó������ �Ǵ��� ��!!
	
  case CMD_RD_:
  	break;
  	
  case CMD_SLOW_MODE_ON:
  	 break;
*/

	default:
		ret = -1;
		break;
	}

	return ret;
}


int SERVO_close(nDEV numdev, nOPT option){

	OUTPORT(PIN);
	TIMER_MODE_DISABLE();

	return TRUE;

}

#if USE_RMMODE == ENABLED
int SERVO_rmmod(nDEV numdev){

	return deletefdlist(numdev);		
}
#endif
