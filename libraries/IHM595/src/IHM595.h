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
 
 
#ifndef IHM595_H
#define IHM595_H

#include <defines.h>
#include <digital.h>
#include <Print.h>

class IHM595 : private Digital, public Print {
private:
	uint8_t _background;
	uint8_t clock, data, enable;
	uint8_t _row, _col;
	uint8_t _addressrow[4];
	void send(uint8_t d);
	void cmd(uint8_t d, uint8_t c);
	void _mode();
public:
	IHM595(uint8_t data, uint8_t clock, uint8_t enable);
	virtual size_t write(uint8_t c);
	virtual size_t write(const char *s);
	virtual size_t write(const uint8_t *s, size_t l);
	using Print::write;
	void init();
	inline void config(uint8_t col, uint8_t row) {
		_col = col;
		_row = row;
		this->_mode();
	}
	void clear();
	void home();
	void cursor(uint8_t mode);
	void display(uint8_t state);
	void set(uint8_t col, uint8_t lin);
	void background(uint8_t state);
};

#endif
