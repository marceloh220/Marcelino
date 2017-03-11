#ifndef SERIAL_H
#define SERIAL_H

#include "defines.h"
#include <Print.h>

class Serial : public Print {
private:
	uint8_t test_mode;
public:
	Serial(uint16_t baund = 9600);
	
	//Tto config serial
	void mode(uint8_t _mode);
	void bits(uint8_t bit);
	void stop(uint8_t bit);
	void parity(uint8_t _mode);
	void bound(uint16_t rate);
	
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
