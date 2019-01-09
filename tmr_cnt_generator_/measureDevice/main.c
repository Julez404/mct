/*
* measureDevice.c
*
* Created: 08.01.2019 17:19:34
* Author : julia
*/

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t tmr2_OV_took_place = 0;

void initPort();
void initTmr();

int main(void)
{
	initPort();
	initTmr();

	while (1)
	{

	}
}

void initPort()
{
DDRD = 0;
PORTD = 0;
}


void initTmr()
{
	//TIMER 1 Generator Count
	TCCR1A = 0;
	TCCR1B = 0b00000111;
	TCCR1C = 0;

	//TIMER 2 TIMER Windows
	TCCR2A = 0;
	TCCR2B = 0b00000111;
	TIMSK2 = (1 << 0);
	sei();
}

ISR(TIMER2_OVF_vect)
{
	if(tmr2_OV_took_place >= 12)
	{
//		Serial.Print(TCNT1/0.19661);
		TCNT1 = 0;
		tmr2_OV_took_place = 0;
	}
	else
	{
		tmr2_OV_took_place++;
	}
}