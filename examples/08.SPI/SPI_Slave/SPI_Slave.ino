/*
   Marcelo H Moraes
   marceloh220@hotmail.com

   Recive and send anythig to any SPI master device.
   A simple sketch in Arduino using Marcelino cores.

   For detail of the modules read the manual.

*/

Digital digital;      //Module Digital instantiate
Delay delay;          //Module Delay instantiate
SPI spi(SLAVE);       //Module Serial instantiate in slave mode, the bit rate is determined by the master anyway

void instruction() {

  byte aux = spi.get();           //Reads data received from SPI

  digital.port(&PORTD, aux);      //Put received data from SPI in PORTD

  spi.put(0xFF);                  //Send something to the master on the next SPI broadcast

}

void setup() {

  digital.port(&DDRD, 0xFF); //Made all pins of PORTD output, of Digital pin 0 to Digital pin 7

  spi.attach(instruction);  //Attach the function instruction in the SPI Serial Transfer Complete

}

void loop() {

  //Do something while there is no SPI activity

}
