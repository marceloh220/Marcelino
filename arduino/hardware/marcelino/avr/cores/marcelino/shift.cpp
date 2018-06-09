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


#include "shift.h"

Shift::Shift(uint8_t data, uint8_t clock, uint8_t bits) {
	this->init(data,clock, bits);
}

Shift::Shift(uint8_t data, uint8_t clock, uint8_t enable, uint8_t bits) {
	this->init(data,clock,enable, bits);
}

void Shift::init(uint8_t data, uint8_t clock, uint8_t bits) {
	this->data_pin = data;
	this->clock_pin = clock;
	this->n_bits = bits;
	Digital::write(data_pin,LOW);
	Digital::write(clock_pin,LOW);
	Digital::write(enable_pin,LOW);
	Digital::mode(data_pin,OUTPUT);
	Digital::mode(clock_pin,OUTPUT);
	this->_mode=0;
}

void Shift::init(uint8_t data, uint8_t clock, uint8_t enable, uint8_t bits) {
	this->data_pin = data;
	this->clock_pin = clock;
	this->enable_pin = enable;
	this->n_bits = bits;
	Digital::write(data_pin,LOW);
	Digital::write(clock_pin,LOW);
	Digital::write(enable_pin,LOW);
	Digital::mode(data_pin,OUTPUT);
	Digital::mode(clock_pin,OUTPUT);
	Digital::mode(enable_pin,OUTPUT);
	this->_mode=1;
}

void Shift::clock() {
	Digital::write(clock_pin,HIGH);
	Digital::write(clock_pin,LOW);
}

void Shift::enable() {
	Digital::write(enable_pin,HIGH);
	Digital::write(enable_pin,LOW);
}

void Shift::send(uint32_t _data, uint8_t first) {
	if(first) {
		for(int aux=0; aux < this->n_bits; aux++) {
			uint8_t bit=(_data&0x01) ? 1 : 0;
			Digital::write(data_pin,bit);
			clock();
			_data=(_data>>1);
		}
	}
	else {
		for(int aux=0; aux < this->n_bits; aux++) {
			uint8_t bit=(_data&0x80) ? 1 : 0;
			Digital::write(data_pin,bit);
			clock();
			_data=(_data<<1);
		}
	}
	if(this->_mode) enable();
}

void Shift::ack() {
	Digital::write(data_pin,HIGH);
	this->clock();
	Digital::write(data_pin,LOW);
	this->clock();
}
