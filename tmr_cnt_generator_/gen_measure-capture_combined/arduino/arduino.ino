//Prescaler for Outout frequency
// #define PRESCALER_0
// #define PRESCALER_1
// #define PRESCALER_8
// #define PRESCALER_32
// #define PRESCALER_64
// #define PRESCALER_128
// #define PRESCALER_256
 #define PRESCALER_1024

#ifndef SCALES_H_
#define SCALES_H_

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

#endif /* SCALES_H_ */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void initPort(void);
void initTmr(void);


volatile uint8_t tmr1_ovf_count = 0;
volatile double period_us = 0;


void setup() {
 Serial.begin(115200);
 Serial.println("Startup...");

  initPort();
  initTmr();
 
 Serial.println("Startup Complete");
}

int main(void)
{
  setup();
  while (1)
  {
    double period = period_us/1000/1000;
    Serial.print("T: ");
    Serial.print(period_us);
    Serial.println(" us");
    Serial.print("F: ");
    Serial.print(1/period);
    Serial.println(" Hz");
    Serial.println();
    _delay_ms(250);
  }
}

void initPort(void)
{
  DDRB &= ~(1 << 0);  //PB0 Input
  PORTB = 0;
  DDRD |= (1 << 7); //PD7 Output
  PORTD = 0;
  Serial.println("Ports Configured");
}

void initTmr(void)
{
  //Init Timer 1 for Signal Capture
  TCCR1A = 0;
  TCCR1B = (1 << 7) | (1 << 6) | (1 << CS10);
  TCCR1C = 0;
  TIMSK1 = (1<<ICIE1) | (1 << TOIE1);
  Serial.println("Timer1 initialized");
  
  //Init Timer 2 for output Signal
  TCCR2A = 0;
  TCCR2B = (PRE_BIT_2 << 2) |(PRE_BIT_1 << 1)|(PRE_BIT_0 << 0);
  TIMSK2 |= (1 << 0);
  Serial.println("Timer2 initialized");
  sei();
  Serial.println("Interrupts activ!");
}

ISR(TIMER2_OVF_vect)
{
  PORTD ^= (1 << 7);
}


ISR(TIMER1_CAPT_vect)
{
  
  uint16_t timestamp = (ICR1L) | (ICR1H << 8);
  uint32_t period_count = 0;
  static uint16_t timestamp_old;

  if(tmr1_ovf_count == 0)
  {
    period_count = timestamp-timestamp_old;
  }
  else
  {
    period_count = timestamp;
    
    while (tmr1_ovf_count != 1)
    {
      period_count += 65536;
      tmr1_ovf_count--;
    }
    period_count+= (65536-timestamp_old);
  }

  period_us = period_count * 0.5;//0.0625 for prescaler=1
  timestamp_old = timestamp;
  tmr1_ovf_count=0;
}

ISR(TIMER1_OVF_vect)
{
  tmr1_ovf_count++;
}
