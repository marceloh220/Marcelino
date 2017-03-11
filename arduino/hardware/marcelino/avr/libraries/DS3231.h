#ifndef DS3231_h
#define DS3231_h

#include <defines.h>
#include <wire.h>
#include <cmath.h>

#define A1IE		0
#define A2IE		1
#define INTCN		2
#define RS1			3
#define RS2			4
#define CONV		5
#define BBSQW		6
#define EOSC		7

#define A1F			0
#define A2F			1
#define	BSY			2
#define	EN32kHz		3
#define OSF			7

class DS3231 : private Wire, private Math {
private:
	uint8_t pos = 0;
	const char* _week[8] = 		{
									"   ",
									"sun",
									"mon",
									"tue",
									"wed",
									"thu",
									"fri",
									"sat",
								};
	const char* _month[13] = 	{
									"   ",
									"jan",
									"feb",
									"mar",
									"apr",
									"may",
									"jun",
									"jul",
									"aug",
									"sep",
									"oct",
									"nov",
									"dec",
								};

	uint8_t get(uint8_t address);
	void put(uint8_t data, uint8_t address);
public:
	DS3231();
	uint8_t sec(uint8_t data = 255);
	uint8_t min(uint8_t data = 255);
	uint8_t hour(uint8_t data = 255);
	uint8_t week(uint8_t data = 255);
	uint8_t day(uint8_t data = 255);
	uint8_t month(uint8_t data = 255);
	uint8_t year(uint8_t data = 255);
	float temp();
	char* weekSTR();
	char* monthSTR();
	uint8_t control(uint8_t data);
	uint8_t control();
	uint8_t status(uint8_t data);
	uint8_t status();
	uint8_t busy();
	uint8_t stoped();
	void wave(uint8_t scale);
	void k32(uint8_t status);
	uint8_t push(uint8_t _data);
	uint8_t pop();
	uint8_t ram(uint8_t address);
	uint8_t ram(uint8_t data, uint8_t address);
	void sp(uint8_t address);
};

#endif
