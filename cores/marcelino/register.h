#ifndef REGISTER_H
#define REGISTER_H

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


class Register {
private:
	uint8_t _register;
public:
	Register(uint8_t value = 0) { _register = value; }
	
	inline void set(uint8_t bit) { _register |= (1<<bit); }
	inline void clear(uint8_t bit) { _register &= ~(1<<bit); }
	inline void toggle(uint8_t bit) { _register ^= (1<<bit); }
	
	inline uint8_t ifset(uint8_t bit) { return _register&(1<<bit); }
	inline uint8_t ifclear(uint8_t bit) { return !(_register&(1<<bit)); }
	
	inline void reg(uint8_t value) { _register = value; }
	inline uint8_t reg() {return _register; }

	//operators
	//void operator= (uint8_t &v1) { _register = v1; }
	
		
};


#endif
