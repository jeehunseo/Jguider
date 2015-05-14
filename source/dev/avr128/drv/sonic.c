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

// global variable
static U32 sonic_start=0;
static U32 sonic_end=0;

// interrupt 7
#pragma vector = INT7_vect
__interrupt void SONIC_interrupt(){
	static U8 sonic_trigger =0;
	
	if(sonic_trigger++ == 0){
		sonic_start = oTimerGet5usTick();
		rEXTERNAL_INT_MOD_B = 0x80; // falling edge
	}else{
		sonic_trigger =0;
		sonic_end = oTimerGet5usTick();			
	}
}


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

	SONIC_PORT_OPEN();
	
  return ret;
}

int SONIC_open(nDEV numdev, nOPT option){
	/*when it is initialized, sensor is activated  */

	sonic_start=0;
	sonic_end=0;
	
	return 0;
}

ssize_t SONIC_read(FILED *filp, unsigned char *buf, unsigned int count)
{
	U32 time;

	if(count <SIZE_SONIC_DATA_OF_BUF)
		return err(ERR_RD_BUF_OVERFLOW,0);
		
	rEXTERNAL_INT_MOD_B |= 0xC0; // rising edge
	rEXTERNAL_INT_MASK |= 0x80; // enable int7
	
	// input signal
	DDRB_Bit3  = 1;
	PORTB_Bit3 = 1;
	oTimerDelay5us(4);	// 20us (triggger pulse 10us Min : SRF05)
	DDRB_Bit3 = 0;
	PORTB_Bit3  = 0; 
	
	oTimerDelay(35);	// 35msec (100us ~ 25ms, 30msec is overtime :SRF05 )
	
	time = sonic_end - sonic_start;

	buf[0] = (U8)(time>>24);
	buf[1] = (U8)(time>>16);
	buf[2] = (U8)(time>>8);
	buf[3] = (U8)(time);
	
	rEXTERNAL_INT_MASK &= ~0x80;
	
	return SIZE_SONIC_DATA_OF_BUF;
}

IOCTL SONIC_ioctl(FILED *filp, unsigned int cmd, unsigned long arg)
{
	IOCTL ret = 0;

	// temp
	
	return ret;
}

#if USE_RMMODE == ENABLED
int SONIC_rmmod(nDEV numdev){
	return deletefdlist(numdev);		
}
#endif
