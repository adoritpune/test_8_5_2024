/*
 * File:   led_main.c
 * Author: sm06
 *
 * Created on 12 July, 2017, 5:34 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <pic18.h>
#define _XTAL_FREQ  4000000

#pragma config CONFIG1H=0X08        //internal oscillator selected
//#pragma config CONFIG2L=0X01        //
#pragma config CONFIG2H=0X00        //watchdog timer
#pragma config CONFIG3H=0X00        //MCLR FUNCTION ENABLED
#pragma config CONFIG4L=0X00        //
#pragma config CONFIG5L=0X00        //
#pragma config CONFIG5H=0X80        //Data EEPROM Code Protection bit (Data EEPROM not code-protected)
#pragma config CONFIG6L=0X00        //
#pragma config CONFIG6H=0X80        //Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config CONFIG7L=0X00        //
#pragma config CONFIG7H=0X00        //

void UART_Init()
{
    RCSTAbits.SPEN=1;
    TRISCbits.RC6=0;
    TRISCbits.RC7=1;
    TXSTAbits.BRGH=0;
    BAUDCONbits.BRG16=0;
    TXSTAbits.SYNC=0;
    SPBRG=51;
    TXSTA=0X20;
    TXSTAbits.TXEN=1;
    RCSTAbits.CREN=1;
    PIE1bits.RCIE=1;
}
void delay()
{
    int ddd;
    int eee;
    for(ddd=0;ddd<20000;ddd++);
    for(eee=0;eee<20000;eee++);
}
void Send_Byte(unsigned char uartdata)
{
    while(TXSTAbits.TRMT != 1);
    TXREG=uartdata;
}

void oscillator_init()
{
   OSCCON=0x74;
   OSCTUNEbits.TUN=0;
   OSCTUNEbits.PLLEN=1;
   OSCTUNEbits.INTSRC=1;
   OSCCONbits.IRCF=7;
}

int main()
{
    UART_Init();
    oscillator_init();
    INTCONbits.GIE=1;          //global interrupt enable.
    INTCONbits.PEIE=1;         //peripheral interrupt enable.
    INTCONbits.INT0IE=1;       //INT0 External Interrupt Enable bit
    TRISA=0X00;
    TRISD=0XFF;
    Send_Byte('A');
    //TRISC0=0x00;
    while(1)
    {
        /*unsigned char uartdata= 'A';
        for(int i=0; i<5;i++)
        {
            uartdata=  uartdata+1;
            Send_Byte(uartdata);
        }
          */
        PORTA=0X00;
        delay();
        PORTA=0XFF;
        delay();
        
    }
    return (0);
}

