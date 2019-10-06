
	The Manual of Timer0 Module
	
	This module is compatible with:
									Atmega48A/Atmega48PA,
									Atmega88A/Atmega88PA,
									Atmega168A/Atmega168PA,
									Atmega328/Atmega328P (Arduino Uno).

  Can work with other devices in the mega family,
  but without charge that works without some modifications in the code

  Marcelo H Moraes
  marceloh220@hotmail.com
  
  
  The AVR timer0 is an 8-bit timer/counter hardware, that can be used to generate
  a wide range of functions for a variety of applications.
  
  Module Timer0 is a very useful module with method to offer the
  programmer several easy tools to control this hardware.
  
  This module provides...
  
  
  
  TO Config of timer
  
  prescale(prescale);		//prescale control of timer
  
  Accepted prescaler for this timer are:
  
  1 to CPU_CLOCK/1
  8 to CPU_CLOCK/8
  64 to CPU_CLOCK/64
  256 to CPU_CLOCK/256
  1024 to CPU_CLOCK/1024
  FALLING to detect falling edge in pin T0 (Digital pin 4)
  RISING to detect rising edge in pin T0 (Digital pin 4)
  
  mode(mode, top);		//configure the mode of timer
  
  Accept modes for this timer are:
  NORMAL to normal mode timer/counter
  CTC to clear timer when compare, generally used to generete waves forms in pins OC0A (Digital pin 6) and OC0B (Digital pin 5)
  FAST to generate a fast pwm in pins OC0A (Digital pin 6) and OC0B (Digital pin 5)
  CORRECT to generete pwm with correct phase in pins OC0A (Digital pin 6) and OC0B (Digital pin 5)
  
  The top for this timer can be configured to the timer max value or the register comparator A
  
  When the timer is configured in CTC mode, the top of timer are determined for the camparator A.
 
  But, when configured for FAST or CORRECT PWM wave generator the top can be configured for timer max value, default,
  or like COMPA by comparator A.
 
  In the case of PWM wave generator, when the top are configured by comparator A,
  naturely the PWM in OC0A (Digital pin 6) will be disabled,
  but the PWM in OC0B (Digital pin 5) can have its varied frequency with the method "frequency(freq)"
  
  When top is not passed, for default the top value for this timer will be the max value, in case is 2^8 (255/0xFF).
  
  pinA(mode);			//Configure action for pin OC0A (Digital pin 6) when happens timer value match with value in comparator A
  
  Accepted modes are:
  OFF					//The pin is disconnected
  CHANGE				//Change status of pin when compare match
  SET					//Put pin in high when compare match
  CLEAR					//Put pin in low when compare match
  
  pinB(mode);			//Configure action for pin OC0B (Digital pin 5) when happens timer value match with value in comparator B
  
  Same modes of pinA;
 
  For generate waves, the pin OC0A/OC0B (Digital pin 6/Digital pin 5) 
  need be configured like output with "mode(pin,mode)" method from Digital module.
  
  
  
  TO Access registers
  
  timer(value);			//to recharg value in timer
  compA(value);			//to recharg value in comparator A
  compB(value);			//to recharg value in comparator B
  
  char a = timer();		//to get value from timer
  char a = compA();		//to get value from comparator A
  char a = compB();		//to get value from comparator B
  
  
  
  TO PWM wave generator
  
  pwmA(value);				//Generate a PWM wave in pin OC0A (Digital pin 6)
  
  pwmA(value, mode);		//Generate a PWM wave in pin OC0A (Digital pin 6)
  Accepted mode are:
  INVERT to inverted PWM wave
  NINVERT to not inverted PWM wave, this mode is default  when mode not is passed
  
  
  pwmB(value);				//Generate a PWM wave in pin OC0B (Digital pin 5)
  
  pwmB(value, mode);
  The modes accepted are the same of pwmA
  Mode not inverted is default when mode not is passed
  
  For generate PWM waves, the pin OC0A/OC0B (Digital pin 6/Digital pin5) 
  need be configured like output with "mode(pin,mode)" method of Digital module.

  Calculation frequency for PWM wave
  
  The frequency is calculate with:
  
	frequency = F_CPU / ( 2 * prescale * ( 1 + compA ) )	For mode CTC or CORRECT
	
	and:
	
	frequency = F_CPU / ( prescale * ( 1 + compA ) )	For mode FAST
	
  The min and max frequency generated by the timer depend on prescaler configured and need be calculated.
  
  LIKE:
  
  In CTC mode and CORRECT mode
  				fmax = F_CPU / (2 * prescale * 1)  		with comparator A equal 0
  				fmin = F_CPU / (2 * prescale * 256)		with comparator A equal 255
  
  In FAST mode
  				fmax = F_CPU / (prescale * 1)  			with comparator A equal 0
  				fmin = F_CPU / (prescale * 256)			with comparator A equal 255
  				
  F_CPU is the current speed clock of microcontroler, in Arduino Uno this clock is 16MHz
  
  The range out of prescaler limits cause overflow of comparator register and error in wave frequency.
  
  
  TO Interrupts of timer
  
  attach(interrupt, funct);	//Attach a function in a interrupt on timer
  
  The interrupt for this timer are:
  
  OVF to interrupt in timer overflow
  
  When the timer hit the top and overflow to 0, a function passed will be called.
  This is very useful for timings without delays.
 
  
  COMPA to interrupt when timer match with comparator A
  
  When the timer value match with comparator A value, a function passed will be called.
 
  
  COMPB to interrupt when timer match with comparator B
  
  When the timer value match with comparator B value, a function passed will be called.
  
  These last two interrupts can be used to generate actions at different times in the same timer.
  This means a delay in interrupt actions that can be controlled.
 
  Or in CTC mode, this comparators can be used to generate signal with variable frequency.
 
  
  detach(interrupt, funct);	//Detach a function of an interrupt on timer
  
  Only one function can be attached in an same interrupt each time, the new function attached will replace the older function.
  
  That means, one function can be attached in a OVF interrupt.
  The same function or other function cab be attached in a COMPA interrupt.
  And the same function or other function can be attached in a COMPB interrupt.
 
  The attached functions must be of type void.
 
  
 TO Simple timing
  
  The timer overflow can be calculated for this equation:
  
  time = prescale * ( 65535 - timer(value) ) / CPU_CLOCK
 
   
  The timer compA/compB can be calculated for this equation:
  
  time = prescale * ( 65535 - timer(value) - compA(value) ) / CPU_CLOCK
 
  If timer value is not changed with method "timer(value)", the timer(value) will be 0.

  periode(time);        //Calcule the prescale and timer value to overflow in passed time

  Note:
  The time passed must be in microseconds, it configure the prescaler.
  If prescaler is change in other part of application the timer will be wrong.

  The max and minimal time for the timer0 is:

  In 8MHz
  minimal 1 Microsecond
  maximum 32.64 Milliseconds

  In 16MHz
  minimal 1 Microsecond
  maximum 16.32 Milliseconds
 
	And this is the END.
