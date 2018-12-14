#include <avr/io.h>
#include <avr/interrupt.h>

void initPorts();
void initTimer();
void initInterrupt();

volatile uint8_t count = 0;

int main(void)
{
	initPorts();
	initTimer();
	initInterrupt();
	/* Replace with your application code */
	while (1)
	{
	
	}
}

ISR(TIMER2_COMPA_vect)
{
	if (count>=125)
	{
		PORTB ^= (1 << 3);
		count =0;
	}
	else
	{
		count++;
	}
}

void initPorts()
{
	DDRB = (1 << 3);
	PORTB = 0;
}

void initTimer()
{
	TCCR2A = (1 << WGM21);								// No Compare Operation
	OCR2A = 250;
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);	// Prescaler select
	TIMSK2 |= (1 << 1);									// Compare A Interrupt enable
}

void initInterrupt()
{
	sei();
}