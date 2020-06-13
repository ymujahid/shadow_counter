/* 
 * File:   counter.c
 * Author: Yunus Mujahid
 *
 * Created on June 12, 2020, 9:54 AM
 */


// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 16000000

#include <xc.h>

unsigned char const SEGMENT_MAP[] = {0x3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F};
int first_digit = 0;
int second_digit = 0;

void main(void) {
    PORTA = PORTB = PORTC = PORTD = PORTE = 0;
    TRISB0 = 1;
    TRISD = 0;
    TRISC = 0;
    while(1){
//        when it senses a shadow  --> when there is no light to be absorbed by the LDR
//        send 1 to the microcontroller
//        then increment the count by 1
//        then when the count reaches 9 prepare for 2 digits
//        and make sure that while the first counter displays 1, the other increases
//        what if the shadow(person) stays for long
//        let the counter wait for 10 seconds for the person to move away 
        if (RB0 == 1){
            __delay_ms(10);
            if (RB0 == 1){
                    second_digit++; 
                    if (second_digit > 9){
                        first_digit++;
                        second_digit = 0;
                    }
                    PORTD = SEGMENT_MAP[first_digit];
                    PORTC = SEGMENT_MAP[second_digit];
            }
        }
        for (int i = 1; i<=10; i++){
                        __delay_ms(500);
                    }
 
        
        
    }
    return;
}
