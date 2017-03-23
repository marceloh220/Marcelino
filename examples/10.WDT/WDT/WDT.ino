/*
 * Marcelo H Moraes
 * marceloh220@hotmail.com
 * 
 * Using the Watchdog Timer (WDT) to prevent freeze problems in microcontroller.
 * A simple sketch in Arduino using Marcelino cores.
 * 
 * For detail of the modules read the manual.
 * 
 */

Digital digital;          //Active the Digital module
Delay   delay;            //Active the Delay module
WDT     wdt;              //Active the WDT module

void setup() {

  digital.output(13);     //Pin 13 as output
  digital.pullup(8);      //Pin 8 as input with pull-up resistor

  wdt.config(RESET);      //Config the WDT to do a reset when occur a overflow
  wdt.timeout(W_4S);      //Set the overflow to occur in 4 seconds
  wdt.enable();           //Enable the WDT

}

void loop() {

  digital.toggle(13);     //Blink the led in pin 13
  wdt.clear();            //Clears WDT by stopping the reset

  if (digital.ifclear(8))
    while (1);            //Simulation of a microcontroller freeze problem

  delay.ms(500);          //Delay to blink led

}
