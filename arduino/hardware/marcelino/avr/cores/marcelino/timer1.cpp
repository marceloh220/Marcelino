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
}

#ifndef ATTINY
void Timer1::configure(uint8_t mode) {
	TCCR1A &= ~(bv(WGM11)|bv(WGM10));
	TCCR1B &= ~bv(WGM12);
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
		default:
			break;
	}
}

void Timer1::configure(uint8_t mode, uint8_t top) {
	TCCR1A &= ~(bv(WGM11)|bv(WGM10));
	TCCR1B &= ~bv(WGM12);
	if(mode == FAST) {
		if(top == COMPA) {
			TCCR1B |= bv(WGM13)|bv(WGM12);
			TCCR1A |= bv(WGM11)|bv(WGM10);
		}
		else if(top == COMPC) {
			TCCR1B |= bv(WGM13)|bv(WGM12);
			TCCR1A |= bv(WGM11);
		}
	}
	else if(mode == CORRECT){
		if(top == COMPA) {
			TCCR1B |= bv(WGM13);
			TCCR1A |= bv(WGM10);
		}
		else if(top == COMPC)
			TCCR1B |= bv(WGM13);
	}
}

void Timer1::prescale(uint8_t scale) {
	TCCR1B &= ~(bv(CS12)|bv(CS11)|bv(CS10));
	switch (scale) {
		case P_1 :
			TCCR1B |= bv(CS10);
			break;
		case P_8:
			TCCR1B |= bv(CS11);
			break;
		case P_64:
			TCCR1B |= bv(CS11)|bv(CS10);
			break;
		case P_256:
			TCCR1B |= bv(CS12);
			break;
		case P_1K:
			TCCR1B |= bv(CS12)|bv(CS10);
			break;
		case FALLING:
			TCCR1B |= bv(CS12)|bv(CS11);
			break;
		case RISING:
			TCCR1B |= bv(CS12)|bv(CS11)|bv(CS10);
			break;
		default:
			break;
	}
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

void Timer1::configure(uint8_t mode) {
	switch (mode) {
		case NORMAL:
			TCCR1 &= ~(bv(CTC1)|bv(PWM1A));
			GTCCR &= ~bv(PWM1B);
			break;
		case CTC:
			TCCR1 |= bv(CTC1);
			break;
		default:
			break;
	}
}

void Timer1::prescale(uint8_t scale) {
	TCCR1 &= ~(bv(CS13)|bv(CS12)|bv(CS11)|bv(CS10));
	switch(scale) {
		case P_1:
			TCCR1 |= bv(CS10);
			break;
		case P_2:
			TCCR1 |= bv(CS11);
			break;
		case P_4:
			TCCR1 |= bv(CS11)|bv(CS10);
			break;
		case P_8:
			TCCR1 |= bv(CS12);
			break;
		case P_16:
			TCCR1 |= bv(CS12)|bv(CS10);
			break;
		case P_32:
			TCCR1 |= bv(CS12)|bv(CS11);
			break;
		case P_64:
			TCCR1 |= bv(CS12)|bv(CS11)|bv(CS10);
			break;
		case P_128:
			TCCR1 |= bv(CS13);
			break;
		case P_256:
			TCCR1 |= bv(CS13)|bv(CS10);
			break;
		case P_512:
			TCCR1 |= bv(CS13)|bv(CS11);
			break;
		case P_1K:
			TCCR1 |= bv(CS13)|bv(CS11)|bv(CS10);
			break;
		case P_2K:
			TCCR1 |= bv(CS13)|bv(CS12);
			break;
		case P_4K:
			TCCR1 |= bv(CS13)|bv(CS12)|bv(CS10);
			break;
		case P_8K:
			TCCR1 |= bv(CS13)|bv(CS12)|bv(CS11);
			break;
		case P_16K:
			TCCR1 |= bv(CS13)|bv(CS12)|bv(CS11)|bv(CS10);
			break;
		default:
			break;
	}
}
#endif

void Timer1::pinA(uint8_t mode) {
	#ifdef TCCR1A
	TCCR1A &= ~(bv(COM1A1)|bv(COM1A0));
	switch(mode) {
		case CHANGE:
			TCCR1A |= bv(COM1A0);
			break;
		case CLEAR:
			TCCR1A |= bv(COM1A1);
			break;
		case SET:
			TCCR1A |= bv(COM1A1)|bv(COM1A0);
			break;
		default:
			break;
	}
	#else
	TCCR1 &= ~(bv(COM1A1)|bv(COM1A0));
	switch(mode) {
		case CHANGE:
			TCCR1 |= bv(COM1A0);
			break;
		case CLEAR:
			TCCR1 |= bv(COM1A1);
			break;
		case SET:
			TCCR1 |= bv(COM1A1)|bv(COM1A0);
			break;
		default:
			break;
	}
	#endif
}

void Timer1::pinB(uint8_t mode) {
	#ifdef TCCR1A
	TCCR1A &= ~(bv(COM1B1)|bv(COM1B0));
	switch(mode) {
		case CHANGE:
			TCCR1A |= bv(COM1B0);
			break;
		case CLEAR:
			TCCR1A |= bv(COM1B1);
			break;
		case SET:
			TCCR1A |= bv(COM1B1)|bv(COM1B0);
			break;
		default:
			break;
	}
	#else
	GTCCR &= ~(bv(COM1B1)|bv(COM1B0));
	switch(mode) {
		case CHANGE:
			GTCCR |= bv(COM1B0);
			break;
		case CLEAR:
			GTCCR |= bv(COM1B1);
			break;
		case SET:
			GTCCR |= bv(COM1B1)|bv(COM1B0);
			break;
		default:
			break;
	}
	#endif
}

#ifndef ATTINY
void Timer1::period(uint32_t micros, uint8_t top) {
	uint8_t scale;
	uint32_t cycles;
	TCCR1B &= ~(bv(CS12)|bv(CS11)|bv(CS10));
	timer1_TCNT1 = 0;
	TCNT1 = 0;
	if(micros == 0)
		return;
	cycles = microsecondsToClockCycles(micros);
	if(cycles < 65536)
		scale = bv(CS10);
	else if((cycles /= 8) < 65536)
		scale = bv(CS11);
	else if((cycles /= 8) < 65536)
		scale = bv(CS11)|bv(CS10);
	else if((cycles /= 8) < 65536)
		scale = bv(CS12);
	else if((cycles /= 8) < 65536)
		scale = bv(CS12)|bv(CS10);
	else return;
	if(top == COMPA)
		OCR1A = cycles;
	else {
		timer1_TCNT1 = 65535 - cycles;
		TCNT1 = timer1_TCNT1;
	}
	TCCR1B |= scale;
}
#else
void Timer1::period(uint32_t micros, uint8_t top) {
	uint8_t scale;
	uint32_t cycles;
	TCCR1 &= ~(bv(CS13)|bv(CS12)|bv(CS11)|bv(CS10));
	timer1_TCNT1 = 0;
	TCNT1 = 0;
	if(micros == 0)
		return;
	cycles = microsecondsToClockCycles(micros);
	if(cycles < 256)
		scale = bv(CS10);			//1
	else if((cycles /= 2) < 256)
		scale = bv(CS11);			//2
	else if((cycles /= 2) < 256)
		scale = bv(CS11)|bv(CS10);	//3
	else if((cycles /= 2) < 256)
		scale = bv(CS12);			//4
	else if((cycles /= 2) < 256)
		scale = bv(CS12)|bv(CS10);	//5
	else if((cycles /= 2) < 256)
		scale = bv(CS12)|bv(CS11);	//6
	else if((cycles /= 2) < 256)
		scale = bv(CS12)|bv(CS11)|bv(CS10);	//7
	else if((cycles /= 2) < 256)
		scale = bv(CS13);						//8
	else if((cycles /= 2) < 256)
		scale = bv(CS13)|bv(CS10);				//9
	else if((cycles /= 2) < 256)
		scale = bv(CS13)|bv(CS11);				//10
	else if((cycles /= 2) < 256)
		scale = bv(CS13)|bv(CS11)|bv(CS10);	//11
	else if((cycles /= 2) < 256)
		scale = bv(CS13)|bv(CS12);				//12
	else if((cycles /= 2) < 256)
		scale = bv(CS13)|bv(CS12)|bv(CS10);	//13
	else if((cycles /= 2) < 256)
		scale = bv(CS13)|bv(CS12)|bv(CS11);	//14
	else if((cycles /= 2) < 256)
		scale = bv(CS13)|bv(CS12)|bv(CS11)|bv(CS10);	//15
	else return;
	if (top == COMPA)
		OCR1A = cycles;
	else {
		timer1_TCNT1 = 255 - cycles;
		TCNT1 = timer1_TCNT1;
	}
	TCCR1 |= scale;
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

