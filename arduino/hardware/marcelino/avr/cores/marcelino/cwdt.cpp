#include "cwdt.h"

VoidFuncPtr wdtARRAY = none;

void WDT::timeout(uint8_t time){
	cli();
	wdt_reset();
	uint8_t aux = WDTCSR&0xD8;
	wdt_enable(time);
	WDTCSR |= aux;
	sei();
}

void WDT::config(uint8_t mode) {
	_mode = mode;
	WDTCSR &= ~( (1<<WDE)|(1<<WDIE) );
	if(mode==INTERRUPT)
		WDTCSR |= (1<<WDIE);
	else if(mode==RESET)
		WDTCSR |= (1<<WDE);
	else
		WDTCSR = (1<<WDE)|(1<<WDIE);
}

void volatile WDT::attach(void (*funct)(void)) {
	wdtARRAY = funct;
	sei();
}

void WDT::detach() {
	wdtARRAY = none;
}

ISR(WDT_vect) {
	sregSAVE = SREG;
	wdtARRAY();
	SREG = sregSAVE;
}
