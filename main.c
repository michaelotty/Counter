#pragma     config  FOSC = XT
#pragma     config  WDTE = OFF
#pragma     config  PWRTE = ON
#pragma     config  CP = OFF

#define _XTAL_FREQ  4000000
//#define LED1        PORTBbits.RB1
//#define LED1_TRIS   TRISBbits.TRISB1
//#define LED2        PORTBbits.RB2
//#define LED2_TRIS   TRISBbits.TRISB2

#include <xc.h>

int i = 0;

int convertSevenSegment(int decimalNumber) {
    switch (decimalNumber) {
        case 0:
            return ~0b10111110;
        case 1:
            return ~0b10100000;
        case 2:
            return ~0b11011010;
        case 3:
            return ~0b11110010;
        case 4:
            return ~0b11100100;
        case 5:
            return ~0b01110110;
        case 6:
            return ~0b01111110;
        case 7:
            return ~0b10100010;
        case 8:
            return ~0b11111110;
        case 9:
            return ~0b11100110;
        default:
            return 0b11111110;
    }
}

void interrupt isr() {
    INTCONbits.INTF = 0;
    int run = 1;
    extern int i;
    while(run) {
        i = !PORTAbits.RA4;
        run = !PORTAbits.RA4;
        run = !PORTAbits.RA3;
    }
}


void main() {
    extern int i;
    TRISB = 0b00000001;
    TRISA = 0b11111;
    
//    LED1_TRIS = 0;
//    LED2_TRIS = 0;
    
    INTCONbits.INTF = 0;
    
    OPTION_REGbits.INTEDG = 1;
    
    INTCONbits.INTE = 1;
    
    INTCONbits.GIE = 1;
    
    while(1) {
//        LED1 = 1;
//        __delay_ms(500);
//        
//        LED1 = 2;
//        __delay_ms(500);
        for (i = 0; i < 10; i++) {
            PORTB = convertSevenSegment(i);
            __delay_ms(1000);
        }
        
    }
    
    return;
}
