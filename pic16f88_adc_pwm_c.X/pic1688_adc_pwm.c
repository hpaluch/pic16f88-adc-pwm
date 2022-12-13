/*
 * File:   pic1688_adc_pwm.c
 * Summary:
 *    TODO: Will read potentiometer value with ADC
 *          and set LED brightness on
 *          that value using PWM
 *     I/O: RA1/PIN18 LED output
 *  DevKit: DM163045 - PICDEM Lab Development Kit
 *    MCU: PIC16F88 PDIP
 *     SW: MPLAB X IDE v6.05, XC8 v2.40, DFP 1.3.42
 * Created on December 13, 2022, 1:20 PM
 */

// PIC16F88 Configuration Bit Settings
// 'C' source line config statements
// Window -> Target Memory Views -> Configuration Bits
// CONFIG1 and 2 mostly generated from:
// Window -> Target Memory Views -> Configuration Bits
// CONFIG1
#pragma config FOSC = INTOSCCLK // Oscillator Selection bits (INTRC oscillator; CLKO function on RA6/OSC2/CLKO pin and port I/O function on RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#ifndef __DEBUG
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT disabled fo debug)
#else
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#endif
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON        // Low-Voltage Programming Enable bit ON
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB0      // CCP1 Pin Selection bit (CCP1 function on RB0)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// CONFIG2
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode disabled)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define  _XTAL_FREQ 4000000 // f_osc (4MHz) for __delay_ms();
#include <xc.h>

// My I/O ports
#define fLED_MASK  _PORTA_RA1_MASK

// show to user which mode is compiled
#ifdef __DEBUG
#warning Build in Debug mode
#else
#warning Build in Production (Run) mode
#endif

// start with Flash LED ON
// v = variable
// PIC16F88 has no LATA (Latch on Port A) - read-modify-write
// reads real value on input which often leads to unexpected
// behaviour - therefore we use "shadow variable"
volatile unsigned char vLATA = fLED_MASK;

void toggle_LED(void)
{
    vLATA = vLATA ^ fLED_MASK;
    PORTA = vLATA;
}

void main(void) {
    // initialize PINs as soon as possible
    PORTA = vLATA;
    TRISA = ~fLED_MASK; // only our LED set as output
    PORTA = vLATA; // ensure that values are really set
    
    // enable I/O on RA1 (Flash LED)
    ANSEL = ~ _ANSEL_ANS1_MASK; 
    
    OSCCONbits.IRCF = 0b110;    // f = 4 MHz => 1 MHz instruction clock
    // wait until OSC is stable, otherwise we will screw up 1st
    // call of __delay_ms() !!! it will be much slower then expected!!
    while(OSCCONbits.IOFS == 0){/*nop*/};
    vLATA &= ~fLED_MASK; // Flash LED now off
    PORTA = vLATA;

    while(1){
       toggle_LED();
       __delay_ms(250);
    }
}
