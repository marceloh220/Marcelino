/*
 * Marcelo H Moraes
 * marceloh220@hotmail.com
 * 
 * Using the Watchdog Timer (WDT) just to make simple timings.
 * A simple sketch in Arduino using Marcelino cores.
 * 
 * For detail of the modules read the manual.
 * 
 */

Digital digital;          //Active the Digital module
Delay delay;              //Active the Delay module
WDT wdt;                  //Active the WDT module
Serial serial;            //Active the Serial module;


byte a;                   //Variable to test no reset

void blink() {

  digital.toggle(13);     //Blink a led each WDT overflow
  
  wdt.config(INTERRUPT);  //Reconfig the WDT to INTERRUPT mode
                          //This needs to be done so the WDT does not reset the microcontroller

}

void setup() {

  digital.output(13);     //Pin 13 as output

  wdt.config(INTERRUPT);  //Config the WDT to call the interrupt when occur a overflow
  wdt.timeout(W_512MS);   //Set the overflow to occur in 512ms
  wdt.attach(blink);      //Attach the blink() function in WDT interrupt
  wdt.enable();           //Enable the WDT

}

void loop() {

  delay.ms(5000);         //A long delay
  serial.println(a++);    //Print variable to confirm no reset

}
