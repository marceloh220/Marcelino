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


#include "spi.h"

marcelino_PTRFunc SPIArray = none;

//private
void SPI::prescale(uint8_t scale) {
	
	SPCR &= ~(3<<SPR0);
	SPSR &= ~(1<<SPI2X);
	
	switch(scale) {
		case 2:
			SPSR |= (1<<SPI2X);
			break;
		case 4:
			break;
		case 8:
			SPCR |= (1<<SPR0);
			SPSR |= (1<<SPI2X);
			break;
		case 16:
			SPCR |= (1<<SPR0);
			break;
		case 32:
			SPCR |= (1<<SPR1);
			SPSR |= (1<<SPI2X);
			break;
		case 64:
			SPCR |= (3<<SPR0);
			SPSR |= (1<<SPI2X);
			break;
		case 128:
			SPCR |= (3<<SPR0);
			break;
		default:
			SPCR |= (1<<SPR0);
			break;
	}
	
}

//public

SPI::SPI(uint8_t mode, uint8_t scale) {
	
	PRR &= ~(1<<PRSPI);
	
	prescale(scale);
	
	if(mode) {
		DDR_SPI |= (1<<DD_MOSI)|(1<<DD_SCK);
		DDR_SPI &= ~(1<<DD_MISO);
		SPCR |= (1<<SPE)|(1<<MSTR);
	}
	else {
		DDR_SPI |= (1<<DD_MISO);
		DDR_SPI &= ~((1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SCK));
		SPCR |= (1<<SPE);
	}
	
}

void SPI::order(uint8_t mode) {
	if(mode)
		SPCR |= (1<<DORD);
	else
		SPCR &= ~(1<<DORD);
}

uint8_t SPI::send(uint8_t data) {
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

uint8_t SPI::recive() {
	while(!(SPSR & (1<<SPIF)));
	return SPDR;	
}

uint8_t SPI::transcive(uint8_t data) {
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

size_t SPI::write(uint8_t d) {
	send(d);
	return 1;
}

size_t SPI::write(const char *s) {
	while(*s!='\0')
		send(*s++);
	return 1;
}

size_t SPI::write(const uint8_t *s, size_t l) {
	while(l--)
		send(*s++);
	return 1;
}

void SPI::attach(void (*funct)(void)) {
	SPIArray = funct;
	SPCR |= (1<<SPIE);
	sei();
}

void SPI::detach() {
	SPIArray = none;
	SPCR &= ~(1<<SPIE);
}

ISR(SPI_STC_vect) {
	sregSAVE = SREG;
	SPIArray();
	SREG = sregSAVE;
}
