
   Marcelo H Moraes
   marceloh220@hotmail.com
   
   Digital module is a basic module for handling the digital pins of the microcontroller.
   This provides the methods:
  
   mode(pin,mode); 		//To determine direction of pin
   
   Modes accepted:
   OUTPUT to made the pin like output
   INPUT to made the pin like input
   PULLUP or INPUT_PULLUP to made the pin INPUT with internal pullup resistor
  
  
   write(pin,state);	//To determine the digital state of pin
  
   State accepted:
   LOW or CLEAR to put the pin in low state
   HIGH or SET to put the pin in high state
   TOGGLE or CHANGE to alternate the pin state
  
   read(pin);			//Read state of pin
   Return HIGH (1) or LOW (0), depending on the state of the pin.

   
   Methods to atomics access:
   Configure and manipulate various digital pins in the same function.
   
   input(n, pins...);		  //Configures pins is like input
   output(n, pins...);		//Configures pins is like output
   pullup(n, pins...);		//Configures pins is like input INPUT with internal pullup resistor
   
   set(n, pins...);			  //Set the pins
   clear(n, pins...);		  //Clear the pins
   toggle(n, pins...);		//Toggle the pins
   
   "n" is the number of pins to configure in same instruction, e.g.:
   
   /****************************************************************************************
   Digital digital;					//Load digital module with name digital
   
   void setup() {
	   digital.output(3,5,6,13);	//In same time are configured 3 pins in output mode
									              //The digital pin 5, digital pin 6 and digital pin 13
   }
   ****************************************************************************************/
   
   ifset(pin)			  //Test if pin is set
   ifclear(pin)			//Test if pin is clear 
  
   ATmega328/p:
   
   In F_CPU 16MHZ, the microcontroller have your clock 
   running with the crystal of 16MH built in Arduino's board.
   
   In F_CPU 8MHz, the microcontroller run with a internal clock in 8MHz.
   The speed is half, but the timer2 can be used like asynchronous mode,
   using a external crystal on 32.768KHz can be implemented a RTC (Real Time Clock)
   using only the microcontroller.
   
   And anyway, even if this feature is not needed, the programmer will gain two more digital pin.
   These pins will be called 20 and 21 pins and the digital method can be used in both
					        __ __
            RST	-|	U  |-	D19/A5/SCL
          D0/RX	-|	   |-	D18/A4/SDA
          D1/TX	-|	   |-	D17/A3
	      D2/INT0	-|	   |-	D16/A2
  D3/INT1/OC2B	-|	   |-	D15/A1
		  D4/T0/XCK	-|	   |-	D14/A0
			      VCC	-|	   |-	GND
			      GND	-|	   |-	Aref
	       D20/X1	-|	   |-	AVCC
	       D21/X2	-|	   |-	D13/SCK
    D5/T1/OC0B	-|	   |-	D12/MISO
   D6/AINP/OC0A	-|	   |-	D11/OC2A/MOSI
		   D7/AINN	-|	   |-	D10/OC1B/SS
		     D8/ICP	-|_____|-	D9/OC1A
					  
					        DIP-28
   
   Alternate Function of pins:
   
   RST: 	Reset of system;
   RX:		USART Input Pin
   TX:		USART Output Pin
   INT0:	External Interrupt 0 Input
   INT1:	External Interrupt 1 Input
   OC2B:	Compare Match B Output and PWM Output of timer2
   OC2A:	Compare Match A Output and PWM Output of timer2
   T0:		Timer/Counter 0 External Counter Input
   XCK:		USART External Clock Input/Output
   T1:		Timer/Counter 1 External Counter Input
   OC0B:	Compare Match B Output and PWM Output of timer0
   OC0A:	Compare Match A Output and PWM Output of timer0
   AINP:	Analog Comparator Positive Input
   AINN:	Analog Comparator Negative Input
   ICP:		Timer/Counter 1 Capture Input
   OC1A:	Compare Match A Output and PWM Output of timer1
   OC1B:	Compare Match B Output and PWM Output of timer1
   SS:		SPI Bus Master Slave select, this input is active in low state
   MOSI:	SPI Bus Master Output/Slave Input
   MISO:	SPI Bus Master Input/Slave Output
   SCK:		SPI Bus Master clock OUTPUT
   SCL:		2-wire Serial Bus Clock Line
   SDA:		2-wire Serial Bus Data Input/Output Line
   
   X1//X2:	External Crystal ocillator.
   
   VCC:		Digital supply voltage
   GND:		Ground
   AVCC:	A/D Converte supply voltage
   Aref:	Analog reference pin for the A/D Converter
   
   D0 to D21:	Digital pins
   A0 to A5:	Analog A/D Converter pins

   ATtiny85:
   
   In F_CPU 16MHZ, the microcontroller have your clock 
   running with the PLL internal circuit.
   
   In F_CPU 8MHz, the microcontroller run with a internal clock in 8MHz.

   In F_CPU 1MHz, the microcontroller run with a internal clock in
   8MHz divided by 8 resulting in low power consumition of device.
   

                  +--U--+
            RST  1|     |8  VCC
          D3/A3  2|     |7  D2/A1/INT0/T0/SCK/USCK/SCL
          D4/A2  3|     |6  D1/OC0B/AINN/MISO/DO
            GND  4|     |5  D0/OC0A/AINP/MOSI/DI/SDA/Aref
                  +-----+

                   DIP-8

   Alternate Function of pins:
   
   RST: 	Reset of system;
   DI:		USI Input Pin
   DO:		USI Output Pin
   INT0:	External Interrupt 0 Input
   T0:		Timer/Counter 0 External Counter Input
   USCK:	USI Clock Input/Output
   OC0B:	Compare Match B Output and PWM Output of timer0
   OC0A:	Compare Match A Output and PWM Output of timer0
   AINP:	Analog Comparator Positive Input
   AINN:	Analog Comparator Negative Input
   MOSI:	SPI Bus Master Output/Slave Input
   MISO:	SPI Bus Master Input/Slave Output
   SCK:		SPI Bus Master clock Output
   SCL:		2-wire Serial Bus Clock Line
   SDA:		2-wire Serial Bus Data Input/Output Line
   
   VCC:		Supply voltage
   GND:		Ground
   Aref:	Analog reference pin for the A/D Converter
   
   D0 to D4:	Digital pins
   A1 to A3:	Analog A/D Converter pins

   
   Macros defineds:
   
	sbi(sfr, bit)				//Set the Bit In register
	cbi(sfr, bit)				//Clear the Bit In register
	tbi(sfr, bit)				//Toggle the Bit In register

	is_set(sfr, bit)			//Test if bit is set in register
	is_clear(sfr, bit)			//Test if bit is clear in register

	bv(bit)						//Bit shift to convert a bit in a mask byte value
   
  
   Delay module provide methods to handle delays of system.
   This provides the methods:
  
   ms(long); 		//Delay in milliseconds
   us(long); 		//Delay in microseconds
   
