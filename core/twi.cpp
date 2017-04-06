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


#include "twi.h"

VoidFuncPtr TWIARRAY = none;
uint8_t mode_twi;

//privete
void TWI::address(uint8_t _address) {
	TWAR = _address;
	TWCR = (1<<TWEA)|(1<<TWEN);
}

//public
TWI::TWI(uint8_t mode, uint8_t option) {
	PRR &= ~(1<<PRTWI);
	mode_twi = mode;
	if(mode==MASTER) {
#if F_CPU == 8000000UL
		if(option == SLOW)
			TWBR = 32;
		else
			TWBR = 2;
#elif F_CPU == 16000000UL
		if(option == SLOW)
			TWBR = 72;
		else
			TWBR = 12;
#endif
	}
	else
		address(option);
}

void TWI::send(uint8_t data) {
    TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

uint8_t TWI::recive(uint8_t ack) {
	if(ack)
		TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	else
		TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
    return TWDR;
}

void TWI::attach(VoidFuncPtr funct) {
	TWIARRAY = funct;
	TWCR |= (1<<TWIE);
	sei();
}

void TWI::detach() {
	TWIARRAY = none;
	TWCR &= ~(1<<TWIE);
}

uint8_t TWI::ifstart() {
	uint8_t aux = status();
	if(aux == 0x08) return 1;
	return 0;
}

ISR(TWI_vect) {
	sregSAVE = SREG;
	TWIARRAY();
	SREG = sregSAVE;
}
