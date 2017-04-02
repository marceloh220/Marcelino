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


#ifndef AT24C32_H
#define AT32C32_H

#include "defines.h"
#include "twi.h"

class AT24C32 : private TWI {
private:
	volatile uint8_t addr_w = 0xA0;
	volatile uint8_t addr_r = 0xA1;
public:
	AT24C32(volatile uint16_t addr = 0);
	void device(volatile uint8_t addr);
	uint8_t read(volatile uint16_t addr);
	void write(uint8_t data, volatile uint16_t addr);
	void update(uint8_t data, volatile uint16_t addr);
	uint8_t get(volatile uint16_t addr);
	uint8_t get(volatile uint8_t ack = ACK);
	void put(uint8_t data, volatile uint16_t addr);
	void put(uint8_t data);
	void stop();
};


#endif
