#include "cwdt.h"

void (*wdtARRAY)(void) = none;

void WDT::timeout(uint8_t time){
	cli();
	wdt_reset();
	#ifdef WDTCSR
	uint8_t aux = WDTCSR&0xD8;
	wdt_enable(time);
	WDTCSR |= aux;
	#else
	uint8_t aux = WDTCR&0xD8;
	wdt_enable(time);
	WDTCR |= aux;
	#endif
	sei();
}

void WDT::config(uint8_t mode) {
	this->_mode = mode;
	#ifdef WDTCSR
	WDTCSR &= ~( (1<<WDE)|(1<<WDIE) );
	if(mode==INTERRUPT)
		WDTCSR |= (1<<WDIE);
	else if(mode==RESET)
		WDTCSR |= (1<<WDE);
	else
		WDTCSR = (1<<WDE)|(1<<WDIE);
	#else
	WDTCR &= ~( (1<<WDE)|(1<<WDIE) );
	if(mode==INTERRUPT)
		WDTCR |= (1<<WDIE);
	else if(mode==RESET)
		WDTCR |= (1<<WDE);
	else
		WDTCR = (1<<WDE)|(1<<WDIE);
	#endif
}

void WDT::attach(void (*funct)(void)) {
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
