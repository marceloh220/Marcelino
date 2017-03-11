#ifndef EXTERNAL_H
#define EXTERNAL_H

#include "defines.h"
#include "digital.h"

class External {

public:
	void attach(uint8_t _pin, VoidFuncPtr funct);
	void attach(uint8_t interrupt, uint8_t mode, VoidFuncPtr funct);
	void detachPC(uint8_t interrupt);
	void detachINT(uint8_t interrupt);
};



#endif
