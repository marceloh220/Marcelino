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
	PRR &= ~bv(PRTIMER2);
}

void Timer2::prescale(uint8_t scale) {
	if(!scale)
		return;
	switch(scale) {
		case P_1:
			scale = bv(CS20);	//1
			break;
		case P_8:
			scale = bv(CS21);	//2
			break;
		case P_32:
			scale = bv(CS21)|bv(CS20);	//3
			break;
		case P_64:
			scale = bv(CS22);	//4
			break;
		case P_128:
			scale = bv(CS22)|bv(CS20);	//5
			break;
		case P_256:
			scale = bv(CS22)|bv(CS21);	//6
			break;
		case P_1K:
			scale = bv(CS22)|bv(CS21)|bv(CS20);	//7
			break;
		default:
			break;
	}
	cli();
	while(update());
	TCCR2B &= ~(bv(CS22)|bv(CS21)|bv(CS20));
	TCCR2B |= scale;
	sei();
}

void Timer2::mode(uint8_t mode, uint8_t top) {
	cli();
	while(update());
	TCCR2B &= ~bv(WGM22);
	TCCR2A &= ~(bv(WGM21)|bv(WGM20));
	switch(mode) {
		case CORRECT:
			TCCR2A |= bv(WGM20);
			break;
		case CTC:
			TCCR2A |= bv(WGM21);
			break;
		case FAST:
			TCCR2A |= bv(WGM21)|bv(WGM20);
			break;
		default:
			break;
	}
	if(top == COMPA)
		TCCR2B |= bv(WGM22);
	sei();
}

void Timer2::pinA(uint8_t mode) {
	cli();
	while(update());
	TCCR2A &= ~(bv(COM2A1)|bv(COM2A0));
	switch(mode) {
		case CHANGE:
			TCCR2A |= bv(COM2A0);
			break;
		case CLEAR:
			TCCR2A |= bv(COM2A1);
			break;
		case SET:
			TCCR2A |= bv(COM2A1)|bv(COM2A0);
			break;
	}
	sei();
}

void Timer2::pinB(uint8_t mode) {
	cli();
	while(update());
	TCCR2A &= ~(bv(COM2B1)|bv(COM2B0));
	switch(mode) {
		case CHANGE:
			TCCR2A |= bv(COM2B0);
			break;
		case CLEAR:
			TCCR2A |= bv(COM2B1);
			break;
		case SET:
			TCCR2A |= bv(COM2B1)|bv(COM2B0);
			break;
	}
	sei();
}

void Timer2::pwmA(uint8_t value, uint8_t mode) {
	cli();
	while(update());
	if(value) {
		if(mode)
			TCCR2A |= bv(COM2A1)|bv(COM2A0);
		else {
			TCCR2A &= ~bv(COM2A0);
			TCCR2A |= bv(COM2A1);
		}
	}
	else
		TCCR2A &= ~(bv(COM2A1)|bv(COM2A0));
	OCR2A = value;
	sei();
}

void Timer2::pwmB(uint8_t value, uint8_t mode) {
	cli();
	while(update());
	if(value) {
		if(mode)
			TCCR2A |= bv(COM2B1)|bv(COM2B0);
		else {
			TCCR2A &= ~bv(COM2B0);
			TCCR2A |= bv(COM2B1);
		}
	}
	else
		TCCR2A &= ~(bv(COM2B1)|bv(COM2B0));
	OCR2B = value;
	sei();
}

void Timer2::period(uint32_t micros, uint8_t top) {
	uint8_t scale;
	uint32_t cycles;
	cli();
	while(update());
	TCCR2B &= ~(bv(CS22)|bv(CS21)|bv(CS20));
	timer2_TCNT2 = 0;
	TCNT2 = 0;
	sei();
	if(micros == 0)
		return;
	cycles = microsecondsToClockCycles(micros);
	if(cycles < 256)
		scale = bv(CS20);
	else if((cycles /= 8) < 256)
		scale = bv(CS21);
	else if((cycles /= 4) < 256)
		scale = bv(CS21)|bv(CS20);
	else if((cycles /= 2) < 256)
		scale = bv(CS22);
	else if((cycles /= 2) < 256)
		scale = bv(CS22)|bv(CS20);
	else if((cycles /= 2) < 256)
		scale = bv(CS22)|bv(CS21);
	else if((cycles /=4) < 256)
		scale = bv(CS22)|bv(CS21)|bv(CS20);
	cli();
	while(update());
	if(top == COMPA)
		OCR2A = cycles;
	else {
		timer2_TCNT2 = 255 - cycles;
		TCNT2 = timer2_TCNT2;
	}
	TCCR2B |= scale;
	sei();
}

void Timer2::attach(uint8_t interrupt, void (*funct)(void)) {
	cli();
	while(update());
	switch(interrupt) {
		case OVF:
			T2Array[0] = funct;
			TIMSK2 |= bv(TOIE2);
			break;
		case COMPA:
			T2Array[1] = funct;
			TIMSK2 |= bv(OCIE2A);
			break;
		case COMPB:
			T2Array[2] = funct;
			TIMSK2 |= bv(OCIE2B);
			break;
		default:
			break;
	}
	sei();
}

void Timer2::attach(uint8_t interrupt, uint8_t mode, void (*funct)(void)) {
	cli();
	while(update());
	switch(interrupt) {
		case OVF:
			T2Array[0] = funct;
			TIMSK2 |= bv(TOIE2);
			break;
		case COMPA:
			T2Array[1] = funct;
			TIMSK2 |= bv(OCIE2A);
			break;
		case COMPB:
			T2Array[2] = funct;
			TIMSK2 |= bv(OCIE2B);
			break;
		default:
			break;
	}
	if(mode == ASYNCHRON)
		ASSR|=bv(AS2);
	sei();
}

void Timer2::detach(uint8_t interrupt) {
	cli();
	while(update());
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
	sei();
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
