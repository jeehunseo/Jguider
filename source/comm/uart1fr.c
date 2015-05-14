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

#include "uart1fr.h"

#if USE_UART1 == ENABLED

// struct 
OS_FOP URT1_fop;

// function prototype 
int URT1_open(nDEV numdev, nOPT option);
ssize_t URT1_write(FILED *filp, unsigned char *buf, unsigned int count);
ssize_t URT1_read(FILED *filp, unsigned char *buf, unsigned int count);
int URT1_close(nDEV numdev, nOPT option);


#if USE_UART0 == ENABLED
U8 u1txtemp[GOTHROU_BUF_SIZE];
U16 u1lentemp;
U32 u1timetemp = GOTHROU_DEFUAT_TIME;
#endif


U8 GoThroughTxUart1fr(U8 *tx,int dataLen){
	
	return 0;
}


int URT1_insmod(nDEV numdev){
  int ret;  
  
  URT1_fop.open = URT1_open;
  URT1_fop.read = URT1_read;
  URT1_fop.write = URT1_write;
  URT1_fop.ioctl = URT1_ioctl;
  URT1_fop.close = URT1_close;
  
  ret = addfdlist(numdev,&URT1_fop);
	
	/* initialize device drv */
	
  return ret;
}

int URT1_open(nDEV numdev, nOPT option){
  
  /* initialize valuable */
  return 0;
}

ssize_t URT1_write(FILED *filp, unsigned char *buf, unsigned int count)
{
  
  return count;
}

ssize_t URT1_read(FILED *filp, unsigned char *buf, unsigned int count)
{
	ssize_t ret;
	
	return ret;
}

IOCTL URT1_ioctl(FILED *filp, unsigned int cmd, unsigned long arg)
{
	int ret =0;
  
  return ret;
}


int URT1_close(nDEV numdev, nOPT option){
	return TRUE;
}

#if USE_RMMODE == ENABLED
int URT1_rmmod(nDEV numdev){
	int ret;  
  
	oMemSet((U8*)&URT1_fop,0, sizeof(OS_FOP));
	Uart1EnableRx(FALSE);
	return deletefdlist(numdev);
}
#endif


#endif
