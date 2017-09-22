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


#ifndef SPI_H
#define SPI_H

#include "defines.h"
#include "Print.h"

class SPI : public Print {
private:
	void prescale(uint8_t scale);
public:

	//to initiate
	SPI(uint8_t mode = MASTER, uint8_t scale = 16);
	
	//to configure
	void order(uint8_t mode);
	
	//to comunication
	uint8_t send(uint8_t data);
	uint8_t recive();
	uint8_t transcive(uint8_t data);
	inline uint8_t get() {
		return SPDR;
	}
	inline void put(uint8_t data) {
		SPDR = data;
	}
	
	//to print methods
	virtual size_t write(uint8_t c);
	virtual size_t write(const char *s);
	virtual size_t write(const uint8_t *s, size_t l);
	using Print::write;
	
	//to attach or detach a function in interrupt SPI Serial Transfer Complete
	void attach(void (*funct)(void));
	void detach();
	
};




#endif
