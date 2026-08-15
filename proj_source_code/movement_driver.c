#include<lpc21xx.h>
#define HW201_PIN (1<<6)

void HW201_init(void){
	IODIR0 &= void HW201_PIN;	
	}

   char HW201_read(void)
   {
   char temp=(IOPIN0&HW201_PIN);
   return temp;
   
   }