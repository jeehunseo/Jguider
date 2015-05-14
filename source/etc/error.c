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

#include "error.h"
#include "printf.h"

#if KERNEL_DEBUG == TRUE

int err(int errno, signed char where){
	
	switch(errno){
	case ERR_FDLIST_FULL:	
	case ERR_UNKNOWNED_NUM_DEV:
		break;
	case ERR_RD_NODATA:
	case ERR_EMPTY_RXBUFF_UART0:
	case ERR_NULL_FUNCTION_CALL_IN_FASTTASK:
		return errno;
	default: 
		break;
	}
	
	xprintf("K>error:%d\n",errno);
	
	return errno;
}

#endif
