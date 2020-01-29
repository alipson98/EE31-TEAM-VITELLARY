
const int ANALOG_READ_MAX = 1023;
int driveSpeed = 255;
int ledPin = 9;    // motor speed control

int speedPot = A0;
void setup() {
  pinMode(22, OUTPUT);
  pinMode(26, OUTPUT);

  Serial.begin(9600);
  while (! Serial);
  Serial.println("Serial ready. Enter a speed");
}

void loop() {
 digitalWrite(22, LOW);
 //digitalWrite(24, LOW);
 digitalWrite(26, HIGH);
 //digitalWrite(28, HIGH);
 // fade in from min to max in increments of 5 points:
 for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
   // sets the value (range from 0 to 255):
   analogWrite(ledPin, fadeValue);
   // wait for 30 milliseconds to see the dimming effect
   delay(40);
 }

 // fade out from max to min in increments of 5 points:
 for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
   // sets the value (range from 0 to 255):
   analogWrite(ledPin, fadeValue);
   // wait for 30 milliseconds to see the dimming effect
   delay(40);
 }

 digitalWrite(22, HIGH);
 //digitalWrite(24, HIGH);
 digitalWrite(26, LOW);
 //digitalWrite(28, LOW);
 // fade in from min to max in increments of 5 points:
 for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
   // sets the value (range from 0 to 255):
   analogWrite(ledPin, fadeValue);
   // wait for 30 milliseconds to see the dimming effect
   delay(40);
 }

 // fade out from max to min in increments of 5 points:
 for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
   // sets the value (range from 0 to 255):
   analogWrite(ledPin, fadeValue);
   // wait for 30 milliseconds to see the dimming effect
   delay(40);
 }

  

}
