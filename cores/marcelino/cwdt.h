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

class WDT {
private:
	uint8_t _mode;
public:
	
	WDT() {
		enable();
		_mode = RESET;
	}

	//to config
	void config(uint8_t mode);
	void timeout(uint8_t time);
	
	//to enable and disable
	inline void enable() { WDTCSR |= (1<<WDE); }
	inline void disable() { WDTCSR &= ~(1<<WDE); }
	
	//to reset wtd
	inline void clear() {  wdt_reset(); }
	inline void reset() {  wdt_reset(); }
	
	//to management the interrupt
	void attach(VoidFuncPtr func);
	void detach();
};

#endif
