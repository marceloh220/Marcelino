#include <CLZD01.h>

#define dataPin   2
#define clockPin  3

Serial monitor(9600);
CLZD temperature(dataPin, clockPin);

void setup() {



  
}



void loop() {

  monitor.print(temperature.read());
  monitor.println("° C");

  
}

