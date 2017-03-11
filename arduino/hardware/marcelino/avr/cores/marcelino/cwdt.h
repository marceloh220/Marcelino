#ifndef CWDT_H
#define CWDT_H

#include "defines.h"

VoidFuncPtr wdtARRAY = none;

class WDT {
	
public:
	WDT(uint8_t timeout = 7) {
		if(timeout>9)
			timeout=7;
		wdt_reset();
		wdt_enable(timeout);
	}
	inline void clear() {  wdt_reset();}
	inline void off() { wdt_disable();}
	void on(uint8_t timeout = 7) {
		if(timeout>9)
			timeout=7;
		WDTCSR &= ~(1<<WDIE);
		wdt_reset();
		wdt_enable(timeout);
	}
	void attach(VoidFuncPtr func) {
		wdtARRAY = func;
		WDTCSR |= (1<<WDIE);
		sei();
	}
};

ISR(WDT_vect) {
	wdtARRAY();
}

#endif
