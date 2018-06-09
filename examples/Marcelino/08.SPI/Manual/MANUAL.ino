
	The Manual of SPI Module
	
	This module is compatible with:
									Atmega48A/Atmega48PA,
									Atmega88A/Atmega88PA,
									Atmega168A/Atmega168PA,
									Atmega328/Atmega328P (Arduino Uno).

  Can work with other devices in the mega family,
  but without charge that works without some modifications in the code

  Marcelo H Moraes
  marceloh220@hotmail.com
  
  
  The Serial Peripheral Interface (SPI) allows high-speed synchronous data transfer
  between the microcontroller and peripheral devices or between several AVR devices.
   
  Module SPI is a very useful module with method to offer the
  programmer several easy tools to control the SPI of microcontroller.
  
  This module provides...
  
    
  TO Config the Serial Peripheral Interface (SPI)
  
  When the module is initialized, the mode and the prescale need be configured.
  The SPI hardware dont accept changes of mode and prescale when program is runing.
  
  SPI spi(mode, scale);		//Initialized the module passing mode and prescale configurations
  
  Mode accepted are:
  MASTER to master SPI.
  SLAVE to slave SPI.
  
  In SLAVE mode the SS pin (Digital pin 10) must be connected to GND to allow the In SLAVE
  mode the SS pin (Digital pin 10) must be connected to GND to allow the communication.
  That can be used to selected this device by the master SPI.
  
  The bits rates is selectable passing the prescaler to SPI module
  
  Accepted prescale are:
  2 	to F_CPU/2 prescale
  4 	to F_CPU/4 prescale
  8 	to F_CPU/8 prescale
  16 	to F_CPU/16 prescale
  32 	to F_CPU/32 prescale
  64 	to F_CPU/64 prescale
  128 	to F_CPU/128 prescale
  
  The bit rate can be calculate with:
  
  bit_rate = F_CPU / prescale;
  
			In 8MHz
	prescale	|	bit rate
				|
		2		|	4MHz
		4		|	2MHz
		8		|	1MHz
		16		|	500KHz
		32		|	250KHz
		64		|	125KHz
		128		|	62.5KHz
	
	
			In 16MHz
	prescale	|	bit rate
				|
		2		|	8MHz
		4		|	4MHz
		8		|	2MHz
		16		|	1MHz
		32		|	500KHz
		64		|	250KHz
		128		|	125KHz
  
  The bit rate is only configurable in MASTER mode.
  
  The SPI is initiated by default in MASTER mode and with prescaler in 16.
  
  order(mode)		//Selects the order in which bytes are sent
  
  Accepted modes are:
  MSBF to More Significant Bit First
  LSBF to Less Significant Bit First
  
  The shipping order can be modified at any time in the application.
  
  To send  and received the information using the SPI hardware:
  
  send(byte)				//to send direct byte information
  byte a = recive();		//to recive direct byte information
  byte a = transcive(byte);	//to send and recive direct byte information
  
  
  And print methods can also be used from the Print class:
  print()					//To print anything
  println()					//to print any stuff with a end line
  Maybe don't have any application for that methods print, but here they are.
  
  
  TO Interrupts of SPI Serial Transfer Complete
  
  attach(funct);			//The attached function will be called when a Serial Transfer Complete is detected
  
  detach();					//Detach a function of the interrupt
  
  Only one function can be attached, the new function attached will replace the older function.
 
  The attached functions must be of type void.
  
  This can be used to implement of a device for some application with SPI serial communication in SLAVE mode.
  
	And this is the END.
