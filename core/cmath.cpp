#include "cmath.h"

float Math::sqrt(float x, float y) {
	return (float)::pow(x,1/y);
}

float Math::log(float x, float base) {
	return (float)(log10(x)/log10(base));
}

long Math::random(long big) {
	if (big == 0)
		return 0;
	return rand() % big;
}

long Math::random(long small, long big) {
	if (small >= big)
		return small;
	return random(big - small) + small;
}

long Math::tobcd(long _dec) {
	return ( ( (_dec / 10) * 16 ) + (_dec % 10) );	
}

long Math::todec(long _bcd) {
	return ((_bcd & 0xF0) >> 4) * 10 + (_bcd & 0x0F);
}

long Math::map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
