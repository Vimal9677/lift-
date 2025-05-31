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
#include <xc.h>
int floor,sensor;
void delay(unsigned int a)
{
    while(a--);
}
void enable()
{
    RE1=1;
    delay(50);
    RE1=0;
    delay(50);
}
void data(char a, char b)
{
    RE0=a;
    PORTD=b;
    enable();
}
void string(char *ptr)
{
    while(*ptr)
    {
        data(1,*ptr++);
    }
}
void main()
{
    PORTA=PORTB=PORTD=PORTE=PORTC=0x00;
    TRISA=0x0F;
    TRISB=0x0F;
    TRISC=TRISD=TRISE=0x00;
    ANSEL=ANSELH=0x00;
    
    data(0,0x38);
    data(0,0x0E);
    data(0,0x80);
    string("FLR");
    while(1)
    {
         data(0,0x84);
         data(1,floor+'0');
         string(" FLR AT ");
         data(1,sensor+'0');

        if(RA0==1)
            sensor=3;
            
        if(RA1==1)
            sensor=2;
        if(RA2==1)
            sensor=1;
        if(RA3==1)
            sensor=0;
        
        if(RB0==1)
            floor=3;
        if(RB1==1)
            floor=2;
        if(RB2==1)
            floor=1;
        if(RB3==1)
            floor=0;
        
        if(floor==sensor)
        {
            RC0=RC1=0;
            data(0,0xc0);
            string("Motor stop");
        }
        if(floor<sensor)
        {
            RC0=0;RC1=1;
            data(0,0xc0);
            string("Motor rev ");
        }
        if(floor>sensor)
        {
            RC1=0;RC0=1;
            data(0,0xc0);
            string("MOTOR for ");
        }
        
    }
}