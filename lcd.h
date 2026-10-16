#include"timer.h"
#define LCD_D 0xff<<23
#define RS 1<<18
#define E 1<<19
void LCD_init(void);
void LCD_command(unsigned char);
void LCD_data(unsigned char);
void LCD_string(unsigned char*);

void LCD_init(void)
{
PINSEL2=0;
IODIR1|=RS|E|LCD_D;
LCD_command(0x01);
LCD_command(0x02);
LCD_command(0x0C);
LCD_command(0x38);
}
void LCD_command(unsigned char cmd)
{
IOCLR1=LCD_D;
IOSET1=cmd<<23;
IOCLR1=RS;
IOSET1=E;
delay_millisecond(2);
IOCLR1=E;
}
void LCD_data(unsigned char d)
{
IOCLR1=LCD_D;
IOSET1=d<<23;
IOSET1=RS;
IOSET1=E;
delay_millisecond(2);
IOCLR1=E;
}
 
void LCD_string(unsigned char*s)
{
 while(*s)
  LCD_data(*s++);
}





