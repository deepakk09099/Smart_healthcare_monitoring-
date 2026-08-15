#include<lpc21xx.h>
#include"header.h"
int emergency=0;
int buzzer=0;
int c=0;
void EINT0_ISR(void) __irq{
	c++;
	emergency = 1;
	buzzer=1;

	EXTINT=1;
	VICVectAddr = 0;
}

void config_eint0_intr(void){
	PINSEL1 |= 0x1;
	EXTMODE=1;
	EXTPOLAR=0;
	VICIntSelect=0;
	VICVectCntl2=14|(1<<5);
	VICVectAddr2=(unsigned int)EINT0_ISR;
	VICIntEnable=1<<14;
}


