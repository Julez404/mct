#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t period_count = 0;

void initPort(void);
void initTmr(void);

int main(void)
{
	initPort();
	initTmr();

	while (1)
	{

	}
}

void initPort(void)
{
DDRD = 0;
PORTD = 0;
}


void initTmr(void)
{
	//TIMER 1 Generator Count
	TCCR1A = 0;
	TCCR1B = 0b11000010;
	TCCR1C = 0;
	TIMSK1 = (1 << 5);
	sei();
}

ISR(TIMER1_CAPT_vect)
{
	period_count = TCNT1;
	TCNT1 = 0;
	
	float period_ms = period_count*0.0000625;
	/*
	Serial.print(period_ms);
	*/

}