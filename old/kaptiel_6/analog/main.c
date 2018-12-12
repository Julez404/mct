#define ANALOG_RES 0.00488

#include <avr/io.h>
#include <avr/interrupt.h>

void initPorts(void);
void initADC(void);
void initInterrupt(void);

float x=0;
float y=0;
uint16_t adc_read=0;

int main(void)
{
	//INIT
	initPorts();
	initInterrupt();
	initADC();

	//MAIN-LOOP
	while (1)
	{
		//Output to LEDs, depending on Input Voltage
		if (x > 1.0)
		{
			PORTB |= (1<<0);
		}
		else
		{
			PORTB &=~(1<<0);
		}
		if (x < -1.0)
		{
			PORTB |= (1<<1);
		}
		else
		{
			PORTB &= ~(1<<1);
		}
		if (y>1.0)
		{
			PORTB |= (1<<2);
		}
		else
		{
			PORTB &=~(1<<2);
		}
		if (y < -1.0)
		{
			PORTB |= (1<<3);
		}
		else
		{
			PORTB &=~(1<<3);
		}
	}
}

void initPorts(void)
{
	DDRB = 0x0F;
	PORTB = 0;
	DDRC = 0x00;
	PORTC = 0;
	DIDR0 |= (1 << 0) | (1 << 1);	//Disable Digital-Inputs on Analag Pins
}

void initADC()
{
	ADMUX = (1 << REFS0);
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1)| ( 1 << ADPS0);
	ADCSRA |= (1 << ADSC);
}

void initInterrupt(void)
{
	sei();
}

ISR(ADC_vect)
{
	static uint8_t wasX = 1;

	switch (wasX)
	{
		//Read x-Value
		case 1:
		adc_read = ADC;							//Read integer analog value
		x = adc_read * (float)ANALOG_RES;		//Convert integer to voltage
		x -= 2.5;
		ADMUX |= (1 << MUX0);					//Switch analog input to y
		ADCSRA |= (1 << ADSC);					//Trigger next conversion
		wasX = 0;
		break;

		//Read y-Value
		case 0:
		adc_read = ADC;
		y = adc_read * (float)ANALOG_RES;
		y -= 2.5;
		ADMUX &= ~(1 << MUX0);					//Switch analog input to x
		ADCSRA |= (1 << ADSC);					//Trigger next conversion
		wasX =1;
		break;
	}
}
