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
