/*
   Marcelo H Moraes
   marceloh220@hotmail.com

   Hello World!
   All the fancy is only for demonstration
*/

#include <IHM8574.h>

uint8_t s, m, h;

//(address)
IHM8574 board(0x70);

Timer0 timer;

void setup() {
  board.background(HIGH);
  board.set(2, 0);
  String a = "Hello World!";
  board.print(a);
}

void loop() {
  board.set(0, 1);
  board.print(timer.millis() / 1000);
  board.print("seconds");
}
