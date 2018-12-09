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


#include "external.h"

void (*INTArray[2])(void) = {none,none};
void (*PCINTArray[3])(void) = {none,none,none};

void External::attach(uint8_t pin, void (*funct)(void)) {
	uint8_t vec = get_PCMASK_vec(pin);
	sfr_type port  = get_PCMASK(pin);
	*port |= get_bit(pin);
	#ifdef PCICR
	PCICR |= bv(vec);
	#endif
	PCINTArray[vec] = funct;
	sei();
}

void External::attach(uint8_t interrupt, uint8_t mode, void (*funct)(void)) {
	
	#ifndef NOINT1
	uint8_t i = interrupt*2;
	EICRA &= ~(3<<i);

	if(mode == CHANGE)
		EICRA |= (1<<i);
	if(mode == FALLING)
		EICRA |= (2<<i);
	if(mode == RISING)
		EICRA |= (3<<i);
	
	EIMSK |= (1<<interrupt);
	#else
	if(mode == CHANGE)
		MCUCR |= bv(ISC00);
	if(mode == FALLING)
		MCUCR |= bv(ISC01);
	if(mode == RISING)
		MCUCR |= bv(ISC01)|bv(ISC00);
	GIMSK |= bv(INT0);
	#endif
	INTArray[interrupt] = funct;
	
	sei();
}

void External::detachPC(uint8_t pin) {
	
	uint8_t vec = get_PCMASK_vec(pin);
	sfr_type port  = get_PCMASK(pin);
	*port &= ~get_bit(pin);
		
	
	if(!(*port)) {
		#ifdef PCICR
		PCICR &= ~bv(vec);
		#endif
		PCINTArray[vec] = none;
	}
	
}

void External::detachINT(uint8_t interrupt) {
	
	INTArray[interrupt] = none;
	#ifndef NOINT1
	EIMSK &= ~(1<<interrupt);
	#else
	GIMSK &= ~bv(INT0);
	#endif
	
}

uint8_t External::rising(uint8_t interrupt) {
	
	#ifndef NOINT1
	uint8_t aux = EICRA;
	if(interrupt) {
		aux&=(3<<ISC10);
		aux=aux>>ISC10;
	}
	else
		aux&=(3<<ISC00);
	#else
	uint8_t aux = MCUCR;
	aux&=(3<<ISC00);
	#endif
	
	return aux == 3 ? 1 : 0;
	
}

uint8_t External::falling(uint8_t interrupt) {
	
	#ifndef NOINT1
	uint8_t aux = EICRA;
	if(interrupt) {
		aux&=(3<<ISC10);
		aux=aux>>ISC10;
	}
	else
		aux&=(3<<ISC00);
	#else
	uint8_t aux = MCUCR;
	aux&=(3<<ISC00);
	#endif
	
	return aux == 2 ? 1 : 0;
	
}

uint8_t External::change(uint8_t interrupt) {
	
	#ifndef NOINT1
	uint8_t aux = EICRA;
	if(interrupt) {
		aux&=(3<<ISC10);
		aux=aux>>ISC10;
	}
	else
		aux&=(3<<ISC00);
	#else
	uint8_t aux = MCUCR;
	aux&=(3<<ISC00);
	#endif
		
	return aux == 1 ? 1 : 0;
	
}

uint8_t External::lower(uint8_t interrupt) {
	
	#ifndef NOINT1
	uint8_t aux = EICRA;
	if(interrupt) {
		aux&=(3<<ISC10);
		aux=aux>>ISC10;
	}
	else
		aux&=(3<<ISC00);
	#else
	uint8_t aux = MCUCR;
	aux&=(3<<ISC00);
	#endif
	
	return !aux;
	
}

ISR(INT0_vect) {
	sregSAVE = SREG;
	INTArray[0]();
}

#ifndef ATTINY
ISR(INT1_vect) {
	sregSAVE = SREG;
	INTArray[1]();
}
#endif

ISR(PCINT0_vect) {
	sregSAVE = SREG;
	PCINTArray[0]();
}

#ifndef ATTINY
ISR(PCINT1_vect) {
	sregSAVE = SREG;
	PCINTArray[1]();
}

ISR(PCINT2_vect) {
	sregSAVE = SREG;
	PCINTArray[2]();
}
#endif
