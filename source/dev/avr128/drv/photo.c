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
unsigned int nSampling;

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

	PORTF_Bit0 = 0; // avrapi·Î ¿È±æ°Í 
	DDRF_Bit0 = 0;

	ADMUX = (0<<REFS1)|(1<<REFS0)|(1<<ADLAR);
	ADCSR = (0<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

  return ret;
}

int PHOTO_open(nDEV numdev, nOPT option){
	/*nSampling = 261 // 30msec : no test
		nSampling = 209 // 24msec
		nSampling = 156 // 18msec	*/
		  
	nSampling = DEFAULT_SAMPLING_RATE;  

	ADCSR	|= (1<<ADEN);

	return 0;
}

ssize_t PHOTO_read(FILED *filp, unsigned char *buf, unsigned int count)
{
 
	U32 total =0;
	U8 RdADC[2];
	U32 go;

	if(count < SIZE_PHOTO_DATA_OF_BUF)
		return err(ERR_RD_BUF_OVERFLOW,0);
	
	for(go =0; go < nSampling; go++){
		/* START CONVERSION	*/
		ADCSR	= ADCSR | (1<<ADSC);	
		/* INTERRUPT FLAG IS SET */
		while(!(ADCSR & 0x10));	
		RdADC[0] = (ADCL);
		RdADC[1] = (ADCH);
		
		/*INTERRUPT FLAG IS CLEARED */
		ADCSR &= ~0x10;
		
		/*CACULATE THE AVERAGE OF ADC VALUE*/
		
	#if NO_NOISE_MODE == ENABLED
		if(go == 0){
			total = (U16)(RdADC[1]<<8)|RdADC[0];
		}else
			total = ( total + ((U16)(RdADC[1]<<8)|RdADC[0]) ) / 2;
	#else
		total += (U16)(RdADC[1]<<8)|RdADC[0];
	#endif
	
	}

#if NOISE_MODE == ENABLED
	total = (U16)(total / nSampling);
#endif

	buf[0] = (U8)(total>>8);
	buf[1] = (U8)(total);
	
  return (SIZE_PHOTO_DATA_OF_BUF);
}

IOCTL PHOTO_ioctl(FILED *filp, unsigned int cmd, unsigned long arg)
{
	IOCTL ret = 0;
	
	switch(cmd){
	case CMD_WD_SAMPLE_RATE:
		if( MAX_SAMPLING_VALUE >= arg)
			nSampling = arg; 
		else
			return -2;	
		break;
		
	case CMD_DF_SAMPLE_RATE:
		nSampling = DEFAULT_SAMPLING_RATE;
		break;
		
	default:
		ret = -1;
		break;
	}
	
	return ret;
}


int PHOTO_close(nDEV numdev, nOPT option){

	ADCSR	&= ~(1<<ADEN);

	return TRUE;
  
}

#if USE_RMMODE == ENABLED
int PHOTO_rmmod(nDEV numdev){

	return deletefdlist(numdev);		
}
#endif
