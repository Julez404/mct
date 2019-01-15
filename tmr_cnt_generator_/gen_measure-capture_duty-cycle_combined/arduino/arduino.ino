#define ARDUINO_IDE
#define SET_DUTY_CYCLE 0.15
// #define PRESCALER_0
// #define PRESCALER_1
// #define PRESCALER_8
// #define PRESCALER_32
// #define PRESCALER_64
 #define PRESCALER_128
// #define PRESCALER_256
// #define PRESCALER_1024

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

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void setup(void);
void initPort(void);
void initTmr(void);

volatile uint8_t tmr1_ovf_count = 0;
volatile double period_us = 0;
volatile double period_high_us = 0;
volatile double period_low_us = 0;


void setup()
{
  #ifdef ARDUINO_IDE
  Serial.begin(2000000);
  Serial.println("Startup...");
  #endif

  initPort();
  initTmr();

  #ifdef ARDUINO_IDE
  Serial.println("Startup Complete");
  #endif
}

int main(void)
{
  setup();
  while (1)
  {
    double period = period_us/1000/1000;
    #ifdef ARDUINO_IDE
    Serial.print("T: ");
    Serial.print(period_us);
    Serial.println(" us");
    Serial.print("F: ");
    Serial.print(1/period);
    Serial.println(" Hz");
    Serial.print("Duty: ");
    Serial.println(period_high_us/period_us);
    Serial.print("T_on: ");
    Serial.print(period_high_us);
    Serial.println(" us");
    Serial.print("T_off: ");
    Serial.print(period_low_us);
    Serial.println(" us");
    Serial.println();
    #endif
    _delay_ms(500);
  }
}

void initPort(void)
{
  DDRB &= ~(1 << 0);  //PB0 Input
  DDRB |= (1 << 3); //PD7 Output
  PORTB = 0;


  #ifdef ARDUINO_IDE
  Serial.println("Ports Configured");
  #endif
}

void initTmr(void)
{
  //Init Timer 1 for Signal Capture
  TCCR1A = 0;
  TCCR1B = (1 << 7) | (1 << 6) | (1 << CS11);
  TCCR1C = 0;
  TIMSK1 = (1 << ICIE1)|(1 << TOIE1);

  //Init Timer 2 for output Signal
  TCCR2A = (1 << WGM21) | (1 << WGM20) | (1 << COM2A1);
  TCCR2B = (PRE_BIT_2 << 2) | (PRE_BIT_1 << 1) | (PRE_BIT_0 << 0);
  OCR2A = (int)(SET_DUTY_CYCLE * 255);
     
  sei();
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

  if(TCCR1B & (1 << ICES1))
  {
    period_low_us = period_count * 0.5; //0.0625 for prescaler=1
    TCCR1B &= ~(1 << 6);
  }
  else
  {
    period_high_us = period_count * 0.5;  //0.0625 for prescaler=1
    TCCR1B |= (1 << 6);
  }

  period_us = period_low_us + period_high_us;
  //period_count * 0.5;//0.0625 for prescaler=1
  timestamp_old = timestamp;
  tmr1_ovf_count=0;
}

ISR(TIMER1_OVF_vect)
{
  tmr1_ovf_count++;
}
