/*
 * EEPROM Clear
 *
 * Sets all of the bytes of the EEPROM to 0.
 * Please see eeprom_iteration for a more in depth
 * look at how to traverse the EEPROM.
 *
 * This example code is in the public domain.
 */

Digital digital;
EEPROM eeprom;

void setup() {
  // initialize the LED pin as an output.
  digital.mode(13, OUTPUT);
  
  /***
    Iterate through each byte of the EEPROM storage.

    Larger AVR processors have larger EEPROM sizes, E.g:
    - ATmega168: 512b EEPROM storage.
    - ATmega328: 1kb EEPROM storage.

    Rather than hard-coding the length, you should use the pre-provided length function.
    This will make your code portable to all AVR processors.
  ***/

  for (int i = 0 ; i < eeprom.length() ; i++) {
    eeprom.write(i, 0);
  }

  // turn the LED on when we're done
  digital.write(13, HIGH);
}

void loop() {
  /** Empty loop. **/
}
