#include <AccelStepper.h>

// #define In4Pin 24
// #define In3Pin 25
// #define In2Pin 26
// #define In1Pin 27

#define In1Pin 24
#define In2Pin 25
#define In3Pin 26
#define In4Pin 27

#define dirPin 6
#define stepPin 7

// const int SPU = 2048;
AccelStepper Motor(8, In1Pin, In3Pin, In2Pin, In4Pin);

// const int SPU = 2048;
// Stepper Motor(SPU, In4Pin, In2Pin, In3Pin, In1Pin);

class Car {
   	public:
		int speed = 0;
		int angle = 0;

		Car () {
			Motor.setMaxSpeed(1000.0);
			Motor.setAcceleration(100.0);
			Motor.setSpeed(200);
		};

		void calcDir(int a) {
			angle = a;
			digitalWrite(dirPin, angle >= 0 && angle <= 180 ? HIGH : LOW);
		};

		void setSpeed(int strength) {
			int speedTemp = speed;

			if (strength >= 95) {
				speed = 12;
			} else if (strength >= 50) {
				speed = 20;
			} else if (strength > 0) {
				speed = 30;
			} else {
				speed = 0;
			}

			if (speedTemp != speed) {
				Serial.println("Car: Setting speed from " + String(speedTemp) +
							" to " + String(speed));
			}
		};

		int tempAngle = 0;

		void steering(int carAngle) {
			//  300 left 	(angle = 180)
			//    0 middle 	(angle = 90)
			// -300 right 	(angle = 0)
			Serial.println("tempAngle: " + String(tempAngle));

			if (angle > 90) {
				if (angle <= 120) {
					if (tempAngle == 120) return;
					tempAngle = 120;
					Motor.move(100);
				}
				else if (angle <= 150) {
					if (tempAngle == 150) return;
					tempAngle = 150;
					Motor.move(200);
				}
				else if (angle <= 180) {
					if (tempAngle == 180) return;
					tempAngle = 180;
					Motor.move(300);
				}
			} else if (angle < 90) {
				if (angle >= 60) {
					if (tempAngle == 60) return;
					tempAngle = 60;
					Motor.moveTo(-100);
				} else if (angle >= 30) {
					if (tempAngle == 30) return;
					tempAngle = 30;
					Motor.moveTo(-200);
				} else if (angle >= 0) {
					if (tempAngle == 0) return;
					tempAngle = 0;
					Motor.moveTo(-300);
				}
			} else {
				tempAngle = -1;
				Motor.moveTo(0);
			}
		};

		void drive() {
  			Motor.run();
			if (speed < 1) {
				return;
			}

			for (int i = 0; i < 2; i++) {
				digitalWrite(stepPin, HIGH);
				delayMicroseconds(speed * 5);
				digitalWrite(stepPin, LOW);
				delayMicroseconds(speed * 5);
			}
		};
};