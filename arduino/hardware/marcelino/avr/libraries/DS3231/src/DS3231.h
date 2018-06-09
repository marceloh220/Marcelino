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


#ifndef DS3231_h
#define DS3231_h

#include "defines.h"
#include "twi.h"
#include "cmath.h"

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

#define	en_us		1
#define pt_br		2


class DS3231 : private TWI, private Math {
private:
	uint8_t pos = 0, _language;

	const char* _weeken[8] = 		{
									"   ",
									"SUN",
									"MON",
									"TUE",
									"WED",
									"THU",
									"FRI",
									"SAT",
								};
	const char* _monthen[13] = 	{
									"   ",
									"JAN",
									"FEB",
									"MAR",
									"APR",
									"MAY",
									"JUN",
									"JUL",
									"AUG",
									"SEP",
									"OCT",
									"NOV",
									"DEC",
								};
	const char* _weekpt[8] = 		{
									"   ",
									"DOM",
									"SEG",
									"TER",
									"QUA",
									"QUI",
									"SEX",
									"SAB",
								};
	const char* _monthpt[13] = 	{
									"   ",
									"JAN",
									"FEV",
									"MAR",
									"ABR",
									"MAI",
									"JUN",
									"JUL",
									"AGO",
									"SET",
									"OUT",
									"NOV",
									"DEZ",
								};

	uint8_t get(uint8_t address);
	void put(uint8_t data, uint8_t address);
public:
	DS3231(uint8_t lng = en_us);
	void language(uint8_t lng);
	uint8_t second(uint8_t data = 255);
	uint8_t minute(uint8_t data = 255);
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
