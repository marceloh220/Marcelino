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

marcelino_PTRFunc INTArray[2] = {none,none};
marcelino_PTRFunc PCINTArray[3] = {none,none,none};

const uint8_t digital_PCMASK[3] PROGMEM = {
	(uint16_t)&PCMSK0,
	(uint16_t)&PCMSK1,
	(uint16_t)&PCMSK2,
};

void External::attach(uint8_t pin, void (*funct)(void)) {
	
	uint8_t _sfr = get_sfr(pin);
	
	volatile uint8_t* port  = get_PCMASK(_sfr);
	*port |= get_bit(pin);
	PCICR |= (1<<_sfr);
	
	PCINTArray[_sfr] = funct;

	sei();
		
}


void External::attach(uint8_t interrupt, uint8_t mode, void (*funct)(void)) {
	
	uint8_t i = interrupt*2;
	EICRA &= ~(3<<i);

	if(mode == CHANGE)
		EICRA |= (1<<i);
	if(mode == FALLING)
		EICRA |= (2<<i);
	if(mode == RISING)
		EICRA |= (3<<i);
	
	EIMSK |= (1<<interrupt);
	INTArray[interrupt] = funct;
	
	sei();
}

void External::detachPC(uint8_t pin) {
	
	uint8_t _sfr = get_sfr(pin);
	
	volatile uint8_t* port  = get_PCMASK(_sfr);
	*port &= ~get_bit(pin);
		
	
	if(!(*port)) {
		PCICR &= ~(1<<_sfr);
		PCINTArray[_sfr] = none;
	}
	
}

void External::detachINT(uint8_t interrupt) {
	
	INTArray[interrupt] = none;
	EIMSK &= ~(1<<interrupt);
	
}

uint8_t External::rising(uint8_t interrupt) {
	
	uint8_t aux = EICRA;
	
	if(interrupt) {
		aux&=(3<<ISC10);
		aux=aux>>ISC10;
	}
	else
		aux&=(3<<ISC00);
		
	return aux == 3 ? 1 : 0;
	
}

uint8_t External::falling(uint8_t interrupt) {
	
		uint8_t aux = EICRA;
	
	if(interrupt) {
		aux&=(3<<ISC10);
		aux=aux>>ISC10;
	}
	else
		aux&=(3<<ISC00);
		
	return aux == 2 ? 1 : 0;
	
}

uint8_t External::change(uint8_t interrupt) {
	
		uint8_t aux = EICRA;
	
	if(interrupt) {
		aux&=(3<<ISC10);
		aux=aux>>ISC10;
	}
	else
		aux&=(3<<ISC00);
		
	return aux == 1 ? 1 : 0;
	
}

uint8_t External::lower(uint8_t interrupt) {
	
		uint8_t aux = EICRA;
	
	if(interrupt) {
		aux&=(3<<ISC10);
		aux=aux>>ISC10;
	}
	else
		aux&=(3<<ISC00);
		
	return !aux;
	
}

ISR(INT0_vect) {
	sregSAVE = SREG;
	INTArray[0]();
}

ISR(INT1_vect) {
	sregSAVE = SREG;
	INTArray[1]();
}

ISR(PCINT0_vect) {
	sregSAVE = SREG;
	PCINTArray[0]();
}

ISR(PCINT1_vect) {
	sregSAVE = SREG;
	PCINTArray[1]();
}

ISR(PCINT2_vect) {
	sregSAVE = SREG;
	PCINTArray[2]();
}
