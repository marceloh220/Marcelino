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


#include "analog.h"

marcelino_PTRFunc AnalogArray[2] = {none,none};

Analog::Analog(uint8_t Vref) {
	PRR &= ~bv(PRADC);
	this->_Vref = Vref&0x03;
	this->_prescale = 6;
}

void Analog::aref(uint8_t Vref) {
	this->_Vref = Vref&0x03;	
}

void Analog::prescale(uint8_t scale) {
	if(scale==2)
		scale=1;
	else if(scale==4)
		scale=2;
	else if(scale==8)
		scale=3;
	else if(scale==16)
		scale=4;
	else if(scale==32)
		scale=5;
	else if(scale==64)
		scale=6;
	else if(scale==128)
		scale=7;
	this->_prescale = scale;
}

uint16_t Analog::read(uint8_t pin) {
	if (pin > 5)
		return 0;
	DIDR0 |= bv(pin);
	ADMUX = (this->_Vref<<REFS0)|pin;
    ADCSRA = bv(ADEN)|bv(ADSC)|this->_prescale;
    while(ADCSRA & bv(ADSC));
    uint16_t _adc = ADC;
    DIDR0 &= ~bv(pin);
    return _adc;
}

uint16_t Analog::read(uint8_t pin, uint8_t ref) {
	ref = ref&0x03;
	if (pin > 5 && pin != 8)
		return 0;
	DIDR0 |= bv(pin);
	ADMUX = (ref<<REFS0)|pin;
    ADCSRA = bv(ADEN)|bv(ADSC)|this->_prescale;
    while(ADCSRA & bv(ADSC));
    uint16_t _adc = ADC;
    DIDR0 &= ~bv(pin);
    return _adc;
}

void Analog::read(uint8_t pin, void (*funct)(void)) {
	if(ADCSRA & bv(ADSC))
		return 0;
	if (pin > 5)
		return 0;
	AnalogArray[1] = funct;
	DIDR0 |= bv(pin);
	ADMUX = (this->_Vref<<REFS0)|pin;
    ADCSRA = bv(ADEN)|bv(ADSC)|bv(ADIE)|this->_prescale;
}

void Analog::read(uint8_t pin, uint8_t ref, void (*funct)(void)) {
	if(ADCSRA & bv(ADSC))
		return 0;
	if (pin > 5)
		return 0;
	AnalogArray[1] = funct;
	ref = ref&0x03;
	DIDR0 |= bv(pin);
	ADMUX = (ref<<REFS0)|pin;
    ADCSRA = bv(ADEN)|bv(ADSC)|bv(ADIE)|this->_prescale;
}


float Analog::temp() {
	 return ( ( read(8,INTERNAL) - 314.31 ) / 1.22);
}

void Analog::attach(uint8_t mode, void (*funct)(void)) {
	AnalogArray[0] = funct;
	if(mode == FALLING)
		ACSR = bv(ACIE)|bv(ACIS1);
	else if(mode == RISING)
		ACSR = bv(ACIE)|3;
	sei();
}

void Analog::attach(uint8_t mode, uint8_t reference, void (*funct)(void)) {
	AnalogArray[0] = funct;
	if(mode == FALLING)
		ACSR = bv(ACIE)|bv(ACIS1);
	else if(mode == RISING)
		ACSR = bv(ACIE)|3;
	if(reference == INTERNAL)
		ACSR |= bv(ACBG);
	sei();
}

void Analog::detach(uint8_t interrupt) {
	if(interrupt == COMP) {
		AnalogArray[0] = none;
		ACSR = bv(ACD);
	}
	else if(interrupt == ADC) {
		AnalogArray[0] = none;
		ADMUX = 0;
		ADCSRA = 0;
	}
}

uint8_t Analog::falling() {
	 return ( ACSR &bv(ACIS1) ) && ( !( ACSR & bv(ACIS0) ) );
}

uint8_t Analog::rising() {
	return ( ACSR &bv(ACIS1) ) && ( ACSR & bv(ACIS0) );
}

uint8_t Analog::change() {
	return !( ACSR &bv(ACIS1) ) && ( ACSR & bv(ACIS0) );
}

ISR(ANALOG_COMP_vect) {
	sregSAVE = SREG;
	AnalogArray[0]();
}

ISR(ANALOG_ADC_vect) {
	sregSAVE = SREG;
	AnalogArray[1]();
}
