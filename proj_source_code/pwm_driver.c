/*Hardware PWM5 Driver*/
/*
#include<lpc21xx.h>
#include"header.h"

void pwm_init(void){
	PINSEL0 |= 0x0008; // Configure P0.21 as PWM5
	PWMPCR = 0x2000; // Enable PWM5 output channel
	PWMPR = 0x00; // Prescale counter to 0
	PWMMR0 = 1000; // Set Period frequency baseline
	PWMMR5 = 0; // Initial Duty cycle 0% (Fan stopped)
	PWMMCR = 0x0002; // Reset on PWMMR0 match
	PWMLER = 0x21; // Latch MR0 and MR5
	PWMTCR = 0x09; // Counter enable and PWM enable
}


void pwm5_SetDuty(unsigned int duty) {
	if(duty > 1000) duty = 1000;
	PWMMR5 = duty;
	PWMLER = 0x20; // Latch MR5 updates
}


*/

 #include<lpc21xx.h>
 #include"header.h"

void pwm_init(void){
	 PINSEL0|=0X8000;///USE P0.7
	 PWMTCR=0X02;///RESET PWM
	 PWMPR=59;///SETTING PRE SCALER VALUE
	 PWMMR0=1000;//SET PWM PERIOD
	 PWMMR2=0;//SET DUTY CYCLE
	 PWMMCR=0X02;
	 //PWMMR2=750;
	 PWMLER=(1<<0)||(1<<2);
	 PWMPCR=(1<<10);
	 PWMTCR=0X09;
}

void pwm_function(unsigned int duty){
	if(duty>PWMMR0)
	duty=PWMMR0;
	PWMMR2=duty;
	PWMLER=(1<<2);
}




                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     