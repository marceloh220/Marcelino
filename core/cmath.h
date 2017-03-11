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

	//Squares
	inline float sqrt(float x) { return (float)::sqrt(x);}
	float sqrt(float x, float y);

	//Logarithms
	inline float log(float x) { return (float)log10(x);}
	float log(float x, float base);
	inline float ln(float x) { return (float)::log(x);}

	//Utils
	inline float abs(float x) { return (float)fabs(x);}
	inline float max(float x, float y) { return (float)fmax(x,y);}
	inline float min(float x, float y) { return (float)fmin(x,y);}
	inline float trunc(float x) { return (float)trunc(x);}
	inline float round(float x) { return (float)round(x);}
	long random(long big);
	long random(long small, long big);

	//Conversions
	inline float rad(float _deg) { return _deg*DEG_TO_RAD;}
	inline float deg(float _rad) { return _rad*RAD_TO_DEG;}
	inline float inch(float _cm) { return _cm*CM_TO_INCH;}
	inline float cm(float _inch) { return _inch*INCH_TO_CM;}
	long tobcd(long _dec);
	long todec(long _bcd);
	inline float rms(float _vp) { return _vp*SQRT1_2;}
	inline float vp(float _rms) { return _rms*SQRT2;}
	long map(long x, long in_min, long in_max, long out_min, long out_max);

};

#endif
