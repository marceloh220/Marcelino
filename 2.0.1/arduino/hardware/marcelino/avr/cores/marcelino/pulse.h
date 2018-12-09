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
 
 
#ifndef PULSE_H
#define PULSE_H

#include "defines.h"

#ifdef __cplusplus
extern "C"{
#endif
uint32_t countPulseASM(sfr_type port, uint8_t bit, uint8_t stateMask, uint32_t maxloops);
#ifdef __cplusplus
}
#endif

class Pulse  {

private:
	uint32_t count(Gpio_type, uint8_t, uint8_t, uint32_t);
public:
	uint32_t in(uint8_t pin, uint8_t state, uint32_t timeout = 1000);
	
};

#endif
