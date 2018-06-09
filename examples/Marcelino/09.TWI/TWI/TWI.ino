/*
 * Marcelo H Moraes
 * marceloh220@hotmail.com
 * 
 * Send anythig to any TWI device.
 * A simple sketch in Arduino using Marcelino cores.
 * 
 * For detail of the modules read the manual.
 * 
 */

Delay delay;          //Module Delay instantiate
TWI twi;              //Module TWI instantiate

//By default the TWI module initiate in MASTER mode FAST bit rate
//    SCL_frequency = 400KHz

#define address 0x42  //Device's address

byte data = 0;        //Data to be sent

void setup() {
  
}

void loop() {
  
  twi.start();              //Send a start condition
  twi.send(address);        //Send the device's address
  twi.send(data);           //Send the data to device
  twi.stop();               //Send a stop condition
  data++;                   //Increase the data to send
  delay.ms(500);            //Wait 500 milliseconds to next broadcast
  
}
