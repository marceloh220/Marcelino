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
