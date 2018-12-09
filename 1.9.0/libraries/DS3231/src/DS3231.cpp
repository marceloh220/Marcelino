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


#include "DS3231.h"

#define ADDR_R		0xD1
#define ADDR_W		0xD0

#define GET			0
#define PUT			1

#define SHORT		1
#define LONG		2

#define LITTLE		1
#define BIG			2
#define MIDDLE		3

#define SEC			0x00
#define MIN			0x01
#define HOUR		0x02
#define WEEK		0x03
#define DATE		0x04
#define MON			0x05
#define YEAR		0x06

#define CONTROL		0x0E
#define STATUS		0x0F

#define TEMP_INT	0x11
#define TEMP_DEC	0x12

#define RATE_1		0
#define RATE_4K		1
#define RATE_8K		2
#define RATE_32K	3

DS3231::DS3231(uint8_t lng) {
	uint8_t reg = get(CONTROL);
	reg &= ~(1<<BBSQW);
	put(reg,STATUS);
	reg = get(STATUS);
	reg &= ~(1<<EN32kHz);
	put(reg,STATUS);
	language(lng);
}

void DS3231::language(uint8_t lng) { 
		if(lng > pt_br)
			lng = en_us;
		_language = lng; 
}

uint8_t DS3231::get(uint8_t address) {
	TWI::start();
	TWI::send(ADDR_W);
	TWI::send(address);
	TWI::start();
	TWI::send(ADDR_R);
	uint8_t data = TWI::recive(NACK);
	TWI::stop();
	return data;
}

void DS3231::put(uint8_t data, uint8_t address) {
	TWI::start();
	TWI::send(ADDR_W);
	TWI::send(address);
	TWI::send(data);
	TWI::stop();	
}

//public
uint8_t DS3231::second(uint8_t data) {
	if(data != 255)
		put(Math::tobcd(data),SEC);
	return Math::todec(get(SEC));
}

uint8_t DS3231::minute(uint8_t data) {
	if(data != 255)
		put(Math::tobcd(data),MIN);
	return Math::todec(get(MIN));
}

uint8_t DS3231::hour(uint8_t data) {
	if(data != 255)
		put(Math::tobcd(data),HOUR);
	return Math::todec(get(HOUR));
}

uint8_t DS3231::week(uint8_t data) {
	if(data != 255)
		put(Math::tobcd(data),WEEK);
	return Math::todec(get(WEEK));
}

uint8_t DS3231::day(uint8_t data) {
	if(data != 255)
		put(Math::tobcd(data),DATE);
	return Math::todec(get(DATE));
}

uint8_t DS3231::month(uint8_t data) {
	if(data != 255)
		put(Math::tobcd(data),MON);
	return Math::todec(get(MON));
}

uint8_t DS3231::year(uint8_t data) {
	if(data != 255)
		put(Math::tobcd(data),YEAR);
	return Math::todec(get(YEAR));
}

float DS3231::temp() {
	uint8_t c = get(CONTROL);
	c|=(1<<CONV);
	put(c,CONTROL);
	_delay_ms(4);
	uint8_t decimal = get(TEMP_DEC)>>6;
	uint8_t integer = get(TEMP_INT);
	return integer + decimal * 0.25;
}

char* DS3231::weekSTR() {
	if (_language==en_us)
		return (char*)_weeken[week()];
	else
		return (char*)_weekpt[week()];
}

char* DS3231::monthSTR() {
	if (_language==en_us)
		return (char*)_monthen[month()];
	else
		return (char*)_monthpt[month()];
}

uint8_t DS3231::control(uint8_t data) {
	put(data,CONTROL);
	return get(CONTROL);
}

uint8_t DS3231::control() {
	return get(CONTROL);
}

uint8_t DS3231::status(uint8_t data) {
	put(data,STATUS);
	return get(STATUS);
}

uint8_t DS3231::status() {
	return get(STATUS);
}

uint8_t DS3231::busy() {
	return get(STATUS)&BSY;
}

uint8_t DS3231::stoped() {
	return get(STATUS)&OSF;
}

void DS3231::wave(uint8_t scale) {
	uint8_t reg = get(CONTROL);
	scale=scale&3;
	reg|=(1<<BBSQW)|(scale<<RS1);
	put(reg,CONTROL);
}

void DS3231::k32(uint8_t status) {
	uint8_t reg = get(STATUS);
	if(status)
		reg |= (1<<EN32kHz);
	else
		reg &= ~(1<<EN32kHz);
	put(reg,STATUS);
}

uint8_t DS3231::push(uint8_t _data) {
	if(pos>=0 && pos<7) {
		put(_data, 7 + (pos++) );
		return 0;
	}
	else
		return 1;
}

uint8_t DS3231::pop() {
	if(pos>0 && pos<8)
		return get( 7 + (--pos) );
	else
		return 0;
}

void DS3231::sp(uint8_t address) {
	if(address>=1 && address<8)
		pos=address;
}

uint8_t DS3231::ram(uint8_t address) {
	if(address>=0 && address<7)
		return get(7+address);
	else
		return 0;
}

uint8_t DS3231::ram(uint8_t _data, uint8_t address) {
	if(address>=0 && address<7) {
		put(_data,7+address);
		return 0;
	}
	else
		return 1;
}
