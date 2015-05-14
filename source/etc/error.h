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

#ifndef __ERROR_H
#define __ERROR_H

#include "override.h"

/* ERROR CODE FOR SYSTEM*/
#define ERR_GOTHROU_UART0_OVERFLOW -95
#define ERR_RXUART0_BUFF_OVERFLOW_RCV_SKIP -94 // Rxdata�� ó�� ���� �ʾƼ� 
#define ERR_EMPTY_RXBUFF_UART0 -95 // ���� RxData�� ���� 
#define ERR_PBUFF_UART0_ERR -95 // uart0���� buffer pointer�� �ű涧 error �߻� 
#define ERR_LRC_UART0_DEV -96 // uart0���� lrc error�϶� 
#define ERR_NO_REGISTED_DEV -97 // device�� ��� �Ǿ����� �ʴ�
#define ERR_DUPLICATED_NUMDEV -98 // �ߺ��� numDev�� �������
#define ERR_UNKNOWNED_NUM_DEV -99 // �˼� ���� numDev�� insmode ����
#define ERR_FDLIST_FULL -100 // FDlist�� �� á�� 
#define ERR_ALREADY_OPENED -101 // open�� �̹� ���� �Ǿ� �ִ� ������ device
#define ERR_DB_START_ADDRESS_NOT_SEARCH -102 // ���۵Ǵ� DB address�� ã�� ���� 
#define ERR_DB_FULL -103 // db�� �� �� 
#define ERR_NULL_FUNCTION_CALL_IN_TASK -104 // task���� next function pointer�� �߸� �Ǿ 0������ �� 
#define ERR_NULL_FUNCTION_CALL_IN_FASTTASK -105 // task���� next function pointer�� �߸� �Ǿ 0������ �� 
#define ERR_MSG_BUFF_OVERFLOW -106 // message�� buffer �� full�̶� error ó����嶧���� ��ٸ��ų� �ٸ���� 
#define ERR_CONTENTS_TLV_WRONG -107 // content���� tlv error�� �߻� 
#define ERR_NOT_ENOUGH_TXDATAFORM  -108 // TEMP_SIZE�� ũ�Ⱑ ������� ���� 
#define ERR_READ_BUFFER_POINTER_NULL -109 
#define ERR_WRITE_BUFFER_POINTER_NULL -110 

/*WHERE CODE*/
#define WHR_REGISTERDEV		-1	//registerDEV       
#define WHR_GETFD				-2	//getfd             
#define WHR_OPEN				-3	//open              
#define WHR_READ				-4	//read              
#define WHR_WRITE				-5	//write             
#define WHR_CLOSE				-6	//close             
#define WHR_ADDFDLIST			-7 	//addfdlist         
#define WHR_CHKFDLIST			-8	//chkfdlist         
#define WHR_READFDLIST			-9	//readfdlist        
#define WHR_DELETEFDLIST		-10	//deletefdlist      
#define WHR_SENDMSG			-11	//SendMsg           
#define WHR_NULLFUNCTT			-12 //NullFunctT        	
#define WHR_NULLFUNCTFT		-13	//NullFunctFT       	
#define WHR_GOTHROUGHTX0FR	-14	//GoThroughTxUart0fr	



#define ERR_RD_BUF_OVERFLOW -30 // Read�Լ��� �Ҵ�� buffer�� size�� ���� 
#define ERR_RD_NODATA -1


#if KERNEL_DEBUG == TRUE
	int err(int errno, signed char where);
#else
	#define err(a, b) 0
#endif

#endif
