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

#include "fdlist.h"
#include "error.h"

fdlist mfdlist[MAX_NUM_DEV_FDLIST];

int initfdlist(void){
	
	return 0;
}

int checknDev(nDEV numdev){
	int i;
	
	for(i =0; i< MAX_NUM_DEV_FDLIST; i++)
	{
		if(mfdlist[i].numdev == numdev)
			return ERR_DUPLICATED_NUMDEV;	
	}
	
	return 0;
}

int emptyfd(void){
	int i;
	
	for(i =0; i< MAX_NUM_DEV_FDLIST; i++)
	{
		if(mfdlist[i].numdev == 0)
			return i;	
	}
	
	return ERR_FDLIST_FULL;
}

int addfdlist(nDEV numdev, OS_FOP* fop){
	int fd;
	
	// check out whether there is duplicated 'nDEV' each other
	fd = checknDev(numdev);
	if(fd <0) 
		return err(fd,WHR_ADDFDLIST);
	// find out empty place in fdlist
	fd = emptyfd();
	if(fd < 0)
		return err(fd,WHR_ADDFDLIST);
		
	mfdlist[fd].osfop = fop;
	mfdlist[fd].numdev = numdev;

#if KERNEL_INIT_VIEW == ENABLED
	xprintf("K>Driver [%d] Init ... OK\n",numdev);
#endif

	return 0;
}

int chkfdlist(nDEV numdev){
	int i;
	
	for(i =0; i< MAX_NUM_DEV_FDLIST; i++)
	{
		if(mfdlist[i].numdev == numdev){
			if(mfdlist[i].open == FALSE){
				return i;	
			}else
				return err(ERR_ALREADY_OPENED,WHR_CHKFDLIST);
		}
	}
	
	return err(ERR_UNKNOWNED_NUM_DEV,WHR_CHKFDLIST);
}

int readfdlist(nDEV numdev){
	int i;
	
	for(i =0; i< MAX_NUM_DEV_FDLIST; i++)
	{
		if(mfdlist[i].numdev == numdev)
			return i;	
	}
	
	return err(ERR_UNKNOWNED_NUM_DEV,WHR_READFDLIST);
}

int deletefdlist(nDEV numdev){
	int i;
	
	for(i =0; i< MAX_NUM_DEV_FDLIST; i++)
	{
		if(mfdlist[i].numdev == numdev){
			// initialize pointed numdev 
			mfdlist[i].numdev = 0; 
			return 0;	
		}
	}
	return err(ERR_UNKNOWNED_NUM_DEV,WHR_DELETEFDLIST);
}

