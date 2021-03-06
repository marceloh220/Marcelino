/*
  Copyright (c) 2017 Marcelo Henrique Moraes

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3.0 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

 */


#ifndef DEFINES_H
#define DEFINES_H

#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "pins_arduino.h"

#if defined ARDUINO_AVR_MARCELINO
#define INPUT 		0
#define OUTPUT		1
#define INPUT_PULLUP 2
#endif
#define PULLUP		2

#if defined ARDUINO_AVR_MARCELINO
#define LOW 		0
#endif
#define CLEAR		0
#define OFF 		0
#define DISABLE		0
#define DISCONNECT	0

#if defined ARDUINO_AVR_MARCELINO
#define HIGH		1
#endif
#define SET			1
#define ON			1
#define ENABLE		1
#define CONNECTED	1

#define TOGGLE		2
#define CHANGE		2

#define OVF			0

#define COMPA		1
#define OCRA		1

#define COMPB		2

#define COMPC		3
#define CAPT		3
#define ICR			3

#define COMP		4
#define TIMER		5

#define	NORMAL		0
#define CORRECT		1
#define CTC			2

#define FAST		3
#define SLOW		0

#define CORRECT8	1
#define CORRECT9	4
#define CORRECT10	5

#define FAST8		3
#define FAST9		6
#define FAST10		7

#define NINVERT		0
#define INVERT		1

#define P_1			1
#define P_2			2
#define P_4			3
#define P_8			4
#define P_16		5
#define P_32		6
#define P_64		7
#define P_128		8
#define P_256		9
#define P_512		10
#define P_1K		11
#define P_2K		12
#define P_4K		13
#define P_8K		14
#define P_16K		15
#define FALLING		16
#define RISING		17

#define RECOVERY	0
#define SAVE		1

#if defined ARDUINO_AVR_MARCELINO
#define EXTERNAL	0
#define DEFAULT		1
#define INTERNAL	3
#define INTERNAL1V1 4
#define INTERNAL2V5 5
#endif

#define W_16MS		0
#define W_32MS		1
#define W_64MS		2
#define W_128MS		3
#define W_256MS		4
#define W_512MS		5
#define W_1S		6
#define W_2S		7
#define W_4S		8
#define W_8S		9

#define INTERRUPT	1
#define RESET		2
#define INT_RESET	3

#define SLEEP		(8<<1)
#define IDLE 		SLEEP_MODE_IDLE
#define ADCNOISE 	SLEEP_MODE_ADC
#define POWERDOWN	SLEEP_MODE_PWR_DOWN
#define POWERSAVE	SLEEP_MODE_PWR_SAVE
#define STANDBY		SLEEP_MODE_STANDBY
#define STANDBYEXT	SLEEP_MODE_EXT_STANDBY

#define ALL			8
#ifdef PRTIM2
#define PRTIMER2	PRTIM2
#endif
#define PRTIMER0	PRTIM0
#define PRTIMER1	PRTIM1
#ifdef PRUSART0
#define PRUSART		PRUSART0
#endif
#if defined ARDUINO_AVR_MARCELINO
#define MSBF		0
#define LSBF		1
#endif

#define ASYNCHRON	0
#define SYNCHRON	1

#define EVEN		1
#define ODD			0

#define SLAVE		0
#define MASTER		1
#define DDR_SPI		DDRB
#define DD_MOSI		3
#define DD_MISO		4
#define DD_SCK		5

#define XCLK_DDR	DDRD
#define XCLK_PIN	4
#define XCK			4
#define RX			0
#define TX			1

#define NACK		0
#define ACK			1

#if defined ARDUINO_AVR_MARCELINO
#define A0			0
#define A1			1
#define A2			2
#define A3			3
#define A4			4
#define A5			5
#endif

#ifndef ATTINY
#define T0			4
#define T1			5
#define AINP		6
#define AINN		7
#define ICP			8

#define OC0A		6
#define OC0B		5
#define OC1A		9
#define OC1B		10
#define OC2A		11
#define OC2B		3

#else

#define T0			2
#define AINP		0
#define AINN		1

#define OC0A		0
#define OC0B		1

#endif

#if defined ARDUINO_AVR_MARCELINO
#define D0			0
#define D1			1
#define D2			2
#define D3			3
#define D4			4
#define D5			5
#define D6			6
#define D7			7
#define D8			8
#define D9			9
#define D10			10
#define D11			11
#define D12			12
#define D13			13
#define D14			14
#define D15			15
#define D16			16
#define D17			17
#define D18			18
#define D19			19
#define D20			20
#define D21			21
#define D22			22

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( (a) / clockCyclesPerMicrosecond() )
#define microsecondsToClockCycles(a) ( (a) * clockCyclesPerMicrosecond() )

#define PI 			3.1415926535897932384626433832795
#define HALF_PI 	1.5707963267948966192313216916398
#define TWO_PI 		6.283185307179586476925286766559
#define DEG_TO_RAD 	0.017453292519943295769236907684886
#define RAD_TO_DEG 	57.295779513082320876798154814105
#define CM_TO_INCH	0.393701
#define INCH_TO_CM	2.54
#define EULER 		2.718281828459045235360287471352
#define LN2			0.69314718055994530942
#define SQRT2		1.41421356237309504880
#define SQRT1_2		0.70710678118654752440
#define SQRT3		1.73205080757

#define sbi(_sfr,_bit)		(_sfr|=(1<<_bit))
#define cbi(_sfr,_bit)		(_sfr&=~(1<<_bit))
#define tbi(_sfr,_bit)		(_sfr^=(1<<_bit))

#define is_set(_sfr,_bit)	(_sfr&(1<<_bit))
#define is_clear(_sfr,_bit)	(!(_sfr&(1<<_bit)))

#define bv(_bit)			(1<<_bit)
#define nop() 				asm volatile ("nop")

#endif

#ifdef PROGMEM
#undef PROGMEM
#define PROGMEM __attribute__((section(".progmem.data")))
#endif

#if defined ARDUINO_AVR_MARCELINO
typedef uint8_t byte;
typedef uint16_t word;
#endif
typedef uint32_t dword;

extern uint8_t sregSAVE;

#define get_bit(P)		pgm_read_byte(&digital_bit[P])
#define get_sfr(P)		pgm_read_byte(&digital_sfr[P])
#define get_DDR(P)		(volatile uint8_t *)pgm_read_byte(&digital_DDR[P])
#define get_PORT(P)		(volatile uint8_t *)pgm_read_byte(&digital_PORT[P])
#define get_PIN(P)		(volatile uint8_t *)pgm_read_byte(&digital_PIN[P])
#define get_PCMASK(P)	(volatile uint8_t *)pgm_read_byte(&digital_PCMASK[P])

#define pgm_get(sfr,P)	pgm_read_byte(&sfr[P])

#define clockMS			(F_CPU/1000000UL)
#define clock2ms(c)		(c / clockMS)
#define ms2clock(m)		(m * clockMS)

#define clockMC			(F_CPU/1000UL)
#define clock2mc(c)		(c / clockMC)
#define mc2clock(m)		(m * clockMC)

void none();
#if defined ARDUINO_AVR_MARCELINO
void setup();
void loop();
#endif

#endif
