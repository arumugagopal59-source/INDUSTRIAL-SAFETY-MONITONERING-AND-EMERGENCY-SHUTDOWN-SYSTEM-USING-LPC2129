#include<LPC21xx.h>
#include "delay.h"
#include "lcd.h"
#include "UART0header.h"
#define  led 1<<21  
#define motor1 1<<18
#define motor2 1<<19
int flag=0;
void NonVect_ISR(void) __irq
{
  if((VICIRQStatus>>14)&1)//p 16 //ir
  {
    EXTINT=1<<0;
	IOCLR0|=motor1|motor2;
	IOSET0|=led;
	delay_millisecond(2000);
	IOCLR0|=led;
	LCD_init();
	LCD_string("motor off");
	UART0_str("motor off");
  }
  else if((VICIRQStatus>>15)&1)	//p 14	//switch
  {
  	 EXTINT=1<<1;
	 IOCLR0|=motor1|motor2;
	 IOSET0|=led;
	 delay_millisecond(2000);
	 IOCLR0|=led;
	 LCD_init();
	 LCD_string("motor off");
	 UART0_str("motor off");
	 }
	 flag=0;
	 VICVectAddr=0;
	 }
int main()
{

    
	PINSEL1|=(1<<0); 
	PINSEL1&=~(1<<1);// p0.16 exint_0
	PINSEL0|=(1<<29);
	PINSEL0&=~(1<<28);// p0.14 exint_1
	IODIR0|= motor1|motor2|led;
	//LCD_string("industrial safety and emergency shutdown system");
	LCD_command(0x18);
	UART0_configure();
	LCD_init();
	VICIntSelect=0;
	VICDefVectAddr=(unsigned long)NonVect_ISR;
	EXTMODE=0x03;
	EXTPOLAR=0x00;
	VICIntEnable=(1<<14)|(1<<15);
	
	
	while(1)
	{
	//IODIR0|= motor1|motor2;
	if(flag==0){
	LCD_command(0x01);
	LCD_string("motor on");
	UART0_str("motor on");
	IOSET0|= motor1;
	IOCLR0|= motor2;
	flag=1;
	}

	//delay_ms(2000);
	}


}
