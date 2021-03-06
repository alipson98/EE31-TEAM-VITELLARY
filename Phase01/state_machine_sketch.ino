enum State {On, Off, Run, Sleep, Diagnostic};

State currState;
int ledPin = LED_BUILTIN;
int redPin = 9;
int bluePin = 12;
int greenPin = 11;

const byte button2 = 3;
const byte switchOn = 18;
const byte switch1 = 19;
const byte switch2 = 2;
const byte flashPot = 0;
const byte brightPot = 1;

int runFlashPot = 0;
int runBrightPot = 1;

int redBrightness = 100;
int initBrightness = 100;
int runTime = 5000;
//int fadeAmount = 5;
long runStart, runStopTime;

bool shouldReturn = false;
bool statusRSBO = false; //Red should be on
bool statusBB = false; //Blue blink

void setup() {

  //Serial.begin(9600);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(button2, INPUT);
  pinMode(switchOn, INPUT);
  pinMode(flashPot, INPUT);
  pinMode(brightPot, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(button2), button2ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(switchOn), switchISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(switch1), switch1ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(switch2), switch2ISR, CHANGE);
  
  if(digitalRead(switchOn)){
    currState = On;
  }
  else
  {
    currState = Off;
  }
}

void loop() {
  switch (currState) {
    case On:
      blink(2000, 10, redPin);
      if(currState != Off)
      {
        currState = Run;
      }
      runStart = millis();
      break;
    case Run:
      if (millis() - runStart >= runTime) {
        currState = Sleep;
        break;
      }
      executeRun();
      break;
    case Sleep:
      executeSleep();
      break;
    case Off:
      analogWrite(redPin, 0);
      analogWrite(bluePin, 0);
      analogWrite(greenPin, 0);
      shouldReturn = false;
      break;
    case Diagnostic:
      executeDiagnostic();
      break;
  }
}

void blink(long blinkTime, float freq, int pinNum) {
  float orgFreq = freq;
  long startTime = millis();
  long stopTime = startTime;
  float firstRead;
  while((stopTime - startTime) <= blinkTime){
    if(currState == Run){
      firstRead = (float)analogRead(flashPot);
      freq = ((float)analogRead(flashPot) / 1023) * orgFreq;
    }
    if(shouldReturn){
      return;
    }
    float delayTime = ((1 / (float)freq) / 2) * 1000;
    if(firstRead != analogRead(flashPot) && currState == Run){
      stopTime = millis();
      continue; 
    }
    digitalWrite(pinNum, HIGH);
    delay(delayTime);
    digitalWrite(pinNum, LOW);
    delay(delayTime);
    stopTime = millis();
  }
}

void blinkSub2(long blinkTime, int freq, int pinNum) {
  float orgFreq = freq;
  long startTime = millis();
  long stopTime = startTime;
  float firstRead;
  while((stopTime - startTime) <= blinkTime){
    firstRead = (float)analogRead(flashPot);
    freq = ((float)analogRead(flashPot) / 1023) * orgFreq;
    if(shouldReturn){
      return;
    }
    if(statusRSBO){
      redBrightness = ((float)analogRead(brightPot) / 1023) * initBrightness;
      analogWrite(redPin, redBrightness);
    }
    float delayTime = ((1 / (float)freq) / 2) * 1000;
    if(firstRead != analogRead(flashPot)){
      continue; 
    } 
    digitalWrite(pinNum, HIGH);
    delay(delayTime);
    digitalWrite(pinNum, LOW);
    delay(delayTime);
    stopTime = millis();
  }

  digitalWrite(redPin, LOW);
}

void fade(long fadeTime, int pinNum, int fadeAmount) {
  int brightness = initBrightness;
  long startTime = millis();
  long stopTime = startTime;
  while((stopTime - startTime) <= fadeTime){
    if(shouldReturn){
      return;
    }
    analogWrite(pinNum, brightness);
    
    brightness = brightness - fadeAmount;
    
    if (brightness <= 0 || brightness >= 255){
      fadeAmount = -fadeAmount;
    }
  
    delay(30);
    stopTime = millis();
  }

}

void decayOverMs(long decayMs, int pinNum) {
  int brightness = initBrightness;
  long startTime = millis();
  long stopTime = startTime;
  int decayIncrement = initBrightness / ((float)decayMs / 30);
  decayIncrement = (decayIncrement == 0) ? 1 : decayIncrement;
  while((stopTime - startTime) <= decayMs){
    if(shouldReturn){
      return;
    }
    analogWrite(pinNum, brightness);
    
    brightness = brightness - decayIncrement;
    
    if (brightness <= 0 || brightness >= 255){
      brightness = 0;
    }
  
    delay(30);
    stopTime = millis();
  }
}

void executeRun() {
  executeRunSub();
  decayOverMs(6000, greenPin);
  blink(500, 4, greenPin);
  executeRunSub();
  shouldReturn = false;
}

void executeSleep() {
  blink(1000, 4, bluePin);
  decayOverMs(1000, bluePin);
  shouldReturn = false;
}

void executeRunSub() {
  while(statusBB)
  {
    shouldReturn = false;
    if(currState == Off){
      shouldReturn = true;
      return;
    }
    
    digitalWrite(greenPin, HIGH);
    blink(2000, 1, bluePin);
    blinkSub2(2000, 10, bluePin);
    if(digitalRead(switch1)){
      statusBB = false;
      break;
    }
  }
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);
}
void executeDiagnostic()
{
  analogWrite(redPin, initBrightness);
  delay(500);
  analogWrite(redPin, 0);
  analogWrite(bluePin, initBrightness);
  delay(500);
  analogWrite(bluePin, 0);
  analogWrite(greenPin, initBrightness);
  delay(500);
  analogWrite(greenPin, 0);
}

//-------------------ISR--------------------------
void button1ISR() {
  currState = Run;
  runStart = millis();
  shouldReturn = true;
}

void button2ISR(){
  if(currState != Diagnostic && currState != Off)
  {
    currState = Diagnostic;
  }
  else if(currState == Off){
    return;
  }
  else{
    runStart = millis();
    currState = Run;
  }
  shouldReturn = true;
}

void switchISR(){
  if(!digitalRead(switchOn))
  {
    currState = Off;
    shouldReturn = true;
  }
 else
 {
  currState = On;
 }
}

void switch1ISR(){
  if(!digitalRead(switch1))
  {
    statusBB = true;
    shouldReturn = true;
  }
  else{
    shouldReturn = true;
    statusBB = false;
  }
  
}

void switch2ISR(){
  if(digitalRead(switch2)){
    statusRSBO = true;
  }
  else{
    statusRSBO = false;
  }
    
}
