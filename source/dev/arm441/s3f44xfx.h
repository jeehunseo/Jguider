/*
__ARM44X_H__
*/

#ifndef __ARM44X_H__
#define __ARM44X_H__

#define ARM_S3F441FX 		0	 
#define ARM_S3F443FX		1	

#define CPU_TYPE	ARM_S3F441FX

/* system manager*/
#define rSYSCFG        	  (*(volatile unsigned *)		0x1ff3000)
#define rMEMCON0        (*(volatile unsigned *)		0x1ff4000)
#define rMEMCON1        (*(volatile unsigned *)		0x1ff4004)
#define rMEMCON2        (*(volatile unsigned *)		0x1ff4008)

    
/* internal flash ROM */
#define rFMKEY0          (*(volatile unsigned char *)	0x1ff3010)
#define rFMKEY1          (*(volatile unsigned char *)	0x1ff3011)
#define rFMKEY2          (*(volatile unsigned char *)	0x1ff3012)
#define rFMKEY3          (*(volatile unsigned char *)	0x1ff3013)
#define rFMADDR         (*(volatile unsigned *)		0x1ff3014)
#define rFMDATA         (*(volatile unsigned *)		0x1ff3018)
#define rFMUCON         (*(volatile unsigned char *)	0x1ff301f)
#define rFMACON         (*(volatile unsigned char *)	0x1ff3027)
#define rFMERR          	 (*(volatile unsigned char *)	0x1ff3023)
#define rFSOREAD        (*(volatile unsigned *)		0x1ff3028)
#define rFPOREAD        (*(volatile unsigned *)		0x1ff302c)

/* UART */
#define rLCON         	(*(volatile unsigned char *)	0x1ff5003)
#define rUCON         	(*(volatile unsigned char *)	0x1ff5007)
#define rUSSR         	(*(volatile unsigned char *)	0x1ff500b)
#define rTBR         	(*(volatile unsigned char *)	0x1ff500f)
#define rRBR         	(*(volatile unsigned char *)	0x1ff5013)
#define rUBRDR         	(*(volatile unsigned short *)	0x1ff5016)

/* timer0~5 */
#define rT0DATA       	(*(volatile unsigned short *)	0x1ff9000)
#define rT0PRE         	(*(volatile unsigned char *)	0x1ff9002)
#define rT0CON         	(*(volatile unsigned char *)	0x1ff9003)
#define rT0CNT         	(*(volatile unsigned short *)	0x1ff9006)
#define rT1DATA       	(*(volatile unsigned short *)	0x1ff9010)
#define rT1PRE         	(*(volatile unsigned char *)	0x1ff9012)
#define rT1CON         	(*(volatile unsigned char *)	0x1ff9013)
#define rT1CNT         	(*(volatile unsigned short *)	0x1ff9016)
#define rT2DATA       	(*(volatile unsigned short *)	0x1ff9020)
#define rT2PRE         	(*(volatile unsigned char *)	0x1ff9022)
#define rT2CON         	(*(volatile unsigned char *)	0x1ff9023)
#define rT2CNT         	(*(volatile unsigned short *)	0x1ff9026)
#define rT3DATA       	(*(volatile unsigned short *)	0x1ff9030)
#define rT3PRE         	(*(volatile unsigned char *)	0x1ff9032)
#define rT3CON         	(*(volatile unsigned char *)	0x1ff9033)
#define rT3CNT         	(*(volatile unsigned short *)	0x1ff9036)
#define rT4DATA       	(*(volatile unsigned short *)	0x1ff9040)
#define rT4PRE         	(*(volatile unsigned char *)	0x1ff9042)
#define rT4CON         	(*(volatile unsigned char *)	0x1ff9043)
#define rT4CNT         	(*(volatile unsigned short *)	0x1ff9046)
#define rT5DATA       	(*(volatile unsigned short *)	0x1ff9050)
#define rT5PRE         	(*(volatile unsigned char *)	0x1ff9052)
#define rT5CON         	(*(volatile unsigned char *)	0x1ff9053)
#define rT5CNT         	(*(volatile unsigned short *)	0x1ff9056)


/* basic timer & watch-dog timer */
#define rBTCON       	(*(volatile unsigned short *)	0x1ffa002)
#define rBTCNT         	(*(volatile unsigned char *)	0x1ffa007)

/* I/O port */ 
#define rP0       		(*(volatile unsigned char *)	0x1ffb000)
#define rP1         		(*(volatile unsigned char *)	0x1ffb001)
#define rP2       		(*(volatile unsigned char *)	0x1ffb002)
#define rEINTCON       	(*(volatile unsigned char *)	0x1ffb018)
#define rEINTMOD       (*(volatile unsigned char *)	0x1ffb01a)
#define rP0CON       	(*(volatile unsigned char *)	0x1ffb010)
#define rP1CON         	(*(volatile unsigned short *)	0x1ffb012)
#define rP2CON       	(*(volatile unsigned char *)	0x1ffb014)
#define rP0PUR       	(*(volatile unsigned char *)	0x1ffb015)
#define rP1PUDR         (*(volatile unsigned char *)	0x1ffb016)
#define rP2PUR       	(*(volatile unsigned char *)	0x1ffb017)

/* interrupt controller */
#define rINTMODE       (*(volatile unsigned *)		0x1ffc000)
#define rINTPEND       (*(volatile unsigned *)		0x1ffc004)
#define rINTMASK       (*(volatile unsigned *)		0x1ffc008)
#define rINTPRI0        (*(volatile unsigned *)		0x1ffc00c)
#define rINTPRI1        (*(volatile unsigned *)		0x1ffc010)
#define rINTPRI2        (*(volatile unsigned *)		0x1ffc014)
#define rINTPRI3        (*(volatile unsigned *)		0x1ffc018)
#define rINTPRI4        (*(volatile unsigned *)		0x1ffc01c)
#define rINTPRI5        (*(volatile unsigned *)		0x1ffc020)
#define rINTPRI6        (*(volatile unsigned *)		0x1ffc024)
#define rINTPRI7        (*(volatile unsigned *)		0x1ffc028)

/* system control */
#define rSYSCON         (*(volatile unsigned short*)	0x1ffd002)
#if  CPU_TYPE == ARM_S3F441FX
#define rPLLCON         (*(volatile unsigned *)		0x1ffd004)
#endif

#define pISR_RESET      (*(unsigned *)(_ISR_STARTADDRESS+0x0))
#define pISR_UNDEF      (*(unsigned *)(_ISR_STARTADDRESS+0x4))
#define pISR_SWI        (*(unsigned *)(_ISR_STARTADDRESS+0x8))
#define pISR_PABORT     (*(unsigned *)(_ISR_STARTADDRESS+0xc))
#define pISR_DABORT     (*(unsigned *)(_ISR_STARTADDRESS+0x10))
#define pISR_RESERVED   (*(unsigned *)(_ISR_STARTADDRESS+0x14))
#define pISR_IRQ        (*(unsigned *)(_ISR_STARTADDRESS+0x18))
#define pISR_FIQ        (*(unsigned *)(_ISR_STARTADDRESS+0x1c))

#define pISR_URXD       (*(unsigned *)(_ISR_STARTADDRESS+0x20))
#define pISR_UTXD       (*(unsigned *)(_ISR_STARTADDRESS+0x24))
#define pISR_UERR       (*(unsigned *)(_ISR_STARTADDRESS+0x28))
#define pISR_T0OVF      (*(unsigned *)(_ISR_STARTADDRESS+0x2c))
#define pISR_T0MC       (*(unsigned *)(_ISR_STARTADDRESS+0x30))
#define pISR_T1OVF      (*(unsigned *)(_ISR_STARTADDRESS+0x34))
#define pISR_T1MC       (*(unsigned *)(_ISR_STARTADDRESS+0x38))
#define pISR_T2OVF      (*(unsigned *)(_ISR_STARTADDRESS+0x3c))
#define pISR_T2MC       (*(unsigned *)(_ISR_STARTADDRESS+0x40))
#define pISR_T3OVF      (*(unsigned *)(_ISR_STARTADDRESS+0x44))
#define pISR_T3MC       (*(unsigned *)(_ISR_STARTADDRESS+0x48))
#define pISR_T4OVF      (*(unsigned *)(_ISR_STARTADDRESS+0x4c))
#define pISR_T4MC       (*(unsigned *)(_ISR_STARTADDRESS+0x50))
#define pISR_T5OVF      (*(unsigned *)(_ISR_STARTADDRESS+0x54))
#define pISR_T5MC       (*(unsigned *)(_ISR_STARTADDRESS+0x58))
#define pISR_BT         (*(unsigned *)(_ISR_STARTADDRESS+0x5c))
#define pISR_EINT0      (*(unsigned *)(_ISR_STARTADDRESS+0x60))
#define pISR_EINT1      (*(unsigned *)(_ISR_STARTADDRESS+0x64))
#define pISR_EINT2      (*(unsigned *)(_ISR_STARTADDRESS+0x68))

/*CAUTION:You must clear the pending bit as general special register.
          it's different way with KS32C6x00 */
#define BIT_URXD       (0x1)
#define BIT_UTXD       (0x1<<1)
#define BIT_UERR       (0x1<<2)
#define BIT_T0OVF      (0x1<<3)
#define BIT_T0MC       (0x1<<4)
#define BIT_T1OVF      (0x1<<5)
#define BIT_T1MC       (0x1<<6)
#define BIT_T2OVF      (0x1<<7)
#define BIT_T2MC       (0x1<<8)
#define BIT_T3OVF      (0x1<<9)
#define BIT_T3MC       (0x1<<10)
#define BIT_T4OVF      (0x1<<11)
#define BIT_T4MC       (0x1<<12)
#define BIT_T5OVF      (0x1<<13)
#define BIT_T5MC       (0x1<<14)
#define BIT_BT         (0x1<<15)
#define BIT_EINT0      (0x1<<16)
#define BIT_EINT1      (0x1<<17)
#define BIT_EINT2      (0x1<<18)

#endif
