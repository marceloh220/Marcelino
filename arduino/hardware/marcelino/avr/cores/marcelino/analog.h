#ifndef ANALOG_H
#define ANALOG_H

#include "defines.h"

class Analog {
private:
	uint8_t _Vref, _prescale;
public:
	Analog(uint8_t Vref = DEFAULT);

	//to config ADC
	void aref(uint8_t ref);
	void prescale(uint8_t scale);

	//to read analogics
	uint16_t read(uint8_t pin);
	uint16_t read(uint8_t pin, uint8_t ref);
	double temp();

	//interrupt of comparator
	void attach(uint8_t mode, VoidFuncPtr funct);
	void attach(uint8_t mode, uint8_t reference, VoidFuncPtr funct);
	void detach();
	
	//tests of comparator
	uint8_t falling();
	uint8_t rising();
	uint8_t change();

};

#endif
