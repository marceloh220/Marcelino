
	The Manual of Timer2 Module
	
	This module is compatible with:
									Atmega48A/Atmega48PA,
									Atmega88A/Atmega88PA,
									Atmega168A/Atmega168PA,
									Atmega328/Atmega328P (Arduino Uno).
                  This module has no compatibility whith Attiny85 microcontroller.

  Can work with other devices in the mega family,
  but without charge that works without some modifications in the code

  Marcelo H Moraes
  marceloh220@hotmail.com
  
  
  The AVR timer2 is an 8-bit timer/counter hardware, that can be used to generate
  a wide range of functions for a variety of applications.
  
  Module Timer2 is a very useful module with method to offer the
  programmer several easy tools to control this hardware.
  
  This module provides...
  
  
  
  TO Config of timer
  
  prescale(prescale);		//prescale control of timer
  
  Accepted prescaler for this timer are:
  
  P_1 to CPU_CLOCK/1
  P_8 to CPU_CLOCK/8
  P_32 to CPU_CLOCK/32
  P_64 to CPU_CLOCK/64
  P_128 to CPU_CLOCK/128
  P_256 to CPU_CLOCK/256
  P_1K to CPU_CLOCK/1024
  
  configure(mode, top);		//configure the mode of timer
  
  Accept modes for this timer are:
  NORMAL to normal mode timer/counter
  CTC to clear timer when compare, generally used to generete waves forms in pins OC2A and OC2B
  FAST to generate a fast pwm in pins OC2A and OC2B
  CORRECT to generete pwm with correct phase in pins OC2A and OC2B
  
  The top for this timer can be configured to the timer max value or the register comparator A
  
  When the timer is configured in CTC mode, the top of timer are determined for the camparator A.
 
  But, when configured for FAST or CORRECT PWM wave generator the top can be configured for timer max value, default,
  or like COMPA by comparator A.
 
  In the case of PWM wave generator, when the top are configured by comparator A,
  naturely the PWM in OC0A will be disabled, but the PWM in OC0B can have its varied frequency.
  
  When top is not passed, for default the top value for this timer will be the max value, in case is 2^8 (255/0xFF).
  
  pinA(mode);			//Configure action for pin OC2A when happens timer value match with value in comparator A
  
  Accepted modes are:
  OFF or DISCONNECT. The pin is disconnected
  CHANGE or TOGGLE. Change status of pin when compare match
  SET or HIGH. Put pin in high when compare match
  CLEAR of LOW. Put pin in low when compare match
  
  pinB(mode);			//Configure action for pin OC2B when happens timer value match with value in comparator B
  
  Same modes of pinA;
  
  The default of this timer are prescale OFF in NORMAL mode with pinA and pinB disconected.
  That can be change in any time with metodh "prescale(scale)", "configure(mode)" "pinA(mode)/pinB(mode)".
 
  For generate waves, the pin OC2A/OC2B
  need be configured like output with "mode(pin,mode)" method of Digital module.
  
  
  
  TO Access registers
  
  timer(value);			//to recharg value in timer
  compA(value);			//to recharg value in comparator A
  compB(value);			//to recharg value in comparator B
  
  char a = timer();		//to get value from timer
  char a = compA();		//to get value from comparator A
  char a = compB();		//to get value from comparator B
  
  
  
  TO PWM wave generator
  
  pwmA(value, mode);    //Generate a PWM wave in pin OC2A
  Accepted mode are:
  INVERT to inverted PWM wave
  NINVERT to not inverted PWM wave, this mode is default  when mode not is passed
  			
  
  pwmB(value, mode);    //Generate a PWM wave in pin OC2B
  The modes accepted are the same of pwmA
  Mode not inverted is default when mode not is passed
  
  For generate PWM waves, the pin OC2A/OC2B 
  need be configured like output with "mode(pin,mode)" method of Digital module.
 
  
  
  TO Control period of timer
  
  period(microsseconds, top);      //Sets the timer to occur during a required period

  The top parameter can be TIMER (default) to save the calculated period in timer counter;
  Or COMPA, to save the calculated period in comparator A register.
  
  The max period selectable is calculate with the equation:

  maxPeriod = 1 / F_CPU * 255 * 1024;

  in F_CPU 16MHz:
  maxPeriod = 16.31ms

  in F_CPU 8MHz:
  maxPeriod = 32.63ms

  in F_CPU 1MHz:
  maxPeriod = 261.11ms
  
  
  TO Interrupts of timer
  
  attach(interrupt, mode, funct);	//Attach a function in a interrupt on timer

  The mode accepted are:

  SYNCHRON, the timer 2 will use the system clock, this is the default mode when mode are not passed.
  
  ASYNCHRON, in this mode the timer 2 use a clock of oscilator OSCAL.
  When the system uses the 8MHz internal oscillator, OSCAL can use a different clock source to be used in timer 2,
  such as an external 32.768kHz crystal to implement an RTC application.
  
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
 
  
  detach(interrupt);	  //Detach a function of an interrupt on timer
  
  Only one function can be attached in an same interrupt each time, the new function attached will replace the older function.
  
  That means, one function can be attached in a OVF interrupt.
  The same function or other function cab be attached in a COMPA interrupt.
  And the same function or other function can be attached in a COMPB interrupt.
 
  The attached functions must be of type void.
 
  
  TO Simple timing
  
  The timer overflow can be calculated for this equation:
  
  time = prescale  (255 - timer(value) ) / CPU_CLOCK
 
  
  The timer compA/compB can be calculated for this equation:
  
  time = prescale  ( 255 - timer(value) - compA(value) ) / CPU_CLOCK
 
 
  If timer value is not changed with method "timer(value)", the timer(value) will be 0.
  
