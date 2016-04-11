#pragma     config  FOSC = XT
#pragma     config  WDTE = OFF
#pragma     config  PWRTE = ON
#pragma     config  CP = OFF

#define _XTAL_FREQ  4000000

#include <xc.h>

#define START PORTAbits.RA3
#define STOP PORTAbits.RA2
#define RESET PORTAbits.RA4
//global variable for current output number
int number = 0;

/*
 * Takes a decimal number as an argument and returns the pin values for output 
 * to a seven segment display or blank screen if input is out of bounds.
 */
int convertSevenSegment(int decimalNumber)
{
    switch (decimalNumber)
    {
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
            return ~0b00000001;
    }
}

void interrupt isr()
{
    INTCONbits.INTF = 0;
    int run = 1;
    extern int number;
    
//  Fix this
    while (run)
    {
        
        run = !START;
        
        if (RESET)
        {
            number = 0;
            PORTB = convertSevenSegment(number);
        }
    }
    
    
}

void main()
{
    extern int number;
    TRISB = 0b00000001;
    TRISA = 0b11111;
    
    INTCONbits.INTF = 0;

    OPTION_REGbits.INTEDG = 1;

    INTCONbits.INTE = 1;

    INTCONbits.GIE = 1;

    while (1)
    {
        for (number = 0; number < 10; number++)
        {
            PORTB = convertSevenSegment(number);
            //  TODO set delayTime to 1000 when not in simulator
            __delay_ms(1000);
        }
    }
}
