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


#include "delay.h"

void Delay::loop_us(uint8_t __counter) {
	__asm__ volatile (
		"1: dec %0"	"\n\t"
		"brne 1b"	"\n\t"
		: "=r" (__counter)
		: "0" (__counter)
	);
}

void Delay::loop_ms(uint16_t __counter) {
	__asm__ volatile (
		"1: sbiw %0,1	\n\t"
		"brne 1b		\n\t"
		: "=w"	(__counter)
		: "0"	(__counter)
	);
}

void Delay::us(double __millis) {
	uint8_t __ticks;
	double __tmp = ((F_CPU) / 3e6) * __millis;
	if (__tmp > 255) {
		this->ms(__millis / 1e3); return;
	}
	else if (__tmp < 1.0)
		__ticks = 1;
	else
		__ticks = (uint8_t)__tmp;
	this->loop_us(__ticks);
}
	
void Delay::ms(double __micros) {
	uint16_t __ticks;
	double __tmp = ((F_CPU) / 4e3) * __micros;
	if (__tmp > 65535) {
		__ticks = (uint16_t)(__micros * 10.0);
		while(__ticks--) {
			this->loop_ms((F_CPU) / 4e4);
		}
		return;
	}
	else if (__tmp < 1.0)
		__ticks = 1;
	else
		__ticks = (uint16_t)__tmp;
	this->loop_ms(__ticks);
}
