/* 
* Library of common functions
* For the readers of the Beginner's Guide to Embedded C book series
* by Chuck Hellebuyck
* Copyright 2010
* Version 1.1 - Written for Chipino with 16F886
*/

#include <htc.h>
#include <stdio.h>


// _____________Hardware Defines and Settings ____________

//#define _XTAL_FREQ 16MHZ       //-- Define the crystal frequenc

// ******************
// LCD Setup
// ******************
// ** Special Note: You also need to change the TRIS Port setting in lcd_init()
// --- For PortB LCD control
#define	LCD_RS RC3
//#define	LCD_RW RC1
#define LCD_EN RC0
#define LCD_DATA PORTD
// --- For PortC LCD Control
//#define	LCD_RS RC4
//#define	LCD_RW RC6
//#define LCD_EN RC5
//#define LCD_DATA	PORTC
// --- For PortD LCD Control
//#define	LCD_RS RD4
//#define	LCD_RW RD5
//#define LCD_EN RD6
//#define LCD_DATA	PORTD

#define	LCD_STROBE()	((LCD_EN = 1),(pause(10)),(LCD_EN=0))

// ******************
// USART PINs Defined
// ******************

// USART PIN defined settings 16F690
//#define RX_PIN TRISB5
//#define TX_PIN TRISB7

// USART PIN defined settings 16F886
//#define RX_PIN TRISC7
//#define TX_PIN TRISC6

// ******************
// Hardware SPI Setup
// ******************
// PIC16F690
//#define CS RC6		//CS = RC6  'Chip select pin
// SCK - RB6 	SPI Clock Connection
// SDI - RB4	SPI Data Into PIC Connection
// SDO - RC7	SPI Data Out of PIC Connection

// PIC16F886
//#define CS RA5		//CS = RA5  'Chip select pin
// SCK - RC3 	SPI Clock Connection
// SDI - RC4	SPI Data Into PIC Connection
// SDO - RC5	SPI Data Out of PIC Connection

// ******************
// External MSP23S08 I/O Expander Write
// ******************

//#define IODIR 0x00	// Data Direction Register
//#define OLAT 0x0A	// Output Latch Register
//#define GPIO 0x09	// Port Register


// *****************
// Simple C Prototypes
// *****************
#define _XTAL_FREQ 48000000

#define TRIG_DIR TRISB0
#define ECHO_DIR TRISB1

#define TRIG_PIN RB0
#define ECHO_PIN RB1

void HCSR04_Init(void);
float HCSR04_Get_Distance(void);
void init_micro(void);
void usecbase(void);
void pauseus ( unsigned int usvalue );
void msecbase(void);
void pause( unsigned short usvalue );
void high(char pin);
void low(char pin);
char input(char pin);
void pulseout(char pin, unsigned long per);
void lcd_write(unsigned char c);
void lcd_clear(void);
void lcd_text(const char * s);
void lcd_symbol(char c);
void lcd_goto(unsigned char pos);
void lcd_number(char c);
void lcd_number1(char c);
void lcd_number2(char c);
void lcd_init(void);
void init_serial(int baud);
//void putch(unsigned char byte);
//unsigned char getch();
void spi_init(void);
char SPI_OUTPUT ( char spi_byte );
void WR_BYTE ( char EE_address, char EE_data );
char RD_BYTE ( char EE_address );
void WR_MCP23S08 ( char regist, char data );
char RD_MCP23S08 ( char regist );
void pwmout1 (char duty, int freq); 
void pwmout2 (char duty, int freq); 
char adcin (char chan);
void i2c_init();
void i2c_waitForIdle();
void i2c_start();
void i2c_repStart();
void i2c_stop();
int i2c_read( unsigned char ack );
unsigned char i2c_write( unsigned char i2cWriteData );
void I2C_EEOUT (unsigned char address, unsigned char data);
unsigned char I2C_EEIN(unsigned char address);

//DEFINIDAS PARA PRÁCTICAS
char  DEC2VOLT (char chan,char *voltaje,char *Rvalue);
char adcAHAL (char chan,char *val1,char *val2);
