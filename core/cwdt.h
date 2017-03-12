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


#ifndef CWDT_H
#define CWDT_H

#include "defines.h"

VoidFuncPtr wdtARRAY = none;

class WDT {
	
public:
	WDT(uint8_t timeout = 7) {
		if(timeout>9)
			timeout=7;
		wdt_reset();
		wdt_enable(timeout);
	}
	inline void clear() {  wdt_reset();}
	inline void off() { wdt_disable();}
	void on(uint8_t timeout = 7) {
		if(timeout>9)
			timeout=7;
		WDTCSR &= ~(1<<WDIE);
		wdt_reset();
		wdt_enable(timeout);
	}
	void attach(VoidFuncPtr func) {
		wdtARRAY = func;
		WDTCSR |= (1<<WDIE);
		sei();
	}
};

ISR(WDT_vect) {
	wdtARRAY();
}

#endif
