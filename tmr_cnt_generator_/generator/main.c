#include <avr/io.h>
#include <avr/interrupt.h>

/*
#define PRESCALER_0
#define PRESCALER_1
#define PRESCALER_8
#define PRESCALER_32
#define PRESCALER_64	
#define PRESCALER_128

#define PRESCALER_1024
*/

#define PRESCALER_64


#ifdef PRESCALER_0
#define PRE_BIT_0 0
#define PRE_BIT_0 0
#define PRE_BIT_0 0
#endif

#ifdef PRESCALER_1
#define PRE_BIT_0 1
#define PRE_BIT_1 0
#define PRE_BIT_2 0
#endif

#ifdef PRESCALER_8
#define PRE_BIT_0 0
#define PRE_BIT_1 1
#define PRE_BIT_2 0
#endif


#ifdef PRESCALER_32
#define PRE_BIT_0 1
#define PRE_BIT_1 1
#define PRE_BIT_2 0
#endif

#ifdef PRESCALER_64
#define PRE_BIT_0 0
#define PRE_BIT_1 0
#define PRE_BIT_2 1
#endif

#ifdef PRESCALER_128
#define PRE_BIT_0 1
#define PRE_BIT_1 0
#define PRE_BIT_2 1
#endif

#ifdef PRESCALER_256
#define PRE_BIT_0 0
#define PRE_BIT_1 1
#define PRE_BIT_2 1
#endif

#ifdef PRESCALER_1024
#define PRE_BIT_0 1
#define PRE_BIT_1 1
#define PRE_BIT_2 1
#endif

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
	DDRD = 0b10000000;
	PORTD = 0;
}

void initTmr(void)
{
	TCCR2A = 0;
	TCCR2B = (PRE_BIT_2 << 2) |(PRE_BIT_1 << 1)|(PRE_BIT_0 << 0);
	TIMSK2 |= (1 << 0);
	sei();
}

ISR(TIMER2_OVF_vect)
{
	PORTD ^= (1 << 7);
}