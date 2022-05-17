#include <Stepper.h>

#define dirPin 6
#define stepPin 7

#define In4Pin 24
#define In3Pin 25
#define In2Pin 26
#define In1Pin 27

const int SPU = 2048;
Stepper Motor(SPU, In4Pin, In2Pin, In3Pin, In1Pin);

int carSteeringAngleTemp = 0;
int carSteeringAngle = 0;
int carSpeed = 0;

void setup() {
	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);

	Serial.begin(9600);

	Motor.setSpeed(15);
}

void loop() {
	if (Serial.available() > 0) {
		Serial.println("");
		Serial.println("");
		Serial.println("New input");
		String value = Serial.readStringUntil('#');
		// Serial.println(value);

		if (value.length() == 7) {
			String angle = value.substring(0, 3);
			String strength = value.substring(3, 6);
			String button = value.substring(6, 8);

			// Serial.println(strength);

			// Serial.print("angle: ");Serial.print(angle);Serial.print('\t');
			// Serial.print("strength: ");Serial.print(strength);Serial.print('\t');
			// Serial.print("button: ");Serial.print(button);Serial.println("");

			// direction
			int dir = angle.toInt();
			if (dir >= 0 && dir <= 180) {
				digitalWrite(dirPin, HIGH);
			} else {
				digitalWrite(dirPin, LOW);
			}

			Serial.println("Begin Steering Angle");
			carSteering(dir);
			Serial.println("End Steering Angle");

			if (strength.toInt() > 95) {
				// Serial.println("1");
				carSpeed = 10;
			}

			if (strength.toInt() < 96 && strength.toInt() > 50) {
				// Serial.println("2");
				carSpeed = 20;
			}

			if (strength.toInt() < 51) {
				// Serial.println("3");
				carSpeed = 30;
			}

			if (strength.toInt() < 1) {
				// Serial.println("3");
				carSpeed = 0;
			}

			Serial.flush();
			value = "";

			// Serial.println("Speed: " + String(carSpeed));
		}
	}

	if (carSpeed > 0) {
		// Serial.println("Setting speed");
		//  digitalWrite(dirPin, HIGH);
		for (int i = 0; i < 2; i++) {
			digitalWrite(stepPin, HIGH);
			delayMicroseconds(carSpeed * 5);
			digitalWrite(stepPin, LOW);
			delayMicroseconds(carSpeed * 5);
		}
	}
}



void carSteering (int dir) {
	if (dir >= 80 && dir <= 100) {
		carSteeringAngle = 0;
	} else if (dir >= 40 && dir < 80) {
		// right
		carSteeringAngle = 10;
	} else if (dir > 0 && dir < 40) {
		// extreme right
		carSteeringAngle = 20;
	}

	else if (dir >= 100 && dir < 140) {
		// left
		carSteeringAngle = -10;
	}
	else if (dir >= 140 && dir <= 180) {
		// extreme left
		carSteeringAngle = -20;
	}
	
	else {
		carSteeringAngle = 0;
	}

	// Serial.println("Spinning now: " + String(carSteeringAngle));

	Serial.println("DOing222");
	if (carSteeringAngle > 0 && carSteeringAngle != carSteeringAngleTemp) {
		Serial.println("DOing");
		carSteeringAngleTemp = carSteeringAngle;
		Motor.step(carSteeringAngle);
		delay(500);
	}
}
