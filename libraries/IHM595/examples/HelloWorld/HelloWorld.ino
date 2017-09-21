/*
 * Marcelo H Moraes
 * marceloh220@hotmail.com
 * 
 * Hello World!
 * All the fancy is only for demonstration
 */

#include <IHM595.h>

uint8_t s,m,h;
uint64_t mil;
//(Data pin, Clock pin, Enable pin)
IHM595 board(2,3,4);

Timer0 timer;

void setup() {
  board.backlight(HIGH);
  board.set(2,0);
  String a = "Hello World!";
  board.print(a);
}

void loop() {
    board.set(0,1);
    board.print(timer.millis()/1000);
	board.print("seconds");
}
