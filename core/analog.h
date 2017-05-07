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


#ifndef ANALOG_H
#define ANALOG_H

#include "defines.h"

class Analog {
private:
	uint8_t _Vref, _prescale;
public:
	Analog(uint8_t Vref = DEFAULT);
	~Analog() { PRR |= (1<<PRADC); }

	//to config ADC
	void aref(uint8_t ref);
	void prescale(uint8_t scale);

	//to read analogics
	uint16_t read(uint8_t pin);
	uint16_t read(uint8_t pin, uint8_t ref);
	void read(uint8_t pin, void (*funct)(void));
	void read(uint8_t pin, uint8_t ref, void (*funct)(void));
	inline uint16_t read() { return ADC; }
	inline uint8_t amux() { return ADMUX&0x0F; }
	float temp();

	//interrupt of comparator
	void attach(uint8_t mode, void (*funct)(void));
	void attach(uint8_t mode, uint8_t reference, void (*funct)(void));
	void detach(uint8_t interrupt);
	
	//tests of comparator
	uint8_t falling();
	uint8_t rising();
	uint8_t change();

};

#endif
