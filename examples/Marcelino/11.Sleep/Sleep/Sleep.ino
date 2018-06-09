/*
 * Marcelo H Moraes
 * marceloh220@hotmail.com
 * 
 * Put the microcontroller to sleep and wake-up him with external interrupt INT0.
 * A simple sketch in Arduino using Marcelino cores.
 * 
 * For detail of the modules read the manual.
 * 
 */


Serial monitor;       //Active the Serial module to print mensage in serial monitor
Timer0 timer;         //Active the Timer0 module to make somes timing with millis()

Digital digital;      //Active the Digital module to configure the digital pin 2 for INT0 interrupt
External interrupt;   //Active the External module to use the INT0 interrupt to wake up the microcontroller
Delay delay;          //Active the Delay module to make a delay to show the messages

Sleep littlechildren; //Active the Sleep module to put the microcontroller to sleep

byte aux;             //Count the passed time to put microcontroller in sleep mode

void wakeup();        //Prototye of function to wake-up the microcontroller

void setup() {

  digital.pullup(2);  //Config INT0 pin as input with internal pullup resistor
  
}


void loop() {

  delay.ms(1000);                             //Wait a time to work

  monitor.println(timer.millis()/1000);       //Show in serial monitor the timer of microcontroller


  if(aux == 5) {                              //If passed 5 times of 1000 milli seconds
  
    aux = 0;                                  //Reset the variable of time
    
    interrupt.attach(INT0,CHANGE,wakeup);     //Active INT0 interrupt to wake-up the microcontroler
                                              //A logical change in INT0 pin will awaken the microcontroller
    
    monitor.println("Go sleep sweetheart.");  //Print some mensage in serial monitor
    
    delay.us(500);                            //Wait a time to mensage be sended
    littlechildren.sleep(POWERDOWN);          //Put the microcontrolle to sleep in POWERDOWN mode
  
  }

  aux++;    //increase the variable to timing
  
}

void wakeup() {                               //Wake-up function

  littlechildren.disable(SLEEP);              //Disable the sleep
  
  interrupt.detachINT(INT0);                  //Detach the wakeup interrupt to INT0 interrupt
  
  monitor.println("Wake up sweetheart.");     //Print some mensage in serial monitor
  
}

