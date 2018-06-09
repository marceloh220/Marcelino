/*
 * Marcelo H Moraes
 * marceloh220@hotmail.com
 * 
 * Print a mensage in the Serial monitor.
 * A simple sketch to Hello World in Arduino using Marcelino cores.
 * 
 * For detail of the modules read the manual.
 * 
 */

Digital digital;      //Module Digital instantiate
Delay delay;          //Module Delay instantiate
Serial serial;        //Module Serial instantiate

void setup() {
  
  digital.mode(13,OUTPUT);        //Pin digital 13 as output
  serial.print("Hello World!");   //Simple print the message
  
}

void loop() {
  
  digital.write(13,TOGGLE); //Change status of pin digital 13
  delay.ms(500);            //Wait 500 milliseconds to next toggle
  
}
