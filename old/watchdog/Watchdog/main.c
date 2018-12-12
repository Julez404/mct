/*
 * Watchdog.c
 *
 * Created: 27.11.2018 16:19:13
 * Author : julian
 */ 

 #define TIMEOUT_GE 3
 #define TIMEOUT_RT 6

 


#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/wdt.h>
volatile uint8_t count = 0;

void initInterrupt(void);
void initWDT(void);
void initPorts(void);


int main(void)
{
initPorts();
initInterrupt();
initWDT();
sei();

    while (1) 
    {
		if(PIND & (1 << 2))
		{
			count =0;
		}
    }
}

//void initInterrupt(void);



void initPorts(void)
{
DDRB = 0xFF;
PORTB = 0;
DDRD = 0x00;
PORTD = 0xFF;
}

void initInterrupt(void)
{
}

void initWDT(void)
{
uint8_t WDTCSR_soll = 0b01010110;

WDTCSR |= ((1 << WDCE) | (1 << WDE)) ;
WDTCSR = WDTCSR_soll;

}

ISR(WDT_vect)
{
	count++;
	if(count >= TIMEOUT_GE)
	{
		PORTB |= (1 << 2);
	}
	if(count >= TIMEOUT_RT)
	{
		PORTB |= (1 << 3);
	}
}