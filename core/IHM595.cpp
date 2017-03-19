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



#include "IHM595.h"

IHM595::IHM595(uint8_t data, uint8_t clock, uint8_t enable) {
	this->data = data;
	this->clock = clock;
	this->enable = enable;
	this->_col = 0x0F;
	this->_row = 0x02;
	this->_mode();
	this->init();
}

void IHM595::init() {
	Digital::write(clock,LOW);
	Digital::write(data,LOW);
	Digital::write(enable,LOW);
	Digital::mode(clock,OUTPUT);
	Digital::mode(data,OUTPUT);
	Digital::mode(enable,OUTPUT);
	_delay_us(10000);
	cmd(0x03,1);
	_delay_us(4500);
	cmd(0x03,1);
	_delay_us(4500);
	cmd(0x03,1);
	_delay_us(150);
	cmd(0x02,1);
	_delay_us(2000);
	cmd(0x28,1);
	_delay_us(2000);
	cmd(noCURSOR,1);
	_delay_us(2000);
	cmd(0x01,1);
	_delay_us(2000);
	set(0,0);
}

//private:
void IHM595::send(uint8_t d) {
	for(uint8_t aux=0; aux<7; aux++){
      if(d&0x01) Digital::write(data,HIGH);
      else  Digital::write(data,LOW);
      Digital::write(clock,HIGH);
      Digital::write(clock,LOW);
      d>>=1;
    }
	Digital::write(enable,HIGH);
	_delay_us(1);
	Digital::write(enable,LOW);
	_delay_us(40);
}

void IHM595::cmd(uint8_t d, uint8_t c) {
	uint8_t _send;
    _send=d>>3;
    if (c) _send&=~(1<<5);
    else _send|=(1<<5);
    if (_background) _send |= (1<<0);
    else _send&=~(1<<0);
    send(_send);
    _send=d<<1;
    if (c) _send &= ~(1<<5);
    else _send|=(1<<5);
    if (_background) _send|=(1<<0);
    else _send&=~(1<<0);
    send(_send);
}

void IHM595::_mode() {
	_addressrow[0] = 0x00;
	_addressrow[1] = 0x40;
	_addressrow[2] = _col;
	_addressrow[3] = _col + 0x40;
}

//public:
size_t IHM595::write(uint8_t d) {
	cmd(d,0);
	return 1;
}

size_t IHM595::write(const char *s) {
	while(*s!='\0')
		cmd(*s++,0);
	return 1;
}

size_t IHM595::write(const uint8_t *s, size_t l) {
	while(l--)
		cmd(*s++,0);
	return 1;
}

void IHM595::clear() {
	cmd(0x01,1);
	_delay_us(2000);
}

void IHM595::home() {
	cmd(0x02,1);
	_delay_us(2000);
}
void IHM595::cursor(uint8_t mode) {
	cmd(mode,1);
}

void IHM595::display(uint8_t state) {
	clear();
	if(state) cmd(0x0C,1);
	else cmd(0x08,1);
}
void IHM595::set(uint8_t col, uint8_t row) {
	size_t max_lines = sizeof(_addressrow) / sizeof(*_addressrow);
	if(row >= max_lines)
		row = max_lines-1;
	if(row >= _col)
		row = _col - 1;
	uint8_t aux = 0x80 | (col + _addressrow[row]);
	cmd(aux,1);
	_delay_us(2000);

}

void IHM595::background(uint8_t state) {
	_background=state;
	cmd(0x00,1);
}
