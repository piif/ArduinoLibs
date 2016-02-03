/**
 * minimal library to handle a 7 segment display driven by a 74xx164 shift register
 * - data and clock pins must be connected to arduino pins 2 and 3
 * - segments must be connected to outputs in high to low order :
 *   q7 = t, q6 = L, ... q0 = p
 *
 * TODO : affect data and clock pins thru constructor
 * TODO : allow to revert outputs order
 */

#ifndef LED_7_xx164_H
#define LED_7_xx164_H 1

#include "led7.h"

class xx164 : public Led7 {
public:
	xx164();
	void send();

	~xx164() {};

protected:
	void prepareDisplay(byte pos, byte segments);
	void updateDisplay();

};
#endif
