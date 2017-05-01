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


#include "timer1.h"

uint16_t timer1_TCNT1;

VoidFuncPtr T1Array[4] = {none,none,none,none};

Timer1::Timer1() {
	PRR &= ~(1<<PRTIMER1);
	TCCR1B = 3;
	def_prescale = 64;
}

void Timer1::config(uint8_t mode, uint8_t mode2, uint8_t top) {
	TCCR1A &= ~3;
	TCCR1B &= ~(3<<WGM12);
	def_mode2 = mode2;
	switch(mode) {
		case CORRECT:
			TCCR1A |= 1;
			break;
		case CORRECT9:
			TCCR1A |= 2;
			break;
		case CORRECT10:
			TCCR1A |= 3;
			break;
		case CTC:
			TCCR1B |= (1<<WGM12);
		case FAST:
			TCCR1A |= 1;
			TCCR1B |= (1<<WGM12);
			break;
		case FAST9:
			TCCR1A |= 2;
			TCCR1B |= (1<<WGM12);
			break;
		case FAST10:
			TCCR1A |= 3;
			TCCR1B |= (1<<WGM12);
			break;
		case VARIABLE:
			variable(mode2, top);			
			break;
	}
}

void Timer1::variable(uint8_t mode, uint8_t top) {
	if(mode == FAST) {
		if(top) {
			TCCR1B |= (3<<WGM12);
			TCCR1A |= (3<<WGM10);
			def_top = COMPA;
		}
		else {
			TCCR1B |= (3<<WGM12);
			TCCR1A |= (2<<WGM10);
			def_top = CAPT;
		}
	}
	else {
		if(top == COMPA) {
			TCCR1B |= (2<<WGM12);
			TCCR1A |= (1<<WGM10);
			def_top = COMPA;
		}
		else {
			TCCR1B |= (2<<WGM12);
			def_top = CAPT;
		}
	}
}

void Timer1::prescale(uint16_t scale) {
	TCCR1B &= ~7;
	def_prescale = scale;
	if(!scale)
		return;
	if(scale==1)
		scale=1;
	else if(scale==8)
		scale=2;
	else if(scale==64)
		scale=3;
	else if(scale==256)
		scale=4;
	else if(scale==1024)
		scale=5;
	else if(scale==FALLING)
		scale=6;
	else if(scale==RISING)
		scale=7;
	TCCR1B |= scale;
}

void Timer1::pinA(uint8_t mode) {
	TCCR1A &= ~(3<<COM1A0);
	if(mode == CHANGE)
		TCCR1A |= (1<<COM1A0);
	else if(mode == CLEAR)
		TCCR1A |= (2<<COM1A0);
	else if(mode == SET)
		TCCR1A |= (3<<COM1A0);
}

void Timer1::pinB(uint8_t mode) {
	TCCR1A &= ~(3<<COM1B0);
	if(mode == CHANGE)
		TCCR1A |= (1<<COM1B0);
	else if(mode == CLEAR)
		TCCR1A |= (2<<COM1B0);
	else if(mode == SET)
		TCCR1A |= (3<<COM1B0);
}

void Timer1::pwmA(uint16_t value) {
	if(value) {
		TCCR1A &= ~(1<<COM1A0);
		TCCR1A |= (1<<COM1A1);
	}
	else
		TCCR1A &= ~(3<<COM1A0);		
	OCR1A = value;
}

void Timer1::pwmA(uint16_t value, uint8_t mode) {
	if(value) {
		if(mode)
			TCCR1A |= (3<<COM1A0);
		else {
			TCCR1A &= ~(1<<COM1A0);
			TCCR1A |= (1<<COM1A1);
		}
	}
	else
		TCCR1A &= ~(3<<COM1A0);
	OCR1A = value;
}

void Timer1::pwmB(uint16_t value) {
	if(value) {
		TCCR1A &= ~(1<<COM1B0);
		TCCR1A |= (1<<COM1B1);
	}
	else 
		TCCR1A &= ~(3<<COM1B0);
	OCR1B = value;
}

void Timer1::pwmB(uint16_t value, uint8_t mode) {
	if(value) {
		if(mode)
			TCCR1A |= (3<<COM1B0);
		else {
			TCCR1A &= ~(1<<COM1B0);
			TCCR1A |= (1<<COM1B1);
		}
	}
	else
		TCCR1A &= ~(3<<COM1B0);
	OCR1B = value;
}

void Timer1::frequency(uint32_t freq) {
	
	uint8_t factor;
	
	if(def_mode2 == FAST)
		factor = 1;
	else
		factor = 2;
	
	if(def_top == COMPA)
		OCR1A = F_CPU / (factor * def_prescale * freq) - 1;
	else if(def_top == CAPT)
		ICR1 = F_CPU / (factor * def_prescale * freq) - 1;
}

void Timer1::period(uint32_t micros) {
  uint8_t scale;
  uint32_t cycles = microsecondsToClockCycles(micros);
  if(!micros) {
	timer1_TCNT1 = 0;
	return;
  }
  if(cycles < 65536)
	scale = 1;
  else if((cycles /= 8) < 65536)
	scale = 2;
  else if((cycles /= 8) < 65536)
	scale = 3;
  else if((cycles /= 8) < 65536)
	scale = 4;
  else {
	cycles /= 8;
	scale = 5;
  }
  TCCR1B &= ~7;
  timer1_TCNT1 = 65535 - cycles;
  TCCR1B |= scale;
}

void Timer1::attach(uint8_t interrupt, VoidFuncPtr funct) {
	if(interrupt == CAPT)
		return;
	T1Array[interrupt] = funct;
	TIMSK1 |= (1<<interrupt);
	sei();
}

void Timer1::attach(uint8_t interrupt, uint8_t mode, VoidFuncPtr funct) {
	if(interrupt != CAPT)
		return;
	TCCR1B |= (1<<ICNC1);
	if(mode == FALLING)
		TCCR1B &= ~(1<<ICES1);
	else if(mode == RISING)
		TCCR1B |= (1<<ICES1);
	TIMSK1 |= (1<<ICIE1);
	T1Array[CAPT] = funct;
	sei();
}

void Timer1::detach(uint8_t interrupt) {
	T1Array[interrupt] = none;
	if(interrupt == CAPT)
		interrupt=ICIE1;
	TIMSK1 &= ~(1<<interrupt);
}

uint8_t Timer1::attached(uint8_t interrupt) {
	if(interrupt == CAPT)
		interrupt=ICIE1;
	return (TIMSK1&(1<<interrupt));
}

ISR(TIMER1_OVF_vect) {
	sregSAVE = SREG;
	TCNT1 = timer1_TCNT1;
	T1Array[0]();
	SREG = sregSAVE;
}

ISR(TIMER1_COMPA_vect) {
	sregSAVE = SREG;
	T1Array[1]();
	SREG = sregSAVE;
}

ISR(TIMER1_COMPB_vect) {
	sregSAVE = SREG;
	T1Array[2]();
	SREG = sregSAVE;
}

ISR(TIMER1_CAPT_vect) {
	sregSAVE = SREG;
	T1Array[3]();
	SREG = sregSAVE;
}
