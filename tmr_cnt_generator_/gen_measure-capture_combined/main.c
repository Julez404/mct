// #define PRESCALER_0
// #define PRESCALER_1
// #define PRESCALER_8
// #define PRESCALER_32
// #define PRESCALER_64
// #define PRESCALER_128
#define PRESCALER_256
// #define PRESCALER_1024


#include <avr/io.h>
#include <avr/interrupt.h>

#include "scales.h"


void initPort(void);
void initTmr(void);


volatile uint8_t tmr1_ovf_count = 0;
volatile float period_ms = 0;


int main(void)
{
	//Serial.begin(115200);
	initPort();
	initTmr();
	while (1)
	{
	//Seriel.println(period_ms);
	}
}

void initPort(void)
{
	DDRB &= ~(1 << 0);	//PB0 Input
	PORTB = 0;
	DDRD |= (1 << 7);	//PD7 Output
	PORTD = 0;
}

void initTmr(void)
{
	//Init Timer 1 for Signal Capture
	TCCR1A = 0;
	TCCR1B = (1 << 7) | (1 << 6) | (1 << CS10);
	TCCR1C = 0;
	TIMSK1 = (1<<ICIE1) | (1 << TOIE1);
	
	//Init Timer 2 for output Signal
	TCCR2A = 0;
	TCCR2B = (PRE_BIT_2 << 2) |(PRE_BIT_1 << 1)|(PRE_BIT_0 << 0);
	TIMSK2 |= (1 << 0);
	sei();
}

ISR(TIMER2_OVF_vect)
{
	PORTD ^= (1 << 7);
}


ISR(TIMER1_CAPT_vect)
{
	uint16_t timestamp = (ICR1L) | (ICR1H << 8);
	uint16_t period_count = 0;
	static uint16_t timestamp_old;

	if(tmr1_ovf_count != 0)
	{
		period_count = timestamp;
		
		while (tmr1_ovf_count != 0)
		{
			period_count += 65536;
			tmr1_ovf_count--;
		}
		period_count+= (65536-timestamp_old);
	}
	else
	{
		period_count = timestamp-timestamp_old;
	}
	period_ms = period_count * 0.0625;
	timestamp_old = timestamp;
}

ISR(TIMER1_OVF_vect)
{
	tmr1_ovf_count++;
}
