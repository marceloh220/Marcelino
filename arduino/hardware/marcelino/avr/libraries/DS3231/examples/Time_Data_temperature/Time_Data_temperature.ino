/*
 * Marcelo H Moraes
 * marceloh220@hotmail.com
 * 
 * Blink the led in pin 13 of Arduino Uno board.
 * A simple sketch to Hello World in Arduino using Marcelino cores.
 * 
 * For detail of the modules read the manual.
 * 
 */

#include <DS3231.h>
DS3231    clock(en_us);

Digital   digital;
Delay     delay;
Serial    serial(9600);
Timer1    timer;

void blink() {

    digital.write(13, TOGGLE);
    
}

void setup() {

	digital.mode(13,OUTPUT);
  timer.period(200000);
  timer.attach(OVF,blink);
	
}

void loop() {

  byte aux = clock.hour();
  if(aux<10)
    serial.print('0');
  serial.print(aux);
  serial.print(':');
  aux = clock.minute();
  if(aux<10)
    serial.print('0');
  serial.print(aux);
  serial.print(':');
  aux = clock.second();
  if(aux<10)
    serial.print('0');
  serial.println(aux);
  
  serial.print(clock.weekSTR());
  serial.print(" ");
  aux = clock.day();
  if(aux<10)
    serial.print('0');
  serial.print(aux);
  serial.print(" ");
  serial.print(clock.monthSTR());
  serial.print(", 20");
  aux = clock.year();
  if(aux<10)
    serial.print('0');
  serial.println(aux);
  
  serial.print(clock.temp());
  serial.println("°C");
  
  delay.ms(1000);
	
}
