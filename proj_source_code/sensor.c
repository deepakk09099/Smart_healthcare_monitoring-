/* all_sensors definition */
#include<lpc21xx.h>
#include"header.h"

float read_temperature(void){
	unsigned int t;
	t=DHT11_ReadTemperature();
	return t;
}


unsigned int read_pulse(void){
//	return i2c_read_heart(0xAE,0xFF);
	return i2c_read(0xAE,0xFF);
}


float read_current(void){
	unsigned int adc;
	float voltage;
	adc=adc_read(3);
	voltage=((adc*3.3)/1023);
	return ((voltage-2.5)/0.185);
}


unsigned char read_movement(void){
	if(IR_SENSOR)
		return 1;
	else
		return 0;
}


/* PIR_sensor.c */
void PIR_init(void){
//configure p0.10 as input
	IODIR0&=~(1<<10);
}


unsigned char PIR_read(void){
	if(IOPIN0&(1<<10))
		return 1;
 	else
		return 0;
}

