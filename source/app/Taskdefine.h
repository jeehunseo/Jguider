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
 
#ifndef _TASK_DEFINE_
#define _TASK_DEFINE_

/*------------- TASK COMMON INCLUDE FILE ----------------------------------------------
	Common header file in tasks 

	ex) e2pAddr.h (it call be called some tasks)

*/

#include "e2pAddr.h"


/*------------- TASK COMMON DEFINE ----------------------------------------------
	Common define in tasks 

	ex) NUM_EID, NUM_CID ( it is called in ActionTask.c )

*/

#define NUM_EID U8
#define NUM_CID U8


#define _MSG_SEND_TEST_ DISABLED // 'MESSAGE_SEND' TEST IN THE MULTITASK


#endif

