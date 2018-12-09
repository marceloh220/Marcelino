/*
 * Marcelo H Moraes
 * marceloh220@hotmail.com
 * 
 * A simple hexadecimal display clock.
 * Well, not so simples. 
 * All the fancy is only for demonstration.
 * You don't realy need of a String object to print something.
 */

#include <IHM8574.h>

uint8_t s,m,h;
uint32_t mil;

//(address)
IHM8574 board(0x70);

Timer0 timer;

void setup() {
  board.background(HIGH);
  board.set(5,0);
  String a = "UPTime";
  board.print(a);
}

void loop() {
    board.set(0,1);
    if(timer.millis()-mil>=1000) {
      s++;
      mil=timer.millis();
    }
    if(s>60) {
      s=0;
      m++;
    }
    if(m>60) {
      m=0;
      h++;
    }
    if(h>24) h=0;
    board.print(' ');
    if(h<16) board.print("0x0");
    else board.print("0x");
    board.print(h,HEX);
    board.print(' ');
    if(m<16) board.print("0x0");
    else board.print("0x");
    board.print(m,HEX);
    board.print(' ');
    if(s<16) board.print("0x0");
    else board.print("0x");
    board.print(s,HEX);
}
