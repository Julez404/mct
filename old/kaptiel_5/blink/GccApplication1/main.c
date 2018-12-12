/*
 * GccApplication1.c
 *
 * Created: 06.11.2018 16:51:18
 * Author : julia
 */ 

 #define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0b00100000;
	PORTB= 0;
    /* Replace with your application code */
    while (1) 
    {
		_delay_ms(1000);
		PORTB ^= (1 << 5);
    }
}

