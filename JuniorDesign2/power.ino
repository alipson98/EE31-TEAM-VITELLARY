//thermistor pin will be A1

int thermPin = A1;
int tempReading = 0;
int statusLight = 2;

void setup() {
  // put your setup code here, to run once:
pinMode(thermPin, INPUT);
pinMode(statusLight, OUTPUT);
tempReading = analogRead(thermPin);
SleepNow();

}

void loop() {
  // put your main code here, to run repeatedly:
}


void SleepNow(){
  while(tempReading < 540)
  {
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    tempReading = analogRead(thermPin);
    Serial.println(tempReading);
    if(tempReading >= 540){
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(statusLight, HIGH);
      delay(1500);
      digitalWrite(statusLight, LOW);
      break;
    }
  }
}
