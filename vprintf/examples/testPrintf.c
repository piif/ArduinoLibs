/**
 * minimal code to test print function
 */

#ifdef ARDUINO
// PIF_TOOL_CHAIN_OPTION: EXTRA_LIBS := ArduinoLibs
	#include <Arduino.h>
	#include "vprintf/vprintf.c"
#else
	#include <stdio.h>
	#include <string.h>
	#include "../vprintf.c"
#endif

char buffer[100];
int bufPos = 0;

void writeChar(char c) {
	buffer[bufPos++] = c;
}

int assert(char *expected, char *fmt, ...) {
	bufPos = 0;
	memset(buffer, '?', 100);
	va_list ap;
	va_start(ap, fmt);
	int len = gvprintf(writeChar, fmt, ap);
	buffer[len] = '\0';
	va_end(ap);
	if (strcmp(expected, buffer) == 0) {
#ifdef ARDUINO
		Serial.print("OK '");Serial.print(fmt);
		Serial.print("' -> '");Serial.print(expected);
		Serial.println("'");
#else
		printf("OK '%s' -> '%s'\n", fmt, expected);
#endif
		return 0;
	} else {
#ifdef ARDUINO
		Serial.print("KO ");Serial.print(fmt);
		Serial.print("' -> '");Serial.print(buffer);
		Serial.print("' instead of '");Serial.print(expected);
		Serial.println("'");
#else
		printf("KO '%s' -> '%s' instead of '%s'\n", fmt, buffer, expected);
#endif
		return 1;
	}
}

#ifdef ARDUINO
void loop() {}
void setup() {
	Serial.begin(115200);
#else
int main() {
#endif
	int nbErr = 0;
	nbErr += assert("azeqsd", "azeqsd");
	nbErr += assert("aze,wxc,qsd", "aze,%s,qsd", "wxc");
	nbErr += assert("42", "%d", 42);
	nbErr += assert(".", "%.", 42);
	nbErr += assert(".", "%1.", 42);
	nbErr += assert("[X]", "[%c]", 'X');
	nbErr += assert("[A]", "[%c]", 0xff41);
	nbErr += assert("[\377]", "[%c]", 0xff);
	nbErr += assert("-1", "%d", -1);
	nbErr += assert("65535", "%u", (int16_t)-1);
	nbErr += assert("x002a", "x%x", 42);
	nbErr += assert("ffff", "%x", -1);
	nbErr += assert("2a", "%1x", 42);
	nbErr += assert("0000000000101010", "%2b", 42);
	nbErr += assert("aze,42,qsd,ff,wxc", "aze,%d,qsd,%1x,wxc", 42, -1);

#ifndef ARDUINO
	return nbErr;
#endif
}
