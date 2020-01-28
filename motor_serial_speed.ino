
const int ANALOG_READ_MAX = 1023;
int driveSpeed = 255;
int ledPin = 9;    // LED connected to digital pin 9

int speedPot = A0;
void setup() {
  pinMode(22, OUTPUT);
  pinMode(26, OUTPUT);

  Serial.begin(9600);
  while (! Serial);
  Serial.println("Serial ready. Enter a speed");
}

void loop() {


  
//  int speed;
  digitalWrite(22, HIGH);
  digitalWrite(26, LOW);
  if (Serial.available()) {
    driveSpeed = Serial.parseInt();
  }
  analogWrite(ledPin, driveSpeed);
}