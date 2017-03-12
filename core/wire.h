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


#ifndef WIRE_H
#define WIRE_H

#include "defines.h"

class Wire {
private:
	inline uint8_t status() { return TWSR & 0xF8;}
public:
	Wire(uint8_t speed = SLOW);
	Wire(uint8_t address, VoidFuncPtr funct);
	inline void start() {
		TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
		while (!(TWCR & (1<<TWINT)));
	}
	inline void stop() { TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);}
	void send(uint8_t data);
	uint8_t read(uint8_t ack = ACK);
	inline uint8_t ifaddress() { return status()&0x60;}
	inline uint8_t ifbyte() { return status()&0x80;}
	inline uint8_t ifstop() { return status()&0xA0;}
};



#endif
