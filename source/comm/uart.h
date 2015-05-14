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

#ifndef __UART_H
#define __UART_H

#include "fdlist.h"


#if USE_UART0 == ENABLED
void Uart0Init(void);
void Uart0SetSpeed(U32 baud);
void Uart0EnableTx(BOOL enable);
void Uart0EnableRx(BOOL enable);
void Uart0SendByte(U8 aByte);
#endif

#if USE_UART1 == ENABLED
void Uart1Init(void);
void Uart1SetSpeed(U32 baud);
void Uart1EnableTx(BOOL enable);
void Uart1EnableRx(BOOL enable);
void Uart1SendByte(U8 aByte);
#endif

U8 headerSend(U8 tSeq, U16 tDes, U16 tSrc,U8 tCmd, U8 selnUart);
U8 Sendrdata(U8 *rdat, U16 count, U8 selnUart);

void Uart_Process(void);


typedef void (*pFunctHeader)(unsigned char);

/*SELECT UART0 OR UART1*/
#define SEL_SEND_UART0	0x01
#define SEL_SEND_UART1	0x02


/*FCMD*/
#define FCMD_ERR_JAM_IN_TUBE	0xFF
#define FCMD_APP_DATA	0xC1
#define FCMD_UPDATE	0xCF

/*SRC/DES ADDRESS*/
#define ADDR_PC	0x0000
#define ADDR_DEFAULT	0xFFFF

/*DRIVER CMD*/
#define CMD_SET_BAUD	0x01
#define CMD_TX_DST_WR	0x02
#define CMD_RD_RXDONE	0x03
#define CMD_WR_RXDONE	0x04
#define CMD_GOTHROU_CHKSEND 0x05
#define CMD_COMPARE_GOTHROU_TIME 0x06
#define CMD_RD_UART_ERR	0x07

/*DRIVER ERR(bit calculation)*/
#define ERR_RXBUF_FULL 0x01 // this error is occured when All RXbuff is occuping.
#define ERR_GOTHROU_JAM 0x02 // when all the buffers of 'gothroug buffer' are using, it is occured and return value
//#define ERR_RESERVED 0x04 ..0x08 ..0x10

/*PROTOCOL DEFINE*/
#define UA_STX 0x02
#define UA_ETX 0x03
#define UA_LRC_OK 0x00 // all the data(SEQ ~ LRC) ^ calculated lrc = 0

/*GOTHROUGH SETTING*/
#define GOTHROU_DEFUAT_TIME 0xFFFFFFFF

#endif
