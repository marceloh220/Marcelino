/*
  Copyright (c) 2017 Marcelo Henrique Moraes

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3.0 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.
 */


#include "csleep.h"

void Sleep::sleep(uint8_t mode) {
	set_sleep_mode(mode);
	cli();
	sleep_enable();
#if defined (__AVR_ATmega328__) || (__AVR_ATmega328P__)
	sleep_bod_disable();
#endif
    sei();
    sleep_cpu();
}

void Sleep::disable(uint8_t hardware) {
	if(hardware==SLEEP)
		sleep_disable();
	else if(hardware == ALL)
		PRR = 0xFF;
	else
		PRR |= (1<<hardware);
}

void Sleep::enable(uint8_t hardware) {
	if(hardware==SLEEP)
		sleep_enable();
	else if(hardware == ALL)
		PRR = 0x00;
	else
		PRR &= ~(1<<hardware);	
}
