/*uart0_driver*/
/*status : working all funtion tested */
// check again float:
#include<lpc21xx.h>
#include "header.h"
#define RDR (U0LSR>>0&1)
void uart0_init(unsigned int baud){
	int pclk, result=0;
	if(VPBDIV==0x00)
		pclk=15000000;
	else if(VPBDIV==0x01)
		pclk=60000000;
	else if(VPBDIV==0x02)
		pclk=30000000;

	result=pclk/(16*baud);

	PINSEL0 |= 0x05;
	U0LCR=0x83;
	U0DLL=(result & 0xff);
	U0DLM=(result>>8)&0xff;
	U0LCR=0x03;
}

void uart0_tx(unsigned char data){
	U0THR=data;
	while((U0LSR>>5&1)==0);
}

unsigned char uart0_rx(void){
	while(RDR==0);
	return U0RBR;
}

void uart0_tx_string(char *p){
	int i;
	for(i=0; p[i]; i++)
		uart0_tx(p[i]);
}			

void uart0_rx_string(char *p){
	int i;
	unsigned char t;
	for(i=0; ;i++){
		t=uart0_rx();
		uart0_tx(t);
		if(t=='\r')
			break;
		p[i]=t;
	}
	p[i]='\0';
}

void uart0_rfid(char *p, int len){
	int i;
	for(i=0;i<len;i++){
		while(RDR==0);
		p[i]=U0RBR;
		if(p[i]=='\r')
			break;
	}
	p[i]='\0';
}


void uart0_integer(int num){
	int a[10], i;
	if(num==0){
		uart0_tx('0');
	 	return;
	}else if(num<0){
		num=-num;
		uart0_tx('-');
	}
	i=0;
	while(num){
		a[i]=num%10+48;
		num/=10;
        i++;
	}
	for(i=i-1; i>=0; i--)
		uart0_tx(a[i]);	
}

void uart0_float(float f){
	int num;
	if(f==0){
		uart0_tx_string("0.0");
		return;
	}
	if(f<0){
		f=-f;
		uart0_tx('-');
	}
	num=f;
	uart0_integer(num); //123.5
	uart0_tx('.');
	f=(f-num)*1000000;
	uart0_integer(f);
}

