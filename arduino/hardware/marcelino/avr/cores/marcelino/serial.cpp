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
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (3<<UCSZ00);
}

void Serial::mode(uint8_t _mode) {
		UCSR0C &= ~(3<<UMSEL01);
		UCSR0C |= (_mode<<UMSEL00);
		this->test_mode = 0;
		if(_mode) {
			XCLK_DDR|=(1<<XCLK_PIN);
			this->test_mode = 1;
		}
}

void Serial::bits(uint8_t bit) {
	UCSR0C &= ~(3<<UCSZ00);
	UCSR0B &= ~(1<<UCSZ02);
	if(bit==5) return;
	else if(bit==6)
		UCSR0C |= (1<<UCSZ00);
	else if(bit==7)
		UCSR0C |= (2<<UCSZ00);
	else if(bit==8)
		UCSR0C |= (3<<UCSZ00);
	else {
		UCSR0C |= (3<<UCSZ00);
		UCSR0B |= (1<<UCSZ02);
	}
}

void Serial::stop(uint8_t bit) {
	UCSR0C &= ~(1<<USBS0);
	if(bit>1)
		UCSR0C |= (1<<USBS0);
}

void Serial::parity(uint8_t _mode) {
		UCSR0C &= ~(3<<UPM00);
		UCSR0C |= (_mode<<UPM00);
}

void Serial::baud(uint16_t rate) {
	if(this->test_mode) {
		UBRR0H = (uint8_t)(F_CPU/2/rate-1)>>8;
		UBRR0L = (uint8_t)(F_CPU/2/rate-1);
	}
	else {
		UBRR0H = (uint8_t)(F_CPU/16/rate-1)>>8;
		UBRR0L = (uint8_t)(F_CPU/16/rate-1);
	}
}

size_t Serial::write(uint8_t d) {
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = d;
	return 0;
}

size_t Serial::write(const char *s) {

	while(*s) {
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *s++;
	}
	return 0;
}

size_t Serial::write(const uint8_t *s, size_t l) {
	while(l--) {
		while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = *s++;
	}
	return 0;
}

uint8_t Serial::read() {
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}


#endif
