/* lcd_4bit_driver */
/* status : ----- */
/* pending : float fun */

#include<lpc21xx.h>
#include "header.h"
void lcd_data(unsigned int data){
	unsigned int temp;
	IOCLR1=0XFE<<16;	  
	temp=(data&0xf0)<<16;
	IOSET1=temp;
	IOSET1=1<<17;  // RS=1
	IOCLR1=1<<18;  //RW=0
	IOSET1=1<<19;  //EN=1
	delay_ms(2);
	IOCLR1=1<<19;  //EN=0

	IOCLR1=0XFE<<16;	  
	temp=(data&0x0f)<<20;
	IOSET1=temp;
	IOSET1=1<<17;  // RS=1
	IOCLR1=1<<18;  //RW=0
	IOSET1=1<<19;  //EN=1
	delay_ms(2);
	IOCLR1=1<<19;  //EN=0
}

void lcd_cmd(unsigned int cmd){
	unsigned int temp;
	IOCLR1=0XFE<<16;	  
	temp=(cmd&0xf0)<<16;
	IOSET1=temp;
	IOCLR1=1<<17;  // RS=1
	IOCLR1=1<<18;  //RW=0
	IOSET1=1<<19;  //EN=1
	delay_ms(2);
	IOCLR1=1<<19;  //EN=0

	IOCLR1=0XFE<<16;	  
	temp=(cmd&0x0f)<<20;
	IOSET1=temp;
	IOCLR1=1<<17;  // RS=1
	IOCLR1=1<<18;  //RW=0
	IOSET1=1<<19;  //EN=1
	delay_ms(2);
	IOCLR1=1<<19;  //EN=0
}

void lcd_init(void){
	IODIR1=0XFE<<16;
	PINSEL2  |=0X0;
	lcd_cmd(0x02);	 
	lcd_cmd(0x28);
	lcd_cmd(0x0e);   //enable the row and col
	lcd_cmd(0x01);   // clear the screen
}

void lcd_string(char *p){
	int i;
	for(i=0; p[i]; i++)
		lcd_data(p[i]);
}	


void lcd_integer(int num){
	int a[10],i;
	if(num<0){
		lcd_data('-');
		num=-num;
	}			
	if(num==0){
		lcd_data('0');
		return;
	}
	for(i=0; num; num/=10,i++)
		a[i]=num%10+48;
	for(i-=1; i>=0; i--)
		lcd_data(a[i]);
}

void lcd_float(float f){
	int num;
	if(f<0){
		lcd_data('-');
		f=-f;
	}
	if(f==0){
		lcd_string("0.0");
		return;
	}
	num=f;
	lcd_integer(num);
	lcd_data('.');
	num=(f-num)*1000000;
	lcd_integer(num);
}


void lcd_clear(void){
	lcd_cmd(0x01);
	delay_ms(2);
}


