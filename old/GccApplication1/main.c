 /*
 First Application

 Turning Lights Controller

 Autor: Yoshi
 
 */
 
 #define 	F_CPU   16000000UL

 #define	SWITCH_TIME	1000	//Switch time in ms
 #define	TRAFFIC_GREEN_TIME	5000
 #define	TRAFFIC_RED_TIME	5000

 #define	AMPEL	_SFR_IO8(0x0B)
 #define	PEDESTRIAN_GREEN 5
 #define	PEDESTRIAN_RED 4

 #define	TASTER	3

 #define	TRAFFIC_RED		2
 #define	TRAFFIC_YELLOW	1
 #define	TRAFFIC_GREEN	0


 #include <avr/io.h>
 #include <util/delay.h>
 #include "ampel.h"



 void switchToTRAFFIC_GREEN(void);
 void switchToTRAFFIC_RED(void);
 void switchOff(uint8_t _color);
 void switchOn(uint8_t _color);
 void initAmpel(void);


 int main(void)
 {
	 DDRB = 0b00000000;
	 DDRD = 0b11110111;
	 PORTB = 0;
	 PORTD = 0;
	 initAmpel();

	 while (1)
	 {
		 
		 if(PIND & (1 << TASTER))
		 {
			 switchToTRAFFIC_RED();
			 _delay_ms(TRAFFIC_GREEN_TIME);
			 switchToTRAFFIC_GREEN();
			 _delay_ms(TRAFFIC_GREEN_TIME);
			 
		 }
		 
	 }
 }


 void switchToTRAFFIC_GREEN(void)
 {
	 switchOn(TRAFFIC_YELLOW);
	 _delay_ms(SWITCH_TIME);
	 switchOff(TRAFFIC_YELLOW);
	 switchOff(TRAFFIC_RED);
	 switchOn(TRAFFIC_GREEN);
 }

 void switchToTRAFFIC_RED(void)
 {
	 switchOff(TRAFFIC_GREEN);
	 switchOn(TRAFFIC_YELLOW);
	 _delay_ms(SWITCH_TIME);
	 switchOff(TRAFFIC_YELLOW);
	 switchOn(TRAFFIC_RED);
 }

 void  switchOff(uint8_t _color)
 {
	 AMPEL &= ~(0 << _color);
 }
 void  switchOn(uint8_t _color)
 {
	 AMPEL |= (1 << _color);
 }

 void initAmpel(void)
 {
	 switchOff(TRAFFIC_YELLOW);
	 switchOff(TRAFFIC_RED);
	 switchOn(TRAFFIC_GREEN);
	 switchOff(PEDESTRIAN_RED);
	 switchOn(PEDESTRIAN_GREEN);
 }

