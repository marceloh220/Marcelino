#ifndef _PINS_ARDUINO_H_
#define _PINS_ARDUINO_H_

#include <avr/pgmspace.h>

/***********************************************************************

                  +--U--+
            PC6  1|     |28  PC5
            PD0  2|     |27  PC4
            PD1  3|     |26  PC3
            PD2  4|     |25  PC2
            PD3  5|     |24  PC1
            PD4  6|     |23  PC0
            VCC  7|     |22  GND
            GND  8|     |21  AREF
            PB6  9|     |20  AVCC
            PB7 10|     |19  PB5
            PD5 11|     |18  PB4
            PD6 12|     |17  PB3
            PD7 13|     |16  PB2
            PB0 14|     |15  PB1
                  +-----+

***********************************************************************/

// Digital Ports Atmega328
const uint8_t digital_bit[22] PROGMEM = {
	1,		//0
	2,
	4,
	8,
	16,
	32,
	64,
	128,
	1,		//8
	2,
	4,
	8,
	16,
	32,
	1,		//14
	2,
	4,
	8,
	16,
	32,
	64,		//20
	128		//21
};

const uint8_t digital_sfr[22] PROGMEM = {
	2,		//0
	2,
	2,
	2,
	2,
	2,
	2,
	2,
	0,		//8
	0,
	0,
	0,
	0,
	0,
	1,		//14
	1,
	1,
	1,
	1,
	1,
	0,		//20
	0		//21
};

const uint8_t digital_DDR[3] PROGMEM = {
	(uint16_t)&DDRB,
	(uint16_t)&DDRC,
	(uint16_t)&DDRD
};

const uint8_t digital_PORT[3] PROGMEM = {
	(uint16_t)&PORTB,
	(uint16_t)&PORTC,
	(uint16_t)&PORTD
};

const uint8_t digital_PIN[3] PROGMEM = {
	(uint16_t)&PINB,
	(uint16_t)&PINC,
	(uint16_t)&PIND,
};

const uint8_t digital_PCMASK[3] PROGMEM = {
	(uint16_t)&PCMSK0,
	(uint16_t)&PCMSK1,
	(uint16_t)&PCMSK2,
};

#endif
