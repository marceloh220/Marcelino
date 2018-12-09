	Marcelo H Moraes
	marceloh220@hotmail.com
	
	https://github.com/marceloh220/Marcelino
	
	Hi, i'm a brazilian engineer student.
	This text are completely in english, why that? Most of the material for technology students is in English, and that language becomes a global language. Therefore, this material can reach a larger audience being written so.
	
	The three rules of Core Marcelino:
	First rule: Make the things in easy way.
	Second rule: But don't make the easy things.
	Third rule: Don't waste time of the processor doing with software if you have a peripheral hardware to do that.
	
	
	The sketches following in this example are a way to show the features of this core. These examples came with an MIT license and no warranty of any kind offered will be.
	
	
	The Marcelino core is distributed with a GPL 3.0 use license.
	
	The Marcelino project is open to contributors of anything, with code programming, documentation or any guidance on setting up the microcontrollers.
	
	Be free to study this core, modify and distribute the modifications, following the guidelines of the current use license for the core.


	
The Marcelino extensible core for Arduino Uno / Nano / Mini boards *, and now the attiny85** microcontroller has partial support.

	Core Marcelino expands software configuration capabilities, giving the programmer easy tools to configure these Arduino boards.
	Program the Arduino without software limitations, and explorer the powerful hardware of AVR microcontroller.
	
*Any module is compatible with:
					Atmega48A/Atmega48PA,
					Atmega88A/Atmega88PA,
					Atmega168A/Atmega168PA,
					Atmega328/Atmega328P (Arduino Uno).
	
**Most modules are compatible with:
					Attiny25,
					Attiny45,
					Attiny85 (Digispark).

	The bootloaders are an optiboot implementation, source page in:
	https://github.com/Optiboot/optiboot
	
	In Arduino IDE:

	Marcelino 328 is the configuration to ATmega328 chips board.
	Marcelino 168 is the configuration to ATmega168 chips board.
		In "F_CPU: 8MHz" the microcontroller work with internal oscillator on 8MHz speed,  in standalone Arduino build this can be very useful.
		In "F_CPU: 16MHz", the microcontroller works with external crystal oscillator on the Arduino board.

	Attiny85 is the configuration to ATtiny85 chips board.
		In "F_CPU: 8MHz" the microcontroller work with internal oscillator on 8MHz speed.
		In "F_CPU: 1MHz", the microcontroller work with reduced speed in internal oscillator, can be used to reduced power consumption.
