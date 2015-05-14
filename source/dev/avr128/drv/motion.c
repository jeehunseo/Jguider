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

// global variable
static U16 gSensivity;
static U8 Filter;

U8 mtbuf_lock = 1;
static U8 mtbuf_end; // because buffer size is not over 256
static U8 mtbuf_start;

rTIME motTim[MOTION_BUFF_SIZE];
U32 motBuf[MOTION_BUFF_SIZE];

U32 Freq_min1;
static U32 motionTick;

rTIME tsysTime;
rTIME *getSystime;
U8 MASK;

// function prototype 
int MOT_open(nDEV numdev, nOPT option);
ssize_t MOT_write(FILED *filp, unsigned char *buf, unsigned int count);
ssize_t MOT_read(FILED *filp, unsigned char *buf, unsigned int count);
IOCTL MOT_ioctl(FILED *filp, unsigned int cmd, unsigned long arg);
int MOT_close(nDEV numdev, nOPT option);

OS_FOP MOT_fop;

/*
	interrupt2개를 쓴다 
		: 1개를 쓸때 rising & falling 변환이 느려서 오동작 할 수 있음 
*/

/*the external interrupt0 for rising edge detecton */
#pragma vector = INT0_vect
__interrupt void START_interrupt(){
	motionTick = oGetSystemTime();
}

/*the external interrupt1 for falling edge detection*/
#pragma vector = INT1_vect
__interrupt void END_interrupt(){
	U32 tTime = oGetSystemTime()- motionTick;
	U8 tFilter;
	U8 tMASK;
	
	if(tTime >gSensivity){
		tFilter = Filter;
		tMASK = MASK;
		Freq_min1 += tTime;
		
		if( ( (tMASK) & (tsysTime>>tFilter) )  !=  ( (tMASK) & ((*getSystime)>>tFilter) )  ){
			mtbuf_lock = 1;
			if(++mtbuf_end > MOTION_BUFF_SIZE - 1 ) 
				mtbuf_end = 0;
			motBuf[mtbuf_end] = Freq_min1;
			motTim[mtbuf_end] = *getSystime;
			mtbuf_lock = 0;

			Freq_min1 = 0;
			tsysTime = (*getSystime);
			//xprintf("x\n");
		}
		
	}
	//else
		//xprintf(".");
		
}


int MOT_insmod(SYSCBlk* sysblk, nDEV numdev){
	int ret;  
	OS_FOP *tMOT_fop = &MOT_fop;
	
	tMOT_fop->open = MOT_open;
	tMOT_fop->read = MOT_read;
	tMOT_fop->write = MOT_write;
	tMOT_fop->ioctl = MOT_ioctl;
	tMOT_fop->close = MOT_close;

	ret = addfdlist(numdev,tMOT_fop);

	motionTick = 0;
	getSystime = &(sysblk->rtime);
	tsysTime = *getSystime;
	Freq_min1=0;
	Filter = FILTER_1MIN;
	MASK = MASK_1MIN;
	
	MOTION_PORT_OPEN();
	
	REG_SET(rEXTERNAL_INT_MOD,0x0E);

	return ret;
}

int MOT_open(nDEV numdev, nOPT option){
	/*when it is initialized, sensor is activated  */
	REG_SET(rEXTERNAL_INT_MASK,0x03);
	gSensivity = DEFAULT_SENSITIVITY;

	return 0;
}

ssize_t MOT_write(FILED *filp, unsigned char *buf, unsigned int count)
{
	ssize_t size;
	size = size;
	return size;
}

ssize_t MOT_read(FILED *filp, unsigned char *buf, unsigned int count)
{
	ssize_t size=0;
	U32 tmBuf;
	rTIME tmTim;

	if(count == 0){
		// 
		tmBuf = Freq_min1;
		oMemCopy((U8*)&buf[0], (U8*)&tmBuf, 4);
		
		// 현재의 freq 전달 
		tmBuf = *getSystime;
		oMemCopy((U8*)&buf[4], (U8*)&tmBuf, 4);
		return 8;	
	}
	
	if(mtbuf_lock == 1)
		return err(ERR_RD_NODATA,0);// interrupt 처리 중 이거나 data 없음 
	
	while(mtbuf_end !=mtbuf_start){
		
		if(++mtbuf_start >MOTION_BUFF_SIZE - 1)
			mtbuf_start =0;
		
		tmBuf = motBuf[mtbuf_start];
		tmTim = motTim[mtbuf_start];

		if(count < size + SIZE_MOT_DATA_OF_BUF)
			return err(ERR_RD_BUF_OVERFLOW,0);// 얻어오는 buffer의 size가 적음 

		/* BUFFER STRUCT : rTIME(4byte) |Freq_H ~ Freq_L(4byte) */
	
		oMemCopy((U8*)&buf[size], (U8*)&tmBuf, sizeof(U32));
		size += 4;	
		oMemCopy((U8*)&buf[size],(U8*)&tmTim, sizeof(rTIME));
		size += 4;
		mtbuf_lock = 1;
	}
	

	return size;
}

IOCTL MOT_ioctl(FILED *filp, unsigned int cmd, unsigned long arg)
{
	IOCTL ret = 0;
	U8 tFilter;
	U8 tMASK;
	
	//oStopHardware();
	
	switch(cmd){
		case CMD_SENSOR_ON:
		REG_SET(rEXTERNAL_INT_MASK,0x03);
		break;

	case CMD_SENSOR_OFF:
		REG_CLEAR(rEXTERNAL_INT_MASK,0x03);
		break;

	case CMD_WR_SENSITIVITY:
		gSensivity = (U16)arg;
		break;
		
	case CMD_CHANGE_FILTER:
		Filter = (U8)arg;
		MASK = (U8)(arg>>8);
		break;
		
	case CMD_RD_CURRENT_MOVEMENT:
		if(Freq_min1 > arg)
			ret = TRUE;
		else
			ret = FALSE;
		break;
		
	case CMD_LOOP_CHECK:
		tFilter = Filter;
		tMASK = MASK;
	
		if( ( (tMASK) & (tsysTime>>tFilter) )  !=  ( (tMASK) & ((*getSystime)>>tFilter) )  ){
			mtbuf_lock = 1;
			if(++mtbuf_end > MOTION_BUFF_SIZE - 1 ) 
				mtbuf_end = 0;
			motBuf[mtbuf_end] = Freq_min1;
			motTim[mtbuf_end] = *getSystime;
			mtbuf_lock = 0;

			Freq_min1 = 0;
			tsysTime = (*getSystime);
		}
		break;
		
	case CMD_FREQ_CLEAR:
		Freq_min1 = 0;
		break;
		
	default:
		ret = -1;
		break;
	}
	
	//oResumeHardware();
	
	return ret;
}


int MOT_close(nDEV numdev, nOPT option){
  
	REG_CLEAR(rEXTERNAL_INT_MASK,0x03);

	return TRUE;
  
}

#if USE_RMMODE == ENABLED
int MOT_rmmod(nDEV numdev){

	return deletefdlist(numdev);		
}
#endif


