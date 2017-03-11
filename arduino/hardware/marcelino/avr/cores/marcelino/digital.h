#ifndef DIGITAL_H
#define DIGITAL_H

#include "defines.h"

class Digital {
public:
	void mode(uint8_t _pin, uint8_t _mode);
	void write(uint8_t _pin, uint8_t _state);
	uint8_t read(uint8_t _pin);
};

#endif
