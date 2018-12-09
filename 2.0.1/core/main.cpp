#include "defines.h"

uint8_t sregSAVE;

void none() {
}

int main() {
	setup();
	for(;;)
		loop();
	return 0;
}
