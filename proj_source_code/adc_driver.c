/*adc_driver.c*/
#include<lpc21xx.h>
#include"header.h"
void adc_init(void){
    PINSEL1 |= 0x15400000;
    ADCR = 0x200400;
}

u32 adc_read(int ch_num){
    u32 result;
    ADCR |= (1<<ch_num);
    ADCR |= 1<<24;
    while(((ADDR>>31)&1)==0);
    ADCR ^= 1<<24;
    ADCR ^= 1<<ch_num;
    result = ((ADDR>>6)&0x3FF);
    return result;
}
