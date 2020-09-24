//thermistor pin will be A1

const int thermPin = A1;
int tempReading = 0;
int statusLight = 2;
const int thermThresh = 267; // TODO: test and change this to the correct value

void setup() {
  Serial.begin(9600);
  while (!Serial){
    ;
  }
  // put your setup code here, to run once:
pinMode(thermPin, INPUT);
pinMode(statusLight, OUTPUT);
tempReading = analogRead(thermPin);
SleepNow();

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("hi");
  while(true);
  Serial.println(analogRead(thermPin));
}


void SleepNow(){
  Serial.println(analogRead(thermPin));
  while(tempReading < thermThresh)
  {
    Serial.println(analogRead(thermPin));
    digitalWrite(LED_BUILTIN, LOW);
    tempReading = analogRead(thermPin);
    Serial.println(tempReading);
    if(tempReading >= thermThresh){
      digitalWrite(LED_BUILTIN, LOW);

      break;
    }
  }
}
