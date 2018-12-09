#ifndef _PINS_ARDUINO_H_
#define _PINS_ARDUINO_H_

#include <avr/pgmspace.h>

/***********************************************************************

                  +--U--+
            RST  1|     |8  VCC
            PB3  2|     |7  PB2
            PB4  3|     |6  PB1
            GND  4|     |5  PB0
                  +-----+

***********************************************************************/

// Digital Ports Atmega328
const uint8_t digital_bit[5] PROGMEM = {
	1,
	2,
	4,
	8,
	16
};

const uint8_t digital_sfr[5] PROGMEM = {
	0,
	0,
	0,
	0,
	0
};

const uint8_t digital_DDR[1] PROGMEM = {(uint16_t)&DDRB};
const uint8_t digital_PORT[1] PROGMEM = {(uint16_t)&PORTB};
const uint8_t digital_PIN[1] PROGMEM = {(uint16_t)&PINB};
const uint8_t digital_PCMASK[1] PROGMEM = {(uint16_t)&PCMSK};

#define ATTINY
#define NOTIMER2
#define NOSPI
#define NOTWI
#define NOINT1
#define NOSERIAL

#endif
