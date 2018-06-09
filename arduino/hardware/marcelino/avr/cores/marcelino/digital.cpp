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


#include "digital.h"

void Digital::mode(uint8_t pin, uint8_t _mode) {
	
	uint8_t _sfr = get_sfr(pin);
	volatile uint8_t* ddr  = get_DDR(_sfr);
	volatile uint8_t* port  = get_PORT(_sfr);

	uint8_t bit = get_bit(pin);

	if(_mode==INPUT) {
		*ddr &= ~bit;
		*port &= ~bit;
	}
	else if(_mode==PULLUP) {
		*ddr &= ~bit;
		*port |= bit;
	}
	else
		*ddr |= bit;

}
	
void Digital::write(uint8_t pin, uint8_t state) {

	volatile uint8_t* port  = get_PORT(get_sfr(pin));

	uint8_t bit = get_bit(pin);

	if(state == HIGH)
		*port |= bit;
	else if(state == TOGGLE)
		*port ^= bit;
	else
		*port &= ~bit;

}

uint8_t Digital::read(uint8_t pin) {

	volatile uint8_t* port  = get_PIN(get_sfr(pin));

	uint8_t bit = get_bit(pin);

	return ((*port) & bit) ? 1 : 0;

}

void Digital::output( byte bits, ... ) {
    va_list aux;
	va_start(aux, bits);
	for (int i = 0; i<bits; i++)
		this->mode(va_arg(aux,int),OUTPUT);
	va_end(aux);
}

void Digital::input( byte bits, ... ) {
    va_list aux;
	va_start(aux, bits);
	for (int i = 0; i<bits; i++)
		this->mode(va_arg(aux,int),INPUT);
	va_end(aux);
}

void Digital::pullup( byte bits, ... ) {
    va_list aux;
	va_start(aux, bits);
	for (int i = 0; i<bits; i++)
		mode(va_arg(aux,int),PULLUP);
	va_end(aux);
}

void Digital::set( byte bits, ... ) {
    va_list aux;
	va_start(aux, bits);
	for (int i = 0; i<bits; i++)
		this->write(va_arg(aux,int),HIGH);
	va_end(aux);
}

void Digital::clear( byte bits, ... ) {
    va_list aux;
	va_start(aux, bits);
	for (int i = 0; i<bits; i++)
		write(va_arg(aux,int),LOW);
	va_end(aux);
}

void Digital::toggle( byte bits, ... ) {
    va_list aux;
	va_start(aux, bits);
	for (int i = 0; i<bits; i++)
		this->write(va_arg(aux,int),TOGGLE);
	va_end(aux);
}
