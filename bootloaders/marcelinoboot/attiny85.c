#include <avr/io.h>
#include <util/delay.h>

int main() {

	DDRB |= (1<<2);

	for(;;) {

		PORTB^=(1<<2);
		_delay_ms(1000);
	
	}
	
	return 0;

}
