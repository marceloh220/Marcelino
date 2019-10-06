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


#include "timer0.h"

uint8_t timer0_TCNT0;

void (*T0Array[3])(void) = {none,none,none};

Timer0::Timer0() {
	PRR &= ~bv(PRTIMER0);
}

void Timer0::prescale(uint8_t scale) {
	TCCR0B &= ~(bv(CS02)|bv(CS01)|bv(CS00));
	switch(scale) {
		case P_1:
			TCCR0B |= bv(CS00);
			break;
		case P_8:
			TCCR0B |= bv(CS01);
			break;
		case P_64:
			TCCR0B |= bv(CS01)|bv(CS00);
			break;
		case P_256:
			TCCR0B |= bv(CS02);
			break;
		case P_1K:
			TCCR0B |= bv(CS02)|bv(CS00);
			break;
		case FALLING:
			TCCR0B |= bv(CS02)|bv(CS01);
			break;
		case RISING:
			TCCR0B |= bv(CS02)|bv(CS01)|bv(CS00);
			break;
		default:
			break;
	}
}

void Timer0::mode(uint8_t mode, uint8_t top) {
	TCCR0B &= ~bv(WGM02);
	TCCR0A &= ~(bv(WGM01)|bv(WGM00));
	switch(mode) {
		case CORRECT:
			TCCR0A |= bv(WGM00);
			break;
		case CTC:
			TCCR0A |= bv(WGM01);
			break;
		case FAST:
			TCCR0A |= bv(WGM01)|bv(WGM00);
			break;
		default:
			break;
	}
	if(top == COMPA)
		TCCR0B |= bv(WGM02);
}

void Timer0::pinA(uint8_t mode) {
	TCCR0A &= ~(bv(COM0A1)|bv(COM0A0));
	switch(mode) {
		case CHANGE:
			TCCR0A |= bv(COM0A0);
			break;
		case CLEAR:
			TCCR0A |= bv(COM0A0);
			break;
		case SET:
			TCCR0A |= bv(COM0A1)|bv(COM0A0);
			break;
		default:
			break;
	}
}

void Timer0::pinB(uint8_t mode) {
	TCCR0A &= ~(bv(COM0B1)|bv(COM0B0));
	switch(mode) {
		case CHANGE:
			TCCR0A |= bv(COM0B0);
			break;
		case CLEAR:
			TCCR0A |= bv(COM0B0);
			break;
		case SET:
			TCCR0A |= bv(COM0B1)|bv(COM0B0);
			break;
	}
}

void Timer0::pwmA(uint8_t value, uint8_t mode) {
	if(value) {
		if(mode == INVERT)
			TCCR0A |= bv(COM0A1)|bv(COM0A0);
		else {
			TCCR0A &= ~bv(COM0A0);
			TCCR0A |= bv(COM0A1);
		}
	}
	else
		TCCR0A &= ~(bv(COM0A1)|bv(COM0A0));
	OCR0A = value;
}

void Timer0::pwmB(uint8_t value, uint8_t mode) {
	if(value) {
		if(mode==INVERT)
			TCCR0A |= (bv(COM0B1)|bv(COM0B0));
		else {
			TCCR0A &= ~bv(COM0B0);
			TCCR0A |= bv(COM0B1);
		}
	}
	else
		TCCR0A &= ~(bv(COM0B1)|bv(COM0B0));
	OCR0B = value;
}

void Timer0::period(uint32_t micros, uint8_t top) {
	uint8_t scale;
	uint32_t cycles;
	TCCR0B &= ~(bv(CS02)|bv(CS01)|bv(CS00));
	timer0_TCNT0 = 0;
	TCNT0 = 0;
	if(micros == 0)
		return;
	cycles = microsecondsToClockCycles(micros);
	if(cycles < 256)
		scale = bv(CS00);
	else if((cycles /= 8) < 256)
		scale = bv(CS01);
	else if((cycles /= 8) < 256)
		scale = bv(CS01)|bv(CS00);
	else if((cycles /= 8) < 256)
		scale = bv(CS02);
	else if((cycles /= 8) < 256)
		scale = bv(CS02)|bv(CS00);
	else return;
	if(top == COMPA)
		OCR0A = cycles;
	else {
		timer0_TCNT0 = 255 - cycles;
		TCNT0 = timer0_TCNT0;
	}
	TCCR0B |= scale;
}

void Timer0::attach(uint8_t interrupt, void (*funct)(void)) {
	switch(interrupt) {
		case OVF:
			T0Array[0] = funct;
			#ifdef TIMSK0
			TIMSK0|=bv(TOIE0);
			#else
			TIMSK|=bv(TOIE0);
			#endif
			break;
		case COMPA:
			T0Array[1] = funct;
			#ifdef TIMSK0
			TIMSK0|=bv(OCIE0A);
			#else
			TIMSK|=bv(OCIE0A);
			#endif
			break;
		case COMPB:
			T0Array[2] = funct;
			#ifdef TIMSK0
			TIMSK0|=bv(OCIE0B);
			#else
			TIMSK|=bv(OCIE0B);
			#endif
			break;
		default:
			break;
	}
	sei();
}

void Timer0::detach(uint8_t interrupt) {
	switch(interrupt) {
		case OVF:
			T0Array[0] = none;
			#ifdef TIMSK0
			TIMSK0&=~bv(TOIE0);
			#else
			TIMSK&=~bv(TOIE0);
			#endif
			break;
		case COMPA:
			T0Array[1] = none;
			#ifdef TIMSK0
			TIMSK0&=~bv(OCIE0A);
			#else
			TIMSK&=~bv(OCIE0A);
			#endif
			break;
		case COMPB:
			T0Array[2] = none;
			#ifdef TIMSK0
			TIMSK0&=~bv(OCIE0B);
			#else
			TIMSK&=~bv(OCIE0B);
			#endif
			break;
	}
}

ISR(TIMER0_OVF_vect) {
	sregSAVE = SREG;
	TCNT0 = timer0_TCNT0;
	T0Array[0]();
	SREG = sregSAVE;
}

ISR(TIMER0_COMPA_vect) {
	sregSAVE = SREG;
	T0Array[1]();
	SREG = sregSAVE;
}

ISR(TIMER0_COMPB_vect) {
	sregSAVE = SREG;
	T0Array[2]();
	SREG = sregSAVE;
}
