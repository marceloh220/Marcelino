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


#include "timer2.h"

#ifndef NOTIMER2

uint8_t timer2_TCNT2;

void (*T2Array[3])(void) = {none,none,none};

Timer2::Timer2() {
	PRR &= ~(1<<PRTIMER2);
	def_prescale = 64;
	TCCR2B = 4;
}

void Timer2::prescale(uint16_t scale) {
	def_prescale = scale;
	TCCR2B &= ~7;
	if(!scale)
		return;
	if(scale==1)
		scale=1;
	else if(scale==8)
		scale=2;
	else if(scale==32)
		scale=3;
	else if(scale==64)
		scale=4;
	else if(scale==128)
		scale=5;
	else if(scale==256)
		scale=6;
	else if(scale==1024)
		scale=7;
	cli();
	while(update());
	TCCR2B |= scale;
	sei();
}

void Timer2::config(uint8_t mode, uint8_t top) {
	def_top = top;
	def_mode = mode;
	cli();
	while(update());
	TCCR2B &= ~(1<<WGM22);
	TCCR2A &= ~3;
	TCCR2A |= (mode&3);
	if(top)
		TCCR2B |= (1<<WGM22);
	sei();
}

void Timer2::pinA(uint8_t mode) {
	cli();
	while(update());
	TCCR2A &= ~(3<<COM2A0);
	if(mode == CHANGE)
		TCCR2A |= (1<<COM2A0);
	else if(mode == CLEAR)
		TCCR2A |= (2<<COM2A0);
	else if(mode == SET)
		TCCR2A |= (3<<COM2A0);
	sei();
}

void Timer2::pinB(uint8_t mode) {
	cli();
	while(update());
	TCCR2A &= ~(3<<COM2B0);
	if(mode == CHANGE)
		TCCR2A |= (1<<COM2B0);
	else if(mode == CLEAR)
		TCCR2A |= (2<<COM2B0);
	else if(mode == SET)
		TCCR2A |= (3<<COM2B0);
	sei();
}

void Timer2::pwmA(uint8_t value) {
	cli();
	while(update());
	if(value) {
		TCCR2A &= ~(1<<COM2A0);
		TCCR2A |= (1<<COM2A1);
	}
	else
		TCCR2A &= ~(3<<COM2A0);		
	OCR2A = value;
	sei();
}

void Timer2::pwmA(uint8_t value, uint8_t mode) {
	cli();
	while(update());
	if(value) {
		if(mode)
			TCCR2A |= (3<<COM2A0);
		else {
			TCCR2A &= ~(1<<COM2A0);
			TCCR2A |= (1<<COM2A1);
		}
	}
	else
		TCCR2A &= ~(3<<COM1A0);
	OCR2A = value;
	sei();
}

void Timer2::pwmB(uint8_t value) {
	cli();
	while(update());
	if(value) {
		TCCR2A &= ~(1<<COM2B0);
		TCCR2A |= (1<<COM2B1);
	}
	else 
		TCCR2A &= ~(3<<COM2B0);
	OCR2B = value;
	sei();
}


void Timer2::pwmB(uint8_t value, uint8_t mode) {
	cli();
	while(update());
	if(value) {
		if(mode)
			TCCR2A |= (3<<COM2B0);
		else {
			TCCR2A &= ~(1<<COM2B0);
			TCCR2A |= (1<<COM2B1);
		}
	}
	else
		TCCR2A &= ~(3<<COM2B0);
	OCR2B = value;
	sei();
}

void Timer2::frequency(uint32_t freq) {
	
	uint8_t factor;
	
	if(def_mode == FAST)
		factor = 1;
	else
		factor = 2;
	cli();
	while(update());
	if(def_top == COMPA || def_mode == CTC)
		OCR2A = F_CPU / (factor * def_prescale * freq) - 1;
	sei();
}

void Timer2::period(uint32_t micros) {
  uint8_t scale;
  uint32_t cycles = microsecondsToClockCycles(micros);
  if(!micros) {
	timer2_TCNT2 = 0;
	return;
  }
  if(cycles < 256)
	scale = 1;
  else if((cycles / 8) < 256) {
	scale = 2;
	cycles /= 8;
  }
  else if((cycles / 32) < 256) {
	scale = 3;
	cycles /= 32;
  }
  else if((cycles / 64) < 256) {
	scale = 4;
	cycles /= 64;
  }
  else if((cycles / 128) < 256) {
	scale = 5;
	cycles /= 128;
  }
  else if((cycles / 256) < 256) {
	scale = 6;
	cycles /= 256;
  }
  else {
	cycles /= 1024;
	scale = 7;
  }
  cli();
  while(update());
  TCCR2B &= ~7;
  timer2_TCNT2 = 255 - cycles;
  TCCR2B |= scale;
  sei();
}

void Timer2::attach(uint8_t interrupt, void (*funct)(void)) {
	switch(interrupt) {
		case OVF:
			T2Array[0] = funct;
			TIMSK2 |= (1<<TOIE2);
			break;
		case COMPA:
			T2Array[1] = funct;
			TIMSK2 |= (1<<OCIE2A);
			break;
		case COMPB:
			T2Array[2] = funct;
			TIMSK2 |= (1<<OCIE2B);
			break;
		default:
			break;
	}
	sei();
}

void Timer2::attach(uint8_t interrupt, uint8_t mode, void (*funct)(void)) {
	switch(interrupt) {
		case OVF:
			T2Array[0] = funct;
			TIMSK2 |= (1<<TOIE2);
			break;
		case COMPA:
			T2Array[1] = funct;
			TIMSK2 |= (1<<OCIE2A);
			break;
		case COMPB:
			T2Array[2] = funct;
			TIMSK2 |= (1<<OCIE2B);
			break;
		default:
			break;
	}
	if(mode == ASYNCHRON)
		ASSR|=(1<<AS2);
	sei();
}

void Timer2::detach(uint8_t interrupt) {
	switch(interrupt) {
		case OVF:
			T2Array[0] = none;
			TIMSK2 &= ~(1<<TOIE2);
			break;
		case COMPA:
			T2Array[1] = none;
			TIMSK2 &= ~(1<<OCIE2A);
			break;
		case COMPB:
			T2Array[2] = none;
			TIMSK2 &= ~(1<<OCIE2B);
			break;
		default:
			break;
	}
	if(!TIMSK2)
		ASSR&=~(1<<AS2);
}

ISR(TIMER2_OVF_vect) {
	sregSAVE = SREG;
	TCNT2 = timer2_TCNT2;
	T2Array[0]();
	SREG = sregSAVE;
}

ISR(TIMER2_COMPA_vect) {
	sregSAVE = SREG;
	T2Array[1]();
	SREG = sregSAVE;
}

ISR(TIMER2_COMPB_vect) {
	sregSAVE = SREG;
	T2Array[2]();
	SREG = sregSAVE;
}

#endif
