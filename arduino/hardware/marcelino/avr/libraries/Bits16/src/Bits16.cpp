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


#include "Bits16.h"

Bits16::Bits16(uint8_t data, uint8_t clock) {
	_clock = clock;
	_data  = data;
	Digital::write(_clock,LOW);
	Digital::write(_data,LOW);
	Digital::mode(_clock,OUTPUT);
	Digital::mode(_data,OUTPUT);
}

void Bits16::send(uint16_t data) {
    uint8_t aux;
    for(aux=0; aux<16; aux++) {
    	if(data&0x01) Digital::write(_data,HIGH);
    	else  Digital::write(_data,LOW);
    	Digital::write(_clock,HIGH);
    	Digital::write(_clock,LOW);
    	data=data>>1;
	}
}

uint16_t Bits16::out(uint8_t port, uint8_t state) {
	if(state)
		_ports|=(1<<port);
	else
		_ports&=~(1<<port);
	send(_ports);
	return _ports;
}

void Bits16::print(uint16_t number) {
	uint16_t _send;
	_send=pgm_get(bits16_segments,number/10)<<8;
	_send|=pgm_get(bits16_segments,number%10);
	send(_send);
	_ports=_send;
}

void Bits16::dot(uint8_t pos) {
	if(pos)
		_ports&=~(1<<15);
	else
		_ports&=~(1<<7);
	send(_ports);
}
