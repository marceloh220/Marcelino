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

void (*AnalogArray[2])(void) = {none,none};

Analog::Analog() {
	PRR &= ~bv(PRADC);
	this->_Vref = 1;
	this->_prescale = 6;
}

Analog::Analog(uint8_t Vref) {
	PRR &= ~bv(PRADC);
	this->reference(Vref);
	this->_prescale = 6;
}

void Analog::reference(uint8_t Vref) {
	switch(Vref) {
		case EXTERNAL:
			this->_Vref = 0;
			break;
		case DEFAULT:
			this->_Vref = 1;
			break;
		case INTERNAL:
			this->_Vref = 3;
			break;
		default:
			this->_Vref = 1;
			break;
	}	
}

void Analog::prescale(uint8_t scale) {
	switch(scale) {
		case 2:
			this->_prescale=1;
			break;
		case 4:
			this->_prescale=2;
			break;
		case 8:
			this->_prescale=3;
			break;
		case 16:
			this->_prescale=4;
			break;
		case 32:
			this->_prescale=5;
			break;
		case 64:
			this->_prescale=6;
			break;
		case 128:
			this->_prescale=7;
			break;
		default:
			this->_prescale=6;
			break;
	}
}

uint16_t Analog::read(uint8_t pin) {
	if (pin > 5)
		return 0;
	DIDR0 |= bv(pin);
	ADMUX = (_Vref<<REFS0)|pin;
	_delay_ms(10);
    ADCSRA = bv(ADEN)|bv(ADSC)|_prescale;
    while(ADCSRA & bv(ADSC));
    uint16_t _adc = ADC;
    DIDR0 &= ~bv(pin);
    return _adc;
}

uint16_t Analog::read(uint8_t pin, uint8_t ref) {
	switch(ref) {
		case EXTERNAL:
			ref = 0;
			break;
		case DEFAULT:
			ref = 1;
			break;
		case INTERNAL:
			ref = 3;
			break;
		default:
			ref = 1;
			break;
	}
	DIDR0 |= bv(pin);
	ADMUX = (ref<<REFS0)|pin;
	_delay_ms(10);
    ADCSRA = bv(ADEN)|bv(ADSC)|_prescale;
    while(ADCSRA & (1<<ADSC));
    uint16_t _adc = ADC;
    DIDR0 &= ~bv(pin);
    return _adc;
}

void Analog::read(uint8_t pin, void (*funct)(void)) {
	if(ADCSRA & bv(ADSC))
		return 0;
	AnalogArray[1] = funct;
	DIDR0 |= bv(pin);
	ADMUX = (this->_Vref<<REFS0)|pin;
	_delay_ms(10);
    ADCSRA = bv(ADEN)|bv(ADSC)|bv(ADIE)|this->_prescale;
}

void Analog::read(uint8_t pin, uint8_t ref, void (*funct)(void)) {
	if(ADCSRA & bv(ADSC))
		return 0;
	switch(ref) {
		case EXTERNAL:
			ref = 0;
			break;
		case DEFAULT:
			ref = 1;
			break;
		case INTERNAL:
			ref = 3;
			break;
		default:
			ref = 1;
			break;
	}
	AnalogArray[1] = funct;
	DIDR0 |= bv(pin);
	ADMUX = (ref<<REFS0)|pin;
	_delay_ms(10);
    ADCSRA = bv(ADEN)|bv(ADSC)|bv(ADIE)|this->_prescale;
}

float Analog::temp() {
	 return ( ( this->read(8,INTERNAL) - 314.31 ) / 1.22);
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

ISR(ANALOG_COMP_vect) {
	sregSAVE = SREG;
	AnalogArray[0]();
}

ISR(ANALOG_ADC_vect) {
	sregSAVE = SREG;
	AnalogArray[1]();
}
