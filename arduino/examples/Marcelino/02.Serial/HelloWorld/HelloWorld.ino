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
  serial.println("Hello World!"); //Simple print the message
  delay.ms(2000);                 //Wait to you see that print
  
}

void loop() {
  static long time;         //Only to mark time
  serial < time++;          //Print without a change of line
  serial << " s";           //Print with with a change of line
  digital.write(13,TOGGLE); //Change status of pin digital 13
  delay.ms(1000);           //Wait 1 second to next toggle
  
}
