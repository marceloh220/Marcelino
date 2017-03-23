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

VoidFuncPtr AnalogArray = none;

Analog::Analog(uint8_t Vref) {
	PRR &= ~(1<<PRADC);
	_Vref = Vref&0x03;
	_prescale = 6;
}

void Analog::aref(uint8_t Vref) {
	_Vref = Vref&0x03;	
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
	_prescale = scale;
}

uint16_t Analog::read(uint8_t pin) {
	if (pin > 5)
		return 0;
	DIDR0 |= (1<<pin);
	ADMUX = (_Vref<<REFS0)|pin;
    ADCSRA = (1<<ADEN)|(1<<ADSC)|_prescale;
    while(ADCSRA & (1<<ADSC));
    uint16_t _adc = ADC;
    DIDR0 &= ~(1<<pin);
    return _adc;
}

uint16_t Analog::read(uint8_t pin, uint8_t ref) {
	ref = ref&0x03;
	if (pin > 5 && pin != 8)
		return 0;
	DIDR0 |= (1<<pin);
	ADMUX = (ref<<REFS0)|pin;
	_delay_ms(10);
    ADCSRA = (1<<ADEN)|(1<<ADSC)|_prescale;
    while(ADCSRA & (1<<ADSC));
    uint16_t _adc = ADC;
    DIDR0 &= ~(1<<pin);
    return _adc;
}

double Analog::temp() {
	 return ( ( read(8,INTERNAL) - 314.31 ) / 1.22);
}

void Analog::attach(uint8_t mode, VoidFuncPtr funct) {
	AnalogArray = funct;
	if(mode == FALLING)
		ACSR = (1<<ACIE)|(1<<ACIS1);
	else if(mode == RISING)
		ACSR = (1<<ACIE)|3;
	sei();
}

void Analog::attach(uint8_t mode, uint8_t reference, VoidFuncPtr funct) {
	AnalogArray = funct;
	if(mode == FALLING)
		ACSR = (1<<ACIE)|(1<<ACIS1);
	else if(mode == RISING)
		ACSR = (1<<ACIE)|3;
	if(reference == INTERNAL)
		ACSR |= (1<<ACBG);
	sei();
}

void Analog::detach() {
	AnalogArray = none;
	ACSR = (1<<ACD);
}

uint8_t Analog::falling() {
	 return ( ACSR &(1<<ACIS1) ) && ( !( ACSR & (1<<ACIS0) ) );
}

uint8_t Analog::rising() {
	return ( ACSR &(1<<ACIS1) ) && ( ACSR & (1<<ACIS0) );
}

uint8_t Analog::change() {
	return !( ACSR &(1<<ACIS1) ) && ( ACSR & (1<<ACIS0) );
}

ISR(ANALOG_COMP_vect) {
	sregSAVE = SREG;
	AnalogArray();
}
