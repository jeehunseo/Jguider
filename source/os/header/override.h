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

#ifndef __OVERRIDE_H
#define __OVERRIDE_H
#include "types.h"

// kernel debug trigger 
#define KERNEL_DEBUG ENABLED

// kernel speed trigger : In order that developer can see debug-process, J-guider offer an trigger of 'low speed process'.
#define KERNEL_SPEED_LOW KERNEL_DEBUG

// kernel initialization text view
#define KERNEL_INIT_VIEW KERNEL_DEBUG


#endif
