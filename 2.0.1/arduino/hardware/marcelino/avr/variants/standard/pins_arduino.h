#ifndef _PINS_ARDUINO_H_
#define _PINS_ARDUINO_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>

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
const uint8_t digital_bit[] PROGMEM = {
	(1<<PD0),		//0
	(1<<PD1),		//1
	(1<<PD2),		//2
	(1<<PD3),		//3
	(1<<PD4),		//4
	(1<<PD5),		//5
	(1<<PD6),		//6
	(1<<PD7),		//7
	(1<<PB0),		//8
	(1<<PB1),		//9
	(1<<PB2),		//10
	(1<<PB3),		//11
	(1<<PB4),		//12
	(1<<PB5),		//13
	(1<<PC0),		//14
	(1<<PC1),		//15
	(1<<PC2),		//16
	(1<<PC3),		//17
	(1<<PC4),		//18
	(1<<PC5),		//19
	//Internal oscilator (8MHz)
	(1<<PB6),		//20
	(1<<PB7),		//21
};

const uint8_t digital_GPIO[] PROGMEM = {
	(uint8_t)&PIND,		//0
	(uint8_t)&PIND,		//1
	(uint8_t)&PIND,		//2
	(uint8_t)&PIND,		//3
	(uint8_t)&PIND,		//4
	(uint8_t)&PIND,		//5
	(uint8_t)&PIND,		//6
	(uint8_t)&PIND,		//7
	(uint8_t)&PINB,		//8
	(uint8_t)&PINB,		//9
	(uint8_t)&PINB,		//10
	(uint8_t)&PINB,		//11
	(uint8_t)&PINB,		//12
	(uint8_t)&PINB,		//13
	(uint8_t)&PINC,		//14
	(uint8_t)&PINC,		//15
	(uint8_t)&PINC,		//16
	(uint8_t)&PINC,		//17
	(uint8_t)&PINC,		//18
	(uint8_t)&PINC,		//19
	(uint8_t)&PINB,		//20
	(uint8_t)&PINB		//21
};

const uint8_t digital_PCMASK[] PROGMEM = {
	(uint8_t)&PCMSK2,		//0
	(uint8_t)&PCMSK2,		//1
	(uint8_t)&PCMSK2,		//2
	(uint8_t)&PCMSK2,		//3
	(uint8_t)&PCMSK2,		//4
	(uint8_t)&PCMSK2,		//5
	(uint8_t)&PCMSK2,		//6
	(uint8_t)&PCMSK2,		//7
	(uint8_t)&PCMSK1,		//8
	(uint8_t)&PCMSK1,		//9
	(uint8_t)&PCMSK1,		//10
	(uint8_t)&PCMSK1,		//11
	(uint8_t)&PCMSK1,		//12
	(uint8_t)&PCMSK1,		//13
	(uint8_t)&PCMSK0,		//14
	(uint8_t)&PCMSK0,		//15
	(uint8_t)&PCMSK0,		//16
	(uint8_t)&PCMSK0,		//17
	(uint8_t)&PCMSK0,		//18
	(uint8_t)&PCMSK0,		//19
	(uint8_t)&PCMSK1,		//20
	(uint8_t)&PCMSK1		//21
};

const uint8_t digital_PCMASK_vec[] PROGMEM = {
	2,		//0
	2,		//1
	2,		//2
	2,		//3
	2,		//4
	2,		//5
	2,		//6
	2,		//7
	1,		//8
	1,		//9
	1,		//10
	1,		//11
	1,		//12
	1,		//13
	0,		//14
	0,		//15
	0,		//16
	0,		//17
	0,		//18
	0,		//19
	1,		//20
	1		//21
};

#endif
