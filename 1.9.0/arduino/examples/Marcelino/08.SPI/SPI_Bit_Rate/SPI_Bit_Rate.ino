/*
 * Marcelo H Moraes
 * marceloh220@hotmail.com
 * 
 * Send anythig to any SPI device.
 * A simple sketch in Arduino using Marcelino cores.
 * 
 * For detail of the modules read the manual.
 * 
 */

Delay delay;          //Module Delay instantiate
SPI spi(MASTER, 64);  //Module Serial instantiate in master mode and 1/64 bit rate

//By default the SPI module initiate in MASTER mode and 1/16 prescale
//    SCK_frequency = 16MHz / 64 = 250KHz

void setup() {
  
  
}

void loop() {
  
  spi.send(0xFF);           //Send something to any SPI device
  delay.ms(500);            //Wait 500 milliseconds to next toggle
  
}
