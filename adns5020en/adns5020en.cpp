#include "adns5020en.h"

adns5020en::adns5020en(byte SCLK, byte SDIO, byte NCS, byte NRESET):
		SCLK(SCLK), SDIO(SDIO), NCS(NCS), NRESET(NRESET) {
	pinMode(SCLK,   OUTPUT);
	pinMode(NRESET, OUTPUT);
	pinMode(NCS,    OUTPUT);
}

byte adns5020en::readRegister(byte address) {
	pinMode(SDIO, OUTPUT);

	digitalWrite(NCS, LOW);
	delayMicroseconds(10);
	address &= 0x7F;
	for (byte i = 0x80; i > 0; i >>= 1) {
		digitalWrite(SCLK, LOW);
		digitalWrite(SDIO, (address & i) != 0 ? HIGH : LOW);
		delayMicroseconds(1);
		digitalWrite(SCLK, HIGH);
		delayMicroseconds(1);
	}
    // shiftOut(SDIO, SCLK, MSBFIRST, address & 0x7F);

	pinMode(SDIO, INPUT);
	delayMicroseconds(100);
	byte data = 0;
	for (byte i = 0x80; i > 0; i >>= 1) {
		digitalWrite(SCLK, LOW);
		delayMicroseconds(1);
		digitalWrite(SCLK, HIGH);
		delayMicroseconds(1);
		if(digitalRead(SDIO)) {
			data |= i;
		}
	}
	// byte data = shiftIn(SDIO, SCLK, MSBFIRST);

	delayMicroseconds(100);
	digitalWrite(NCS, HIGH);

	return data;
}

void adns5020en::writeRegister(byte address, byte data) {
	pinMode(SDIO, OUTPUT);
	digitalWrite(NCS, LOW);
	delayMicroseconds(1);

	address |= 0x80;
	for (byte i = 0x80; i > 0; i >>= 1) {
		digitalWrite(SCLK, LOW);
		digitalWrite(SDIO, (address & i) != 0 ? HIGH : LOW);
		digitalWrite(SCLK, HIGH);
		delayMicroseconds(1);
	}
    // shiftOut(SDIO, SCLK, MSBFIRST, address | 0x80);
	delayMicroseconds(100);
	for (byte i = 0x80; i > 0; i >>= 1) {
		digitalWrite(SCLK, LOW);
		digitalWrite(SDIO, (data & i) != 0 ? HIGH : LOW);
		digitalWrite(SCLK, HIGH);
		delayMicroseconds(1);
	}
    // shiftOut(SDIO, SCLK, MSBFIRST, data);

	delayMicroseconds(100);
	digitalWrite(NCS, HIGH);
}

void adns5020en::reset() {
	digitalWrite(NRESET, LOW);
	delayMicroseconds(1);
	digitalWrite(NRESET, HIGH);
	delayMicroseconds(1);
	writeRegister(REG_CHIP_RESET, 0x5A);
	delayMicroseconds(1);
}

void adns5020en::getId(byte &productId, byte &revisionId) {
	productId  = readRegister(REG_PRODUCT_ID);
	revisionId = readRegister(REG_REVISION_ID);
}

byte adns5020en::getSum() {
	return readRegister(REG_SUM_PIXEL);
}

void adns5020en::getFrame(int dumpWidth, byte *frame) {
	writeRegister(REG_PIXEL_GRAB, 42);

	int count = 0;
	do {
		byte data = readRegister(REG_PIXEL_GRAB);
		if ((data & 0x80) != 0) { // Data is valid
			frame[count++] = data;
		}
	} while (count != dumpWidth);
}

bool adns5020en::getMotion(char &dx, char &dy) {
	if (readRegister(REG_MOTION) & 0x80) {
		dx = readRegister(REG_DELTA_X);
		dy = readRegister(REG_DELTA_Y);
		writeRegister(REG_MOTION, 0);
		return 1;
	}
	return 0;
}
