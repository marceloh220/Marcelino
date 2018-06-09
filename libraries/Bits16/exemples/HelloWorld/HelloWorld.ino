/*
 *  Bits16 Hello World
 *  
 *  Desmonstration of Bits16 device with displays on-board
 */
 
#include <Bits16.h>
//Bits16 board_name(data, clock);
Bits16 board(2,3);

Delay delay;

void setup() {


}

void loop() {
  
  for(int aux = 0; aux<99; aux++) {
    board.print(aux);        //just print aux in 7-seg displays, max is 99
    delay.ms(1000);
  }

}
