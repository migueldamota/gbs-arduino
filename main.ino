#include <Stepper.h>

#define dirPin 6
#define stepPin 7

#define In4Pin 24
#define In3Pin 25
#define In2Pin 26
#define In1Pin 27

const int SPU = 2048;
Stepper Motor(SPU, In4Pin, In2Pin, In3Pin, In1Pin);

class Car {
  public:

    int speed;
    int dir;

    Car () {
      speed = 0;
      dir = 0;
    };

    void calcDir (int angle) {
      dir = angle;
      digitalWrite(dirPin, dir >= 0 && dir <= 180 ? HIGH : LOW);
    };

    void setSpeed (int strength) {
      int speedTemp = speed;

      if (strength >= 95) {
        speed = 12;
      } else if (strength < 95 && strength >= 50) {
        speed = 20;
      } else if (strength < 50 && strength > 0) {
        speed = 30;
      } else if (strength < 1) {
        speed = 0;
      }

      if (speedTemp != speed) {
        Serial.println("Car: Setting speed from " + String(speedTemp) + " to " + String(speed));
      }
    };

    void steering () {

    };

    void drive () {
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

Car car;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  
  Serial.begin(9600);

  Motor.setSpeed(15);
}

void loop() {
  if (Serial.available() > 0) {
    String value = Serial.readStringUntil('#');
    //Serial.println(value);

    if (value.length() == 7) {
      String angle = value.substring(0, 3);
      String strength = value.substring(3, 6);
      String button = value.substring(6, 8);

      // winkel c:
      car.calcDir(angle.toInt());
      car.setSpeed(strength.toInt());

      Serial.flush();
      value="";

      // Serial.println("Speed: " + String(asdf));
      
    }
  }

  car.drive();
}
