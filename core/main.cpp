#include "defines.h"

uint8_t sregSAVE;

void none() {
	SREG = sregSAVE;
	asm volatile("reti"::);
}

int main() {
	ACSR|=(1<<ACD);
	setup();
	for(;;)
		loop();
	return 0;
}
