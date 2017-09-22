#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

int main() {

	DDRB |= (1<<2);

	for(;;) {

		PORTB^=(1<<2);
		_delay_ms(1000);
	
	}
	
	return 0;

}