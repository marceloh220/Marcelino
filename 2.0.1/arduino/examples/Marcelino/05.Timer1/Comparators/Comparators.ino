 /*
   Marcelo H Moraes
   marceloh220@hotmail.com

   A simple sketch to Hello World in Arduino using Marcelino cores.

   
   Using the timer comparators to take actions at different times in the same timer.

   For detail of this modules read the manual.

*/

Digital digital;		  	        //Module Digital instantiate
Timer1 	timer;				          //Module Timer1 instantiate

int aux;					              //Variable for counting time

void time1() {
  
  // time = prescale * ( 65535 - timer ) / 16e6
  // time = 8 * ( 65535 - 0 ) / 16e6 = 32.768ms
  // Note, the timer 1 are a 16 bits timer. Is all in the manual of module.
  
  digital.write(2, TOGGLE);     //Change state of pin 2 each 32.768ms


}

void timeA() {
  
  // time = prescale * ( 65535 - compA ) / 16e6
  // time = 8 * ( 65535 - 45535 ) / 16e6 = 10ms

  // This action will happens 10ms before the overflow

  digital.write(3, TOGGLE);     //Change state of pin 3 10ms before overflow
  
}

void timeB() {
  
  // time = prescale * ( 65535 - compB ) / 16e6
  // time = 8 * ( 65535 - 25535 ) / 16e6 = 20ms

  // And this action will happens 20 ms before the overflow

  digital.write(4, TOGGLE);     //Change state of pin 4 20ms before overflow
  
}

void setup() {

  digital.mode(2, OUTPUT);	    //Pin digital 2 as output
  digital.mode(3, OUTPUT);      //Pin digital 3 as output
  digital.mode(4, OUTPUT);      //Pin digital 4 as output

  timer.mode(NORMAL);           //Timer1 in normal mode
  timer.prescale(8);			      //Prescale in F_CPU/8

  timer.compA(45535);           //Load 45535 value to comparator A
  timer.compB(25535);           //Load 25535 value to comparator B
  
  timer.attach(OVF, time1);		  //Attach the timeO function on the Overflow interrupt of the timer1
  timer.attach(COMPA, timeA);   //Attach the timeA function on the Overflow interrupt of the timer1
  timer.attach(COMPB, timeB);   //Attach the timeB function on the Overflow interrupt of the timer1

  //And obviously, the signals from comparators A and B can be generated on pins OC1A and OC1B 
  //(digital pins 9 and 10, correspondingly) without the need for interruptions

  digital.mode(OC1A, OUTPUT);   //Pin OC1A (Digital pin 9) as output
  digital.mode(OC1B, OUTPUT);   //Pin OC1B (Digital pin 10) as output
  //To see more about pin's alternate functions, read Digital module manual
  
  timer.pinA(CHANGE);           //Change the pin OC1A state when occur the match with comparator A
  timer.pinB(CHANGE);           //Change the pin OC1B state when occur the match with comparator B

}

void loop() {

  //Now the loop function is free

}
