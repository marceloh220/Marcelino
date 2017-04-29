/*
 *  Bits16 Hello World
 *  
 *  Desmonstration of Bits16 device with ports
 */
#include <Bits16.h>

//Bits16 board_name(clock_pin, data_pin);
Bits16 board(2,3);

void setup() {
  //init board
  board.begin();

}

void loop() {
  
  if(digitalRead(4))           //Test pin 4
    board.out(P0,HIGH);        //Put P0 in HIGH
  else board.out(P0,LOW);      //Put P0 in LOW
  
  if(digitalRead(5))          //Test pin 5
    board.out(P1,HIGH);       //Put P1 in HIGH
  else board.out(P1,LOW);     //Put P1 in LOW

}
