#ifndef SHIFT_H
#define SHIFT_H

#include <defines.h>
#include <digital.h>

class Shift : private Digital {
private:
	uint8_t clock_pin, data_pin, enable_pin, _mode;
	void init(uint8_t data, uint8_t clock);
	void init(uint8_t data, uint8_t clock, uint8_t enable);
	void clock();
	void enable();
	void sendByte(uint8_t _data, uint8_t first);
	void sendWord(uint16_t _data, uint8_t first);
public:
	Shift(uint8_t data, uint8_t clock);
	Shift(uint8_t data, uint8_t clock, uint8_t enable);
	void send(uint8_t _data, uint8_t first);
	void send(uint16_t _data, uint8_t first);
	void ack();
};


#endif
