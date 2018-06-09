/*
 * Marcelo H Moraes
 * marceloh220@hotmail.com
 * 
 * Read the analog pin A0 of Arduino Uno board
 * and by applying a simple moving average algorithm to stabilize the reading.
 * 
 * A simple sketch in Arduino using Marcelino cores.
 * 
 * For detail of the modules read the manual.
 * 
 */

#define Max_Reads 100     //Number of readings in the average calculation
                          //More reads, more stabilition, but more delay in readings

Analog analog;            //Module Analog instantiate
Serial serial(9600);      //Module Serial instantiate

word readings[Max_Reads]; //Vector to save the reads

word total = 0;           //To save the sum of read values
word index = 0;           //To position the reading
word average = 0;         //To save the average of values read

void setup() {
  //The Analog module initiate with a DEFAULT aref and prescale in 1/64
}

void loop() {

  total -= readings[index];             //Decrease previous reading of total
  
  readings[index] = analog.read(A0);    //Saves the new value read in vector
  
  total += readings[index++];           //Sum the new value in total

  if(index == Max_Reads)                //If in the end of vector
    index = 0;                          //Return to initial position

  average = total / Max_Reads;          //Calcules the average of readings

  serial.println(average);              //Print the average in the serial monitor
}
