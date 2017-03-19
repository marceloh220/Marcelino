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

#ifndef BITS16_H
#define BITS16_H

#include "defines.h"
#include "digital.h"

#define P0 		0
#define P1 		1
#define P2 		2
#define P3 		3
#define P4 		4
#define P5 		5
#define P6 		6
#define P7 		7
#define P8 		8
#define P9 		9
#define P10 	10
#define P11 	11
#define P12 	12
#define P13 	13
#define P14 	14
#define P15 	15

#define TEN 1
#define UNIT 0

const uint8_t PROGMEM bits16_segments[10] ={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

class Bits16 : private Digital {
private:
	uint8_t _clock, _data;
	uint16_t _ports;
	void send(uint16_t dado);
public:
	Bits16(uint8_t clock, uint8_t data);
	uint16_t out(uint8_t __port, uint8_t __state);
	void print(uint16_t __number);
	void dot(uint8_t __unit);
	
};
#endif
