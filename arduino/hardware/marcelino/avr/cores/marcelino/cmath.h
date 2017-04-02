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
 

#ifndef CMATH_H
#define CMATH_H

#include "defines.h"
	
class Math {

public:

	//Trigonometric
	inline float sin(float x) { return (float)::sin(x);}
	inline float cos(float x) { return (float)::cos(x);}
	inline float tan(float x) { return (float)::tan(x);}
	inline float arcsin(float x) { return (float)asin(x);}
	inline float arccos(float x) { return (float)acos(x);}
	inline float arctan(float x) { return (float)atan(x);}

	//Exponential
	inline float pow(float x, float y) { return (float)::pow(x,y); }
	float euler(float x);

	//Root functions
	inline float sqrt(float x) { return (float)::sqrt(x);}
	float sqrt(float x, float y);
	
	//Logarithms
	inline float log(float x) { return (float)log10(x);}
	float log(float base, float x);
	inline float ln(float x) { return (float)::log(x);}

	//Utils
	inline float abs(float x) { return (float)fabs(x);}
	inline float max(float x, float y) { return (float)fmax(x,y);}
	inline float min(float x, float y) { return (float)fmin(x,y);}
	inline float trunc(float x) { return (float)::trunc(x);}
	inline float round(float x) { return (float)::round(x);}
	long random(long big);
	long random(long small, long big);

	//Conversions
	inline float rad(float _deg) { return _deg*DEG_TO_RAD;}
	inline float deg(float _rad) { return _rad*RAD_TO_DEG;}
	inline float inch(float _cm) { return _cm*CM_TO_INCH;}
	inline float cm(float _inch) { return _inch*INCH_TO_CM;}
	long tobcd(long _dec);
	long todec(long _bcd);
	long map(long x, long in_min, long in_max, long out_min, long out_max);
	inline float omega(uint32_t freq) { return (float)TWO_PI*freq; }
	
	//Constants
	inline float pi(){ return (float)PI; }
	inline float euler(){ return (float)EULER; }
	
};

#endif
