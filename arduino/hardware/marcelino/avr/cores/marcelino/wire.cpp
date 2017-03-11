#include "wire.h"

VoidFuncPtr wireARRAY = none;

Wire::Wire(uint8_t speed) {
	if(speed)
		TWBR = 12;
	else
		TWBR = 72;
}

Wire::Wire(uint8_t address, VoidFuncPtr funct) {
	TWAR = address<<1;
	wireARRAY = funct;
	TWCR = (1<<TWIE)|(1<<TWEA)|(1<<TWEN);
	sei();
}

void Wire::send(uint8_t data) {
    TWDR = data;
	TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

uint8_t Wire::read(uint8_t ack) {
	if(ack)
		TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	else
		TWCR = (1<<TWINT)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
    return TWDR;
}

ISR(TWI_vect) {
	sregSAVE = SREG;
	wireARRAY();
}
