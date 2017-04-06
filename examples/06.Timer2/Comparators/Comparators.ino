/*
   Marcelo H Moraes
   marceloh220@hotmail.com

   A simple sketch to Hello World in Arduino using Marcelino cores.

   
   Using the timer comparators to take actions at different times in the same timer.

   For detail of this modules read the manual.

*/

Digital digital;		  	        //Module Digital instantiate
Timer2 	timer;				          //Module Timer2 instantiate

int aux;					              //Variable for counting time

void timeO() {
  
  // time = prescale * ( 255 - timer ) / 16e6
  // time = 1024 * ( 255 - 0 ) / 16e6 = 16.32ms
  
  digital.write(2, TOGGLE);     //Change state of pin 2 each 16.32ms


}

void timeA() {
  
  // time = prescale * ( 255 - compA ) / 16e6
  // time = 1024 * ( 255 - 192 ) / 16e6 ~= 4ms

  // This action will happens 4ms before the overflow

  digital.write(4, TOGGLE);     //Change state of pin 3 4ms before overflow
  
}

void timeB() {
  
  // time = prescale * ( 255 - compB ) / 16e6
  // time = 1024 * ( 255 - 98 ) / 16e6 ~= 10ms

  // And this action will happens 10 ms before the overflow

  digital.write(5, TOGGLE);     //Change state of pin 4 10ms before overflow
  
}

void setup() {

  digital.mode(2, OUTPUT);	    //Pin digital 2 as output
  digital.mode(4, OUTPUT);      //Pin digital 4 as output
  digital.mode(5, OUTPUT);      //Pin digital 5 as output
  
  timer.prescale(1024);			    //Prescale in F_CPU/1024

  timer.compA(192);             //Load 192 value to comparator A
  timer.compB(98);              //Load 98 value to comparator A
  
  timer.attach(OVF, timeO);		  //Attach the timeO function on the Overflow interrupt of the timer2
  timer.attach(COMPA, timeA);   //Attach the timeA function on the Overflow interrupt of the timer2
  timer.attach(COMPB, timeB);   //Attach the timeB function on the Overflow interrupt of the timer2

  //The action happens at interruption suffers a small delay of overhead caused by the calls

  //And obviously, the signals from comparators A and B can be generated on pins OC2A and OC2B 
  //(digital pins 11 and 3, correspondingly) without the need for interruptions

  digital.mode(11, OUTPUT);      //Pin digital 11 (OC2A) as output
  digital.mode(3, OUTPUT);      //Pin digital 3 (OC2B) as output
  
  timer.pinA(CHANGE);           //Change the pin(OC2A) state when occur the match with comparator A
  timer.pinB(CHANGE);           //Change the pin(OC2B) state when occur the match with comparator A

}

void loop() {

  //Now the loop function is free

}
