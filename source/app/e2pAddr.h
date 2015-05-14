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

#ifndef __E2PADDR_H
#define __E2PADDR_H



/* Event 관련 *******************************************************
	eeprom의 120byte를 event ON/OFF의 기록을 위해서 할당한다 
	0x10 ~ 0x87 (0x77)


	contents 하나당 4byte(32bit)를 하당한다 
	ex)
	contents1 -> 0x10 ~ 0x13
	contents2 -> 0x14 ~ 0x17
	contents3 -> 0x18 ~ 0x1B
	contents4 -> 0x1C ~ 0x1F
		...		...	~   ...
*/
#define E2ADDR_EVENT_START		0x10
#define E2ADDR_EVENT_END			0x88 // 0x87까지 


/* DB 관련 *******************************************************

	DB LIST :
	prevAddr(1) Ti(3) Ci(1) Ei(1) Fq(1) ETC(1) nextAddr(1) -> total 9bytes

	1. 실제 address는 0 -> 쓰여지는 address는 0
	    9 -> 1
	    18 -> 2
	    이런식으로 나타낸다 
	2. 총 256*9 = 2304 bytes를 사용한다 
		(단 0xFF번째의 DB는 사용하지 않는다 빈공간을 파악하기 위해서 nexAddr = 0xFF이면 사용하지 않은 DB로 친다)

	DB INFO: 
	1byte: DB StartByte 0xFF: 미사용 , 0x00: 사용 
	
*/

#define E2ADDR_DB_START			0x100
#define E2ADDR_DB_END				0xA00 //  0xBFF까지 
#define E2SIZE_DB					0x900


/* Info 관련 ******************************************************* 

	DB time : 0xA00 ~ 0xA005
			rYear ( 2ytes) + rTime (4bytes) : total 6bytes
			
	0xA00 0xA05

*/
#define E2ADDR_SAVE_TIME_START	0xA00
#define E2ADDR_SAVE_TIME_END		0xA06 // 0xA05까지
#define E2SIZE_SAVE_TIME			6

/* user data 관련 ***************************************************
	0xB00 ~ 0xC00
*/
#define E2ADDR_USER_DATA_START	0xB00
#define E2ADDR_USER_DATA_END		0xC00
#define E2ADDR_USER_DATA_SIZE		0x100

/* user ID PWD 관련 */
#define E2ADDR_USER_ID				0xFD0
#define E2ADDR_USER_PWD			0xFF0

/* firmware upgrade 관련 ***************************************************
	0xFF0 ~ 0xFFF : 
*/
#define E2ADDR_BOOT_MODE			0xFF0

#endif

