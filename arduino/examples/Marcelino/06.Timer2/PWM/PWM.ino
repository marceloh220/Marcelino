/*
   Marcelo H Moraes
   marceloh220@hotmail.com

   A simple sketch Arduino using Marcelino cores.

   Using pwm mode in pin OC2A (Digital pin 11) and pin OC2B (Digital pin 3)

   For detail of this modules read the manual.

*/

Digital digital;                //Module Digital instantiate
Delay   delay;                  //Module Delay instantiate
Timer2  timer;                  //Module Timer2 instantiate

void setup() {

  digital.mode(11, OUTPUT);     //Pin digital 11(OC2A) as output
  digital.mode(3, OUTPUT);      //Pin digital 3(OC2B) as output

  timer.config(FAST);           //The timer start in NORMAL mode, now he's is change to FAST mode
                                //In this mode the timer will generate a fast pwm wave
                                //The fast pwm mode is a basic  mode to use this feature, it can control various device
                                //But for more accurate control of induction devices, such as motors, the correct phase mode can be selected with the CORRECT mode
                               
  //In a prescale 1/64 the fixed frequency of pwm can be calculate with
  //  fpwm = 16MHz / ( prescale * 255 ) => fpwm = 16MHz / ( 64 * 255 ) = 980Hz
  //The frequency can be changed modifying the prescale

  //The range of pwm for this timer are of 0 at 255

}

void loop() {

  //Here the pulse width will vary from 0 to 255
  for(int aux=0; aux<255; aux++) {
    timer.pwmA(aux);                  //Generate pwm in digital pin 11
    timer.pwmB(aux, INVERT);          //Generate pwm in digital pin 3, but inverted
    delay.us(200);                    //Wait a time of variation
  }

}
