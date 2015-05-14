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

#if USE_UART0 == ENABLED

// global variable 
static pFunctVoid rx0State;
static U8 rxChar; 
static U16 rxsCount;
static U16 dataLen;
static U8 lrc;
static BOOL rxdone;
static U16 myNumSource = ADDR_DEFAULT;// default setting  
static U16 myNumDesti = ADDR_PC; // default setting
static U8 g_err;

U8 rxtemp[MAX_nTMP_BUF][UART0_RxBUFF_SIZE];
U8 nRxtemp;

#if USE_UART1 == ENABLED
U8 u0txtemp[GOTHROU_BUF_SIZE];
U16 u0lentemp;
U32 u0timetemp = GOTHROU_DEFUAT_TIME;
#endif

U8 *pRxtmp;	// temporarily pointer of Rx buff
U8 *pRxData;	// pointer of Rx buff
int RxLen;
BOOL skipped_Rxdata;

// struct 
OS_FOP URT0_fop;

// function prototype 
int URT0_open(nDEV numdev, nOPT option);
ssize_t URT0_write(FILED *filp, unsigned char *buf, unsigned int count);
ssize_t URT0_read(FILED *filp, unsigned char *buf, unsigned int count);
int URT0_close(nDEV numdev, nOPT option);

static void stNull(void);
static void stSTX(void);
static void stSEQ(void);
static void stDST(void);
static void stSRC(void);
static void stFCMD(void);
static void stLEN(void);
static void stDAT(void);
static void stLRC(void);
static void stETX(void);
static void Sv_tBuff(void);


#if USE_UART1 == ENABLED
U8 GoThroughTxUart0fr(U8 *tx,int RxLen){
	// Duplicate Uart1's data to Uart0's
	// This function is used to be called in Uart0's file.
	if(u0lentemp != 0){
		return err(ERR_GOTHROU_UART0_OVERFLOW,WHR_GOTHROUGHTX0FR);
	}else{	
		oMemCopy(u0txtemp,tx,RxLen);
		u0lentemp = RxLen;
		u0timetemp = oGetSystemTime();
	}
	return 0;
	
}
#endif

void URT0_rxRready(BOOL enable)
{
	if (enable)
		rx0State = stSTX;
	else
		rx0State = stNull;
}


/**** HARDWARE INTERRUPT CALL FUNCTION *********
     -> This function is called in system interrput 
************************************************/
void __IntrCall_Uart0(U8 rx){
	rxChar = rx;
	rx0State();
}


static void Sv_tBuff(void){
	if(rxsCount > UART0_RxBUFF_SIZE){// temporarily setting
		// ignore
		rx0State = stSTX;
	}else{
		pRxtmp[rxsCount]= rxChar; // temp buff
		lrc ^= rxChar;
		rxsCount++;
	}
}

static void stNull(void){
	// NULL
}

static void stSTX(void){
	if(rxChar == UA_STX){
		rxsCount = 0;
		dataLen = 0;
		lrc = 0;
		rx0State = stSEQ;
	}
}

static void stSEQ(void){
	Sv_tBuff();
	rx0State = stDST;
}

static void stDST(void){
	static U8 count=0;

	Sv_tBuff();
	if(++count >= 2){
		count=0;
		rx0State = stSRC;
	}else{
		rx0State = stDST;
	}
}

static void stSRC(void){
	static U8 count=0;

	Sv_tBuff();
	if(++count >= 2){
		count=0;
		rx0State = stFCMD;
	}else{
		rx0State = stSRC;
	}	
}

static void stFCMD(void){
	Sv_tBuff();
	rx0State = stLEN;	
}

static void stLEN(void){
	static U8 count=0;

	Sv_tBuff();
	if(++count >= 2){
		count=0;
		dataLen |= (U8)(rxChar);
		if(dataLen ==0x00){
			rx0State = stLRC;
		}else{
			rx0State = stDAT;
		}
		
		if(dataLen > UART0_RxBUFF_SIZE){
			// occur length error is ignored
			rx0State = stSTX;
			count =0;
		}
	}else{
		dataLen = (U16)((rxChar<<8)&0xFF00);
		rx0State = stLEN;
	}	
}

static void stDAT(void){
	static U32 count=0;

	Sv_tBuff();
	if((++count) >= dataLen ){
		count=0;
		rx0State = stLRC;	
	}else{
		rx0State = stDAT;
	}
}

static void stLRC(void){
	Sv_tBuff();
	rx0State = stETX;	
}

static BOOL chkDST(U8 *dat){
	U16 tmpDst;
	
	tmpDst = (U16)((dat[1]<<8)|dat[2]);
	if(tmpDst & myNumSource)
		return TRUE;
		
	return FALSE;
}

U8 *newpBuf(void)
{
	if(++nRxtemp >= MAX_nTMP_BUF)
		nRxtemp = 0;// initialize
#if KERNEL_DEBUG == ENABLED
	//xprintf("\nK> We will use buffer[%d]\n",nRxtemp);
#endif

	return rxtemp[nRxtemp];
}

static void stETX(void){
	int errno;
#if USE_UART1 == ENABLED
	U8 tmp;
#endif	

	if(rxChar == UA_ETX){
	#if USE_LRC_CHK == ENABLED	
		if(lrc == UA_LRC_OK)
	#else
		if(TRUE)
	#endif
		{
	#if KERNEL_DEBUG == ENABLED	
		xprintf("\nK> Received frame DATA from PC \n");
	#endif	
			if(pRxData != 0){
				skipped_Rxdata = TRUE;
				errno = err(ERR_RXUART0_BUFF_OVERFLOW_RCV_SKIP,0);
				/*Overflow is occured in Rxbuffer*/
				g_err |= ERR_RXBUF_FULL;
			}else{
				pRxData = &pRxtmp[8];// pointer of the first data
				RxLen = dataLen;
				
				pRxtmp = newpBuf();
				
				if(chkDST(pRxData)){
					if(pRxtmp[7] == FCMD_ERR_JAM_IN_TUBE) // check command
						g_err |= ERR_GOTHROU_JAM;
						
					rxdone = TRUE;
				}else{
				#if USE_UART1 == ENABLED	
					// pRxtmp : All data of Rx frame execpt for STX and ETX 
					errno = GoThroughTxUart1fr(pRxtmp,rxsCount);
					if(errno <0)
					{
						/* reflect received data to source address (BIG_ENDIAN)*/
						tmp = pRxtmp[1];
						pRxtmp[1]= pRxtmp[3];
						pRxtmp[3] = tmp;
						tmp = pRxtmp[2];
						pRxtmp[2]= pRxtmp[4];
						pRxtmp[4] = tmp;
						pRxtmp[5] = FCMD_ERR_JAM_IN_TUBE;
						
						Uart0SendByte(UA_STX);
						Sendrdata(pRxtmp,rxsCount,SEL_SEND_UART0);
						Uart0SendByte(UA_ETX);
					}
					pRxData = 0;
				#endif
				}
			}
			
		}else{
			errno = err(ERR_LRC_UART0_DEV,0);
			
		}
	}	
	
	errno = errno;// eliminate warning 
	rx0State = stSTX;	
}



int URT0_insmod(SYSCBlk* sysblk, nDEV numdev){
	int ret;  
  	OS_FOP* tURT0_fop = &URT0_fop;
	
	tURT0_fop->open = URT0_open;
	tURT0_fop->read = URT0_read;
	tURT0_fop->write = URT0_write;
	tURT0_fop->ioctl = URT0_ioctl;
	tURT0_fop->close = URT0_close;

	ret = addfdlist(numdev,tURT0_fop);
	
	/* initialize device drv */
	nRxtemp =0;
	pRxtmp = rxtemp[nRxtemp];
	skipped_Rxdata = FALSE;
	rx0State = stNull;
	
	Uart0Init();
	Uart0SetSpeed(DEFAULT_UART_SPEED);
	Uart0EnableRx(TRUE);
	
	
	return ret;
}

int URT0_open(nDEV numdev, nOPT option){
  
	/* initialize valuable */
	rxdone = FALSE;  
	URT0_rxRready(TRUE);
	return 0;
}

ssize_t URT0_write(FILED *filp, unsigned char *buf, unsigned int count)
{
	U8 slrc = 0;

	//__disable_interrupt();

	Uart0SendByte(UA_STX);
	slrc ^= headerSend(0x01,myNumDesti,myNumSource,FCMD_APP_DATA,SEL_SEND_UART0); // seq(1) + des(2) + src(2)+ fcmd(1)
	slrc ^= Sendrdata(buf, count, SEL_SEND_UART0); // length(2) + acmd(1) + data(n) 
	Uart0SendByte(slrc);
	Uart0SendByte(UA_ETX);

	//__enable_interrupt();
	return count;
}

ssize_t URT0_read(FILED *filp, unsigned char *buf, unsigned int count)
{
	ssize_t ret;

	if(count == RD_FB){
		/* USED TO READ ACMD */
		buf[0] = pRxData[0];
		return 0;
	}
	
	if(rxdone == TRUE){
		
		if(RxLen > count)
			return err(ERR_RD_BUF_OVERFLOW,0);			
		
		if(count >= RxLen){
			oMemCopy(buf,pRxData,RxLen);
			rxdone = FALSE;
			pRxData = 0;
			ret = RxLen;
			
		}else{// count < RxLen
			oMemCopy(buf,pRxData,count);
			pRxData += count;
			RxLen -= count;
			ret = count;
		}
	}else
  		return err(ERR_EMPTY_RXBUFF_UART0,0);
	
	if((skipped_Rxdata == TRUE)&&(count >= RxLen)){
		// As soon as finishing reading all data in buffer, it read next buffer
		skipped_Rxdata = FALSE;
		
		pRxData = &pRxtmp[8];
		RxLen = dataLen;
		pRxtmp = newpBuf();
		rxdone = TRUE;
		
	#if KERNEL_DEBUG == ENABLED
		xprintf("\nK>activate skipped rxbuffer\n",nRxtemp);
	#endif
	}
		
	return ret;
}

IOCTL URT0_ioctl(FILED *filp, unsigned int cmd, unsigned long arg)
{
	int ret =0;
	
	switch(cmd){
	case CMD_SET_BAUD:
		Uart0EnableRx(FALSE);
		URT0_rxRready(FALSE);
		Uart0SetSpeed(arg);
		URT0_rxRready(TRUE);
		Uart0EnableRx(TRUE);
		break;
	
	case CMD_TX_DST_WR:
		myNumDesti = (U16)(arg);
		break;
	
	case CMD_RD_RXDONE:
		if(rxdone != TRUE)
			ret = -1;
		break;
	
	case CMD_WR_RXDONE:
		rxdone = (U8)(arg);
		break;
		
	case CMD_GOTHROU_CHKSEND:
	#if USE_UART1 == ENABLED
		// check there is some data which go through 'uart1'
		if(u0lentemp != 0){
			u0lentemp = 0;
						
			Uart0SendByte(UA_STX);
			Sendrdata(u0txtemp, u0lentemp, SEL_SEND_UART0);
			Uart0SendByte(UA_ETX);
			ret = TRUE;
			
			// go through timer is cleared
			u0timetemp = GOTHROU_DEFUAT_TIME;
		}else
			ret = FALSE;
	#endif
		break;

	case CMD_COMPARE_GOTHROU_TIME:
	#if USE_UART1 == ENABLED
		if(u0lentemp != 0){
			if(u0timetemp > u1timetemp)
				ret = TRUE;
			else
				ret = FALSE;
		}else
			ret = -1;
	#endif
		break;

	case CMD_RD_UART_ERR:
		// it is used to send error number which occur in Uart Driver to application processor
		if(g_err !=0 ){
			ret =(U8)(g_err);
		}else
			ret = 0;
		break;
	
  }
  
  return ret;
}


int URT0_close(nDEV numdev, nOPT option){
	URT0_rxRready(FALSE);
	return TRUE;

}

#if USE_RMMODE == ENABLED
int URT0_rmmod(nDEV numdev){
	int ret;  
  
	oMemSet((U8*)&URT0_fop,0, sizeof(OS_FOP));
	Uart0EnableRx(FALSE);
	return deletefdlist(numdev);
}
#endif

#endif

