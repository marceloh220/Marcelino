/*
 * Marcelo H Moraes
 * marceloh220@hotmail.com
 * 
 * Read a button in a pin 2 of Arduino Uno board and set or clear pin 13.
 * A simple sketch to read pins in Arduino using Marcelino cores.
 * 
 * For detail of the modules read the manual.
 * 
 */

Digital digital;		  //Module Digital instantiate
Delay	delay;			    //Module Delay instantiate

void setup() {
	
	digital.mode(13,OUTPUT);	//Pin digital 13 as output
	digital.mode(2,PULLUP);		//Pin digital 2 as input with internal pullup resistor
	
}

void loop() {

  if(digital.read(2))       //if digital pin 2 is high
    digital.write(13,LOW);  //Digital pin 13 is low
  else
	  digital.write(13,HIGH);	//Digital pin 13 is high
	delay.ms(50);				      //Wait 50 milliseconds to debounce
	
}
