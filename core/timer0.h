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


#ifndef TIMER0_H
#define TIMER0_H

#include "defines.h"

extern uint8_t timer0_TCNT0;

class Timer0 {

public:

	Timer0();
	
	//configs of timer
	void prescale(uint8_t scale);
	void configure(uint8_t mode, uint8_t top = TIMER);
	void pinA(uint8_t mode);
	void pinB(uint8_t mode);
	
	//register of timer
	inline void timer(uint8_t value) { TCNT0 = value; }
	inline void compA(uint8_t value) { OCR0A = value; }
	inline void compB(uint8_t value) { OCR0B = value; }
	inline uint8_t timer() { return TCNT0; }
	inline uint8_t compA() { return OCR0A; }
	inline uint8_t compB() { return OCR0B; }
	
	//pwm generator wave
	void pwmA(uint8_t value, uint8_t mode = NINVERT);
	void pwmB(uint8_t value, uint8_t mode = NINVERT);
	
	//control generator wave
	void period(uint32_t micros, uint8_t top = TIMER);
	
	//interrupts of timer
	void attach(uint8_t interrupt, void (*funct)(void));
	void detach(uint8_t interrupt);

	//test interrupts attached
	inline uint8_t attach() {
		#ifdef TIMSK0
		return TIMSK0;
		#else
		return TIMSK;
		#endif
	}
	
};

#endif
