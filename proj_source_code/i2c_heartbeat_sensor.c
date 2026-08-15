#include<lpc21xx.h>
#include"header.h"

#define SI ((I2CONSET>>3)&1)


void i2c_init_heart(void){
	//***I2CBitfreq,setting***
	//Bitfreq.=FCLK/(I2SCLL+I2SCLH)
	//(I2SCLL+I2SCLH)=15000000/100000;settingas100kBps
	
	PINSEL0|=(1<<4)|(1<<6);//SCL=P0.2&SDA=P0.3 I2SCLL = (15000000/100000)/2;
	I2SCLH=(15000000/100000)/2; I2CONSET = 1<<6 ;
	I2CONCLR=1<<2;
}

void i2c_write_heart(u32 slave_addr,u32 memory_addr,u8 data){
	// Generate start condition uart0_tx_string("\r\nWritestart...\r\n");
	
	
	I2CONSET=(1<<5);//STA=1;
	I2CONCLR=(1<<3);//clearingSIflagwhile(SI==0);
	if(I2STAT!=0x08)//checkingforstartcondition
	{
	uart0_tx_string("\r\nERROR:STARTcondition\r\n"); goto exit ; //need to change to goto exit or somthing
	}
	I2CONCLR=(1<<5);//STA=0;
	
	
	//sendingSA+W
	I2DAT = slave_addr ; //SA+W I2CONCLR=(1<<3);//clearingSIflagwhile(SI==0);
	
	//	uart0_tx_string("\r\nI2STAT=");
	//	uart0_intiger(I2STAT);
	//	uart0_tx_string("\r\n");
	if(I2STAT!=0x18)//checkingforSA+W,ACK
	{
	uart0_tx_string("\r\nERROR:SA+Wfailed,I2STAT!=0x18\r\n"); goto exit ; //need to change to goto exit or somthing
	}
	
	if(I2STAT==0x20)//checkingforSA+W,NOTACK
	{
	uart0_tx_string("\r\nERROR:SA+Wfailed,NOTACK\r\n"); goto exit ; //need to change to goto exit or somthing
	}
	//Sendingmemoryaddr I2DAT=memory_addr;
	I2CONCLR=(1<<3);//clearingSIflagwhile(SI==0);
	if(I2STAT!=0x28)//Data/Memory_addrhasbeentransmittedexpectedstatus
	{
	uart0_tx_string("\r\n ERROR : memory_addr \r\n"); goto exit;//needtochangetogotoexitorsomthing
	}
	if(I2STAT==0x30)//Data/Memory_addrhasbeentransmitted;NOTACKhasbeenreceived
	{
	uart0_tx_string("\r\nERROR:SA+Wfailed,NOTACK\r\n"); goto exit ; //need to change to goto exit or somthing
	}
	
	//Send data I2DAT=data;
	I2CONCLR=(1<<3);//clearingSIflagwhile(SI==0);
	if(I2STAT!=0x28)//Expectedstatus
	{
	uart0_tx_string("\r\nERROR:Data,I2STAT!=0x28\r\n"); goto exit ; //need to change to goto exit or somthing
	}
	if(I2STAT==0x30)//Data/Memory_addrhasbeentransmitted;NOTACKhasbeenreceived
	{
	uart0_tx_string("\r\nERROR:SA+Wfailed,NOTACK\r\n");
	goto exit;//needtochangetogotoexitorsomthing
	}
	exit:
	I2CONSET=(1<<4);
	I2CONCLR=(1<<3);
	delay_ms(100);
	uart0_tx_string("\r\n!!!!!!WriteCOMPLETE!!!!!...\r\n");

}







u8 i2c_read_heart(u32 slave_addr,u32 memory_addr)
{
	u8 result;
	
	uart0_tx_string("\r\nReadstart...\r\n");
	
	//Generatestartcondition
	I2CONCLR=(1<<3);//clearingSIflag I2CONSET = (1<<5); // STA =1;
	while(SI==0);
	I2CONCLR=(1<<5);//STA=0;
	
	
	//SendingSA+W
	I2DAT = slave_addr; //SA+W I2CONCLR=(1<<3);//clearingSIflagwhile(SI==0);
	if(I2STAT!=0x18)//checkingforSA+W,ACK
	{
		uart0_tx_string("\r\nERROR:SA+Wfailed,I2STAT!=0x18\r\n"); goto exit; //need to change to goto exit or somthing
	}
	if(I2STAT==0x20)//checkingforSA+W,NOTACK
	{
		uart0_tx_string("\r\nERROR:SA+Wfailed,NOTACK\r\n"); goto exit; //need to change to goto exit or somthing
	}
	
	
	//Sendingmemoryaddr I2DAT=memory_addr;
	I2CONCLR=(1<<3);//clearingSIflagwhile(SI==0);
	if(I2STAT==0x30)//Data/Memory_addrhasbeentransmitted;NOTACKhasbeenreceived
	{
	uart0_tx_string("\r\nERROR:SA+Wfailed,NOTACK\r\n"); goto exit; //need to change to goto exit or somthing
	}
	
	
	// Sending Restart condition I2CONSET=(1<<5);//STA=1;
	I2CONCLR=(1<<3);//clearingSIflag
	while(SI==0);
	if(I2STAT!=0x10)//ReapetedStartconditionfailedtransmitted
	{
	uart0_tx_string("\r\nERROR:Restartcondition\r\n"); goto exit; //need to change to goto exit or somthing
	}
	I2CONCLR=(1<<5);//STA=0;
	
	
	//SendingSA+R
	I2DAT = slave_addr^1; //SA+R I2CONCLR=(1<<3);//clearingSIflagwhile(SI==0);
	if(I2STAT!=0x40)//Expectedstatus
	{
	uart0_tx_string("\r\nERROR:SA+Wfailed,I2STAT!=0x40\r\n"); goto exit ; //need to change to goto exit or somthing
	}
	if(I2STAT==0x48)//checkingforSA+W,NOTACK
	{
	uart0_tx_string("\r\nERROR:SA+Wfailed,NOTACK\r\n"); goto exit ; //need to change to goto exit or somthing
	}
	
	// Geting data I2CONCLR=1<<2;
	I2CONCLR=(1<<3);//clearingSIflagwhile(SI==0);
	if(I2STAT!=0x58)//checkingfor0x58status
	{
	uart0_tx_string("\r\nERROR:DATAreception\r\n"); goto exit ; //need to change to goto exit or somthing
	}
	result=I2DAT;
	
	I2CONSET=(1<<4);
	I2CONCLR=(1<<3);
	delay_ms(100);return result;
	
	exit:
	
	
	
	uart0_tx_string("\r\n$$$$$$READCOMPLETE$$$$$$...\r\n");
	return result;
}

