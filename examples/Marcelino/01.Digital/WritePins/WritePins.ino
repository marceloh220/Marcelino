/*
 * Marcelo H Moraes
 * marceloh220@hotmail.com
 * 
 * Configure and manipulatting various pins in the same function.
 * A simple sketch to Hello World in Arduino using Marcelino cores.
 * 
 * For detail of the modules read the manual.
 * 
 */

Digital digital;      //Module Digital instantiate
Delay delay;          //Module Delay instantiate

void setup() {
  
  digital.output(5,9,10,11,12,13);  //output(n, pins...)
                                    //n: number of pins to configure
                                    //pins: any pin to configure
  
}

void loop() {

  for(int i = 9; i<14; i++) {       //Run a interator to blink the pins in sequential
    digital.write(i, HIGH);
    delay.ms(500);                  //Wait 500 milliseconds
    digital.write(i, LOW);
  }
  
  delay.ms(500);
  
  digital.set(5,9,10,11,12,13);     //set(n, pins...)
                                    //n: number of pins to set in high state
                                    //pins: any pin to set
                                    
  delay.ms(500);
  
  digital.clear(5,9,10,11,12,13);   //clear(n, pins...)
                                    //n: number of pins to clear
                                    //pins: any pin to clear and put in low state            
  
  delay.ms(500);
  
}
