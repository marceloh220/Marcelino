
	The Manual of TWI Module
	
	This module is compatible with:
									Atmega48A/Atmega48PA,
									Atmega88A/Atmega88PA,
									Atmega168A/Atmega168PA,
									Atmega328/Atmega328P (Arduino Uno).

  Can work with other devices in the mega family,
  but without charge that works without some modifications in the code

  Marcelo H Moraes
  marceloh220@hotmail.com
  
  
  The 2-wire Serial Interface (TWI) is ideally suited for typical microcontroller applications.The TWI protocol
  allows the systems designer to interconnect up to 128 different devices using only two bi-directional bus lines,
  one for clock (SCL) and one for data (SDA). The only external hardware needed to implement the bus is a single
  pull-up resistor for each of the TWI bus lines. All devices connected to the bus have individual addresses, and
  mechanisms for resolving bus contention are inherent in the TWI protocol.
  The TWI protocol is compatible with Philips’ I2C protocol.
   
  Module TWI is a very useful module with method to offer the
  programmer several easy tools to control the TWI of microcontroller.
  
  This module provides...
  
    
  TO Config the 2-wire Serial Interface (TWI)
  
  When the module is initialized, the mode and speed need be configured.
  The TWI hardware dont accept changes of mode and speed when program is runing.
  
  TWI	twi(mode, option);		//Initialized the module passing mode and option configurations
  
  Mode accepted are:
  MASTER to master TWI.
  
  In MASTER mode the option determine the speed of communication, that accept 2 modes:
  FAST to bit rate in 400KHz
  SLOW to bit rate in 100KHz
  
  MASTER mode and FAST bit rate is default.
  
  To send  and received the information using the TWI hardware:
  
  start()					//to send a start condition and communication can begin or be repeated
  stop()					//to send a stop condition and communication can be ended
  
  send(byte)				//to send direct byte information
  byte a = recive() 		//to recive direct byte information

  TWI slave features coming soon.
  
	And this is the END.
