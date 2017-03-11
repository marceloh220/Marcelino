#include "shift.h"

Shift::Shift(uint8_t data, uint8_t clock) {
	this->init(data,clock);
}

Shift::Shift(uint8_t data, uint8_t clock, uint8_t enable) {
	this->init(data,clock,enable);
}

void Shift::init(uint8_t data, uint8_t clock) {
	data_pin = data;
	clock_pin = clock;
	Digital::write(data_pin,LOW);
	Digital::write(clock_pin,LOW);
	Digital::write(enable_pin,LOW);
	Digital::mode(data_pin,OUTPUT);
	Digital::mode(clock_pin,OUTPUT);
	_mode=0;
}

void Shift::init(uint8_t data, uint8_t clock, uint8_t enable) {
	data_pin = data;
	clock_pin = clock;
	enable_pin = enable;
	Digital::write(data_pin,LOW);
	Digital::write(clock_pin,LOW);
	Digital::write(enable_pin,LOW);
	Digital::mode(data_pin,OUTPUT);
	Digital::mode(clock_pin,OUTPUT);
	Digital::mode(enable_pin,OUTPUT);
	_mode=1;
}

void Shift::clock() {
	Digital::write(clock_pin,HIGH);
	Digital::write(clock_pin,LOW);
}

void Shift::enable() {
	Digital::write(enable_pin,HIGH);
	Digital::write(enable_pin,LOW);
}

void Shift::sendByte(uint8_t _data, uint8_t first) {
	if(first)
		for(int aux=0; aux<8; aux++) {
			uint8_t bit=(_data&0x01) ? 1 : 0;
			Digital::write(data_pin,bit);
			clock();
			_data=(_data>>1);
		}
	else
		for(int aux=0; aux<8; aux++) {
			uint8_t bit=(_data&0x80) ? 1 : 0;
			Digital::write(data_pin,bit);
			clock();
			_data=(_data<<1);
		}
	if(_mode) enable();
}

void Shift::sendWord(uint16_t _data, uint8_t first) {
	if(first)
		for(int aux=0; aux<16; aux++) {
			uint8_t bit=(_data&0x01) ? 1 : 0;
			Digital::write(data_pin,bit);
			clock();
			_data=(_data>>1);
		}
	else
		for(int aux=0; aux<16; aux++) {
			uint8_t bit=(_data&0x8000) ? 1 : 0;
			Digital::write(data_pin,bit);
			clock();
			_data=(_data<<1);
		}
	if(_mode) enable();
}

void Shift::send(uint8_t _data, uint8_t first) {
	sendByte(_data,first);
}

void Shift::send(uint16_t _data, uint8_t first) {
	sendWord(_data,first);
}

void Shift::ack() {
	Digital::write(data_pin,HIGH);
	clock();
	Digital::write(data_pin,LOW);
	clock();
}
