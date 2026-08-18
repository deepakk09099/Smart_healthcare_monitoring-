/*header.h*/
/*global variables*/
extern int emergency;
extern int buzzer;

extern int h, min, sec;	 // to store rtc time

/*define*/
#define BUZZER (1<<20)  
#define RED_LED (1<<2)     // emergency led(2)
#define GREEN_LED (1<<3)    
#define SW ((IOPIN0>>15)&1)   // switch for stop buzzer
#define RELAY (1<<5)



typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;

/*delay_header*/
extern void delay_ms(unsigned int ms);
extern void delay_s(unsigned int s);
extern void delay_us(unsigned int us);

/*lcd_4bit_driver header*/
extern void lcd_data(unsigned int data);
extern void lcd_cmd(unsigned int cmd);
extern void lcd_init(void);
extern void lcd_string(char *p);
extern void lcd_integer(int num);
extern void lcd_float(float f);
extern void lcd_clear(void);


/*uart0_header*/
extern void uart0_init(unsigned int baud);
extern void uart0_tx(unsigned char data);
extern unsigned char uart0_rx(void);
extern void uart0_tx_string(char *p);
extern void uart0_rx_string(char *p);
extern void uart0_rfid(char *p, int len);
extern void uart0_integer(int num);
extern void uart0_float(float f);

/*eint0 header*/
extern void config_eint0_intr_init(void);

/*i2c_header*/
extern void i2c_init(void);
extern void i2c_send(u8 sa, u8 mr, u8 data);
extern u8 i2c_read(u8 sa, u8 mr);


/*i2c_heart_beat*/
extern u8 i2c_read_heart(u32, u32);
extern void i2c_init_heart(void);
//extern void i2c_send(u8 sa, u8 mr, u8 data);




/*adc_driver.c*/
extern void adc_init(void);
extern u32 adc_read(int ch_num);

extern void config_eint0_intr(void);


/*other.c*/
extern void emergency_alert(void);
extern void rtc_time_setting(void);
extern void rtc_time_getting(void);
extern void EEPROM_init(void);
extern void pwm_init90(void);
extern void interuupt_init(void);

/*ai_decision.c*/
  extern void AI_decision(float ,unsigned int ,unsigned int,unsigned int,unsigned char ,float ,float);

//PWM DRIVER
extern void pwm_init(void);
extern void pwm_function(unsigned int);


#define IR_SENSOR (IOPIN0&(1<<10))
#define EMERGENCY_SW (IOPIN0&(1<<11))


//int adc_read(int ch_num);
float read_temperature(void);
unsigned int read_pulse(void);
unsigned int read_saline(void);
unsigned int read_oxygen(void);
float read_current(void);

void AI_decision(float temp, unsigned int pulse, unsigned int saline, unsigned int oxygen,unsigned char emergency,
				float current,float movement);

unsigned char read_movement(void);
unsigned char read_emergency(void);



/*PIR_Sensor.h*/
extern void PIR_init(void);
extern unsigned char PIR_read(void);


/*ultrsonic.h*/
extern void ultrasonic_init(void);
extern void send_pulse(void);
extern unsigned int get_range(void);


/*temprature_sensor.h*/
extern unsigned char DHT11_ReadTemperature(void);
void intro(void);


