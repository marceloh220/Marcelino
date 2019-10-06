/*
   Marcelo H Moraes
   marceloh220@hotmail.com

   A simple sketch Arduino using Marcelino cores.

   Using pwm mode in pin OC1A (Digital pin 9) and pin OC1B (Digital pin 10)

   For detail of this modules read the manual.

*/

Digital digital;                //Module Digital instantiate
Delay   delay;                  //Module Delay instantiate
Timer1  timer;                  //Module Timer1 instantiate

void setup() {

  digital.mode(9, OUTPUT);     //Pin digital 9(OC1A) as output
  digital.mode(10, OUTPUT);    //Pin digital 10(OC1B) as output

  //To see more about pin's alterntive function, read the Digital module manual

}

void loop() {

  //And now the news starts
  
  timer.prescale(64);                 //Select a prescaler 1/64 for this timer
  timer.mode(FAST8);                  //Timer configured to FAST mode, to generate a fast pwm with 8 bits of resolution
                                      //The frequency of pwm can be calculate with:
                                      //  fpwm = 16MHz / ( prescale * 255 ) => fpwm = 16MHz / ( 64 * 255 ) = 980Hz
                                      
  
  for(int aux=0; aux<255; aux++) {    //Here the pulse width will vary from 0 to 255
    timer.pwmA(aux);                  //Generate pwm in digital pin 9
    timer.pwmB(aux, INVERT);          //Generate pwm in digital pin 10, but inverted
    delay.ms(10);                     //Wait a time of variation
  }

  timer.mode(FAST9);                  //Timer configured to FAST9 mode, to generate a fast pwm with 9 bits of resolution
                                      //The frequency of pwm can be calculate with:
                                      //  fpwm = 16MHz / ( prescale * 511 ) => fpwm = 16MHz / ( 64 * 511 ) = 489Hz
                                      
  
  for(int aux=0; aux<511; aux++) {    //Here the pulse width will vary from 0 to 511
    timer.pwmA(aux);                  //Generate pwm in digital pin 9
    timer.pwmB(aux, INVERT);          //Generate pwm in digital pin 10, but inverted
    delay.ms(10);                     //Wait a time of variation
  }

  timer.prescale(8);                  //Change prescaler of timer to 1/8
  timer.mode(FAST10);                 //Timer configured to FAST10 mode, to generate a fast pwm with 10 bits of resolution
                                      //The frequency of pwm can be calculate with:
                                      //  fpwm = 16MHz / ( prescale * 1023 ) => fpwm = 16MHz / ( 8 * 1023 ) = 1955Hz
                                      
  
  for(int aux=0; aux<1023; aux++) {   //Here the pulse width will vary from 0 to 1023, more resolution =)
    timer.pwmA(aux);                  //Generate pwm in digital pin 9
    timer.pwmB(aux, INVERT);          //Generate pwm in digital pin 10, but inverted
    delay.ms(10);                     //Wait a time of variation
  }

  timer.prescale(64);                 //Change prescaler of timer to 1/64. Why? Because we can!
  timer.mode(CORRECT8);               //Timer configured to CORRECT mode, to generate a correct phase pwm with 8 bits of resolution
                                      //The frequency of pwm can be calculate with:
                                      //  fpwm = 16MHz / ( 2 * prescale * 255 ) => fpwm = 16MHz / ( 2 * 64 * 255 ) = 490Hz
                                      
  
  for(int aux=0; aux<255; aux++) {   //Here the pulse width will vary from 0 to 255
    timer.pwmA(aux);                  //Generate pwm in digital pin 9
    timer.pwmB(aux, INVERT);          //Generate pwm in digital pin 10, but inverted
    delay.ms(10);                     //Wait a time of variation
  }
  
  timer.prescale(8);                  //Change prescaler of timer to 1/8. Change again? Yep, is so easy, that becomes fun.
  timer.mode(CORRECT9);               //Timer configured to CORRECT9 mode, to generate a correct phase pwm with 9 bits of resolution
                                      //The frequency of pwm can be calculate with:
                                      //  fpwm = 16MHz / ( 2 * prescale * 511 ) => fpwm = 16MHz / ( 2 * 8 * 511 ) = 1955Hz
                                      
  
  for(int aux=0; aux<511; aux++) {    //Here the pulse width will vary from 0 to 511
    timer.pwmA(aux);                  //Generate pwm in digital pin 9
    timer.pwmB(aux, INVERT);          //Generate pwm in digital pin 10, but inverted
    delay.ms(10);                     //Wait a time of variation
  }

  timer.prescale(1);                  //Change prescaler of timer to 1/1. You know how i like that =)
  timer.mode(CORRECT10);              //Timer configured to CORRECT10 mode, to generate a correct phase pwm with 10 bits of resolution
                                      //The frequency of pwm can be calculate with:
                                      //  fpwm = 16MHz / ( 2 * prescale * 1023 ) => fpwm = 16MHz / ( 2 * 1 * 1023 ) = 7820Hz
                                      
  
  for(int aux=0; aux<1023; aux++) {   //Here the pulse width will vary from 0 to 1023
    timer.pwmA(aux);                  //Generate pwm in digital pin 9
    timer.pwmB(aux, INVERT);          //Generate pwm in digital pin 10, but inverted
    delay.ms(10);                     //Wait a time of variation
  }

  timer.prescale(OFF);                //Turn of the timer. Simple and intuitive, that make easy stuffs.

  //Yeah, you can measure the frequency, is all right.

}
