int motorSpeed;
int MotorC = 22;
int MotorD = 24;

void setup() {
  // put your setup code here, to run once:
  pinMode(MotorC, OUTPUT);
  pinMode(MotorD, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  motorSpeed = analogRead(0);
  digitalWrite(MotorC, LOW);
  analogWrite(2, motorSpeed);
  digitalWrite(MotorD, LOW);
  analogWrite(3, motorSpeed);
  

}
