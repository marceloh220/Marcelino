/*
   Marcelo H Moraes
   marceloh220@hotmail.com

   A simple sketch to Hello World in Arduino using Marcelino cores.

   Blink the led in pin 13 of Arduino Uno board, without delay,
   using the overflow of timer0.

   For detail of this modules read the manual.

*/

Digital digital;		  	        //Module Digital instantiate
Timer0 	timer;				          //Module Timer0 instantiate

int aux;					              //Variable for counting time

void time() {

  aux++;                        //Increased variable for counting time

  if (aux == 500) {		          //If passed 500ms
    digital.write(13, TOGGLE);  //Change pin 13 status
    aux = 0;			              //Reset aux variable
  }

  //Each 500ms the led will be change state.
  //F = 1/( 2* 0.5 ) = 1Hz

}

void setup() {

  digital.mode(13, OUTPUT);	    //Pin digital 13 as output
  timer.prescale(64);			      //Explicit the prescale
  timer.attach(OVF, time);		  //Attach the time function on the Overflow interrupt of the timer0

  // Timer overflow in:
  // time = 64 * 255 / 16e6 = 1ms

}

void loop() {

  //Now the loop function is free

}
