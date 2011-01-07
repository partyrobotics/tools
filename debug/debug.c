// 
// Copyright (c) Party Robotics LLC 2010
// Written by Robert Kaye <rob@partyrobotics.com>
//
#include <avr/io.h>
#include <stdarg.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define BAUD 9600
#define UBBR (F_CPU / 16 / BAUD - 1)

#define _UBRRH UBRRH
#define _UBRRL UBRRL
#define _UCSRB UCSRB
#define _UCSRC UCSRC
#define _TXEN  TXEN
#define _USBS  USBS
#define _UCSZ1 UCSZ1
#define _UCSZ0 UCSZ0
#define _UCSRA UCSRA
#define _UDRE  UDRE
#define _UDR   UDR 

// TODO: This section needs to be customized for each AVR chip.
void serial_init(void)
{
    // UART 0
    /*Set baud rate */ 
    _UBRRH = (unsigned char)(UBBR>>8); 
    _UBRRL = (unsigned char)UBBR; 

    /* Enable transmitter */ 
    _UCSRB = (1<<_TXEN); 
    /* Set frame format: 8data, 1stop bit */ 
    _UCSRC = (0<<_USBS)|(3<<_UCSZ0); 

    // UART 1
    /*Set baud rate */ 
    _UBRRH = (unsigned char)(UBBR>>8); 
    _UBRRL = (unsigned char)UBBR; 

    /* Enable transmitter */ 
    _UCSRB = (1<<_TXEN); 
    /* Set frame format: 8data, 1stop bit */ 
    _UCSRC = (0<<_USBS)|(3<<_UCSZ1); 
}

void serial_tx(unsigned char ch)
{
    while ( !( _UCSRA & (1<<_UDRE)) )
        ;

    UDR = ch;
}

#define MAX 80 
void dprintf(const char *fmt, ...)
{
    va_list va;
    va_start (va, fmt);

    char buffer[MAX];
    char *ptr = buffer;
    vsnprintf(buffer, MAX, fmt, va);
    va_end (va);

    for(ptr = buffer; *ptr; ptr++)
		{
		   if (*ptr == '\n') serial_tx('\r');
       serial_tx(*ptr);
    }
}
