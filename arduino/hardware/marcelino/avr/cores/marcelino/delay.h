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

#include "defines.h"
#define __DELAY_BACKWARD_COMPATIBLE__

class Delay {
public:

	static inline void ms(uint32_t milliseconds) {
		while(milliseconds--)
			_delay_ms(1);
	}
	static inline void us(uint32_t microseconds) {
		while(microseconds--)
			_delay_us(1);
	}

};

#endif
