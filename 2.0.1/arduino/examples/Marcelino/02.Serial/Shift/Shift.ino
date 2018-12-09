/*
 * Marcelo H Moraes
 * marceloh220@hotmail.com
 * 
 * Send a byte with de Synchronous mode USART.
 * A simple sketch to Hello World in Arduino using Marcelino cores.
 * 
 * For detail of the modules read the manual.
 * 
 */

Serial serial;        //Module Serial instantiate

void setup() {
  
  serial.mode(SYNCHRON);          //Select the SYNCHRON mode

  //In this mode the XCK pin (Digital pin 4) will send the clock
  
}

void loop() {

  serial.write(0x09);       //Send a simple byte to serial hardware
  
}
