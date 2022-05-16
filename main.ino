#define dirPin 6
#define stepPin 7

#define In4Pin 24
#define In3Pin 25
#define In2Pin 26
#define In1Pin 27

int asdf = 0;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String value = Serial.readStringUntil('#');
    //Serial.println(value);

    if (value.length() == 7) {
      String angle = value.substring(0, 3);
      String strength = value.substring(3, 6);
      String button = value.substring(6, 8);

      Serial.println(strength);

      // Serial.print("angle: ");Serial.print(angle);Serial.print('\t');
      // Serial.print("strength: ");Serial.print(strength);Serial.print('\t');
      // Serial.print("button: ");Serial.print(button);Serial.println("");

      // winkel c:
      int dir = angle.toInt();
      if (dir >= 0 && dir <= 180) {
        digitalWrite(dirPin, HIGH);
      } else 
        digitalWrite(dirPin, LOW);

      if (strength.toInt() > 95) {
        // Serial.println("1");
        asdf = 10;
      }

      if (strength.toInt() < 96 && strength.toInt() > 50) {
        // Serial.println("2");
        asdf = 20;
      }

      if (strength.toInt() < 51) {
        // Serial.println("3");
        asdf = 30;
      }

      if (strength.toInt() < 1) {
        // Serial.println("3");
        asdf = 0;
      }

      Serial.flush();
      value="";

      Serial.println("Speed: " + String(asdf));
      
    }
  }
  
  if (asdf > 0) {
    //Serial.println("Setting speed");
    // digitalWrite(dirPin, HIGH);
    for (int i = 0; i < 2; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(asdf * 10);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(asdf * 10);
    }
  }
}
