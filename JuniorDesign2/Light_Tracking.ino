const int right_F = 5;
const int right_R = 6;
const int left_F = 9;
const int left_R = 10;
bool lightTrack = false;


void setup() {
  pinMode(right_F,OUTPUT);
  pinMode(right_R,OUTPUT);
  pinMode(left_F,OUTPUT);
  pinMode(left_R,OUTPUT);
  pinMode (A0, INPUT);
  //Serial.begin(9600);
}

void loop() {
  Follow_Light();
}

void Follow_Light() {
    if (analogRead(A0) < 775) {
    lightTrack = true;
    while(lightTrack) {
      Drive_forward();
        if (analogRead(A0) >= 775) {
          for (int i = 0; i < 4; i++) {
            Drive_pivot_left();
            delay(500);
            Drive_stop();
            if (analogRead(A0) < 775) {
              break;
            }
            Drive_pivot_right();
            delay(1000);
            if (analogRead(A0) < 775) {
              break;
            }
            if (i == 3) {
              lightTrack = false;
            }
          }
          
        }
    }
    Drive_stop();
  }
  
}
void Drive_forward() {
  digitalWrite(left_F, HIGH);
  digitalWrite(left_R, LOW);
  digitalWrite(right_F, HIGH);
  digitalWrite(right_R, LOW);
}

void Drive_backward() {
  digitalWrite(left_F, LOW);
  digitalWrite(left_R, HIGH);
  digitalWrite(right_F, LOW);
  digitalWrite(right_R, HIGH);
}

void Drive_stop() {
  digitalWrite(left_F, LOW);
  digitalWrite(left_R, LOW);
  digitalWrite(right_F, LOW);
  digitalWrite(right_R, LOW);
}

//spin = center of rotation is the center of the bot
void Drive_spin_left(){
  digitalWrite(left_F, LOW);
  digitalWrite(left_R, HIGH);
  digitalWrite(right_F, HIGH);
  digitalWrite(right_R, LOW);
  
}

void Drive_spin_right(){
  digitalWrite(left_F, HIGH);
  digitalWrite(left_R, LOW);
  digitalWrite(right_F, LOW);
  digitalWrite(right_R, HIGH);
}

//pivot = center of rotation is left or right wheel
void Drive_pivot_left(){
  digitalWrite(left_F, LOW);
  digitalWrite(left_R, LOW);
  digitalWrite(right_F, HIGH);
  digitalWrite(right_R, LOW);
}

void Drive_pivot_right(){
  digitalWrite(left_F, HIGH);
  digitalWrite(left_R, LOW);
  digitalWrite(right_F, LOW);
  digitalWrite(right_R, LOW);
}
