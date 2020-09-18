#include <avr/sleep.h>

//pin 7 thermistor

int thermPin = 7;

void setup() {
  // put your setup code here, to run once:
pinMode(thermPin, INPUT);
attachInterrupt(digitalPinToInterrupt(thermPin), wake_up, CHANGE);

}

void loop() {
  // put your main code here, to run repeatedly:
  SleepNow();
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(5000);
  digitalWrite(LED_BUILTIN, LOW);
}

void wake_up(){

}

void SleepNow(){
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
  sleep_disable();
  detachInterrupt(digitalPinToInterrupt(thermPin));
}
