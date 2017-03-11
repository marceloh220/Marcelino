#ifndef SPI_H
#define SPI_H

#include "defines.h"
#include "Print.h"

class Spi : public Print {
private:
	void prescale(uint8_t scale);
public:

	Spi(uint8_t mode = MASTER, uint8_t scale = 16);
	void order(uint8_t mode);
	uint8_t send(uint8_t data);
	uint8_t recive();
	uint8_t transcive(uint8_t data);
	virtual size_t write(uint8_t c);
	virtual size_t write(const char *s);
	virtual size_t write(const uint8_t *s, size_t l);
	using Print::write;
	

	
	
};




#endif
