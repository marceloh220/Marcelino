#ifndef BITS16_H
#define BITS16_H

#include <defines.h>
#include <digital.h>

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

class Bits16 : private Digital {
private:
	uint8_t _clock, _data;
	uint16_t _ports;
	const uint8_t segments[10] ={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
	void send(uint16_t dado);
public:
	Bits16(uint8_t clock, uint8_t data);
	void begin();
	uint16_t out(uint8_t __port, uint8_t __state);
	void print(uint16_t __number);
	void dot(uint8_t __unit);
	
};
#endif
