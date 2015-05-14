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

#include "serialtask.h"


/*STRUCTURE FOR MAKING TASK*/
TaskContrBlk serialTask;
Trdata serial_data;

SerialBufForm Serialbuf0[SIZE_SERIAL_MSG_BUFF];

int uartfd[SERIAL_FILE_SIZE];

BOOL systemSerialCommand(Dbts* ts, Trdata* trd, U8* data, int len);
void synchtimeValue(Dbts* ts, U8 *rxData);

void serial0Base(Dbts* ts, Trdata* trd);
void serial1Base(Dbts* ts, Trdata* trd);

void serialTaskInit(Dbts* ts, Trdata *tr){
	Trdata *pserial_data = &serial_data;

	/*INITIALIZATION OF THE TRANSFER DATA*/
	oMemSet((U8*)pserial_data, 0, sizeof(Trdata));
	pserial_data->status = 0xFF;
	pserial_data->pNext = serial0Base;
	pserial_data->tid = TID_SERIAL;

	/*device open */
	pserial_data->pfd = uartfd;
	pserial_data->pfd[FILE_UART0]= open(DEV_NUM_UART0FR,0);
#if USE_UART1 == ENABLED
	pserial_data->pfd[FILE_UART1]= open(DEV_NUM_UART1FR,0);
#endif

	/*TRDATA IS LINKED UP WITH TCB*/
	serialTask.trdata = pserial_data;

	insertMsgBox(pserial_data->tid,(U8*)&Serialbuf0, sizeof(Serialbuf0));

}

void serial0Base(Dbts* ts, Trdata* trd){
	int len;
	U8 rxData[SERIAL_BUFFER_SIZE];

	SerialBufForm SerialBuf;
	SerialBufForm txBuf;

	// SERIAL RX PROCESS
	len = read(trd->pfd[FILE_UART0],rxData, sizeof(rxData));
	if(len >= 0){
		
		switch(rxData[0]){
		case ACMD_HELLO_SERIALTASK:
			// 1. make cmd
			txBuf.cmd = ARSP_HELLO_SERIALTASK;
			// 2. make data
			txBuf.data[0] ='J';
			txBuf.data[1] ='G';
			txBuf.data[2] ='V';
			txBuf.data[3] ='0';
			// 3. send message 
			SendMsg(trd->tid, TID_SERIAL, (U8*)&txBuf, sizeof(SerialBufForm));
			break;

		default:
			/* SYSTEM SERIAL COMMAND */
			systemSerialCommand(ts, trd, rxData, len);
			break;
			
		}
	}

	// TASK RX PROCESS
	do{
		len = RecvMsg(trd->tid, (U8*)&SerialBuf, sizeof(SerialBufForm));
		if(len >0){
			switch(SerialBuf.cmd){
			case BCMD_SERIAL_SEND:
				write(trd->pfd[FILE_UART0], SerialBuf.data, SerialBuf.len);
				break;
			}
		}
	}while(len >0);

	nextFunct(trd) = serial1Base;
	
}

void serial1Base(Dbts* ts, Trdata* trd){
	
	nextFunct(trd)= serial0Base;
	
}

BOOL systemSerialCommand(Dbts* ts, Trdata* trd, U8* data, int len){
	BOOL ret;
	
	switch(data[0]){
	case ACMD_ADMIN_USER_LOGIN:
		break;
		
	case ACMD_SYNCH_SYSTEMTIME:
		if(len == (sizeof(RTimeStruct) + sizeof(RTimeStruct) - 1)){// -1: ACMD 
			synchtimeValue(ts,&data[1]);
		}else
			ret = FALSE;
		break;
	}

	return ret;
}

void synchtimeValue(Dbts* ts, U8 *rxData){
	RYearStruct ryearStr;
	RTimeStruct rtimeStr;

	oMemCopy((U8*)&ryearStr,(U8*)&rxData[0], sizeof(RYearStruct));
	oMemCopy((U8*)&rtimeStr,(U8*)&rxData[0+sizeof(RYearStruct)], sizeof(RTimeStruct));
	SynchRYear(ts->pYear,&ryearStr);
	SynchRTime(ts->pRtime,&rtimeStr);	

}


