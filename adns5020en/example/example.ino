#include <Arduino.h>

#ifndef DEFAULT_BAUDRATE
	#define DEFAULT_BAUDRATE 115200
#endif

#include "adns5020en.h"

adns5020en captor(A1, A3, A0, A2);  // SCLK, SDIO, NCS, NRESET

int dumpWidth = 0; // Number of pixels to read for each frame.
byte frame[MAP_SIZE];

void dumpFrame() {
	captor.getFrame(dumpWidth, frame);

	Serial.print("FRAME:");
	for (int i = 0; i < dumpWidth; i++) {
		byte pix = frame[i];
		if (pix < 0x10)
			Serial.print("0");
		Serial.print(pix, HEX);
	}
	Serial.println();

	Serial.print("SUM:");
	Serial.println(captor.getSum(), HEX);

}

void setup() {
	Serial.begin(DEFAULT_BAUDRATE);

	captor.reset();
	byte productId;
	byte revisionId;
	captor.getId(productId, revisionId);

	Serial.print("* Found productId ");
	Serial.print(productId, HEX);
	Serial.print(", rev. ");
	Serial.print(revisionId, HEX);
	Serial.println((productId == 0x12 && revisionId == 0 ) ? " OK." : " Unknown productID. Carry on.");

	Serial.print("REG_PRODUCT_ID      : "); Serial.println(captor.readRegister(REG_PRODUCT_ID      ));
	Serial.print("REG_REVISION_ID     : "); Serial.println(captor.readRegister(REG_REVISION_ID     ));
	Serial.print("REG_MOTION          : "); Serial.println(captor.readRegister(REG_MOTION          ));
	Serial.print("REG_DELTA_X         : "); Serial.println(captor.readRegister(REG_DELTA_X         ));
	Serial.print("REG_DELTA_Y         : "); Serial.println(captor.readRegister(REG_DELTA_Y         ));
	Serial.print("REG_SQUAL           : "); Serial.println(captor.readRegister(REG_SQUAL           ));
	Serial.print("REG_SHUTTER_LOWER   : "); Serial.println(captor.readRegister(REG_SHUTTER_LOWER   ));
	Serial.print("REG_SHUTTER_UPPER   : "); Serial.println(captor.readRegister(REG_SHUTTER_UPPER   ));
	Serial.print("REG_MAXIMUM_PIXEL   : "); Serial.println(captor.readRegister(REG_MAXIMUM_PIXEL   ));
	Serial.print("REG_SUM_PIXEL       : "); Serial.println(captor.readRegister(REG_SUM_PIXEL       ));
	Serial.print("REG_MINIMUM_PIXEL   : "); Serial.println(captor.readRegister(REG_MINIMUM_PIXEL   ));
	Serial.print("REG_PIXEL_GRAB      : "); Serial.println(captor.readRegister(REG_PIXEL_GRAB      ));
	Serial.print("REG_MOUSE_CONTROL   : "); Serial.println(captor.readRegister(REG_MOUSE_CONTROL   ));
	Serial.print("REG_CHIP_RESET      : "); Serial.println(captor.readRegister(REG_CHIP_RESET      ));
	Serial.print("REG_INV_REV_ID      : "); Serial.println(captor.readRegister(REG_INV_REV_ID      ));
}

void loop() {
	captor.writeRegister(REG_PIXEL_GRAB, 42);
	captor.writeRegister(REG_PIXEL_GRAB, 42);
	captor.readRegister(REG_PIXEL_GRAB);
	// byte productId;
	// byte revisionId;
	// captor.getId(productId, revisionId);
	delayMicroseconds(1000);

	// // Allows to set the dump window by sending the number of lines to read via the serial port.
	// if (Serial.available() > 0) {
	// 	int c = Serial.read();
	// 	if (c == 'W') {
	// 		int c = Serial.read();
	// 		dumpWidth = 15 * c2x(c);
	// 		Serial.print("* Width set to ");
	// 		Serial.println(dumpWidth);
	// 	} else if (c == 'D') {
	// 		if (dumpWidth > 0) {
	// 			dumpFrame();
	// 		}

	// 		char dx, dy;
	// 		if(captor.getMotion(dx, dy)) {
	// 			if (dx != 0 || dy != 0) {
	// 				Serial.print("DELTA:");
	// 				Serial.print(dx, DEC);
	// 				Serial.print(" ");
	// 				Serial.println(dy, DEC);
	// 			}
	// 		}
	// 	}
	// 	// else, silently ignore
	// }

}
