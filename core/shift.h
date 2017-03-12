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


#ifndef SHIFT_H
#define SHIFT_H

#include "defines.h"
#include "digital.h"

class Shift : private Digital {
private:
	uint8_t clock_pin, data_pin, enable_pin, _mode;
	void init(uint8_t data, uint8_t clock);
	void init(uint8_t data, uint8_t clock, uint8_t enable);
	void clock();
	void enable();
	void sendByte(uint8_t _data, uint8_t first);
	void sendWord(uint16_t _data, uint8_t first);
public:
	Shift(uint8_t data, uint8_t clock);
	Shift(uint8_t data, uint8_t clock, uint8_t enable);
	void send(uint8_t _data, uint8_t first);
	void send(uint16_t _data, uint8_t first);
	void ack();
};


#endif
