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


#ifndef TIMER2_H
#define TIMER2_H

#include "defines.h"

#ifndef NOTIMER2

extern uint8_t timer2_TCNT2;

class Timer2 {
	
private:

	inline uint8_t update() { return ASSR&0x3F; }

public:

	Timer2();
		
	//configs of timer
	void prescale(uint8_t scale);
	void mode(uint8_t mode, uint8_t top = TIMER);
	void pinA(uint8_t mode);
	void pinB(uint8_t mode);
	
	//register of timer
	inline void timer(uint8_t value) { TCNT2 = value; }
	inline void compA(uint8_t value) { OCR2A = value; }
	inline void compB(uint8_t value) { OCR2B = value; }
	inline uint8_t timer() { return TCNT2; }
	inline uint8_t compA() { return OCR2A; }
	inline uint8_t compB() { return OCR2B; }
	inline uint8_t period() { return timer2_TCNT2; }
	
	//pwm generator wave
	void pwmA(uint8_t value, uint8_t mode = NINVERT);
	void pwmB(uint8_t value, uint8_t mode = NINVERT);
	
	//control generator wave
	void period(uint32_t micros, uint8_t top = TIMER);
	
	//interrupts of timer
	void attach(uint8_t interrupt, void (*funct)(void));
	void attach(uint8_t interrupt, uint8_t mode, void (*funct)(void));
	void detach(uint8_t interrupt);

	//test interrupts attached
	inline uint8_t attach() { return TIMSK2; }
	
};

#endif

#endif
