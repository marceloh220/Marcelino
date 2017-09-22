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
<<<<<<< HEAD
	this->reference(1);
=======
>>>>>>> origin/master
}

Analog::Analog(uint8_t Vref) {
	PRR &= ~bv(PRADC);
	this->reference(Vref);
	this->_prescale = 6;
}

void Analog::reference(uint8_t Vref) {
<<<<<<< HEAD
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
=======
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
>>>>>>> origin/master
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
<<<<<<< HEAD
	ADMUX &= ~(bv(MUX3)|bv(MUX2)|bv(MUX1)|bv(MUX0));
	ADMUX |= pin;
    ADCSRA = bv(ADEN)|bv(ADSC)|_prescale;
    while(ADCSRA & bv(ADSC));
    uint16_t _adc = ADC;
=======
	DIDR0 |= bv(pin);
	ADMUX = (_Vref<<REFS0)|pin;
	_delay_ms(10);
    ADCSRA = bv(ADEN)|bv(ADSC)|_prescale;
    while(ADCSRA & bv(ADSC));
    uint16_t _adc = ADC;
    DIDR0 &= ~bv(pin);
>>>>>>> origin/master
    return _adc;
}

uint16_t Analog::read(uint8_t pin, uint8_t ref) {
<<<<<<< HEAD
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
=======
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
>>>>>>> origin/master
	sei();
}

void Analog::detach(uint8_t interrupt) {
	if(interrupt == COMP) {
		AnalogArray[0] = none;
		ACSR = bv(ACD);
	}
<<<<<<< HEAD
	else {
		AnalogArray[0] = none;
		ADMUX &= ~(bv(MUX3)|bv(MUX2)|bv(MUX1)|bv(MUX0));
=======
	else if(interrupt == ADC) {
		AnalogArray[0] = none;
		ADMUX = 0;
>>>>>>> origin/master
		ADCSRA = 0;
	}
}

<<<<<<< HEAD
#ifndef ATTINY
ISR(ANALOG_COMP_vect) {
	sregSAVE = SREG;
	AnalogArray[0]();
}
#else
ISR(ANA_COMP_vect) {
	sregSAVE = SREG;
	AnalogArray[0]();
=======
ISR(ANALOG_COMP_vect) {
	sregSAVE = SREG;
	AnalogArray[0]();
>>>>>>> origin/master
}
#endif

<<<<<<< HEAD
ISR(ADC_vect) {
=======
ISR(ANALOG_ADC_vect) {
>>>>>>> origin/master
	sregSAVE = SREG;
	AnalogArray[1]();
}
