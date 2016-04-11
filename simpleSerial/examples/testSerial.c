#include "../simpleSerial.h"

void setup() {
	serialBegin(115200, SERIAL_8N1);
	serialPrintf("Test ...\n");
}

void loop() {

}
