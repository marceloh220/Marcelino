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


#ifndef DIGITAL_H
#define DIGITAL_H

#include "defines.h"

class Digital {
public:
	void mode(uint8_t _pin, uint8_t _mode);
	void write(uint8_t _pin, uint8_t _state);
	uint8_t read(uint8_t _pin);
	inline void port(volatile uint8_t* _port, uint8_t _data) { *_port = _data; }
	inline uint8_t port(volatile uint8_t* _port) { return *_port;	}
	inline void set(volatile uint8_t* _port, uint8_t _bit) {	*_port|=(1<<_bit); }
	inline void clear(volatile uint8_t* _port, uint8_t _bit) { *_port&=~(1<<_bit); }
	inline void toggle(volatile uint8_t* _port, uint8_t _bit) { *_port^=(1<<_bit); }
	inline uint8_t ifset(volatile uint8_t* _port, uint8_t _bit) { return *_port&(1<<_bit); }
	inline uint8_t ifclear(volatile uint8_t* _port, uint8_t _bit) { return  !(*_port&(1<<_bit)); }
};

#endif
