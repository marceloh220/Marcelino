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


#ifndef SERIAL_H
#define SERIAL_H

#include "defines.h"

#ifndef NOSERIAL

#include <Print.h>

class Serial : public Print {
private:
	uint8_t test_mode;
public:
	Serial(uint16_t baud = 9600);
	
	//Tto config serial
	void mode(uint8_t _mode);
	void bits(uint8_t bit);
	void stop(uint8_t bit);
	void parity(uint8_t _mode);
	void baud(uint16_t rate);
	
	//virtual functions
	//that functions can be used to write in serial hardware
	//or printing with print method print() and println()
	virtual size_t write(uint8_t d);
	virtual size_t write(const char *s);
	virtual size_t write(const uint8_t *s, size_t l);
	
	//to read serial
	uint8_t read();
	
};

#endif

#endif
