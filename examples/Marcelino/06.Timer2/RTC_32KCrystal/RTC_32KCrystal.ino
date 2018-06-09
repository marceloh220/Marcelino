/*
   Marcelo H Moraes
   marceloh220@hotmail.com

   A simple sketch Arduino using Marcelino cores.

   Using pwm mode in pin OC0A (Digital pin 6) and
   timer 2 in asynchronous mode with a external cristal of 32.768KHz
   in pins XTAL1 and XTAL2.

   This feature only works with bootloader and fuses configured
   of Marcelino F_CPU: 8MHz.

   For detail of this modules read the manual.

*/

Digital digital;                //Module Digital instantiate
Timer2  timer;                  //Module Timer2 instantiate
Timer0  pwm;                    //Module Timer0 instantiate

void blink() {
  
  digital.write(13, TOGGLE);    //This pin will change any precise 1 second

  // Crystal frequency 32768H
  // time = 1 / f  * prescale * 2^6
  // time = 1 / 32768 * 128 * 256 = 1s
  
}

void setup() {
  
  digital.mode(13,OUTPUT);              //Pin digital 13 as output
  digital.mode(OC0A, OUTPUT);           //Pin digital 6(OC0A) as output
  
  timer.prescale(128);                  //Prescaler of timer2 configured with prescaler 1/128
  timer.attach(OVF,OSCILLATOR, blink);  //Function blink attached in overflow interrupt of timer2 in asynchronous mode with external crystal
  
  pwm.config(FAST);                     //PWM in fast mode
  pwm.pwmA(50);                         //PWM with 50 of 255 width
  //PWM frequency
  // Fpwm = F / ( prescale * 2^8 )
  // Fpwm = 8e6 / ( 64 * 256 ) = 488.28H
  // Only the timer 2 is working in 32.768H frequency

}

void loop() {

}
