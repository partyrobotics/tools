#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#define F_CPU 16000000UL
#include <util/delay.h>

// Bit manipulation macros
#define sbi(a, b) ((a) |= 1 << (b))       //sets bit B in variable A
#define cbi(a, b) ((a) &= ~(1 << (b)))    //clears bit B in variable A
#define tbi(a, b) ((a) ^= 1 << (b))       //toggles bit B in variable A

/*

This program drives an EasyDriver Stepper Motor Driver connected
to an Arduino Deicimila.

Arduino pin:   EasyDriver pin:
0 (PD0)        MS1
1 (PD1)        MS2
2 (PD2)        STEP
3 (PD3)        DIR
6 (PD6)        RESET
7 (PD7)        PFD

Driving a Mercury Motor SM-42BYG011-25 a minimum 
wait time between pulses seems to be 1.35ms.

*/

void pin_setup(void)
{
    DDRD |= (1<<PD0)|(1<<PD1)|(1<<PD2)|(1<<PD3)|(1<<PD6)|(1<<PD7);
}

int main(void)
{
    uint8_t i, j, dir;
    pin_setup();

    cbi(PORTD, 0); // MS1
    cbi(PORTD, 1); // MS2
    sbi(PORTD, 3); // DIR
    sbi(PORTD, 6); // RESET
    sbi(PORTD, 7); // PFD

    dir = 0;
    for(j= 0;; j++)
    {
    	sbi(PORTD, 2); // STEP
  	_delay_us(2);
    	cbi(PORTD, 2); // STEP
 	for(i = 0; i < 10; i++)
	    _delay_us(135);

        // Change direction every 256 steps
        if (0) //j == 255)
	{
	   dir = !dir;
            if (dir)
		sbi(PORTD, 3);
            else
                cbi(PORTD, 3);
  	    _delay_ms(2);
	}   
    }
}
