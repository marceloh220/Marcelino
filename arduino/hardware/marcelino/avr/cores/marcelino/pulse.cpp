#include "pulse.h"

uint32_t Pulse::in(uint8_t pin, uint8_t state, uint32_t timeout) {

	uint8_t bit = get_sfr(pin);
	volatile uint8_t* port = get_PIN(bit);
	bit = get_bit(pin);
	uint8_t stateMask = (state ? bit : 0);

	uint32_t maxloops = microsecondsToClockCycles(timeout)/16;
	uint32_t width = countPulseASM(port, bit, stateMask, maxloops);

	if (width)
		return clockCyclesToMicroseconds(width * 16 + 16);
	else
		return 0;
		
}
