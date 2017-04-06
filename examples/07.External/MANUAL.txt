
	The Manual of External Module
	
	This module is compatible with:
									Atmega48A/Atmega48PA,
									Atmega88A/Atmega88PA,
									Atmega168A/Atmega168PA,
									Atmega328/Atmega328P (Arduino Uno).

  Can work with other devices in the mega family,
  but without charge that works without some modifications in the code

  Marcelo H Moraes
  marceloh220@hotmail.com
  
  
  The External Interrupts can be triggered by the pin INT0 (Digital pin 2) and pin INT1 (Digital pin 3).
  And even more, any digital pin of microcontroller can triger a interrupt PCINT.
  
  Module External is a very useful module with method to offer the
  programmer several easy tools to control the External interrupts.
  
  This module provides...
  
  TO attach a external PCINT interrupt
  
  attach(pin,function)				//if occur any change in selected pin, the interrupt call the function passed
  
  Any digital pin can be passed, from D0 to D21*.


  TO attach a external INT0 and INT1 interrupt

  attach(interrupt, mode, function)	//if occur the external interrupt selected, call the function passed
  
  The interrupts accept are:
  INT0 to a external interrupt in INT0 pin (Digital pin 2)
  INT1 to a external interrupt in INT1 pin (Digital pin 3)
  
  The modes accept are:
  LOW to detect the change of external interrupt pin change of high to low
  RISING to detect a rinsing edge of external interrupt pin
  FALLING to detect a falling edge of external interrupt pin
  CHANGE to detect any change of external interrupt pin
	  
	  
  Notes:
  
    The function must be a void type.
    
    INT0 and INT1 have a exclusive interrupt each, and can be selected the mode of the external interrput pin.
    
    But the PCINT interrupt have only three interrupt,
    one for D0 to D7 pin,
    other for D8 to D13 pin and D20 and D21 pin,
    and the last for D14 to D19 pin.
    That way, if attached D0 and D1 pin, the interrupt event will be directed to the same function.
    The mode can't be selected in PCINT interrupt, any change in selected pins will tigger the interrupt.
    
    
  * The D20 and D21 digital pins are available if the microcontroller is used with an internal 8MHz oscillator
	with the Marcelino Uno (8MHz) option, and the asynchronous mode of the timer2 is not used.
	
  
  detachPC(pin)				//detach a pin of PCINT interrupt external event
  
  If more of one pin is attached in a interrupt PCINT, the other pins not detached yet will trigger the interrupt event.
  
  detachINT(interrupt)		//detach the INT interrupt external event
  
  interrupt are INT0 and INT1
  
  
	And this is the END.
