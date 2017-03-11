#ifndef TIMER1_H
#define TIMER1_H

#include "defines.h"
#include "digital.h"

class Timer1 {
private:
	uint8_t def_top, def_mode2;
	uint16_t def_prescale;
	void variable(uint8_t mode, uint8_t top);
public:
	Timer1();
	
	//configs of timer
	void config(uint8_t mode, uint8_t mode2 = FAST, uint8_t top = CAPT);
	void prescale(uint16_t scale);
	void pinA(uint8_t mode);
	void pinB(uint8_t mode);
	
	//register of timer
	inline void timer(uint16_t value) { TCNT1 = value; }
	inline void compA(uint16_t value) { OCR1A = value; }
	inline void compB(uint16_t value) { OCR1B = value; }
	inline void capt(uint16_t value) { ICR1 = value; }
	inline uint16_t timer() { return TCNT1; }
	inline uint16_t compA() { return OCR1A; }
	inline uint16_t compB() { return OCR1B; }
	inline uint16_t capt() { return ICR1; }
	
	//pwm generator wave
	void pwmA(uint16_t value);
	void pwmA(uint16_t value, uint8_t mode);
	void pwmB(uint16_t value);
	void pwmB(uint16_t value, uint8_t mode);
	
	//control generator wave
	void frequency(uint32_t freq);
	
	//interrupts of timer
	void attach(uint8_t interrupt, VoidFuncPtr funct);
	void attach(uint8_t interrupt, uint8_t mode, VoidFuncPtr funct);
	void detach(uint8_t interrupt);
	
	//test states
	inline uint8_t rising() { return (TCCR1B & (1<<ICES1)); }
	inline uint8_t falling() { return !(TCCR1B & (1<<ICES1)); }
	
};

#endif
