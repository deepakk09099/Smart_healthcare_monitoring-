#include<lpc21xx.h>
#include"header.h"
int m=0;
    int main(){
	float temp,current,movement;
	unsigned int pulse,saline,oxygen;
	uart0_init(9600);
	lcd_init();
	config_eint0_intr();
	adc_init();
	i2c_init();
	PIR_init();
	ultrasonic_init();
//	intro();

//	i2c_init_heart();
//  rtc_time_setting();
//	rtc_time_setting();     // set the current time

	IODIR0 |= BUZZER | RED_LED | GREEN_LED;
	IOSET0=RED_LED | GREEN_LED;
	IOCLR0 = BUZZER;

	while(1){
		m++;
		if(emergency){
		   	//buzzer=0;
			emergency_alert();
			emergency = 0;
			//buzzer=0;
		}
		buzzer=0;
		temp=read_temperature();
		uart0_tx_string("\r\ntemperature reading : ");
		uart0_integer(temp);
	/*
//		pulse=read_pulse();
//		pulse = i2c_read_heart(0xAE, 0xFF);
    	pulse = i2c_read(0xAE, 0xFF);   
		uart0_tx_string("\rpulse reading : ");
		uart0_integer(pulse);
	*/

//		saline=get_range();
//		uart0_tx_string("\r\nsaline reading : ");
//		uart0_integer(saline);

		oxygen=adc_read(2);      // reading the o2 lavel using potentiometer
		uart0_tx_string("\r\nOxygen level : ");
		uart0_integer(oxygen);

/*
		current=read_current();		 // ch_num(3)
		uart0_tx_string("\r\nCurrent level : ");
		uart0_integer(current);
*/

		movement=PIR_read();
//		emergency=read_emergency();
		AI_decision(temp,pulse,saline,oxygen,movement,emergency,current);

	//	delay_ms(500);
	}
} 


