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



/* Event ���� *******************************************************
	eeprom�� 120byte�� event ON/OFF�� ����� ���ؼ� �Ҵ��Ѵ� 
	0x10 ~ 0x87 (0x77)


	contents �ϳ��� 4byte(32bit)�� �ϴ��Ѵ� 
	ex)
	contents1 -> 0x10 ~ 0x13
	contents2 -> 0x14 ~ 0x17
	contents3 -> 0x18 ~ 0x1B
	contents4 -> 0x1C ~ 0x1F
		...		...	~   ...
*/
#define E2ADDR_EVENT_START		0x10
#define E2ADDR_EVENT_END			0x88 // 0x87���� 


/* DB ���� *******************************************************

	DB LIST :
	prevAddr(1) Ti(3) Ci(1) Ei(1) Fq(1) ETC(1) nextAddr(1) -> total 9bytes

	1. ���� address�� 0 -> �������� address�� 0
	    9 -> 1
	    18 -> 2
	    �̷������� ��Ÿ���� 
	2. �� 256*9 = 2304 bytes�� ����Ѵ� 
		(�� 0xFF��°�� DB�� ������� �ʴ´� ������� �ľ��ϱ� ���ؼ� nexAddr = 0xFF�̸� ������� ���� DB�� ģ��)

	DB INFO: 
	1byte: DB StartByte 0xFF: �̻�� , 0x00: ��� 
	
*/

#define E2ADDR_DB_START			0x100
#define E2ADDR_DB_END				0xA00 //  0xBFF���� 
#define E2SIZE_DB					0x900


/* Info ���� ******************************************************* 

	DB time : 0xA00 ~ 0xA005
			rYear ( 2ytes) + rTime (4bytes) : total 6bytes
			
	0xA00 0xA05

*/
#define E2ADDR_SAVE_TIME_START	0xA00
#define E2ADDR_SAVE_TIME_END		0xA06 // 0xA05����
#define E2SIZE_SAVE_TIME			6

/* user data ���� ***************************************************
	0xB00 ~ 0xC00
*/
#define E2ADDR_USER_DATA_START	0xB00
#define E2ADDR_USER_DATA_END		0xC00
#define E2ADDR_USER_DATA_SIZE		0x100

/* user ID PWD ���� */
#define E2ADDR_USER_ID				0xFD0
#define E2ADDR_USER_PWD			0xFF0

/* firmware upgrade ���� ***************************************************
	0xFF0 ~ 0xFFF : 
*/
#define E2ADDR_BOOT_MODE			0xFF0

#endif

