#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include<xc.h>

void delay(int a);
void display(int r,char c);
void write(char c);
void read();
void string_display(char *str);
void check(char c,char c1);
void motor_still();
char a=0;
void main(void)
{
  PORTA=0x00;
  TRISA=0x0F;
  PORTB=0x00;
  TRISB=0x0F;
  PORTC=TRISC=0x00;
  PORTD=TRISD=0x00;
  PORTE=TRISE=0x00;
  ANSEL=ANSELH=0x00;
  display(0,0x38);
  display(0,0x0e);
  char floor='0';
  char sensor='0';
  while(1)
{
      if(RB0==1)
      {
          check(sensor,floor);
          floor='3';
          write(floor);
          read();
          display(0,0x80);
          string_display("FLOOR ");
          display(1,a);
          if(RA0==0)
          {
              motor_still();
              sensor='3';
          }
          while(RB0==1);
      }
       if(RB1==1)
      {
          check(sensor ,floor);
          floor='2';
          write(floor);
          read();
          display(0,0x80);
          string_display("FLOOR ");
          display(1,a);
           if(RA1==0)
          {
               motor_still();
               sensor='2';
          }
           while(RB1==1);

      }
      if(RB2==1)
      {
          check(sensor,floor);
          floor='1';
          write(floor);
          read();
          display(0,0x80);
          string_display("FLOOR ");
          display(1,a);
           if(RA2==0)
          {
               motor_still();
               sensor='1';
          }
           while(RB2==1);
      }
      if(RB3==1)
      {
          check(sensor,floor);
          floor='0';
          write(floor);
          read();
          display(0,0x80);
          string_display("FLOOR ");
          display(1,a);
           if(RA3==0)
          {
               motor_still();
               sensor='0';
          }
           while(RB3==1);
      }
}
}
void delay(int a)
{
  while(a--);
}
void display(int r,char c)
{
  RE0=r;
  PORTD=c;
  RE1=1;
  delay(10);
  RE1=0;
  delay(10);
}
void write(char ec)
{
    EEADR=0xD0;
    EEPGD=0;
    EEDATA=ec;
    WREN=1;
    EECON2=0x55;
    EECON2=0xAA;
    WR=1;
    while(WR);
    WREN=0;
}
void read()
{
    EEADR=0xD0;
    EEPGD=0;
    RD=1;
    while(RD);
    RD=0;
    a=EEDATA;
}
void string_display(char *str)
{

    while(*str)
    {
        display(1,*str++);
    }
}
void check(char c,char c1)
{
           if(c>c1){
                 RC1=1;RC0=0;
                display(0,0xC0);
                string_display("Motor mvg bw");
           }
             else if(c==c1)
             {
                RC1=0;RC0=0;
                display(0,0xC0);
                string_display("Motor still");
             }
           else{
               RC1=0;RC0=1;
               display(0,0xC0);
               string_display("Motor mvg fw");
           }
}
void motor_still()
{
                RC1=0;RC0=0;
                display(0,0xC0);
                string_display("Motor still");
}
