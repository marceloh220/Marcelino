/*
 * EEPROM Read
 *
 * Reads the value of each byte of the EEPROM and prints it
 * to the computer.
 * This example code is in the public domain.
 */

Serial serial;
EEPROM eeprom;
Delay delay;

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

void setup() {

}

void loop() {
  // read a byte from the current address of the EEPROM
  value = eeprom.read(address);

  serial.print(address);
  serial.print("\t");
  serial.print(value, DEC);
  serial.println();

  /***
    Advance to the next address, when at the end restart at the beginning.

    Larger AVR processors have larger EEPROM sizes, E.g:
    - ATmega328: 512b EEPROM storage.
    - ATmega168: 1kb EEPROM storage.

    Rather than hard-coding the length, you should use the pre-provided length function.
    This will make your code portable to all AVR processors.
  ***/
  address = address + 1;
  if (address == eeprom.length()) {
    address = 0;
  }

  /***
    As the EEPROM sizes are powers of two, wrapping (preventing overflow) of an
    EEPROM address is also doable by a bitwise and of the length - 1.

    ++address &= eeprom.length() - 1;
  ***/

  delay.ms(500);
}
