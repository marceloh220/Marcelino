#include "external.h"

VoidFuncPtr INTArray[2] = {none,none};
VoidFuncPtr PCINTArray[3] = {none,none,none};

const uint8_t digital_PCMASK[3] PROGMEM = {
	(uint16_t)&PCMSK0,
	(uint16_t)&PCMSK1,
	(uint16_t)&PCMSK2,
};

void External::attach(uint8_t pin, VoidFuncPtr funct) {
	
	uint8_t _sfr = get_sfr(pin);
	
	volatile uint8_t* port  = get_PCMASK(_sfr);
	*port |= get_bit(pin);
	PCICR |= (1<<_sfr);
	
	PCINTArray[_sfr] = funct;

	sei();
		
}


void External::attach(uint8_t interrupt, uint8_t mode, VoidFuncPtr funct) {
	
	uint8_t i = interrupt*2;
	EICRA &= ~(3<<i);

	if(mode == CHANGE)
		EICRA |= (1<<i);
	if(mode == FALLING)
		EICRA |= (2<<i);
	if(mode == RISING)
		EICRA |= (3<<i);
	
	EIMSK |= (1<<interrupt);
	INTArray[interrupt] = funct;
	
	sei();
}

void External::detachPC(uint8_t pin) {
	
	uint8_t _sfr = get_sfr(pin);
	
	volatile uint8_t* port  = get_PCMASK(_sfr);
	*port &= ~get_bit(pin);
		
	
	if(!(*port)) {
		PCICR &= ~(1<<_sfr);
		PCINTArray[_sfr] = none;
	}
	
}

void External::detachINT(uint8_t interrupt) {
	
	INTArray[interrupt] = none;
	EIMSK &= ~(1<<interrupt);
	
}


ISR(INT0_vect) {
	sregSAVE = SREG;
	INTArray[0]();
}

ISR(INT1_vect) {
	sregSAVE = SREG;
	INTArray[1]();
}

ISR(PCINT0_vect) {
	sregSAVE = SREG;
	PCINTArray[0]();
}

ISR(PCINT1_vect) {
	sregSAVE = SREG;
	PCINTArray[1]();
}

ISR(PCINT2_vect) {
	sregSAVE = SREG;
	PCINTArray[2]();
}
