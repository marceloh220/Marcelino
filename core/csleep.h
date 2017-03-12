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


#ifndef CSLEEP_H
#define CSLEEP_H

#include "defines.h"

#define IDLE 		SLEEP_MODE_IDLE
#define ADCNOISE 	SLEEP_MODE_ADC

#define STANDBY		SLEEP_MODE_STANDBY
#define STANDBYEXT	SLEEP_MODE_EXT_STANDBY

#define POWERDOWN	SLEEP_MODE_PWR_DOWN
#define POWERSAVE	SLEEP_MODE_PWR_SAVE

class Sleep {

public:
	void sleep(uint8_t mode = IDLE) {
		set_sleep_mode(mode);
		cli();
		sleep_enable();
		sleep_bod_disable();
        sei();
        sleep_cpu();
	}
	inline void wake() {
		sleep_disable();
	}
	
};

#endif
