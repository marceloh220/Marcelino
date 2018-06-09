/*
   Marcelo H Moraes
   marceloh220@hotmail.com

   A simple sketch Arduino using Marcelino cores.

   Using pwm mode in pin OC1B (Digital pin 10)
   The pwm frequency will be adjusted by the comparator A.

   Using pwm mode in pin OC1B (Digital pin 10) AND pin OC1A (Digital pin 9)
   The pwm frequency will be adjusted by the capture register.

   For detail of this modules read the manual.

*/

Digital digital;               //Module Digital instantiate
Delay   delay;                 //Module Delay instantiate
Timer1  timer;                 //Module Timer1 instantiate

void setup() {

  digital.mode(10, OUTPUT);    //Pin digital 10(OC1B) as output
  digital.mode(9, OUTPUT);     //Pin digital 9(OC1A) as output

  timer.prescale(8);           //Prescale in F_CPU/8
  timer.config(VARIABLE,CORRECT,COMPA); 
                               //The timer start in NORMAL mode, now he's is change to VARIABLE frequency pwm in CORRECT mode
                               //In this mode the timer will generate a pwm wave with constant phase
                               //The top value now is the comparator A
                               
  //Note for the maximum and minimum frequency supported by the prescaler, this can be calculated with:
  //        fmax = 16MHz / (2 * prescale * 1)      with register equal 0
  //        fmin = 16MHz / (2 * prescale * 65536)  with register equal 65535
  //In the prescale 1/8 this range is:
  //  fmax = 1.0MHz
  //  fmin = 15.25Hz
  //Is a very large range with a timer of 16 bits
  
}

void loop() {
/*
  //Here the frequency of pwm will be variated
  for(int i = 0; i <= 15000; i += 5000) {

    timer.compA(10000+i);       //The comparator A will variate from 10000 to 25000

    //f1 = 16MHz / (2 * 8 * 10000) = 100Hz
    //f2 = 16MHz / (2 * 8 * 15000) = 66Hz
    //f3 = 16MHz / (2 * 8 * 20000) = 50Hz
    //f4 = 16MHz / (2 * 8 * 25000) = 40Hz
    
    for(int aux = 0; aux < timer.compA(); aux++) {
      
      //The pwm interval for this aplication is from 0 to the value in comparator A
      
      timer.pwmB(aux);          //Generate pwm in digital pin 5
      delay.ms(1);              //Wait a time of variation
    
    }

    delay.ms(500);            //Wait a time of variation, i can measure the frequencies
    
  }
*/
  //Now the frequency will be configured by capture register
  
  //Only remember, the minimum frequency is 15Hz and maximum is 1MHz

  timer.config(VARIABLE,CORRECT,CAPT);
                              //Configure the timer to VARIABLE frequency pwm in CORRECT mode
                              //In this mode the timer will generate a pwm wave with constant phase
                              //The top value now is the capture register
  
  for(int i = 4; i <= 10; i++) {

    int a = 1000*i;           //The frequency will be a multiple of 1000
    timer.frequency(a);       //The frequency will variate from 4KHz to 10KHz
    
    for(int aux = 0; aux < timer.capt(); aux++) {
      
      //The pwm interval for this aplication is from 0 to the value in comparator A
      
      timer.pwmA(aux);        //Generate pwm in digital pin 9
      timer.pwmB(aux);        //Generate pwm in digital pin 10
      delay.ms(1);            //Wait a time of variation
    
    }

    delay.ms(500);            //Wait a time of variation, i can measure the frequencies
    
  }

  //Note, in this application the resolution of the PWM decreases as the value of comparator A decreases
  
}
