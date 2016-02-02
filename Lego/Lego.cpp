#include "Lego.h"

#define SENSOR_THRESHOLD 700

void Lego::begin(Stream &debug) {
	this->debug = &debug;
	begin();
}

void Lego::begin() {
	for (byte i = 0; i < NB_MOTORS; i++) {
		pinMode(motors_digit[i], OUTPUT);
		pinMode(motors_pwm[i], OUTPUT);
		setMotor(i, 0);
	}
	for (byte i = 0; i < NB_SENSORS; i++) {
		pinMode(sensors[i], INPUT_PULLUP);
	}
	// common GND for sensors
	pinMode(A2, OUTPUT); digitalWrite(A2, LOW);
	pinMode(A4, OUTPUT); digitalWrite(A4, LOW);

	for (byte i = 0; i < NB_LIGHTS; i++) {
		pinMode(lights[i], OUTPUT);
		setLight(i, LOW);
	}

	log("Lego ready");
}

void Lego::log(char *message) {
	if (debug != NULL) {
		debug->println(message);
	}
}
void Lego::log(char *message, int a) {
	if (debug != NULL) {
		debug->print(message);
		debug->print(" ");
		debug->println(a);
	}
}
void Lego::log(char *message, int a, int b) {
	if (debug != NULL) {
		debug->print(message);
		debug->print(" ");
		debug->print(a);
		debug->print(", ");
		debug->println(b);
	}
}

void Lego::setMotor(byte number, int speed) {
	if (number >= NB_MOTORS) {
		return;
	}
	if (speed == 0) {
		digitalWrite(motors_digit[number], LOW);
		digitalWrite(motors_pwm[number], LOW);
		log("Lego::setMotor off", number);
	} else if (speed > 0) {
		digitalWrite(motors_digit[number], LOW);
		analogWrite(motors_pwm[number], speed);
		log("Lego::setMotor forward", number, speed);
	} else {
		digitalWrite(motors_digit[number], HIGH);
		analogWrite(motors_pwm[number], ~(-speed));
		log("Lego::setMotor backward", number, -speed);
	}
}

void Lego::setLight(byte number, bool state) {
	if (number >= NB_LIGHTS) {
		return;
	}
	digitalWrite(lights[number], state);
	log("Lego::setLight", number, state);
}

bool Lego::readSensor(byte number) {
	if (number >= NB_LIGHTS) {
		return false;
	}
	bool result = analogRead(sensors[number]) > SENSOR_THRESHOLD;
	log("Lego::readSensor", number, result);
	return result;
}
