const int red = 5;
const int black = 6;
const int white = 9;
const int blue = 10;

const int led = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(black, OUTPUT);
  pinMode(white, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(led, INPUT);

}


const int LFA_speed = 100;


void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(led)) {
    drive(0, LFA_speed);
  }
  else {
    drive(LFA_speed, 0);
  }
}

void drive(int leftSpeed, int rightSpeed) {
  if (leftSpeed > 0) {
    digitalWrite(blue, LOW);
    analogWrite(white, leftSpeed);
  }
  else {
    digitalWrite(white, LOW);
    analogWrite(blue, -leftSpeed);
  }

  if (rightSpeed > 0) {
    digitalWrite(black, LOW);
    analogWrite(red, rightSpeed);
  }
  else {
    digitalWrite(red, LOW);
    analogWrite(black, -rightSpeed);
  }
  
}