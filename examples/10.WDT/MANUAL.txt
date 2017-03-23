
	The Manual of WDT Module
	
	This module is compatible with:
									Atmega48A/Atmega48PA,
									Atmega88A/Atmega88PA,
									Atmega168A/Atmega168PA,
									Atmega328/Atmega328P (Arduino Uno).

  Can work with other devices in the mega family,
  but without charge that works without some modifications in the code

  Marcelo H Moraes
  marceloh220@hotmail.com
  
  ATmega48A/PA/88A/PA/168A/PA/328/P has an Enhanced Watchdog Timer (WDT).
  The WDT is a timer counting cycles of a separate on-chip 128kHz oscillator.
  The WDT gives an interrupt or a system reset when the counter reaches a given time-out value.
  In normal operation mode, it is required that the system uses the WDR
  - Watchdog Timer Reset - instruction to restart the counter before the time-out value is reached.
  If the system doesn't restart the counter, an interrupt or system reset will be issued.
   
  Module WDT is a very useful module with method to offer the
  programmer several easy tools to control the Watchdog Timer of microcontroller.
  
  This module provides...
  
  
  TO Config the Watchdog Timer (WDT)
  
  config(mode)			//Config the operation mode of wdt
  
  Accept modes are:
  INTERRUPT				//When occur overflow of the WDT the code jumps to function attached in interrupt of the WDT
  RESET					//When occur overflow of the WDT the microcontroller do a reset
  INT_RESET				//When the WDT overflow occurs the interrupt is called and after the microcontroller has reset
  
  timeout(time)			//Set the timer clock to occur the WDT overflow
  
  Accept times are:
  W_16MS to WDT overflows in 16ms
  W_32MS to WDT overflows in 32ms
  W_64MS to WDT overflows in 64ms
  W_128MS to WDT overflows in 128ms
  W_256MS to WDT overflows in 256ms
  W_512MS to WDT overflows in 512ms
  W_1S to WDT overflows in 1.024s
  W_2S to WDT overflows in 2.048s
  W_4S to WDT overflows in 4.096s
  W_8S to WDT overflows in 8.192s
  
  
  TO enable and disable
  
  enable()				//Enable the WDT
  disable()				//Disable the WDT
  
  
  TO reset the WDT
  
  reset()				//Restarts WDT by stopping reboot or interrupt call
  
  clear()				//Do the same as the reset() method
  
  
  TO interrupt management

  attach(function)		//The attached function will be called when a overflow of WDT occur
  
  detach()				//Detach a function of the interrupt
  
  Only one function can be attached, the new function attached will replace the older function.
 
  The attached functions must be of type void.
  
  The WDT module start the WDT hardware in RESET mode and overflow in W_16MS.
  That can be changed any time in application, just remember reset the WDT to avoid resets.
  
	And this is the END.
