#define IN1 1
#define IN2 2
#define IN3 3
#define OUTPUT1 4
#define OUTPUT2 5

#include <avr/io.h>

void initMCU(void);

void input(void);
void convert(void);
void output(void);

void togglePin(uint8_t _pin);

uint8_t in1 = 0;
uint8_t in2 = 0;
uint8_t in3 = 0;
uint8_t out1 = 0;
uint8_t out2 = 0;



int main(void)
{
	initMCU();


	
	while (1)
	{
		input();
		convert();
		output();

	}
}




void initMCU(void)
{
	DDRD = 0;
	PORTD= 0;
	DDRD = 0b00110000;
}

void input()
{
	if (PIND & (1 << IN1))
	{
		in1= 1;
	}
	else
	{
		in1=0;
	}

	if (PIND & (1 << IN2))
	{
		in2= 1;
	}
	else
	{
		in2=0;
	}

	if (PIND & (1 << IN3))
	{
		in3= 1;
	}
	else
	{
		in3=0;
	}

}

void convert(void)
{
out1 = (in1 != in2) != in3;
out2 = (in1 && in2) || ((in1 || in2) && in3);
}

void output(void)
{	

	if((PIND & (1 << OUTPUT1)) != out1)
	{
		togglePin(OUTPUT1);
	}
	if((PIND & (1 << OUTPUT2)) != out2)
	{
		togglePin(OUTPUT2);
	}
	
}


void togglePin(uint8_t _pin)
{
	if (PORTD & (1 << _pin))
	{
		PORTD &= ~(1 << _pin);
	}
	else
	{
		PORTD |= (1 << _pin);
	}
}