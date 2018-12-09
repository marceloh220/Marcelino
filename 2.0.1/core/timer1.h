 /*
  Copyright (c) 2017 Marcelo Henrique Moraes

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3.0 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

 */


#ifndef TIMER1_H
#define TIMER1_H

#include "defines.h"

extern uint16_t timer1_TCNT1;

class Timer1 {

public:

	Timer1();
	
	//configs of timer
	#ifndef ATTINY
	void configure(uint8_t mode, uint8_t top);
	#endif
	void configure(uint8_t mode);
	void prescale(uint8_t scale);
	void pinA(uint8_t mode);
	void pinB(uint8_t mode);
	
	//register of timer
	#ifndef ATTINY
	
	inline void timer(uint16_t value) { TCNT1 = value; }
	inline void compA(uint16_t value) { OCR1A = value; }
	inline void compB(uint16_t value) { OCR1B = value; }
	inline void compC(uint16_t value) { ICR1 = value; }
	inline void capture(uint16_t value) { ICR1 = value; }

	inline uint16_t timer() { return TCNT1; }
	inline uint16_t compA() { return OCR1A; }
	inline uint16_t compB() { return OCR1B; }
	inline uint16_t compC() { return ICR1; }
	inline uint16_t capture() { return ICR1; }
	inline uint16_t period() { return timer1_TCNT1; }
	
	#else
	
	inline void timer(uint8_t value) { TCNT1 = value; }
	inline void compA(uint8_t value) { OCR1A = value; }
	inline void compB(uint8_t value) { OCR1B = value; }
	inline void compC(uint8_t value) { OCR1C = value; }

	inline uint8_t timer() { return TCNT1; }
	inline uint8_t compA() { return OCR1A; }
	inline uint8_t compB() { return OCR1B; }
	inline uint8_t compC() { return OCR1C; }

	#endif
	
	//pwm generator wave
	#ifndef ATTINY
	void pwmA(uint16_t value, uint8_t mode = NINVERT);
	void pwmB(uint16_t value, uint8_t mode = NINVERT);
	#endif
	
	//control generator wave
	void period(uint32_t micros, uint8_t top = TIMER);
	
	//interrupts of timer
	void attach(uint8_t interrupt, void (*funct)(void));
	void attach(uint8_t interrupt, uint8_t mode, void (*funct)(void));
	void detach(uint8_t interrupt);
	
	//test states
	#ifndef ATTINY
	inline uint8_t rising() { return (TCCR1B & (1<<ICES1)); }
	inline uint8_t falling() { return !(TCCR1B & (1<<ICES1)); }
	inline uint8_t attach() { return TIMSK1; }
	#else
	inline uint8_t attach() { return TIMSK; }
	#endif
		
};

#endif
