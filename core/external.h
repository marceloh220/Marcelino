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


#ifndef EXTERNAL_H
#define EXTERNAL_H

#include "defines.h"
#include "digital.h"

class External {

public:
	void attach(uint8_t _pin, void (*funct)(void));
	void attach(uint8_t interrupt, uint8_t mode, void (*funct)(void));
	void detachPC(uint8_t interrupt);
	void detachINT(uint8_t interrupt);
	
	//to test external INt interrupt
	uint8_t rising(uint8_t interrupt);
	uint8_t falling(uint8_t interrupt);
	uint8_t change(uint8_t interrupt);
	uint8_t lower(uint8_t interrupt);
};



#endif
