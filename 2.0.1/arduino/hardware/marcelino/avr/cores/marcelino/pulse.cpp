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


#include "pulse.h"

uint32_t Pulse::count(Gpio_type GPIO, uint8_t bit, uint8_t stateMask, uint32_t maxloops) {
     uint32_t width = 0;
     // wait for any previous pulse to end
     while ((GPIO->PIN & bit) == stateMask)
         if (--maxloops == 0)
             return 0;
     // wait for the pulse to start
     while ((GPIO->PIN & bit) != stateMask)
         if (--maxloops == 0)
             return 0;
     // wait for the pulse to stop
     while ((GPIO->PIN & bit) == stateMask) {
         if (++width == maxloops)
             return 0;
     }
     return width;
}

uint32_t Pulse::in(uint8_t pin, uint8_t state, uint32_t timeout) {
	Gpio_type GPIO = get_GPIO(pin);
	uint8_t bit = get_bit(pin);
	uint8_t stateMask = (state ? 1 : 0);
	uint32_t maxloops = microsecondsToClockCycles(timeout)/16;
	//uint32_t width = this->count(GPIO, bit, stateMask, maxloops);
	//asm function, more presicion
	uint32_t width = countPulseASM(GPIO->PIN, bit, stateMask, maxloops);
	if (width)
		return clockCyclesToMicroseconds(width * 16 + 16);
	else
		return 0;
}
