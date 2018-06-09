
	The Manual of Analog Module
	
	This module is compatible with:
									Atmega48A/Atmega48PA,
									Atmega88A/Atmega88PA,
									Atmega168A/Atmega168PA,
									Atmega328/Atmega328P (Arduino Uno),
                  and Attiny85.

  Can work with other devices in the mega family,
  but without charge that works without some modifications in the code

  Marcelo H Moraes
  marceloh220@hotmail.com
  
  
  The AVR Analog Digital Converter (ADC) is an analog input voltage to 
  a 10-bit digital value through successive approximation.
  The minimum value represents GND and the maximum value represents the 
  voltage on the AREF pin minus 1 LSB.
  
  Optionally the microcontrollers has as reference voltage the voltage 
  applied to the Avcc pin to power the ADC hardware, or an internal
  voltage of 1.1 V.

  The Attiny85 mcu have too an internal reference of 2.5V.
  
  In addition, this microcontrollers also has an analog comparator 
  implemented with an open loop Operational Amplifier (Op Amp).
  
  The Analog Comparator compares the input values on the positive pin AINP
  and negative pin AINN.
  Optionally the positive input can be used with the internal reference voltage of 1.1 V
  and too 2.5V in Atiny85 microcontrollers.
  When the  voltage on the positive pin AINP is higher or lower than the voltage 
  on the negative pin AINN, the Analog Comparator can generate an interrupt.
  
  
  Module Analog is a very useful module with method to offer the
  programmer several easy tools to control the Analogs hardwares of microcontroller.
  
  This module provides...
  
  
  TO Config the Analog Digital Converter (ADC)
  
  aref(Vref);				//select the referency voltage for ADC
  
  Accepted Vref are:

  Atmega328/p:
  DEFAULT to use reference voltage as the same voltage applied to the Avcc pin
  EXTERNAL to use reference voltage applied in Aref pin.
  INTERNAL to use internal reference voltege of 1.1V

  Attiny85:
  DEFAULT to use reference voltage as the same voltage applied to the Avcc pin
  EXTERNAL to use reference voltage applied in Aref pin.
  INTERNAL1V1 to use internal reference voltege of 1.1V
  INTERNAL2V2 to use internal reference voltege of 2.5V
  
  When using the EXTERNAL reference voltage,
  a voltage reference must be applied to the Aref pin.
  
  When using the reference voltage DEFAULT or INTERNAL, 
  any voltage of the Aref pin must be disconnected 
  and placed on this pin a decoupling capacitor to improve the stability of the converter.
  In the Attiny85 the pin Aref pin can be used as digital io.
  
  In Atmega328/p the Avcc pin should be connected to Vcc pin through a low-pass filter.
  
  IGNORE THE WISE ADVICE OF PAI MAI AT YOUR OWN RISK.
  
  prescale(prescale);		//prescale control of ADC
  
  Accepted prescaler are:
  
  2 to CPU_CLOCK/2
  4 to CPU_CLOCK/4
  8 to CPU_CLOCK/8
  16 to CPU_CLOCK/16
  32 to CPU_CLOCK/32
  64 to CPU_CLOCK/64
  128 to CPU_CLOCK/128
  
  With prescale the programer can choose between very fast conversion with a low prescale 
  or a stable readingines in a long amostragem signal with a high prescale.
  This module comes with prescaler in 1/64 as default value, good for most applications.
  
  
  TO Read Analog pins:

    Atmega328/p dip-28 (A0 to A5)
    Atmega328/p qfp-32 (A0 to A7)
    Attiny85 (A1 to A3)
  
  read(pin)					//read the Analog pin
  
  This method return a value 0, to represent GND,
  and 1023 to represent max value determined by Aref (max voltage predefined).
  
  
  Optionally, a reference voltage can be passed to the reading method.
  The passed reference voltage will only be used for this reading,
  other readings where a temporary reference voltage is not passed,
  will be made with the standard reference voltage or defined by aref ();
  
  read(pin,vref)			//read the analog pin with a temporary reference voltage
  
  
  temp()					//read the internal temperature of microcontroller
  
  Note, this method can't be used to measure the ambient temperature.
  The internal temperature is the temperature inside the chip,
  and this temperature tends to grow as more resources are required of the microcontroller.
  
  TO Interrupt of Analog comparator
  
  attach(mode, funct)		//Attach the passed function in interrupt of analog comparator
  
  Accepted mode are:
  RISING to a rising edge, that means the voltage in AINP has become higher than the voltage in the AINN pin.
  FALLING to a falling edge, that means the voltage in AINP has become lower than the voltage in the AINN pin.
  CHANGE to any change in output of comparator, that means of any change in comparator state will call the interrupt function.
  
  The attached functions must be of type void.
  
  Optionally, an INTERNAL can be passed to this method to make the 
  voltage at the positive input of the comparator equal to the internal voltage of 1.1 V
  and also 2.5V in Attiny85.

  Atmega328/p:
  attach(mode, INTERNAL, funct)	//AttaAttach the passed function with a internal reference voltage in positive input
  Attiny85:
  attach(mode, INTERNAL1V1, funct)  //AttaAttach the passed function with a internal reference voltage in positive input
  attach(mode, INTERNAL2V5, funct)  //AttaAttach the passed function with a internal reference voltage in positive input
  
  Only one function can be attached in this interrupt, the new function attached will replace the older function.
  
  And this attached function can be detach with
  
  detach();					//Detach any function of comparator interrupt
  
  
  TO test if Analog comparator is in falling or rising mode, this module provide:
  
  rising()		//Return TRUE if comparator interrupt is in mode RISING
  falling()		//Return TRUE if comparator interrupt is in mode FALLING
  change()		//Return TRUE if comparator interrupt is in mode CHANGE

  
