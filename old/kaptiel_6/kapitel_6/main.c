/*
* kapitel_6.c
*
* Created: 04.12.2018 16:29:35
* Author : julia
*/

#include <avr/io.h>
#include <avr/interrupt.h>

void initMCU(void);

int main(void)
{
	initMCU();

	/* Replace with your application code */
	while (1)
	{

	}
}

void initMCU(void)
{
	DDRD = 0b00000100;
	PORTD = 0;
	ACSR |= (1 << ACIE) | (1 << ACBG);
	sei();
}



ISR (ANALOG_COMP_vect)
{
	if(ACSR & (1 << ACO))
	{
		PORTD |= (1 << 2);
	}
	else
	{
		PORTD &= ~(1 << 2);
	}
}

