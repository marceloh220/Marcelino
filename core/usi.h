#ifdef _USI_H_
#define _USI_H_

#ifdef ATTINY

#include "define.h"

class USI {

private:

public:

	USI(uint8_t mode) {
		USICR &= ~(bv(USIWM1)|bv(USIWM0));
		if(mode == TWO) {
			USICR |= bv(USIWM1);
		}
		else if( mode == THREE) {
			USICR |= bv(USIWM0);
		}
	}
	
	void send(uint8_t data) {
		
	}
	
	uint8_t recive() {
		
	}
	
};

#endif

#endif
