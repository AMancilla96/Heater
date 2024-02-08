// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


char c = 'i',c1=0;
short Uart_Available(void);
short TMR0_Available(void);
char Uart_Read(void);
void Uart_Send_String(char *info);
void Uart_Send_Char(char txData);
void Uart_Read_StringUntil(char stop_c, char* buf, unsigned int st_size);
void Uart_Read_Substring(char* cp, char* vc, int inc, int fn);
void Manda_Pwm(char op);
void Control(void);
char adcAHAL(char chan, char *val1, char *val2);
void DEC2VOLT(float voltaje);
void pause(unsigned short usvalue);
void msecbase(void);
char buf[1],buf1[5],buf2[10],BUF3[10],temperatura[3],tiempo[2],time[2];
char voltaje, Rvalue, AHval,ALval,ti,te;
int VOL;
float TEMP;

void main(void) {
    ANSEL = 0b00100000;
    ANSELH = 0x00;
    TRISB = 0;
    TRISC = 0b00000100;
    TRISD = 0;
    OPTION_REG = 0b11010111;
    TMR0 = 0x3D;
    SPBRG = 0x19;
    RCSTA = 0b10010000;
    RCIF = 0;
    TXSTA = 0b00100110;
    CCP1CON = 0x0C;
    PR2 = 0xFA;
    T2CONbits.T2CKPS = 0b01;
    CCPR1L = 0;
    T2CONbits.TOUTPS = 0;
    T2CONbits.TMR2ON = 1; //encender el timer 2
    while (TMR2IF = 0);
    TRISC = 0;
    RCIE = 1;
    RBIE = 1;
    PEIE = 1;
    GIE = 1;
    T0IE = 1;
    T0IF = 0;
    
    //Uart_Send_String(tiempo);
    while (1) {
        while(RA0==1){
        if (Uart_Available()) {
            c = Uart_Read();
            //Uart_Send_Char(c);
        }
        if(c=='C'){
            //pause(100);
            Control();
            c=0;
        }
        Manda_Pwm(c);
        RB0 = 1;
        RB1 = 0;
        pause(5000);
        RB0=0;
        RB1=1;
        adcAHAL(5, &AHval, &ALval);
        VOL = AHval << 8;
        VOL = VOL + ALval;
        TEMP = VOL / 2.046;
//        sprintf(buf2,"%4.2f\n",TEMP);
        Uart_Send_String("Mando temperatura\n");
    }
        Manda_Pwm('5');
    }}
void Control(void){
    int j=0,residuo;
    char i;
    int LmInf,LmSup;
    while(tiempo[0]!='x'){
if (Uart_Available()) {
            Uart_Read_StringUntil('\n',BUF3,10);
            Uart_Read_Substring(BUF3,tiempo,1,2);
            Uart_Read_Substring(BUF3,temperatura,4,5);
ti=atoi(tiempo);
te=atoi(temperatura);
LmInf=te-2;
LmSup=te+2;

while(j<ti){
        adcAHAL(5, &AHval, &ALval);
        VOL = AHval << 8;
        VOL = VOL + ALval;
        TEMP = VOL / 2.046;
        if(TEMP>=LmSup){
        CCPR1L =0;
        RB0=0;
        RB1=1;
        }
        else if (TEMP>=te&&TEMP<=LmSup){
        CCPR1L =0;
        RB0=0;
        RB1=1;
        }
        else if(TEMP == te){
        CCPR1L =0;
        RB0=0;
        RB1=1;
        }
        else if(TEMP >= LmInf && TEMP <= te ){
            CCPR1L = 0x4B;
            RB0=1;
        RB1=1;
        }
        else{
        CCPR1L = 0x7D;
        RB0=1;
        RB1=1;
        }
        pause(1000);
//       sprintf(buf2,"%4.2f\n",TEMP);
        j++;
        i=j+'0';
        residuo=j%5;
        if(residuo==0){
        Uart_Send_String("Mando temperatura\n");
        }
        }
break;
}
}
}
void Manda_Pwm(char op) {
    //Uart_Send_String("inicie manda PWM");
    switch (op) {
        case '0': //10% CICLO
            //Uart_Send_String("10% de ciclo \n");
            pause(200);
            CCPR1L = 0x19;
            break;

        case '1': //30% CICLO
            //Uart_Send_String("30% de ciclo \n");
            pause(200);
            CCPR1L = 0x4B;
            break;

        case '2': //50% CICLO
            //Uart_Send_String("50% de ciclo \n");
            pause(200);
            CCPR1L = 0x7D;
            break;

        case '3': //70% CICLO
            //Uart_Send_String("70% de ciclo \n");
            pause(200);
            CCPR1L = 0xAF;
            break;

        case '4': //100% CICLO
            //Uart_Send_String("100% de ciclo \n");
            pause(200);
            CCPR1L = 0xFA;
            break;

        default:
            //Uart_Send_String("0% de ciclo \n");
            pause(200);
            CCPR1L = 0;
            break;


    }

}

void pause(unsigned short usvalue) {
    unsigned short x;
    for (x = 0; x < usvalue; x++) {
        msecbase();
    }
}

void msecbase(void) {
    OPTION_REG = 0b11010001;
    TMR0 = 0x0F;
    while (!T0IF);
    T0IF = 0;
}

short Uart_Available(void) // Funcion de verificacion si ha recibido datos
{
    return PIR1bits.RCIF ? 1 : 0;
}

char Uart_Read(void) // Funcion para recibir caracteres
{
    while (PIR1bits.RCIF == 0);
    if (RCSTAbits.OERR == 1) {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    PIR1bits.RCIF = 0;
    return RCREG;
}

void Uart_Send_Char(char txData) // Funcion para transmitir caracteres
{
    while (TXSTAbits.TRMT == 0);
    TXREG = txData;
}

void Uart_Send_String(char *info) // Funcion para transmitir una cadena de caracteres
{
    while (*info) {
        Uart_Send_Char(*info++);
    }
}

char adcAHAL(char chan, char *val1, char *val2) {
    switch (chan) {
        case 5:
            //TRISA0 = 1;				// Make RA0/AN0 an Input
            //ANS0 = 1;				// Configure RA0 to Analog to Digital input
            ADCON1 = 0b10000000;
            ADCON0 = 0b01010100; // Configure A/D to use AN0, left justified
            break;
        case 6:
            ADCON0 = 0xD9; // Configure A/D to use AN1, left justified
            break;
        case 7:
            ADCON0 = 0xDD; // Configure A/D to use AN2, left justified
            break;
        default:
            break;
    }
    ADON = 1; // A/D Converter on;
    pause(2); // Sample Time
    GO_nDONE = 1; // Start A/D conversion on AN0
    while (GO_nDONE == 1); // Wait for conversion to complete
    *val1 = ADRESH;
    *val2 = ADRESL;
    return 0;
}

void DEC2VOLT(float voltaje) {
    float val;
    val = voltaje / 2.046;
    sprintf(buf,"%i\n",val);
        Uart_Send_String(buf);
    }



void Uart_Read_StringUntil(char stop_c, char* buf, unsigned int st_size) {
    unsigned int rx_cont = 0;
    while (*(buf - 1) != stop_c) {
        rx_cont++;
        *buf++ = Uart_Read();
        if (rx_cont >= st_size) break;
    }
    *--buf = 0;
}
void Uart_Read_Substring(char* cp, char* vc, int inc, int fn)
{
    int pt = 0;
    for(int lt=inc; lt<=fn; lt++)
    {
        vc[pt] = cp[lt];
        pt++;
    }
    vc[pt] = '\0';
    pt = 0;
}