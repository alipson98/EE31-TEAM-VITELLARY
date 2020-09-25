#include "Arduino.h"

#include <SPI.h>
#include <WiFiNINA.h>

/*** these name macros should be used only as reference to set ME and PARTNER ***/
// SEAN "2EA3F426665F"
// BRANDON "59350B9773E5"
// TASWAR "F37F8862AD3C"
// ADAM "86A43FF4A96C"
// VARUN "A021AFE7B2B2"
// JOE "6363A1807A43"

// TODO: set these to the correct values
#define ME "86A43FF4A96C" // adam
#define PARTNER "59350B9773E5" // brandon

#define MAX_MESSAGE_SIZE 1024
#define FOLLOW_TIMEOUT 500 // 1 second

enum BOT_STATE {IDLE, ENTERING_FOLLOWING, FOLLOWING, LISTENING};

// TODO: fill this in your wifi info
const char ssid[] = "Raccoon Net";        // your network SSID (name)
const char pass[] = "hauntedhouse";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)
int status = WL_IDLE_STATUS;
char server[] = "ee31.ece.tufts.edu";

WiFiClient client;

char recieved_message[MAX_MESSAGE_SIZE];

const static int right_F = 5;
const static int right_R = 6;
const static int left_F = 9;
const static int left_R = 10;
const int greenLED = 12;
const static int wifiLED = 13;
const static int RED = 11;
const static int GREEN = 7; // digital because we ran out of pwm pins
const static int BLUE = 3;
const int thermPin = A1;
int tempReading = 0;
int statusLight = 2;
const int thermThresh = 286; // TODO: test and change this to the correct value

bool lightTrack = false;

const static int inf_reciever = 4;

const int AN_SPEED = 100;
const int LIGHT_THRESHOLD = 775; // TODO: set this

BOT_STATE state;
unsigned long time_saw_line;
bool green_led_on = false;
unsigned long green_led_start;
unsigned int green_led_flash_time = 2000; // blink for two seconds

void setup(){
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(A0, INPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(wifiLED, OUTPUT);
  pinMode(statusLight, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);


  Serial.begin(9600);
  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
  Drive_stop();

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // status = WiFi.status();
    // Serial.println(status);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    digitalWrite(wifiLED, HIGH);
  }
  sendPost("reset=true", ME, PARTNER);
  pinMode(thermPin, INPUT);
  tempReading = analogRead(thermPin);

  // rgb led purple
  analogWrite(RED, 150);
  digitalWrite(GREEN, LOW);
  analogWrite(3, 210);

  SleepNow();
  
  state = ENTERING_FOLLOWING;
}


void loop(){
  if (client.available()){
    getMessageData();
  }
  
  switch (state)
  {
  case ENTERING_FOLLOWING:
    time_saw_line = millis();
    state = FOLLOWING;
    break;
  case FOLLOWING:
    // rgb led green
    analogWrite(RED, 0);
    digitalWrite(GREEN, HIGH);
    analogWrite(3, 0);
    if (digitalRead(inf_reciever)) {
        Drive_pivot_right();
        time_saw_line = millis();
    } else {
        Drive_pivot_left();
        if (millis() - time_saw_line > FOLLOW_TIMEOUT) {
          Serial.println("follow failed");
          Drive_stop();
          sendPost("myTask=complete&lightTrack=start", ME, PARTNER);
          // while(true);
          state = LISTENING;
          delay(2000);
          green_led_start = millis();
          green_led_on = true;
        }
    }
    break;
  case LISTENING:
    // rgb led yellow
    analogWrite(RED, 240);
    digitalWrite(GREEN, HIGH);
    analogWrite(3, 42);
    // Serial.println("listening");
    // GETServer(ME, PARTNER);
    GETServer(ME, PARTNER);
    delay(300); // delay to not overload the server
    if (client.available()){
      getMessageData();
    }
    break;
  
  default:
    break;
  }

  // green led handler
  if (green_led_on) {
    digitalWrite(greenLED, HIGH);
    if (millis() - green_led_start > green_led_flash_time) {
      green_led_on = false;
      digitalWrite(greenLED, LOW);
    }
  }

}

void readthepins(){
  Serial.println(digitalRead(5));
  Serial.println(digitalRead(6));
  Serial.println(digitalRead(9));
  Serial.println(digitalRead(10)); 
}

void Drive_forward() {
  analogWrite(left_F, AN_SPEED);
  analogWrite(left_R, 0);
  analogWrite(right_F, AN_SPEED);
  analogWrite(right_R, 0);
}

void Drive_backward() {
  analogWrite(left_F, 0);
  analogWrite(left_R, AN_SPEED);
  analogWrite(right_F, 0);
  analogWrite(right_R, AN_SPEED);
}

void Drive_stop() {
  analogWrite(left_F, 0);
  analogWrite(left_R, 0);
  analogWrite(right_F, 0);
  analogWrite(right_R, 0);
}

//spin = center of rotation is the center of the bot
void Drive_spin_left(){
  analogWrite(left_F, 0);
  analogWrite(left_R, AN_SPEED);
  analogWrite(right_F, AN_SPEED);
  analogWrite(right_R, 0);
  
}

void Drive_spin_right(){
  analogWrite(left_F, AN_SPEED);
  analogWrite(left_R, 0);
  analogWrite(right_F, 0);
  analogWrite(right_R, AN_SPEED);
}

//pivot = center of rotation is left or right wheel
void Drive_pivot_left(){
  digitalWrite(left_F, LOW);
  digitalWrite(left_R, LOW);
  analogWrite(right_F, AN_SPEED);
  digitalWrite(right_R, LOW);
}

void Drive_pivot_right(){
  analogWrite(left_F, AN_SPEED);
  digitalWrite(left_R, LOW);
  digitalWrite(right_F, LOW);
  digitalWrite(right_R, LOW);
}

/**
 * @brief follow a light
 * 
 */
void Follow_Light() {
    if (analogRead(A0) < LIGHT_THRESHOLD) {
      digitalWrite(greenLED, HIGH);
      lightTrack = true;
      while(lightTrack) {
        Drive_forward();
          if (analogRead(A0) >= LIGHT_THRESHOLD) {
            for (int i = 0; i < 4; i++) {
              Drive_pivot_left();
              delay(500);
              Drive_stop();
              if (analogRead(A0) < LIGHT_THRESHOLD) {
                break;
              }
              Drive_pivot_right();
              delay(1000);
              if (analogRead(A0) < LIGHT_THRESHOLD) {
                break;
              }
              if (i == 3) {
                lightTrack = false;
              }
            }
          
        }
    }
    Drive_stop();
    digitalWrite(greenLED, LOW);
  }
  
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

/**
 * @brief send a POST to the ee31 server
 * 
 * @param message 
 * @param senderID 
 * @param receiverID 
 */
void sendPost(char *message, const char * senderID, const char * receiverID) {
  if (!client.connected()) {
    client.connect(server, 80);
  }
  String route = String("POST /") + senderID + "/" + receiverID + " HTTP/1.1";
  client.println(route);     
  client.print("Host: ");     
  client.println(server);     
  client.println("Content-Type: application/x-www-form-urlencoded");     
  client.print("Content-Length: ");     
  int postBodyLength = strlen(message);     
  client.println(postBodyLength);     
  client.println();     
  client.print(message);
}

/**
 * @brief make a GET request to the server
 * 
 * @param senderID 
 * @param posterID 
 */
void GETServer(const char *senderID, const char *posterID) {
  String route = String("GET /") + senderID + "/" + posterID + " HTTP/1.1";

 if (client.connect(server, 80)) {
    // Make a HTTP GET request:
    client.println(route);
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
    
    //GetMessageBody(); // get the message from the server
    
    // place in appropriate form and variable
    // if the server's disconnected, stop the client:
    if (!client.connected()) {
      client.stop();
    }
  }
}

/**
 * @brief extract the actual message from the HTTP response to a GET
 * should only be called if client.available() is true
 * 
 * extracts the message and then executes whatever actions it contains
 */
void getMessageData() {
  String message = "";
  while (client.available()) {
    char c = client.read();
    message += String(c);
  }
  // message = message.substring(62);
  String msgbegin = "senderID=";
  for (int i = 0; i < message.length(); i++) {
    if ((message.substring(i, i + 9)).equals("senderID=")) { //
      Serial.print("found message in response: ");
      Serial.println(message.substring(i));
      parse_and_execute(message.substring(i));
    }
  }
  // Serial.println(message);
}

// helper enum for the parse_and_execute function
enum parse_execute_state {reading_key, reading_val};

/**
 * @brief parse a message into key/value pairs and execute each pair
 * 
 * @param message 
 */
void parse_and_execute(String message) {
  String key = "";
  String value = "";
  int msg_idx = 0;
  parse_execute_state state = reading_key;
  while (msg_idx < message.length()) {
    switch (state)
    {
    case reading_key:
      if (message.charAt(msg_idx) == '=') {
        state = reading_val;
      } else {
        key += message.charAt(msg_idx);
      }
      break;

    case reading_val:
      if (message.charAt(msg_idx) == '&') {
        execute_key_value(key, value);
        state = reading_key;
        key = "";
        value = "";
      } else {
        value += message.charAt(msg_idx);
      }
      break;
    
    default:
      break;
    }
    msg_idx++;
  }
  if (!key.equals("")) {
    execute_key_value(key, value);
  }
}

/**
 * @brief execute a key/value pair
 * 
 * @param key 
 * @param value 
 */
void execute_key_value(String key, String value) {
  Serial.print(key + ": ");
  Serial.println(value);
  if (key.equals("foundLight") && value.equals("true")) {
    green_led_on = true;
    green_led_start = millis();
  } else if (key.equals("finished") && value.equals("true")){
    digitalWrite(greenLED, LOW);
    lightShow();
  }
}

void SleepNow(){
  // Serial.println(analogRead(thermPin));
  while(tempReading < thermThresh)
  {
    // Serial.println(analogRead(thermPin));
    digitalWrite(LED_BUILTIN, LOW);
    tempReading = analogRead(thermPin);
    Serial.println(tempReading);
    if(tempReading >= thermThresh){
      digitalWrite(LED_BUILTIN, LOW);

      break;
    }
  }
}

void lightShow(){
  for (int i = 0; i < 5; i++) {
    // red
    analogWrite(RED, 255);
    digitalWrite(GREEN, LOW);
    analogWrite(3, 0);
    delay(500);

    // green
    analogWrite(RED, 0);
    digitalWrite(GREEN, HIGH);
    analogWrite(3, 0);
    delay(500);

    // blue
    analogWrite(RED, 0);
    digitalWrite(GREEN, LOW);
    analogWrite(3, 255);
    delay(500);
  }

  for (int i = 0; i < 5; i++) {
    // red
    analogWrite(RED, 120);
    digitalWrite(GREEN, HIGH);
    analogWrite(3, 200);
    delay(500);

    // green
    analogWrite(RED, 255);
    digitalWrite(GREEN, HIGH);
    analogWrite(3, 0);
    delay(500);

    // blue
    analogWrite(RED, 0);
    digitalWrite(GREEN, HIGH);
    analogWrite(3, 100);
    delay(500);
  }

  for (int i = 0; i < 5; i++) {
    // red
    analogWrite(RED, 255);
    digitalWrite(GREEN, LOW);
    analogWrite(3, 0);
    delay(500);

    // green
    analogWrite(RED, 0);
    digitalWrite(GREEN, HIGH);
    analogWrite(3, 0);
    delay(500);

    // blue
    analogWrite(RED, 0);
    digitalWrite(GREEN, LOW);
    analogWrite(3, 255);
    delay(500);
  }

  // off and end
  analogWrite(RED, 0);
  digitalWrite(GREEN, LOW);
  analogWrite(3, 0);
  while(true);
}