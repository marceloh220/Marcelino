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


#include "serial.h"

#ifndef NOSERIAL

Serial::Serial(uint16_t rate) {
	PRR &= ~(1<<PRUSART);
	UBRR0H = (uint8_t)(F_CPU/16/rate-1)>>8;
	UBRR0L = (uint8_t)(F_CPU/16/rate-1);
	UCSR0B = bv(RXEN0)|bv(TXEN0);
	UCSR0C = bv(UCSZ01)|bv(UCSZ00);
}

void Serial::mode(uint8_t mode) {
	UCSR0C &= ~(bv(UMSEL01)|bv(UMSEL00));
	if(mode == SYNCHRON) {
		UCSR0C |= bv(UMSEL00);
		XCLK_DDR |= bv(XCLK_PIN);
	}
}

void Serial::bit(uint8_t bits) {
	UCSR0C &= ~(bv(UCSZ01)|bv(UCSZ00));
	UCSR0B &= ~bv(UCSZ02);
	switch(bits) {
		case 5:
			break;
		case 6:
			UCSR0C |= bv(UCSZ00);
			break;
		case 7:
			UCSR0C |= bv(UCSZ01);
			break;
		case 8:
			UCSR0C |= bv(UCSZ01)|bv(UCSZ00);
			break;
		case 9:
			UCSR0C |= bv(UCSZ01)|bv(UCSZ00);
			UCSR0B |= bv(UCSZ02);
			break;
	}
}

void Serial::stop(uint8_t bit) {
	UCSR0C &= ~bv(USBS0);
	if(bit>1)
		UCSR0C |= bv(USBS0);
}

void Serial::parity(uint8_t mode) {
	UCSR0C &= ~(bv(UPM01)|bv(UPM00));
	if(mode == EVEN)
		UCSR0C |= bv(UPM01);
	if(mode == ODD)
		UCSR0C |= bv(UPM01)|bv(UPM00);
}

void Serial::baud(uint16_t rate) {
	if(UCSR0C & bv(UMSEL00)) {
		UBRR0H = (uint8_t)(F_CPU/2/rate-1)>>8;
		UBRR0L = (uint8_t)(F_CPU/2/rate-1);
	}
	else {
		UBRR0H = (uint8_t)(F_CPU/16/rate-1)>>8;
		UBRR0L = (uint8_t)(F_CPU/16/rate-1);
	}
}

size_t Serial::write(uint8_t d) {
	while(!(UCSR0A & bv(UDRE0)));
	UDR0 = d;
	return 0;
}

size_t Serial::write(const char *s) {

	while(*s) {
		while(!(UCSR0A & bv(UDRE0)));
		UDR0 = *s++;
	}
	return 0;
}

size_t Serial::write(const uint8_t *s, size_t l) {
	while(l--) {
		while(!(UCSR0A & bv(UDRE0)));
		UDR0 = *s++;
	}
	return 0;
}

uint8_t Serial::read() {
	while(!(UCSR0A & bv(RXC0)));
	return UDR0;
}

Serial Serial::operator<<(const char *s) {
	Print::print(s);
}

Serial Serial::operator<<(uint8_t s) {
	Print::print(s);
}

Serial Serial::operator<<(uint16_t s) {
	Print::print(s);
}

Serial Serial::operator<<(uint32_t s) {
	Print::print(s);
}

Serial Serial::operator<<(float s) {
	Print::print(s);
}

Serial Serial::operator<<(int s) {
	Print::print(s);
}

Serial Serial::operator<<(long s) {
	Print::print(s);
}

#endif
