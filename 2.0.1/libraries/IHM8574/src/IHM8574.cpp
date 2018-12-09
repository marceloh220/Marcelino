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

#define IHM8574_setBit(_sfr,_bit)	(_sfr|=(1<<_bit))
#define IHM8574_clearBit(_sfr,_bit)	(_sfr&=(1<<_bit))
#define IHM8574_MSBnibble(_sfr)		(_sfr&0xF0)
#define IHM8574_LSBnibble(_sfr)		(_sfr<<4)

#define IHM8574_rsBit				(1<<0)
#define IHM8574_rwBit				(1<<1)
#define IHM8574_enableBit			(1<<2)
#define IHM8574_backlightBit		(1<<3)

#define IHM8574_data				(0)
#define IHM8574_command				(1)


IHM8574::IHM8574(uint8_t address) {
	this->_address = address;
	this->_col = 0x0F;
	this->_row = 0x02;
	this->_mode();
	this->init();
}

void IHM8574::init() {
	_delay_us(4500);
	cmd(0x30, IHM8574_command);
	_delay_us(4500);
	cmd(0x30, IHM8574_command);
	_delay_us(4500);
	cmd(0x30, IHM8574_command);
	_delay_us(150);
	cmd(0x02, IHM8574_command);
	_delay_us(2000);
	cmd(0x28, IHM8574_command);
	_delay_us(2000);
	cmd(noCURSOR, IHM8574_command);
	_delay_us(2000);
	cmd(0x01, IHM8574_command);
	_delay_us(2000);
}

void IHM8574::config(uint8_t col, uint8_t row) {
		_col = col;
		_row = row;
		this->_mode();
	}

//private:
void IHM8574::send(uint8_t data) {
	TWI::start();
	TWI::send(_address);
	TWI::send(data);
	TWI::stop();
}

void IHM8574::enable(uint8_t data, uint8_t type) {
	if (type) {
		IHM8574_clearBit(data, IHM8574_rsBit);
	}
    else {
		IHM8574_setBit(data, IHM8574_rsBit);
	}
    if (_backlight) {
		IHM8574_setBit(data, IHM8574_backlightBit);
	}
    else {
		IHM8574_clearBit(data, IHM8574_backlightBit);
	}
	IHM8574_setBit(data, IHM8574_enableBit);
    this->send(data);
    IHM8574_clearBit(data, IHM8574_enableBit);
    this->send(data);
}

void IHM8574::cmd(uint8_t data, uint8_t type) {
	uint8_t _send;
    _send = IHM8574_MSBnibble(data);
    this->enable(_send, type);
    _send = IHM8574_LSBnibble(data);
    this->enable(_send, type);
}

void IHM8574::_mode() {
	this->_addressrow[0] = 0x00;
	this->_addressrow[1] = 0x40;
	this->_addressrow[2] = this->_col;
	this->_addressrow[3] = this->_col + 0x40;
}

//public:
size_t IHM8574::write(uint8_t data) {
	this->cmd(data, IHM8574_data);
	return 1;
}

size_t IHM8574::write(const char *s) {
	while(*s != '\0') {
		this->cmd(*s++, IHM8574_data);
	}
	return 1;
}

size_t IHM8574::write(const uint8_t *s, size_t lenght) {
	while(lenght--) {
		this->cmd(*s++, IHM8574_data);
	}
	return 1;
}

void IHM8574::clear() {
	this->cmd(0x01, IHM8574_command);
	_delay_us(2000);
}

void IHM8574::home() {
	this->cmd(0x02, IHM8574_command);
	_delay_us(2000);
}
void IHM8574::cursor(uint8_t mode) {
	this->cmd(mode, IHM8574_command);
}

void IHM8574::display(uint8_t state) {
	_delay_us(2000);
	this->clear();
	if(state) {
		this->cmd(0x0C, IHM8574_command);
		_delay_us(2000);
		this->init();
	}
	else {
		cmd(0x08, IHM8574_command);
		_delay_us(4500);
	}
}

void IHM8574::toleft() { 
	cmd(0x18, IHM8574_command);
}

void IHM8574::toright() {
	cmd(0x1C, IHM8574_command);
}

void IHM8574::set(uint8_t col, uint8_t row) {
	size_t max_lines = sizeof(this->_addressrow) / sizeof(*_addressrow);
	if(row >= max_lines)
		row = max_lines - 1;
	if(row >= _col)
		row = _col - 1;
	uint8_t aux = 0x80 | (col + this->_addressrow[row]);
	this->cmd(aux, IHM8574_command);
}

void IHM8574::backlight(uint8_t state) {
	this->_backlight = state;
	this->cmd(0x00, IHM8574_command);
}

void IHM8574::create(uint8_t location, uint8_t charmap[]) {
	location &= 0x7;
	this->cmd(0x40 | (location << 3),1);
	for (int i=0; i<8; i++) {
		this->write(charmap[i]);
	}
}

void IHM8574::create(uint8_t location, uint8_t charmap, uint8_t interator) {
	if(!interator) {
		location &= 0x7;
		this->cmd(0x40 | (location << 3), IHM8574_command);
	}
	this->write(charmap);
}
