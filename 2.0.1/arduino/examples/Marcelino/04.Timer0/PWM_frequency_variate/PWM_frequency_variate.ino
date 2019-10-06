/*
   Marcelo H Moraes
   marceloh220@hotmail.com

   A simple sketch Arduino using Marcelino cores.

   Using pwm mode in pin OC0B (Digital pin 5)
   The pwm frequency will be adjusted by the comparator A.

   For detail of this modules read the manual.

*/

Digital digital;                //Module Digital instantiate
Delay   delay;                  //Module Delay instantiate
Timer0  timer;                  //Module Timer0 instantiate

void setup() {

  digital.mode(OC0B, OUTPUT);     //Pin OC0B (Digital pin 5) as output
                                  //To see more about pin's alternate function, read the Digital module manual

  timer.prescale(8);              //Prescale in F_CPU/8
  timer.mode(CORRECT, COMPA);     //Use the timer in CORRECT mode
  //In this mode the timer will generate a pwm wave with constant phase
  //The top value now is the comparator A

  //Note for the maximum and minimum frequency supported by the prescaler, this can be calculated with:
  //        fmax = 16MHz / (2 * prescale * 1)      with comparator A equal 0
  //        fmin = 16MHz / (2 * prescale * 256)    with comparator A equal 255
  //In the prescale 1/8 this range is:
  //  fmax = 1.0MHz
  //  fmin = 3.9KHz

}

void loop() {

  //Here the frequency of pwm will be variated
  for (int i = 0; i <= 150; i += 50) {

    timer.compA(100 + i);     //The comparator A will variate from 100 to 250

    //f1 = 16MHz / (2 * 8 * 100) = 10KHz
    //f2 = 16MHz / (2 * 8 * 150) = 6.6KHz
    //f3 = 16MHz / (2 * 8 * 200) = 5KHz
    //f4 = 16MHz / (2 * 8 * 250) = 4KHz

    for (int aux = 0; aux < timer.compA(); aux++) {

      //The pwm interval for this aplication is from 0 to the value in comparator A

      timer.pwmB(aux);          //Generate pwm in OC0B
      delay.ms(10);             //Wait a time of variation

    }

    delay.ms(500);            //Wait a time of variation, i can measure the frequencies

  }

  delay.ms(500);            //Wait a time of variation, to can measure the frequency

  //Note, in this application the resolution of the PWM decreases as the value of comparator A decreases

}
