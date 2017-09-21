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

void (*T1Array[4])(void) = {none,none,none,none};

Timer1::Timer1() {
	PRR &= ~bv(PRTIMER1);
	#ifndef ATTINY
	TCCR1B = bv(CS11)|bv(CS10);
	#else
	TCCR1 = bv(CS12)|bv(CS11)|bv(CS10);
	#endif
	def_prescale = 64;
}

#ifndef ATTINY
void Timer1::config(uint8_t mode, uint8_t mode2, uint8_t top) {
	TCCR1A &= ~(bv(WGM11)|bv(WGM10));
	TCCR1B &= ~bv(WGM12);
	def_mode2 = mode2;
	switch(mode) {
		case CORRECT:
			TCCR1A |= bv(WGM10);
			break;
		case CORRECT9:
			TCCR1A |= bv(WGM11);
			break;
		case CORRECT10:
			TCCR1A |= bv(WGM11)|bv(WGM10);
			break;
		case CTC:
			TCCR1B |= bv(WGM12);
		case FAST:
			TCCR1A |= bv(WGM10);
			TCCR1B |= bv(WGM12);
			break;
		case FAST9:
			TCCR1A |= bv(WGM11);
			TCCR1B |= bv(WGM12);
			break;
		case FAST10:
			TCCR1A |= bv(WGM11)|bv(WGM10);
			TCCR1B |= bv(WGM12);
			break;
		case VARIABLE:
			variable(mode2, top);			
			break;
	}
}

void Timer1::variable(uint8_t mode, uint8_t top) {
	if(mode == FAST) {
		if(top == COMPA) {
			TCCR1B |= bv(WGM13)|bv(WGM12);
			TCCR1A |= bv(WGM11)|bv(WGM10);
			def_top = COMPA;
		}
		else {
			TCCR1B |= bv(WGM13)|bv(WGM12);
			TCCR1A |= bv(WGM11);
			def_top = CAPT;
		}
	}
	else {
		if(top == COMPA) {
			TCCR1B |= bv(WGM13);
			TCCR1A |= bv(WGM10);
			def_top = COMPA;
		}
		else {
			TCCR1B |= bv(WGM13);
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
		TCCR1B |= bv(CS10);
	else if(scale==8)
		TCCR1B |= bv(CS11);
	else if(scale==64)
		TCCR1B |= bv(CS11)|bv(CS10);
	else if(scale==256)
		TCCR1B |= bv(CS12);
	else if(scale==1024)
		TCCR1B |= bv(CS12)|bv(CS10);
	else if(scale==FALLING)
		TCCR1B |= bv(CS12)|bv(CS11);
	else if(scale==RISING)
		TCCR1B |= bv(CS12)|bv(CS11)|bv(CS10);
}

void Timer1::pwmA(uint16_t value) {
	if(value) {
		TCCR1A &= ~bv(COM1A0);
		TCCR1A |= bv(COM1A1);
	}
	else
		TCCR1A &= ~(bv(COM1A1)|bv(COM1A0));		
	OCR1A = value;
}

void Timer1::pwmA(uint16_t value, uint8_t mode) {
	if(value) {
		if(mode)
			TCCR1A |= (bv(COM1A1)|bv(COM1A0));
		else {
			TCCR1A &= ~bv(COM1A0);
			TCCR1A |= bv(COM1A1);
		}
	}
	else
		TCCR1A &= ~(bv(COM1A1)|bv(COM1A0));
	OCR1A = value;
}

void Timer1::pwmB(uint16_t value) {
	if(value) {
		TCCR1A &= ~bv(COM1B0);
		TCCR1A |= bv(COM1B1);
	}
	else 
		TCCR1A &= ~(bv(COM1B1)|bv(COM1B0));
	OCR1B = value;
}

void Timer1::pwmB(uint16_t value, uint8_t mode) {
	if(value) {
		if(mode)
			TCCR1A |= (bv(COM1B1)|bv(COM1B0));
		else {
			TCCR1A &= ~bv(COM1B0);
			TCCR1A |= bv(COM1B1);
		}
	}
	else
		TCCR1A &= ~(bv(COM1B1)|bv(COM1B0));
	OCR1B = value;
}

#else

void Timer1::config(uint8_t mode) {
	switch (mode) {
		case NORMAL:
			TCCR1 &= ~(bv(CTC1)|bv(PWM1A));
			GTCCR &= ~bv(PWM1B);
			break;
		case CTC:
			TCCR1 |= bv(CTC1);
			break;
	}
}

void Timer1::prescale(uint16_t scale) {
	TCCR1 &= ~(bv(CS13)|bv(CS12)|bv(CS11)|bv(CS10));
	def_prescale = scale;
	switch(scale) {
		case 1:
			TCCR1 |= bv(CS10);
			break;
		case 2:
			TCCR1 |= bv(CS11);
			break;
		case 4:
			TCCR1 |= bv(CS11)|bv(CS10);
			break;
		case 8:
			TCCR1 |= bv(CS12);
			break;
		case 16:
			TCCR1 |= bv(CS12)|bv(CS10);
			break;
		case 32:
			TCCR1 |= bv(CS12)|bv(CS11);
			break;
		case 64:
			TCCR1 |= bv(CS12)|bv(CS11)|bv(CS10);
			break;
		case 128:
			TCCR1 |= bv(CS13);
			break;
		case 256:
			TCCR1 |= bv(CS13)|bv(CS10);
			break;
		case 512:
			TCCR1 |= bv(CS13)|bv(CS11);
			break;
		case 1024:
			TCCR1 |= bv(CS13)|bv(CS11)|bv(CS10);
			break;
		case 2048:
			TCCR1 |= bv(CS13)|bv(CS12);
			break;
		case 4096:
			TCCR1 |= bv(CS13)|bv(CS12)|bv(CS10);
			break;
		case 8192:
			TCCR1 |= bv(CS13)|bv(CS12)|bv(CS11);
			break;
		case 16384:
			TCCR1 |= bv(CS13)|bv(CS12)|bv(CS11)|bv(CS10);
			break;
	}
}

void Timer1::pwmA(uint8_t value) {
	if(value) {
		this->pinA(CHANGE);
		TCCR1 |= bv(PWM1A);
	}
	else {
		this->pinA(DISCONNECT);
		TCCR1 &= ~bv(PWM1A);
	}
	OCR1A = (uint8_t)value;
}
void Timer1::pwmB(uint8_t value) {
	if(value) {
		this->pinB(CHANGE);
		GTCCR |= bv(PWM1B);
	}
	else {
		this->pinB(DISCONNECT);
		GTCCR &= ~bv(PWM1B);
	}
	OCR1B = (uint8_t)value;
}
#endif

void Timer1::pinA(uint8_t mode) {
	#ifdef TCCR1A
	TCCR1A &= ~(3<<COM1A0);
	if(mode == CHANGE)
		TCCR1A |= (1<<COM1A0);
	else if(mode == CLEAR)
		TCCR1A |= (2<<COM1A0);
	else if(mode == SET)
		TCCR1A |= (3<<COM1A0);
	#else
	TCCR1 &= ~(3<<COM1A0);
	if(mode == CHANGE)
		TCCR1 |= (1<<COM1A0);
	else if(mode == CLEAR)
		TCCR1 |= (2<<COM1A0);
	else if(mode == SET)
		TCCR1 |= (3<<COM1A0);
	#endif
}

void Timer1::pinB(uint8_t mode) {
	#ifdef TCCR1A
	TCCR1A &= ~(3<<COM1B0);
	if(mode == CHANGE)
		TCCR1A |= (1<<COM1B0);
	else if(mode == CLEAR)
		TCCR1A |= (2<<COM1B0);
	else if(mode == SET)
		TCCR1A |= (3<<COM1B0);
	#else
	GTCCR &= ~(3<<COM1B0);
	if(mode == CHANGE)
		GTCCR |= (1<<COM1B0);
	else if(mode == CLEAR)
		GTCCR |= (2<<COM1B0);
	else if(mode == SET)
		GTCCR |= (3<<COM1B0);
	#endif
}

#ifndef ATTINY
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
#else
void Timer1::period(uint32_t micros) {
	uint32_t cycles = microsecondsToClockCycles(micros)*2;
	TCCR1 &= ~7;
	if(!micros) {
		timer1_TCNT1 = 0;
		return;
	}
	if(cycles < 256)
		TCCR1 |= 1;
	else if((cycles /= 2) < 256)
		TCCR1 |= 2;
	else if((cycles /= 2) < 256)
		TCCR1 |= 3;
	else if((cycles /= 2) < 256)
		TCCR1 |= 4;
	else if((cycles /= 2) < 256)
		TCCR1 |= 5;
	else if((cycles /= 2) < 256)
		TCCR1 |= 6;
	else if((cycles /= 2) < 256)
		TCCR1 |= 7;
	else if((cycles /= 2) < 256)
		TCCR1 |= 8;
	else if((cycles /= 2) < 256)
		TCCR1 |= 9;
	else if((cycles /= 2) < 256)
		TCCR1 |= 0;
	else if((cycles /= 2) < 256)
		TCCR1 |= 10;
	else if((cycles /= 2) < 256)
		TCCR1 |= 11;
	else if((cycles /= 2) < 256)
		TCCR1 |= 12;
	else if((cycles /= 2) < 256)
		TCCR1 |= 13;
	else if((cycles /= 2) < 256)
		TCCR1 |= 14;
	else if((cycles /= 2) < 256)
		TCCR1 |= 15;
	else return;
	timer1_TCNT1 = 256 - cycles;
}
#endif

void Timer1::attach(uint8_t interrupt, void (*funct)(void)) {
	switch(interrupt) {
		case OVF:
			T1Array[0] = funct;
			#ifdef TIMSK1
			TIMSK1 |= bv(TOIE1);
			#else
			TIMSK |= bv(TOIE1);
			#endif
			break;
		case COMPA:
			T1Array[1] = funct;
			#ifdef TIMSK1
			TIMSK1 |= bv(OCIE1A);
			#else
			TIMSK |= bv(OCIE1A);
			#endif
			break;
		case COMPB:
			T1Array[2] = funct;
			#ifdef TIMSK1
			TIMSK1 |= bv(OCIE1B);
			#else
			TIMSK |= bv(OCIE1B);
			#endif
			break;
	}
	sei();
}

#ifndef ATTINY
void Timer1::attach(uint8_t interrupt, uint8_t mode, void (*funct)(void)) {
	if(interrupt != CAPT)
		return;
	TCCR1B |= (1<<ICNC1);
	if(mode == FALLING)
		TCCR1B &= ~(1<<ICES1);
	else if(mode == RISING)
		TCCR1B |= (1<<ICES1);
	TIMSK1 |= (1<<ICIE1);
	T1Array[3] = funct;
	sei();
}
#endif

void Timer1::detach(uint8_t interrupt) {
	switch(interrupt) {
		case OVF:
			T1Array[0] = none;
			#ifdef TIMSK1
			TIMSK1 &= ~bv(TOIE1);
			#else
			TIMSK &= ~bv(TOIE1);
			#endif
			break;
		case COMPA:
			T1Array[1] = none;
			#ifdef TIMSK1
			TIMSK1 &= ~bv(OCIE1A);
			#else
			TIMSK &= ~bv(OCIE1A);
			#endif
			break;
		case COMPB:
			T1Array[2] = none;
			#ifdef TIMSK1
			TIMSK1 &= ~bv(OCIE1B);
			#else
			TIMSK &= ~bv(OCIE1B);
			#endif
			break;
		#ifndef ATTINY
		case CAPT:
			T1Array[3] = none;
			TIMSK1 &= ~bv(ICIE1);
			TCCR1B &= ~bv(ICES1);
			break;
		#endif
	}
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

#ifndef ATTINY
ISR(TIMER1_CAPT_vect) {
	sregSAVE = SREG;
	T1Array[3]();
	SREG = sregSAVE;
}
#endif

