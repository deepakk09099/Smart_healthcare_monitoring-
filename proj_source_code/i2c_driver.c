/*i2c_driver.c*/

#include<lpc21xx.h>
#include"header.h"
void i2c_init(void){
	PINSEL0 |= 0x50;
	I2SCLH=I2SCLL=75;
	/*select master mode*/
	I2CONCLR=(1<<2);  // AA=0
	I2CONSET=(1<<6);  // I2EN=1
}

#define SI ((I2CONSET>>3)&1) 
void i2c_send(u8 sa, u8 mr, u8 data){
	/*start condition*/
	I2CONSET=1<<5;  // STA=1
	I2CONCLR=1<<3;  // SI=0
	while(SI==0);
	I2CONCLR=1<<5;  // STA=0

	I2DAT=sa;
	I2CONCLR=1<<3;  // SI=0
	while(SI==0);
	if(I2STAT==0x20){
		uart0_tx_string("err : SA+W \r\n");
		goto exit;
	}

	I2DAT=mr;
	I2CONCLR=1<<3;	// SI=0
	while(SI==0);
	if(I2STAT==0x30){
		uart0_tx_string("err : Mr \r\n");
		goto exit;
	}

	I2DAT=data;
	I2CONCLR=1<<3;  // SI=0
	while(SI==0);
	if(I2STAT==0x30){
		uart0_tx_string("err : DATA \r\n");
		goto exit;
	}
	/*stop condition*/
	exit:
	I2CONSET=1<<4;  // STO=1
	I2CONCLR=1<<3;  // SI=0
}

u8 i2c_read(u8 sa, u8 mr){
	u8 res=0;
	I2CONSET=1<<5; //STA=1
	I2CONCLR=1<<3; // SI=0
	while(SI==0);
	I2CONCLR=1<<5; //STA=0
	
	I2DAT=sa^1;
	I2CONCLR=1<<3; // SI=0
	if(I2STAT==0x20){
		uart0_tx_string("err : SA+W \r\n");
		goto exit;
	}

	I2DAT=mr;
	I2CONCLR=1<<3;	// SI=0
	while(SI==0);
	if(I2STAT==0x30){
		uart0_tx_string("err : Mr \r\n");
		goto exit;
	}

	/*Generate Re-Start Condition*/
	I2CONSET=1<<5; //STA=1
	I2CONCLR=1<<3; // SI=0
	while(SI==0);
	I2CONCLR=1<<5; //STA=0

	I2DAT=sa;
	I2CONCLR=1<<3; // SI=0
	if(I2STAT==0x48){
		uart0_tx_string("err : SA+R \r\n");
		goto exit;
	}
	/*Read Data*/
	I2CONCLR=1<<3;   //  SI=0
	while(SI==0);
	res=I2DAT;
	uart0_tx_string("\r\nin i2c : ");
	uart0_integer(res);
		
	exit:
	I2CONSET=1<<4; 	 // STO=1
	I2CONCLR=1<<3;   // SI=0
	return res;
}

