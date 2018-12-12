/*
* 7_segment.c
*
* Created: 06.11.2018 17:17:26
* Author : julia
*/



#define F_CPU 16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "7segment.h"

void	initPorts(void);
void	initInterrupt(void);

volatile uint8_t count=0;

int main(void)
{
	initPorts();
	initInterrupt();

	while (1)
	{
		segment_printNumber(count);
		_delay_ms(200);
		count++;

		if (count >15)
		{
			break;
		}
	}
	segment_printNumber(0);
	count=0;
	while(1)
	{
		segment_printNumber(count);
		
		if(count > 15)
		{
			break;
		}
	}
	while(1)
	{}
}

void	initPorts(void)
{
	DDRB = 0;
	DDRD = 0;
	PORTB = 0;
	PORTD = 0b00000100;
	DDRB = 0xFF;
	DDRD = 0xFF;
}

void	initInterrupt(void)
{
	EICRA |= (1 << ISC01);	//Enable INT0 Irq on Falling edge
	EIMSK |= (1 << INT0);	//
	sei();
}

ISR (INT0_vect) //Interrupt for Interrupt
{
	_delay_ms(100);
	if (PIND & (1 << 2))
	{
		count++;
	}
}