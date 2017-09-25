 /*
  Copyright (c) 2017 Marcelo Henrique Moraes

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3.0 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

 */

#ifndef _CLZD01_H_
#define _CLZD01_H_

#include <marcelino.h>

class CLZD: private Digital {

private:
  
	uint8_t data, clock;
	uint16_t temp;

	void pulse();
	void com();

public:

	CLZD(uint8_t dataPin, uint8_t clockPin);
	float read();

};


#endif
