#include<reg51.h>
#include<intrins.h>
#include<string.h>

// Defines LCD data port as P2
#define lcd_data P2

// Define 16-bit Data Pointer register
sfr16 DPTR=0x82;

// Define pins for ultrasonic sensor
sbit trig=P3^5;  // Trigger pin
sbit echo=P3^2;  // Echo pin

// Variables to store distance and prescription calculation
unsigned int range=0;
unsigned int result_whole = 0;
unsigned int result_fraction = 0;

// Pins for LCD control
sbit rs=P0^0;  // Register Select
sbit rw=P0^1;  // Read/Write
sbit en=P0^2;  // Enable

// Function prototypes (forward declerations)
void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);
void lcd_delay();

void lcd_init()
{
    cmd(0x38);  // 2 lines for 5x7 matrix display
    cmd(0x0e);  // Display ON, cursor ON
    cmd(0x06);  // Increment cursor
    cmd(0x0c);  // Display ON, cursor OFF
    cmd(0x80);  // Force cursor to beginning of 1st line
}

// Sends command to LCD module
void cmd(unsigned char a)
{
    lcd_data=a;
    rs=0;  // Select command register
    rw=0;  // Enables write mode
    en=1;  // Enable  the pulse
    lcd_delay();
    en=0;
}

// Sends data to LCD module
void dat(unsigned char b)
{
    lcd_data=b;
    rs=1;  // Select data register
    rw=0;  // Write mode
    en=1;  // Enable pulse
    lcd_delay();
    en=0;
}

// Display string data on our LCD module
void show(unsigned char *s)
{
    while(*s) {
        dat(*s++);
    }
}

// Delay function for LCD operations (to avoid data collisions)
void lcd_delay()
{
    unsigned int i;
    for(i=0;i<=1000;i++);
}

// Generates an ultrasonic pulse for sending to HC-SR04 module
void send_pulse(void)
{
    TH0=0x00;TL0=0x00;  // Reset our Timer0
    trig=1;
    // Generate a 10µs pulse
    _nop_();_nop_();_nop_();_nop_();_nop_();
    _nop_();_nop_();_nop_();_nop_();_nop_();
    trig=0;
}

// Measuring distance using ultrasonic sensor
unsigned char ultrasonic()
{
    unsigned char get;
    send_pulse();
    while(!echo);  // Wait for echo to start
    while(echo);   // Wait for echo to end
    DPH=TH0;
    DPL=TL0;
    TH0=TL0=0xff;

    // Calculate distance in cm (speed of sound = 343m/s)
    if(DPTR<38000)
        get=DPTR/59;
    else
        get=0;
    return get;
}

void main()
{
    // Initialize Timer0 in 16-bit mode
    TMOD=0x09;
    TH0=TL0=0;
    TR0=1;  // Start Timer0
    
    lcd_init();
    show("POW");  // Display "POW" on LCD
    
    P3|=(1<<2);  // Enable interrupt for echo pin
    
    while(1) {
        cmd(0x84);  // Move cursor to position 4 on the first line
        range=ultrasonic();  // Measure distance
        
        if (range !=0)
        {
            // Calculate prescription based on measured distance
            result_whole = 100/range;
            result_fraction = (((100%range)*100)/range);
        }
        
        // Display prescription on LCD (legacy method!)
        dat('-');
        dat((result_whole/10)+48);
        dat((result_whole%10)+48);
        dat('.');
        dat((result_fraction/10)+48);
        dat((result_fraction%10)+48);
    }
}