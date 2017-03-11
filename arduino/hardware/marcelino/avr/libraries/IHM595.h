/*
*Comments in PT-BR:
*	Author: Marcelo H Moraes
*	marceloh220@hotmail.com
*	Application: Display lcd 16x2 HD44780 based with 74LS595 bit shift.
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
	void send(uint8_t d);
	void cmd(uint8_t d, uint8_t c);
public:
	IHM595(uint8_t data, uint8_t clock, uint8_t enable);
	virtual size_t write(uint8_t c);
	virtual size_t write(const char *s);
	virtual size_t write(const uint8_t *s, size_t l);
	using Print::write;
	void init();
	void clear();
	void home();
	void cursor(uint8_t mode);
	void display(uint8_t state);
	void set(uint8_t col, uint8_t lin);
	void background(uint8_t state);
};

#endif
