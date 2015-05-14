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

#include "dev.h"
#include "fdlist.h"

FILED tfile;// temp 

/* It can be possible to use 'system block' data in this driver area */
void DevInit(SYSCBlk* sysblk){
	tfile.sysinfo = sysblk;
}


int registerDEV(nDEV numdev){
	if(readfdlist(numdev) <0){
	#if DEVICE_DEBUG == ENABLED
		xprintf("K:%d-device reg...FAIL\n",numdev);
	#endif
		return err(ERR_NO_REGISTED_DEV,WHR_REGISTERDEV);
	}
#if DEVICE_DEBUG == ENABLED
	xprintf("K:%d-device reg...OK\n",numdev);
#endif
	return 0;
}


int getfd(nDEV numdev){
	int fd;
	
	fd = chkfdlist(numdev);
	if(fd <0){
		if(fd == ERR_ALREADY_OPENED)
			return ERR_ALREADY_OPENED;
		return err(ERR_NO_REGISTED_DEV,WHR_GETFD);
	}
	return fd;	
}

int open(nDEV numdev,nOPT option){
	int fd= -1;
#if DEVICE_DEBUG == ENABLED
	int tNumDEV =0;
#endif

	fd = readfdlist(numdev);
	if(fd <0)
		return err(ERR_NO_REGISTED_DEV,WHR_OPEN);

	if(mfdlist[fd].open != TRUE){
		// when opening device first, it is initialized
		mfdlist[fd].osfop->open(numdev, option);	
		mfdlist[fd].open = TRUE;
	#if DEVICE_DEBUG == ENABLED
		tNumDEV = mfdlist[fd].numdev;	
		xprintf("K:%d-device opened...\n",tNumDEV);
		tNumDEV = tNumDEV;// eliminate warning
	#endif
	}
	

	return fd;
}

int read(int fd, void *buf, unsigned int count){
	if(buf == 0)
		return err(ERR_READ_BUFFER_POINTER_NULL,WHR_READ);
	
	return (int)(mfdlist[fd].osfop->read(&tfile,buf,count));
}

int write(int fd, void *buf, unsigned int count){
	if(buf == 0)
		return err(ERR_READ_BUFFER_POINTER_NULL,WHR_WRITE);

	return (int)(mfdlist[fd].osfop->write(&tfile,buf,count));
}

IOCTL ioctl(int fd, unsigned int cmd, unsigned long arg){

	return (IOCTL)(mfdlist[fd].osfop->ioctl(&tfile,cmd,arg));	
}


int close(nDEV numdev, nOPT option){
	int ret;
	int fd;
	
	fd = readfdlist(numdev);
	if(fd <0)
		return err(ERR_NO_REGISTED_DEV,WHR_CLOSE);
	
	ret = mfdlist[fd].osfop->close(numdev, option);	
	mfdlist[fd].open = FALSE;
	
#if DEVICE_DEBUG == ENABLED
	xprintf("K:%d-device closed...\n",numdev);
#endif
	return ret;
}

