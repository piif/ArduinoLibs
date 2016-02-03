#include "xx164.h"

#include <Arduino.h>
#include <SPI.h>

#define XX164_NB_DIGITS 1
// TODO : define these pins with constructor arguments
#define DATA 2
#define CLOCK 3

xx164::xx164(byte _nbDigits, volatile byte _pins[]) :
		Led7() {

	nbDigits = _nbDigits;
	pins = _pins;
	toSend = new volatile byte[nbDigits];
	toDisplay = new volatile byte[nbDigits];
	toDisplayBefore = new volatile byte[nbDigits];
	current = 0;

	SPI.begin();
	SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
//	// call super() ?
//	pinMode(DATA, OUTPUT);
//	pinMode(CLOCK, OUTPUT);
//	for (byte i = 0; i < nbDigits; i++) {
//		pinMode(pins[i], OUTPUT);
//		digitalWrite(pins[i], LOW);
//	}
//	digitalWrite(CLOCK, LOW);
	prepareDisplay(0, 0);
}

void xx164::prepareDisplay(byte pos, byte segments) {
	toSend[pos] = ~segments;
}

void xx164::updateDisplay() {
	// nothing to do
}

void xx164::send() {
	Led7::send();

	byte next = (current + 1) % nbDigits;
	digitalWrite(pins[current], LOW);
//	Serial.print(next);
//	Serial.println(toSend[next], HEX);
//	shiftOut(DATA, CLOCK, MSBFIRST, toSend[next]);
	SPI.transfer(toSend[next]);
	digitalWrite(pins[next], HIGH);
	current = next;
}

xx164::~xx164() {
	delete toDisplay;
	delete toDisplayBefore;
}
//volatile short digit = 0;

//void A574g::send() {
//	Led7::send();
//	doSend(toSend[digit]);
//	digit = (digit + 1) % XX164_NB_DIGITS;
//}
