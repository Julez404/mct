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

void initPorts()
{
	DDRB = (1 << 3);
	PORTB = 0;
}

void initTimer()
{
	TCCR2A |= (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);								// No Compare Operation
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);	// Prescaler select
	TIMSK2 = (1 << 0);
	OCR2A = 30;
}

void initInterrupt()
{
	ADMUX = (1 << ADLAR) | (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1)| ( 1 << ADPS0);
	ADCSRA |= (1 << ADSC);
	sei();
}

ISR(ADC_vect)
{
	OCR2A = ADCW;
}

ISR(TIMER2_OVF_vect)
{
	ADCSRA |= (1 << ADSC);
}