#include "structures/Car.h"

Car car;

void setup() {
	Serial.println("Car setup");
	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);

	Serial.begin(9600);
	Motor.setCurrentPosition(0);
}

void loop() {
	if (Serial.available() > 0) {
		String value = Serial.readStringUntil('#');
		Serial.println(value);
		Serial.println(String(value.length()));

		if (value.length() == 7) {
			String angle = value.substring(0, 3);
			String strength = value.substring(3, 6);
			String button = value.substring(6, 8);

			// winkel c:
			car.calcDir(angle.toInt());
			car.setSpeed(strength.toInt());

			car.steering(angle.toInt());

			Serial.flush();
			value = "";
		} else if (car.speed > 0) {
			car.setSpeed(0);
		}
	}

	car.drive();
}
