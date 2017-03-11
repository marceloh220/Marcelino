#include "timer2.h"



VoidFuncPtr T2Array[3] = {none,none,none};

Timer2::Timer2() {
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
	TCCR2B |= scale;
}

void Timer2::config(uint8_t mode, uint8_t top) {
	def_top = top;
	def_mode = mode;
	TCCR2B &= ~(1<<WGM22);
	TCCR2A &= ~3;
	TCCR2A |= (mode&3);
	if(top)
		TCCR2B |= (1<<WGM22);
}

void Timer2::pinA(uint8_t mode) {
	TCCR2A &= ~(3<<COM2A0);
	if(mode == CHANGE)
		TCCR2A |= (1<<COM2A0);
	else if(mode == CLEAR)
		TCCR2A |= (2<<COM2A0);
	else if(mode == SET)
		TCCR2A |= (3<<COM2A0);
}

void Timer2::pinB(uint8_t mode) {
	TCCR2A &= ~(3<<COM2B0);
	if(mode == CHANGE)
		TCCR2A |= (1<<COM2B0);
	else if(mode == CLEAR)
		TCCR2A |= (2<<COM2B0);
	else if(mode == SET)
		TCCR2A |= (3<<COM2B0);
}

void Timer2::pwmA(uint8_t value) {
	if(value) {
		TCCR2A &= ~(1<<COM2A0);
		TCCR2A |= (1<<COM2A1);
	}
	else
		TCCR2A &= ~(3<<COM2A0);		
	OCR2A = value;
}

void Timer2::pwmA(uint8_t value, uint8_t mode) {
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
}

void Timer2::pwmB(uint8_t value) {
	if(value) {
		TCCR2A &= ~(1<<COM2B0);
		TCCR2A |= (1<<COM2B1);
	}
	else 
		TCCR2A &= ~(3<<COM2B0);
	OCR2B = value;
}


void Timer2::pwmB(uint8_t value, uint8_t mode) {
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
}

void Timer2::frequency(uint32_t freq) {
	
	uint8_t factor;
	
	if(def_mode == FAST)
		factor = 1;
	else
		factor = 2;
	
	if(def_top == COMPA || def_mode == CTC)
		OCR2A = F_CPU / (factor * def_prescale * freq) - 1;
}

void Timer2::attach(uint8_t interrupt, VoidFuncPtr funct) {
	T2Array[interrupt] = funct;
	TIMSK2 |= (1<<interrupt);
	sei();
}

void Timer2::detach(uint8_t interrupt) {
	T2Array[interrupt] = none;
	TIMSK2 &= ~(1<<interrupt);
}

ISR(TIMER2_OVF_vect) {
	sregSAVE = SREG;
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
