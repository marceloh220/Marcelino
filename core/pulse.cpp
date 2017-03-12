/*
  wiring_pulse.c - pulseIn() function
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/


#include "pulse.h"

uint32_t Pulse::in(uint8_t pin, uint8_t state, uint32_t timeout) {

	uint8_t bit = get_sfr(pin);
	volatile uint8_t* port = get_PIN(bit);
	bit = get_bit(pin);
	uint8_t stateMask = (state ? bit : 0);

	uint32_t maxloops = microsecondsToClockCycles(timeout)/16;
	uint32_t width = countPulseASM(port, bit, stateMask, maxloops);

	if (width)
		return clockCyclesToMicroseconds(width * 16 + 16);
	else
		return 0;
		
}
