/*
 * Marcelo H Moraes
 * marceloh220@hotmail.com
 * 
 * Using the Analog comparator, a voltage can be monitored.
 * 
 * A simple sketch in Arduino using Marcelino cores.
 * 
 * For detail of the modules read the manual.
 * 
 */

Digital digital;          //Module Digital instantiate
Analog analog;            //Module Analog instantiate

void compare() {

    //Made some action other action
    digital.write(13, TOGGLE);

}


void setup() {

  //Pin 13 like OUTPUT
  digital.mode(13, OUTPUT);

  //Attach the compare function in Comparator Analog interrupt
  analog.attach(FALLING, INTERNAL, compare);

  //When the voltage applied in AINN pin (Digital pin 7) becomes higher than 1.1V
  //the function compare() will be called
  
}

void loop() {


}
