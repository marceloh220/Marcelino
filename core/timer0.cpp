#include "timer0.h"

uint32_t _millis;

VoidFuncPtr T0Array[3] = {none,none,none};

Timer0::Timer0() {
	def_prescale = 64;
	TCCR0B = 3;
	TIMSK0|=(1<<TOIE0);
	sei();
}

uint32_t Timer0::millis() {
#if F_CPU == 16000000UL
	return _millis;
#elif F_CPU == 8000000UL
	return _millis*2;
#endif
	
}

void Timer0::prescale(uint16_t scale) {
	def_prescale = scale;
	TCCR0B &= ~7;
	if(!scale)
		return;
	if(scale == 1)
		scale=1;
	else if(scale == 8)
		scale=2;
	else if(scale == 64)
		scale=3;
	else if(scale == 256)
		scale=4;
	else if(scale == 1024)
		scale=5;
	else if(scale == FALLING)
		scale=6;
	else if(scale == RISING)
		scale=7;
	TCCR0B |= scale;
}

void Timer0::config(uint8_t mode, uint8_t top) {
	def_top = top;
	def_mode = mode;
	TCCR0B &= ~(1<<WGM02);
	TCCR0A &= ~3;
	TCCR0A |= (mode&3);
	if(top)
		TCCR0B |= (1<<WGM02);
}

void Timer0::pinA(uint8_t mode) {
	TCCR0A &= ~(3<<COM0A0);
	if(mode == CHANGE)
		TCCR0A |= (1<<COM0A0);
	else if(mode == CLEAR)
		TCCR0A |= (2<<COM0A0);
	else if(mode == SET)
		TCCR0A |= (3<<COM0A0);
}

void Timer0::pinB(uint8_t mode) {
	TCCR0A &= ~(3<<COM0B0);
	if(mode == CHANGE)
		TCCR0A |= (1<<COM0B0);
	else if(mode == CLEAR)
		TCCR0A |= (2<<COM0B0);
	else if(mode == SET)
		TCCR0A |= (3<<COM0B0);
}

void Timer0::pwmA(uint8_t value) {
	if(value) {
		TCCR0A &= ~(1<<COM0A0);
		TCCR0A |= (1<<COM0A1);
	}
	else
		TCCR0A &= ~(3<<COM0A0);		
	OCR0A = value;
}

void Timer0::pwmA(uint8_t value, uint8_t mode) {
	if(value) {
		if(mode)
			TCCR0A |= (3<<COM0A0);
		else {
			TCCR0A &= ~(1<<COM0A0);
			TCCR0A |= (1<<COM0A1);
		}
	}
	else
		TCCR0A &= ~(3<<COM0A0);
	OCR0A = value;
}

void Timer0::pwmB(uint8_t value) {
	if(value) {
		TCCR0A &= ~(1<<COM0B0);
		TCCR0A |= (1<<COM0B1);
	}
	else 
		TCCR0A &= ~(3<<COM0B0);
	OCR0B = value;
}

void Timer0::pwmB(uint8_t value, uint8_t mode) {
	if(value) {
		if(mode)
			TCCR0A |= (3<<COM0B0);
		else {
			TCCR0A &= ~(1<<COM0B0);
			TCCR0A |= (1<<COM0B1);
		}
	}
	else
		TCCR0A &= ~(3<<COM0B0);
	OCR0B = value;
}

void Timer0::frequency(uint32_t freq) {
	
	uint8_t factor;
	
	if(def_mode == FAST)
		factor = 1;
	else
		factor = 2;
	
	if(def_top == COMPA || def_mode == CTC)
		OCR0A = F_CPU / (factor * def_prescale * freq) - 1;
}

void Timer0::attach(uint8_t interrupt, VoidFuncPtr funct) {
	T0Array[interrupt] = funct;
	TIMSK0 |= (1<<interrupt);
	sei();
}

void Timer0::detach(uint8_t interrupt) {
	T0Array[interrupt] = none;
	if(!interrupt)
		TIMSK0 &= ~(1<<interrupt);
}

ISR(TIMER0_OVF_vect) {
	sregSAVE = SREG;
	_millis++;
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
