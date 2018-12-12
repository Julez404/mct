/*
Author: Julian Linn
MCU: ATMEGA328P
PINOUT:
---------------------------------------------------------------------------------------------------------------
Dir	Function		Pinning			Description
---------------------------------------------------------------------------------------------------------------
In	ModeSelect		PORTB(1:0)		0: On Delay, 1: Off Delay 2: Blink, 3: Pulse	(Only read on power-up)
In	TimeSelect		PORTB(5:2)		Binary coded 0...15s							(Only read on power-up)
In	Start			PORTD(3)		Start selected mode
In	Stop/Lock		PORTD(2)		Stop selected mode (PRIO)
Out LED1			PORTD(6)		Relays active
Out	LED2			PORTD(7)		Off Delay active
---------------------------------------------------------------------------------------------------------------*/

//-------------------------------------------------------------
// Defines
//-------------------------------------------------------------

#define F_CPU 16000000

//-------------------------------------------------------------
// Includes
//-------------------------------------------------------------

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

//-------------------------------------------------------------
// Declarations
//-------------------------------------------------------------

enum
{
	onDelay,
	offDelay,
	blink,
	pulse,
	lock,
};

//-------------------------------------------------------------
// Function Prototypes
//-------------------------------------------------------------

void initPort(void);
void initInterrupt(void);
void initRelaysParameters(void);

void onDelay_handler(void);
void offDelay_handler(void);
void blink_handler(void);
void pulse_handler(void);
void lock_handler(void);

uint8_t debounce (volatile uint8_t *port, uint8_t pin, uint8_t active);
void resetTimers(void);

//-------------------------------------------------------------
// Variables
//-------------------------------------------------------------

volatile uint8_t mode_selected = 0;
volatile uint8_t mode_active = 0;
volatile uint8_t time_selected = 0;

volatile uint8_t tmr0Count = 0;
volatile uint8_t s_count = 0;

volatile bool bnStart = false;
volatile bool bnStop = false;

volatile bool outRelays = false;
volatile bool outOffActive = false;

//-------------------------------------------------------------
// Main
//-------------------------------------------------------------

int main(void)
{
	initPort();
	initInterrupt();
	initRelaysParameters();
	
	mode_active = mode_selected;
	while (1)
	{
		switch(mode_active)	//Goto selected mode
		{
			case onDelay:	onDelay_handler(); break;
			case offDelay:	offDelay_handler(); break;
			case blink:		blink_handler(); break;
			case pulse:		pulse_handler(); break;
			case lock:		lock_handler(); break;
		}
	}
}

//-------------------------------------------------------------
// Handlers
//-------------------------------------------------------------
void onDelay_handler()
{
	resetTimers();
	while(bnStart && !bnStop)
	{
		while((s_count < time_selected) && bnStart)
		{
			;
		}
		outRelays = 1;
	}
	outRelays = 0;
}

void offDelay_handler()
{
	while(bnStart && !bnStop)
	{
		while (bnStart && !bnStop)
		{
			outRelays = 1;
		}

		if (!bnStart && !bnStop)
		{
			outOffActive = 1;
			resetTimers();
			while((s_count < time_selected) && !bnStop)
			{
				;
			}
			outRelays = 0;
			outOffActive = 0;
		}
	}
}

void blink_handler()
{
	while(bnStart && !bnStop)
	{
		outRelays = 1;
		resetTimers();

		while ((s_count < time_selected) && !bnStop && bnStart)
		{
			;
		}

		outRelays = 0;
		resetTimers();
		while ((s_count < time_selected) && !bnStop && bnStart)
		{
			;
		}
	}
	outRelays = 0;
}

void pulse_handler()
{
	if (bnStart)
	{
		outRelays = 1;
		resetTimers();
		while ((s_count < time_selected) && !bnStop && bnStart)
		{
			;
		}
		outRelays = 0;
		while(bnStart)
		{
			;
		}
	}
}

void lock_handler()
{
	if(!bnStop)			//Switch Back to mode_selected
	{
		mode_active = mode_selected;
	}
}

//-------

void ioHandler(void)
{
	//INPUT
	static bool bnStartLast[10] = {0};
	static bool bnStopLast[10] = {0};
	uint8_t countStart = 0;
	uint8_t countStop = 0;
	
	for (int i=9; i>0;i--)
	{
		bnStartLast[i] = bnStartLast[i-1];
		bnStopLast[i] = bnStopLast[i-1];
	}

	bnStartLast[0] = !(PIND & (1 << 3));
	bnStopLast[0] = !(PIND & (1 << 2));

	for (int i=0;i<10;i++)
	{
		countStart += bnStartLast[i];
		countStop += bnStopLast[i];
	}
	if (countStart == 10)
	{
		bnStart = 1;
	}
	else if(countStart == 0)
	{
		bnStart = 0;
	}
	if (countStop == 10)
	{
		bnStop = 1;
	}
	else if(countStop == 0)
	{
		bnStop = 0;
	}
	
	//OUTPUT
	if(mode_active != lock)	//Normal Output if lock is not active
	{
		if(outRelays)		//Set Relays
		{
			PORTD |= (1 << 6);
		}
		else
		{
			PORTD &= ~(1 << 6);
		}

		if(outOffActive)	//Set offDelayActive
		{
			PORTD |= (1 << 7);
		}
		else
		{
			PORTD &= ~(1 << 7);
		}
	}
	else // if Lock is active Clear Outputs
	{
		PORTD &= ~(1 << 6);
		PORTD &= ~(1 << 7);
	}
}

//-------------------------------------------------------------
// Interrupt handler
//-------------------------------------------------------------
//Stop / Lock Interrupt
ISR(INT0_vect) //Interrupt On Falling Edge of INT0
{
	bnStop = debounce(&PIND,2,0);
	if (!bnStop)
	{
		mode_active = lock;
		outRelays=0;
		outOffActive=0;
	}
}


ISR(TIMER0_OVF_vect)
{
	ioHandler();
	if (tmr0Count >= 61)		//Counts ms
	{
		s_count++;
		tmr0Count=0;
	}
	tmr0Count++;
}

//-------------------------------------------------------------
// Other functions
//-------------------------------------------------------------

void initPort(void)
{
	DDRB = 0;
	PORTB = 0xFF;
	DDRD = 0b11000000;
	PORTD = 0b00111111;
}

void initInterrupt(void)
{
	//TMR0 Implementation
	TCCR0A = 0;											// No Compare Operation
	TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00);	// Prescaler select
	TIMSK0 |= (1 << 0);									// Overflow Interrupt enable

	//INT0 Interrupt
	EICRA |= (1 << ISC01) | (1 << ISC00);				// INT0 on Rising Edge
	EIMSK |= (1 << INT0);								// Interrupt enable
	
	//Interrupt Enable
	sei();
}

void initRelaysParameters(void)
{
	time_selected = (PINB & (0b00111100))>>2;		//Read & save selected time value
	mode_selected = PINB & (0b00000011);			//Read & save selected mode
}

void resetTimers(void)
{
	s_count = 0;
	tmr0Count = 0;
}

uint8_t debounce (volatile uint8_t *port, uint8_t pin, uint8_t active)
{
	uint16_t sr = 0x0001;

	while (!((sr == 0xffff) | (sr == 0x0000)))
	{
		sr <<= 1;

		if ( (*port & (1<<pin) ))
		{
			sr |= 0x0001;
		}
		else
		{
			sr &= 0xfffe;
		}
		_delay_us(100);
	}

	if (sr == 0xffff)
	{
		if (active)
		return (1);
		else
		return (0);
	}

	if (sr == 0x0000)
	{
		if (active)
		return (0);
		else
		return (1);
	}
	return(0xff);
}