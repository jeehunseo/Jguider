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

#include "uart0fr.h"
#include "uart1fr.h"

/****************************************** common *************************************/

pFunctHeader selu(U8 selnUart){
#if (USE_UART0 == TRUE) && (USE_UART1== TRUE)
	if(selnUart == SEL_SEND_UART0)
		return Uart0SendByte;
	else
		return Uart1SendByte;
#elif (USE_UART0 == FALSE)&&(USE_UART1== TRUE)
		return Uart1SendByte;
#else 
		return Uart0SendByte;
#endif	
}

void UartErrTask(IOCTL ret,U8 selnUart){
	
	if(ret&ERR_RXBUF_FULL){
		// 			
	}else if(ret&ERR_GOTHROU_JAM){
		// 반송된 data를 다시 보낼 수 있어야 한다 
	}
	
}

void Uart_Process(void){
	FILED *tmp=0;
	IOCTL ret;
	
	
#if (USE_UART0 == TRUE) && (USE_UART1== TRUE)	
	/* check synchro betwee u0's gothrough buffer 
	   and u01's and execute gothrough-process */
	if(u0timetemp < u1timetemp){
		URT0_ioctl(tmp, CMD_GOTHROU_CHKSEND, NONE);
		URT1_ioctl(tmp, CMD_GOTHROU_CHKSEND, NONE);
	}else{
		URT1_ioctl(tmp, CMD_GOTHROU_CHKSEND, NONE);
		URT0_ioctl(tmp, CMD_GOTHROU_CHKSEND, NONE);	
	}
#endif

	/* check the err code that we can read from 
	   Uart0/1 driver using 'ioctl'*/
#if (USE_UART0 == TRUE) && (USE_UART1== TRUE)	
	ret = URT0_ioctl(tmp, CMD_RD_UART_ERR, NONE);
	UartErrTask(ret,SEL_SEND_UART0);
	ret = URT1_ioctl(tmp, CMD_RD_UART_ERR, NONE);
	UartErrTask(ret,SEL_SEND_UART1);
#elif (USE_UART0 == FALSE)&&(USE_UART1== TRUE)
	ret = URT1_ioctl(tmp, CMD_RD_UART_ERR, NONE);
	UartErrTask(ret,SEL_SEND_UART1);
#else 
	ret = URT0_ioctl(tmp, CMD_RD_UART_ERR, NONE);
	UartErrTask(ret,SEL_SEND_UART0);
#endif

	tmp = tmp; // eliminate warning
}


U8 headerSend(U8 tSeq, U16 tDes, U16 tSrc,U8 tCmd, U8 selnUart){
	U8 uptDes, lwtDes;
	U8 uptSrc, lwtSrc;
	pFunctHeader pfunt;
	
	/******
	void (*pF)(unsigned char);
	pF = Uart0SendByte;
	*/

	pfunt = selu(selnUart);
	// Seq
	pfunt(tSeq);
	
	// Des
	uptDes = (U8)(tDes>>8);
	lwtDes = (U8)(tDes);
	pfunt(uptDes);
	pfunt(lwtDes);

	// Src
	uptSrc = (U8)(tSrc>>8);
	lwtSrc = (U8)(tSrc);
	pfunt(uptSrc);
	pfunt(lwtSrc);
  
	// cmd
	pfunt(tCmd);
	
	return tSeq^uptDes^lwtDes^uptSrc^lwtSrc^tCmd;
}


U8 Sendrdata(U8 *rdat, U16 count, U8 selnUart){
	U16 cnt;
	U8 lrc=0;
	pFunctHeader pfunt;
	
	pfunt = selu(selnUart);

	// length 
	pfunt((U8)(count>>8));
	pfunt((U8)(count));

	lrc ^= (U8)(count>>8);
	lrc ^= (U8)(count);

	// data
	for (cnt = 0; cnt < count ;cnt++){
		pfunt(rdat[cnt]);
		lrc ^= rdat[cnt];
	}
	
	return lrc;	
}



/********************************************uart0 *************************************/

void Uart0Init(void)
{
	oStopHardware();
	__UartInit();
	oResumeHardware();
}

void Uart0SetBaud( U32 baud)
{
	oStopHardware();
	UART0_SET_BAUDRATE(__CalBaud(baud));
	oResumeHardware();
}

void Uart0SetSpeed(U32 baud)
{
	oStopHardware();
	Uart0SetBaud(baud);
	oResumeHardware();
}

void Uart0EnableTx(BOOL enable)
{
	oStopHardware();
	TX0_ENABLE_INTR(enable);
	oResumeHardware();	
}

void Uart0EnableRx(BOOL enable)
{
	oStopHardware();
	RX0_ENABLE_INTR(enable);
	oResumeHardware();
}

void Uart0SendByte(U8 aByte)
{
	UART0_SEND(aByte);
}

/********************************************uart1 *************************************/
void Uart1Init(void)
{
	oStopHardware();
	UART1_SETTING();
	oResumeHardware();
}

void Uart1SetBaud( U32 baud )
{
	oStopHardware();
	UART1_SET_BAUDRATE(__CalBaud(baud));
	oResumeHardware();
}

void Uart1SetSpeed(U32 baud)
{
	oStopHardware();
	Uart1SetBaud(baud);
	oResumeHardware();
}

void Uart1EnableTx(BOOL enable)
{
	oStopHardware();
	TX1_ENABLE_INTR(enable);
	oResumeHardware();
}

void Uart1EnableRx(BOOL enable)
{
	oStopHardware();
	RX1_ENABLE_INTR(enable);
	oResumeHardware();
}

void Uart1SendByte(U8 aByte)
{
	UART1_SEND(aByte);
}

