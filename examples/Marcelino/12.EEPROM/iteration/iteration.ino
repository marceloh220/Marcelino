/***
    eeprom_iteration example.

    A set of example snippets highlighting the
    simplest methods for traversing the EEPROM.

    Running this sketch is not necessary, this is
    simply highlighting certain programming methods.

    Written by Christopher Andrews 2015
    Released under MIT licence.
***/

EEPROM eeprom;

void setup() {

  /***
    Iterate the EEPROM using a for loop.
  ***/

  for (int index = 0 ; index < eeprom.length() ; index++) {

    //Add one to each cell in the EEPROM
    eeprom[ index ] += 1;
  }

  /***
    Iterate the EEPROM using a while loop.
  ***/

  int index = 0;

  while (index < eeprom.length()) {

    //Add one to each cell in the EEPROM
    eeprom[ index ] += 1;
    index++;
  }

  /***
    Iterate the EEPROM using a do-while loop.
  ***/

  int idx = 0;  //Used 'idx' to avoid name conflict with 'index' above.

  do {

    //Add one to each cell in the EEPROM
    eeprom[ idx ] += 1;
    idx++;
  } while (idx < eeprom.length());


} //End of setup function.

void loop() {}
