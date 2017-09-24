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
	this->reference(1);
}

Analog::Analog(uint8_t Vref) {
	PRR &= ~bv(PRADC);
	this->reference(Vref);
	this->_prescale = 6;
}

void Analog::reference(uint8_t Vref) {
	this->_Vref = Vref;
	#ifdef ATTINY
	ADMUX &= ~(bv(REFS2)|bv(REFS1)|bv(REFS0));
	#else
	ADMUX &= ~(bv(REFS1)|bv(REFS0));
	#endif
	switch(Vref) {
		#ifdef ATTINY
		case EXTERNAL:
			ADMUX |= bv(REFS0);
			break;
		case DEFAULT:
			break;
		case INTERNAL1V1:
			ADMUX |= bv(REFS1);
			break;
		case INTERNAL2V5:
			ADMUX |= bv(REFS2)|bv(REFS1);
			break;
		#else
		case EXTERNAL:
			break;
		case DEFAULT:
			ADMUX |= bv(REFS0);
			break;
		case INTERNAL:
			ADMUX |= bv(REFS1)|bv(REFS0);
			break;
		#endif
	}
	_delay_ms(10);
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
	if (pin>7)
		return 0;
	ADMUX &= ~(bv(MUX3)|bv(MUX2)|bv(MUX1)|bv(MUX0));
	ADMUX |= pin;
    ADCSRA = bv(ADEN)|bv(ADSC)|_prescale;
    while(ADCSRA & bv(ADSC));
    uint16_t _adc = ADC;
    return _adc;
}

uint16_t Analog::read(uint8_t pin, uint8_t ref) {
	uint8_t SVref = this->_Vref;
	if (pin>7)
		return 0;
	this->reference(ref);
	ADMUX &= ~(bv(MUX3)|bv(MUX2)|bv(MUX1)|bv(MUX0));
	ADMUX |= pin;
    ADCSRA = bv(ADEN)|bv(ADSC)|_prescale;
    while(ADCSRA & (1<<ADSC));
    uint16_t _adc = ADC;
    this->reference(SVref);
    return _adc;
}

float Analog::temp() {
	#ifdef ATTINY
	return ( ( this->read(15,INTERNAL1V1) - 314.31 ) / 1.22);
	#else
	return ( ( this->read(8,INTERNAL) - 314.31 ) / 1.22);
	#endif
}

void Analog::attach(uint8_t interrupt, uint8_t mode, void (*funct)(void)) {
	if(interrupt == COMP) {
		ADCSRA&=~bv(ADEN);
		ADCSRB &= ~bv(ACME);
		AnalogArray[0] = funct;
		if(mode == FALLING)
			ACSR = bv(ACIE)|bv(ACIS1);
		else if(mode == RISING)
			ACSR = bv(ACIE)||bv(ACIS1)|bv(ACIS0);
		else if(mode == TOGGLE)
			ACSR = bv(ACIE);
	}
	else {
		AnalogArray[1] = funct;
		ADMUX &= ~(bv(MUX3)|bv(MUX2)|bv(MUX1)|bv(MUX0));
		ADMUX |= mode;
		ADCSRA = bv(ADEN)|bv(ADSC)|bv(ADIE)|_prescale;
	}
	sei();
}

void Analog::attach(uint8_t interrupt, uint8_t mode, uint8_t reference, void (*funct)(void)) {
	if(interrupt == COMP) {
		ADCSRA&=~bv(ADEN);
		ADCSRB &= ~bv(ACME);
		AnalogArray[0] = funct;
		if(mode == FALLING)
			ACSR = bv(ACIE)|bv(ACIS1);
		else if(mode == RISING)
			ACSR = bv(ACIE)|bv(ACIS1)|bv(ACIS0);
		else if(mode == TOGGLE)
			ACSR = bv(ACIE);
		if(reference == INTERNAL) {
			ACSR |= bv(ACBG);
			_delay_ms(10);
		}
	}
	else {
		AnalogArray[1] = funct;
		this->reference(reference);
		ADMUX &= ~(bv(MUX3)|bv(MUX2)|bv(MUX1)|bv(MUX0));
		ADMUX |= mode;
		ADCSRA = bv(ADEN)|bv(ADSC)|bv(ADIE)|_prescale;
	}
	sei();
}

void Analog::detach(uint8_t interrupt) {
	if(interrupt == COMP) {
		AnalogArray[0] = none;
		ACSR = bv(ACD);
	}
	else {
		AnalogArray[0] = none;
		ADMUX &= ~(bv(MUX3)|bv(MUX2)|bv(MUX1)|bv(MUX0));
		ADCSRA = 0;
	}
}

#ifndef ATTINY
ISR(ANALOG_COMP_vect) {
	sregSAVE = SREG;
	AnalogArray[0]();
}

ISR(ANALOG_ADC_vect) {
	sregSAVE = SREG;
	AnalogArray[1]();
}
#else
ISR(ANA_COMP_vect) {
	sregSAVE = SREG;
	AnalogArray[0]();
}

ISR(ADC_vect) {
	sregSAVE = SREG;
	AnalogArray[1]();
}
#endif
