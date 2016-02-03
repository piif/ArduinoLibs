#include <Arduino.h>

#define NB_LIGHTS 4
#define LIGHT_0 10
#define LIGHT_1 11
#define LIGHT_2 12
#define LIGHT_3 13

#define NB_SENSORS 4
#define SENSOR_0 A0
#define SENSOR_1 A1
#define SENSOR_2 A3
#define SENSOR_3 A5

#define NB_MOTORS 4
#define MOTOR_0_DIGIT 2
#define MOTOR_0_PWM 3
#define MOTOR_1_DIGIT 8
#define MOTOR_1_PWM 9
#define MOTOR_2_DIGIT 4
#define MOTOR_2_PWM 5
#define MOTOR_3_DIGIT 7
#define MOTOR_3_PWM 6

class Lego {
public:
	const byte lights[NB_LIGHTS] = { LIGHT_0, LIGHT_1, LIGHT_2, LIGHT_3 };
	const byte sensors[NB_SENSORS] = { SENSOR_0, SENSOR_1, SENSOR_2, SENSOR_3 };
	const byte motors_pwm[NB_MOTORS] = { MOTOR_0_PWM, MOTOR_1_PWM, MOTOR_2_PWM, MOTOR_3_PWM };
	const byte motors_digit[NB_MOTORS] = { MOTOR_0_DIGIT, MOTOR_1_DIGIT, MOTOR_2_DIGIT, MOTOR_3_DIGIT };

	void begin();
	void begin(Stream &debug);

	void setMotor(byte number, int speed);

	void setLight(byte number, bool state);

	bool readSensor(byte number);

protected:
	Stream *debug;
	void log(char *message);
	void log(char *message, int a);
	void log(char *message, int a, int b);
};
