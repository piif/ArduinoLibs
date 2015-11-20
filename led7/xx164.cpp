#include "xx164.h"

#include <Arduino.h>

#define XX164_NB_DIGITS 1
// TODO : define these pins with constructor arguments
#define DATA 2
#define CLOCK 3

// current segments to light on display
volatile byte _toDisplay[XX164_NB_DIGITS];
// segments lighted on before a roll effect was launched
volatile byte _toDisplayBefore[XX164_NB_DIGITS];

// current mask to send to display
volatile word toSend[XX164_NB_DIGITS];

xx164::xx164() : Led7() {
	nbDigits = XX164_NB_DIGITS;

	this->toDisplay = _toDisplay;
	this->toDisplayBefore = _toDisplayBefore;

	// call super() ?
	pinMode(DATA, OUTPUT);
	pinMode(CLOCK, OUTPUT);
	digitalWrite(CLOCK, LOW);
	prepareDisplay(0, 0);
}

void xx164::prepareDisplay(byte pos, byte segments) {
	toSend[0] = ~segments;
}
void xx164::updateDisplay() {
	shiftOut(DATA, CLOCK, MSBFIRST, toSend[0]);
}

//volatile short digit = 0;

//void A574g::send() {
//	Led7::send();
//	doSend(toSend[digit]);
//	digit = (digit + 1) % XX164_NB_DIGITS;
//}
