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


#include "AT24C32.h"

AT24C32::AT24C32(volatile uint16_t addr) {
	device(addr);
}

void AT24C32::device(volatile uint8_t addr) {
	addr=addr<<1;
	addr_w |= (addr&0x0E);
	addr_r |= (addr&0x0E);
}

uint8_t AT24C32::read(volatile uint16_t addr) {
	TWI::start();
	TWI::send(addr_w);
	TWI::send(addr>>8);
	TWI::send(addr&0xFF);
	TWI::start();
	TWI::send(addr_r);
	uint8_t aux = TWI::recive(NACK);
	TWI::stop();
	return aux;
}

void AT24C32::write(volatile uint8_t data, volatile uint16_t addr) {
	TWI::start();
	TWI::send(addr_w);
	TWI::send(addr>>8);
	TWI::send(addr&0x00FF);
	TWI::send(data);
	TWI::stop();
	_delay_ms(10);
}

void AT24C32::update(volatile uint8_t data, volatile uint16_t addr) {
	uint8_t aux = read(addr);
	if(aux!=data)
		write(data,addr);
}

uint8_t AT24C32::get(volatile uint16_t addr) {
	TWI::start();
	TWI::send(addr_w);
	TWI::send(addr>>8);
	TWI::send(addr&0x00FF);
	TWI::start();
	TWI::send(addr_r);
	return TWI::recive(ACK);
}

uint8_t AT24C32::get(volatile uint8_t ack) {
	if(ack)
		return TWI::recive(ACK);
	else
		return TWI::recive(NACK);
}

void AT24C32::put(volatile uint8_t data, volatile uint16_t addr) {
	TWI::start();
	TWI::send(addr_w);
	TWI::send(addr>>8);
	TWI::send(addr&0x00FF);
	TWI::send(data);
}

void AT24C32::put(volatile uint8_t data) {
	TWI::send(data);
}

void AT24C32::stop() { 
	TWI::stop();
}
