/*Example sketch to control a stepper motor with A4988/DRV8825 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */

// Define stepper motor connections and steps per revolution:
#define dirPin 2
#define stepPin 3
#define stepsPerRevolution 500
String input;

void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  // put your setup code here, to run once:
  Serial.begin(9600); //init Serial
  // put your main code here, to run repeatedly:
  Serial.println("Set a speed.");
  while (Serial.available() == 0) {
    // Wait for Input Data
  }
  input = Serial.readString();
  Serial.println("Command was recieved: `" + input + "");
  if (input.startsWith("A")) {
    Serial.println("'B'");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Set new speed.");
  while (Serial.available() == 0) {
    // Set the spinning direction clockwise:
    digitalWrite(dirPin, HIGH);
    // Spin the stepper motor 1 revolution slowly:
    for (int i = 0; i < 2; i++) {
      // These four lines result in 1 step:
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(input.toInt() * 10);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(input.toInt() * 10);
    }
  }
  input = Serial.readString();
  Serial.println("Command was recieved: `" + input + "");
  if (input.startsWith("A")) {
    Serial.println("'B'");
  }
  //done.

}
