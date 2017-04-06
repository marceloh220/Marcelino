/*
 * Marcelo H Moraes
 * marceloh220@hotmail.com
 * 
 * Read the analogic pin A0 of Arduino Uno board.
 * A simple sketch in Arduino using Marcelino cores.
 * 
 * For detail of the modules read the manual.
 * 
 */

Analog analog;              //Module Analog instantiate
Serial serial(9600);        //Module Serial instantiate

void setup() {
  //The Analog module initiate with a DEFAULT aref and prescale in 1/64
}

void loop() {

  word a = analog.read(A0);   //Read the analog pin A0

  serial.println(a);          //Print the value read in serial monitor
  
}
