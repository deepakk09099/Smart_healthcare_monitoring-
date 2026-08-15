#include<lpc21xx.h>
#include"header.h"

//#define RED_LED (1<<16)
//#define GREEN_LED (1<<17)
//#define BUZZER (1<<18)
//#define RELAY (1<<19)
float temp,current,movement;
unsigned int pulse,saline,oxygen;
//unsigned char emergency;


void AI_decision(float temp,
				unsigned int pulse,
				unsigned int saline,
				unsigned int oxygen,
				unsigned char emergency,
				float current,float movement
				)
	
{


unsigned int flag=0;
	/*
		if(emergency){
			lcd_clear();
			lcd_string("EMERGENCY");
			IOSET0=RED_LED|BUZZER|RELAY;
			uart0_tx_string("emergency\r\n");
//			EEPROM_write_event();
			return;
		}
	*/

		if(temp>39){
			lcd_clear();
			lcd_string("HIGH TEMP");
			IOSET0=RED_LED|BUZZER;
			uart0_tx_string("\r\nHIGH TEMP\n");
			flag=1;
		}

		if(pulse<60||pulse>120){
			lcd_clear();
			lcd_string("HEART ALERT");
			IOSET0=RED_LED|BUZZER;
			flag=1;
		}
		
	   if(oxygen<250){
	   		lcd_clear();
			lcd_string("LOW OXYGEN");
			uart0_tx_string("\r\nLOW OXYGEN\n");
			IOSET0=RED_LED|BUZZER|RELAY;
			flag=1;
		}
		if(saline<20){
			lcd_clear();
			lcd_string("LOW SALINE");
			uart0_tx_string("\r\nLOW SALINE\n");
			IOSET0=RED_LED;
			flag=1;
		}
		if(movement){
			lcd_clear();
			lcd_string("PATIENT MOVE");
			uart0_tx_string("\r\nPATIENT MOVE\n");
			IOSET0=RED_LED;
			flag=1;
		}
		if(flag==0){
			lcd_clear();
			lcd_string("PATIENT OK");
			uart0_tx_string("\r\nPATIENT OK\n");
			IOSET0=GREEN_LED;
			IOCLR0=RED_LED|BUZZER|RELAY;
		}
}


