/*
   Marcelo H Moraes
   marceloh220@hotmail.com

   A simple sketch Arduino using Marcelino cores.

   Using pwm mode in pin OC0A and pin OC0B

   For detail of this modules read the manual.

*/

Digital digital;                //Module Digital instantiate
Delay   delay;                  //Module Delay instantiate
Timer0  timer;                  //Module Timer0 instantiate

void setup() {

  digital.mode(OC0A, OUTPUT);   //Pin OC0A (Digital pin 6) as output
  digital.mode(OC0B, OUTPUT);   //Pin OC0B (Digital pin 5) as output
                                //To see  more about pin's alternatives functions, read the Digital module manual

  timer.mode(FAST);             //The timer is configured in FAST mode
                                //In this mode the timer will generate a fast pwm wave
                                //The fast pwm mode is a basic  mode to use this feature, it can control various device
                                //But for more accurate control of induction devices, such as motors, the correct phase mode can be selected with the CORRECT mode

  timer.prescale(P_64);         //Configute prescale of timer for F_CPU/64
                               
  //In a prescale 1/64 the fixed frequency of pwm can be calculate with
  //  fpwm = F_CPU / ( prescale * 256 )
  //  fpwm = 1MHz / ( 64 * 256 ) = ~61Hz
  //  fpwm = 8MHz / ( 64 * 256 ) = ~488Hz
  //  fpwm = 16MHz / ( 64 * 256 ) = ~976Hz
  //The frequency can be changed modifying the prescale

  //The range of pwm for this timer are of 0 at 255

}

void loop() {

  //Here the pulse width will vary from 0 to 255
  for(int aux = 0; aux < 255; aux++) {
    timer.pwmA(aux);                  //Generate pwm in pin OC0A
    timer.pwmB(aux, INVERT);          //Generate pwm in pin OC0B, but inverted
    delay.us(200);                    //Wait a time of variation
  }

}
