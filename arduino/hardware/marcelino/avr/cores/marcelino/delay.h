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
