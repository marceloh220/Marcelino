#ifndef _PINS_ARDUINO_H_
#define _PINS_ARDUINO_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>

/***********************************************************************

                  +--U--+
            RST  1|     |8  VCC
            PB3  2|     |7  PB2
            PB4  3|     |6  PB1
            GND  4|     |5  PB0
                  +-----+

***********************************************************************/

// Digital Ports Atmega328
const uint8_t digital_bit[] PROGMEM = {
	(1<<PB0),
	(1<<PB1),
	(1<<PB2),
	(1<<PB3),
	(1<<PB4)
};

const uint8_t digital_GPIO[] PROGMEM = {
	(uint8_t)&PINB,
	(uint8_t)&PINB,
	(uint8_t)&PINB,
	(uint8_t)&PINB,
	(uint8_t)&PINB
};

const uint8_t digital_PCMASK[] PROGMEM = {
	(uint8_t)&PCMSK,
	(uint8_t)&PCMSK,
	(uint8_t)&PCMSK,
	(uint8_t)&PCMSK,
	(uint8_t)&PCMSK
};

const uint8_t digital_PCMASK_vec[] PROGMEM = {
	0,
	0,
	0,
	0,
	0
};

#define ATTINY
#define NOTIMER2
#define NOSPI
#define NOTWI
#define NOINT1
#define NOSERIAL

#endif
