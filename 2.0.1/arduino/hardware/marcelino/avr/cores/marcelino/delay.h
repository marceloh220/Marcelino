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


#ifndef DELAY_H
#define DELAY_H

#ifndef F_CPU
# warning "F_CPU not defined, using 1MHz"
# define F_CPU 1000000UL
#endif

#ifndef __OPTIMIZE__
# warning "Compiler optimizations disabled; functions from delay module won't work as designed"
#endif

#include "defines.h"
#define __DELAY_BACKWARD_COMPATIBLE__

class Delay {
private:
	inline void loop_us(uint8_t);
	inline void loop_ms(uint16_t);
public:
	void us(double);
	void ms(double);
};

#endif
