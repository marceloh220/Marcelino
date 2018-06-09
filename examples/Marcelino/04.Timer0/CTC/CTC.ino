/*
   Marcelo H Moraes
   marceloh220@hotmail.com

   A simple sketch Arduino using Marcelino cores.

   Using the CTC mode to generate variable frequency in pin OC0A (Digital pin 6)

   For detail of this modules read the manual.

*/

Digital digital;                //Module Digital instantiate
Delay   delay;                  //Module Delay instantiate
Timer0  timer;                  //Module Timer0 instantiate

void blink() {

  //Here any other pin can be changed with the determined frequency

  digital.write(13, CHANGE);

  //A short delay will occur, but the frequency will be the same

}

void setup() {

  digital.mode(OC0A, OUTPUT);  //Pin OC0A as output

  timer.configure(CTC);        //The timer start in NORMAL mode, now he's is change to CTC mode
  //In this mode the timer will be clean with comparison

  timer.pinA(CHANGE);          //Change the pin(OC0A) state when occur the match with comparator A

  //And naturally, any pin can be used to generate this frequency using the interrupt COMPA of the timer

  digital.mode(13, OUTPUT);    //A pin without any link with the timer is be used like output
  timer.attach(COMPA, blink);  //Jump to blink function when occur a match

}

#define minP  500
#define maxP  5000

//  In this case the frequency is 1/periode
//  Also the minimun frequency will be 1/500us = 2kHz
//  and the maximun frequency will be 1/5000us = 200Hz

void loop() {

  for (int aux = minP; aux < maxP; aux++) {
    timer.period(aux, COMPA);   //Here the period will be variable in the range
    delay.ms(10);               //Wait a time of variation
  }

}
