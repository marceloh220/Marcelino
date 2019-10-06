/*
   Marcelo H Moraes
   marceloh220@hotmail.com

   A simple sketch Arduino using Marcelino cores.

   Using the CTC mode to generate variable frequency in pin OC0A (Digital pin 6)

   For detail of this modules read the manual.

*/

Digital digital;                //Module Digital instantiate
Delay   delay;                  //Module Delay instantiate
Timer1  timer;                  //Module Timer1 instantiate

void comparator() {

  //Here any other pin can be changed with the determined frequency
  
  digital.write(13, TOGGLE);

  //A short delay will occur, but the frequency will be the same

}

void setup() {

  digital.mode(OC1A, OUTPUT);  //Pin OC1A (Digital pin 9) as output

  timer.mode(CTC);             //The timer is configured in CTC mode
                               //In this mode the timer will be clean with match with comparator A

  timer.prescale(8);           //Prescale in F_CPU/8
                              
  timer.pinA(CHANGE);          //Change the pin OC1A state when occur the match with comparator A

  //Now the frequency will be varied
  //Note for the maximum and minimum frequency supported by the prescaler, this can be calculated with:
  //        fmax = 16MHz / (2 * prescale * 1)      with comparator A equal 0
  //        fmin = 16MHz / (2 * prescale * 256)   with comparator A equal 255
  //In the prescale 1/8 this range is:
  //  fmax = 2.0MHz
  //  fmin = 7.812KHz

  //And naturally, any pin can be used to generate this frequency using the interrupt COMPA of the timer

  digital.mode(13, OUTPUT);         //A pin without any link with the timer is be used like output
  timer.attach(COMPA, comparator);  //Jump to comparator function when occur a match


}

#define maxf 30000
#define minf 10000

void loop() {

  for(int aux=minf; aux<maxf; aux++) {
    timer.period(1/aux);              //Here the frequency will be variable in the range of minf to maxf
    delay.us(200);                    //Wait a time of variation
  }

}
