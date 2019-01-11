#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t tmr2_OV_took_place = 0;

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
	TCCR1B = 0b00000111;
	TCCR1C = 0;

	//TIMER 2 TIMER Windows
	TCCR2A = 0;
	TCCR2B = 0b00000111;
	TIMSK2 = (1 << 0);
	sei();
}

ISR(TIMER2_OVF_vect)
{
  uint16_t temp = TCNT1;
  if(tmr2_OV_took_place >= 11)
  {
	  TCNT1 = 0;
	  // ARDUINO IDE Specific
	  /*	
	  Serial.print("Frequenz: ");
	  double freq = temp/0.19661;
	  Serial.print(freq);
	  Serial.println(" Hz");
	  Serial.print("Periodendauer: ");
	  Serial.print(1000/freq);
	  Serial.println(" ms\n");
	 */ 
	  tmr2_OV_took_place = 0;
  }
  else
  {
	  tmr2_OV_took_place++;
  }
}