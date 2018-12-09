 /*
	Author: Marcelo H Moraes
	marceloh220@hotmail.com
	Application: Display lcd 16x2 HD44780 based with 74LS595 bit shift.
 

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
 
 
#ifndef IHM8574_H
#define IHM8574_H

#include <defines.h>
#include <twi.h>
#include <Print.h>

#define noCURSOR 		0x0C
#define blinkCURSOR  	0x0D
#define onCURSOR	    0x0E
#define alternateCURSOR 0x0F

class IHM8574 : private TWI, public Print {
private:
	uint8_t _backlight;
	uint8_t _address;
	uint8_t _row, _col;
	uint8_t _addressrow[4];
	void send(uint8_t);
	void enable(uint8_t, uint8_t);
	void cmd(uint8_t, uint8_t);
	void _mode();
public:
	IHM8574(uint8_t);
	virtual size_t write(uint8_t);
	virtual size_t write(const char*);
	virtual size_t write(const uint8_t*, size_t);
	using Print::write;
	void init();
	inline void config(uint8_t, uint8_t);
	void clear();
	void home();
	void cursor(uint8_t);
	void display(uint8_t);
	inline void toleft();
	inline void toright();
	void set(uint8_t, uint8_t);
	void backlight(uint8_t);
	void create(uint8_t, uint8_t*);
	void create(uint8_t, uint8_t, uint8_t);
};

#endif
