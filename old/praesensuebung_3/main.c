/*
* praesensuebung_3.c
*
* Created: 30.10.2018 17:08:09
* Author : julian
*/
#define F_CPU 16000000
#define T1 PIND4
#define T2 PIND5
#define T3 PIND6
#define T4 PIND7
#define INPUT PIND
#define LED PORTD3


#include <avr/io.h>
#include <util/delay.h>



void	initMCU(void);
uint8_t readDigital(uint8_t _register, uint8_t _pin);
void	waitFallingPegel(uint8_t _register, uint8_t _pin);

uint8_t level = 0;
uint8_t next_level = 1;

int main(void)
{
	initMCU();

	while (1)
	{
		switch (level)
		{
			case 0:
			_delay_ms(500);
			if((PORTD & 0b11110000) == 0)
			{
				level = next_level;
				_delay_ms(500);
			}
			break;

			case 1:
			if (readDigital(INPUT,T1))
			{
				next_level = 2;
				level = 0;
			}
			if (readDigital(INPUT,T2))
			{
				next_level = 1;
				level = 0;
			}
			if (readDigital(INPUT,T3))
			{
				next_level = 1;
				level = 0;
			}
			if (readDigital(INPUT,T4))
			{
				next_level = 1;
				level = 0;
			}
			break;

			case 2:
			if (readDigital(INPUT,T1))
			{
				next_level = 1;
				level = 0;
			}
			if (readDigital(INPUT,T2))
			{
				next_level = 3;
				level = 0;
			}
			if (readDigital(INPUT,T3))
			{
				next_level = 1;
				level = 0;
			}
			if (readDigital(INPUT,T4))
			{
				next_level = 1;
				level = 0;
			}
			break;

			case 3:
			if (readDigital(INPUT,T1))
			{
				next_level = 1;
				level = 0;
				break;
			}
			if (readDigital(INPUT,T2))
			{
				next_level = 1;
				level = 0;
				break;
			}
			if (readDigital(INPUT,T3))
			{
				next_level = 4;
				level = 0;
				break;
			}
			if (readDigital(INPUT,T4))
			{
				next_level = 1;
				level = 0;
				break;
			}

			break;

			case 4:
			if (readDigital(INPUT,T1))
			{
				next_level = 1;
				level = 0;
			}
			if (readDigital(INPUT,T2))
			{
				next_level = 1;
				level = 0;
			}
			if (readDigital(INPUT,T3))
			{
				next_level = 1;
				level = 0;
			}
			if (readDigital(INPUT,T4))
			{
				next_level = 5;
				level = 0;
			}
			break;

			case 5:
			PORTD |= (1 << LED);
			break;

			default:
			break;
		}
	}
	return 0;
}


void initMCU(void)
{
	DDRB = 0b00000000;
	PORTB = 0;
	DDRD = 0b00001000;
	PORTD = 0;
}

uint8_t readDigital(uint8_t _register, uint8_t _pin)
{
	return (_register & (1 << _pin));
}

