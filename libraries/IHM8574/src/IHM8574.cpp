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



#include "IHM8574.h"

IHM8574::IHM8574(uint8_t address) {
	this->_address = address;
	this->_col = 0x0F;
	this->_row = 0x02;
	this->_mode();
	this->init();
}

void IHM8574::init() {
	this->_busy = 1;
	_delay_us(4500);
	cmd(0x30,1);
	_delay_us(4500);
	cmd(0x30,1);
	_delay_us(4500);
	cmd(0x30,1);
	_delay_us(150);
	cmd(0x02,1);
	_delay_us(2000);
	cmd(0x28,1);
	_delay_us(2000);
	cmd(noCURSOR,1);
	_delay_us(2000);
	cmd(0x01,1);
	_delay_us(2000);
	this->_busy = 0;
<<<<<<< HEAD
	this->set(0,0);
=======
>>>>>>> origin/master
}

//private:
void IHM8574::send(uint8_t d) {
	TWI::start();
	TWI::send(_address);
	TWI::send(d);
	TWI::stop();
}

void IHM8574::cmd(uint8_t d, uint8_t c) {
	this->_busy = 1;
	uint8_t _send;
    _send=d&0xF0;
    if (c) _send&=~(1<<0);
    else _send|=(1<<0);
    if (_background) _send |= (1<<3);
    else _send&=~(1<<3);
    _send |= (1<<2);
    this->send(_send);
    _delay_us(1);
    _send &= ~(1<<2);
    this->send(_send);
    _delay_us(37);
    _send=d<<4;
    if (c) _send &= ~(1<<0);
    else _send|=(1<<0);
    if (_background) _send|=(1<<3);
    else _send&=~(1<<3);
    _send |= (1<<2);
    this->send(_send);
    _delay_us(1);
    _send &= ~(1<<2);
    this->send(_send);
    _delay_us(37);
    this->_busy = 0;
}

void IHM8574::_mode() {
	this->_addressrow[0] = 0x00;
	this->_addressrow[1] = 0x40;
	this->_addressrow[2] = this->_col;
	this->_addressrow[3] = this->_col + 0x40;
}

//public:
size_t IHM8574::write(uint8_t d) {
	this->cmd(d,0);
	return 1;
}

size_t IHM8574::write(const char *s) {
	while(*s!='\0')
		this->cmd(*s++,0);
	return 1;
}

size_t IHM8574::write(const uint8_t *s, size_t l) {
	while(l--)
		this->cmd(*s++,0);
	return 1;
}

void IHM8574::clear() {
	this->cmd(0x01,1);
	_delay_us(2000);
}

void IHM8574::home() {
	this->cmd(0x02,1);
	_delay_us(2000);
}
void IHM8574::cursor(uint8_t mode) {
	this->cmd(mode,1);
}

void IHM8574::display(uint8_t state) {
	_delay_us(2000);
	this->clear();
	if(state) {
		this->cmd(0x0C,1);
		_delay_us(2000);
		this->init();
	}
	else {
		cmd(0x08,1);
		_delay_us(4500);
	}
}
void IHM8574::set(uint8_t col, uint8_t row) {
	size_t max_lines = sizeof(this->_addressrow) / sizeof(*_addressrow);
	if(row >= max_lines)
		row = max_lines-1;
	if(row >= _col)
		row = _col - 1;
	uint8_t aux = 0x80 | (col + this->_addressrow[row]);
	this->cmd(aux,1);
	_delay_us(2000);

}

<<<<<<< HEAD
void IHM8574::backlight(uint8_t state) {
=======
void IHM8574::background(uint8_t state) {
>>>>>>> origin/master
	this->_background=state;
	this->cmd(0x00,1);
}

void IHM8574::create(uint8_t location, uint8_t charmap[]) {
	location &= 0x7;
	this->cmd(0x40 | (location << 3),1);
	for (int i=0; i<8; i++) {
		this->write(charmap[i]);
	}
}

void IHM8574::create(uint8_t location, uint8_t charmap, uint8_t i) {
	if(!i) {
		location &= 0x7;
		this->cmd(0x40 | (location << 3),1);
	}
	this->write(charmap);
}
