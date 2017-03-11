#ifndef TIMER2_H
#define TIMER2_H

#include "defines.h"


class Timer2 {
private:
	uint16_t def_prescale;
	uint8_t def_top, def_mode;
public:
	Timer2();
		
	//configs of timer
	void prescale(uint16_t scale);;
	void config(uint8_t mode, uint8_t top = 0);
	void pinA(uint8_t mode);
	void pinB(uint8_t mode);
	
	//register of timer
	inline void timer(uint8_t value) { TCNT2 = value; }
	inline void compA(uint8_t value) { OCR2A = value; }
	inline void compB(uint8_t value) { OCR2B = value; }
	inline uint8_t timer() { return TCNT2; }
	inline uint8_t compA() { return OCR2A; }
	inline uint8_t compB() { return OCR2B; }
	
	//pwm generator wave
	void pwmA(uint8_t value);
	void pwmA(uint8_t value, uint8_t mode);
	void pwmB(uint8_t value);
	void pwmB(uint8_t value, uint8_t mode);
	
	//control generator wave
	void frequency(uint32_t freq);
	
	//interrupts of timer
	void attach(uint8_t interrupt, VoidFuncPtr funct);
	void detach(uint8_t interrupt);
	
};


#endif
