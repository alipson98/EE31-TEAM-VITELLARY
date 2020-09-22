
/*
  Web client

 This sketch connects to a website (http://www.google.com)
 using the WiFi module.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */


#include <SPI.h>
#include <WiFiNINA.h>

#define SEAN "2EA3F426665F"
#define BRANDON "59350B9773E5"
#define TASWAR "F37F8862AD3C"
#define ADAM "86A43FF4A96C"
#define VARUN "A021AFE7B2B2"
#define JOE "6363A1807A43"

#define MAX_MESSAGE_SIZE 1024


#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
const char ssid[] = "Raccoon Net";        // your network SSID (name)
const char pass[] = "hauntedhouse";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "ee31.ece.tufts.edu";    // name address for Google (using DNS)

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

char recieved_message[MAX_MESSAGE_SIZE];

bool did = false;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // Serial.print("connected: ");
  // Serial.println(WL_CONNECTED);
  // Serial.print("idle: ");
  // Serial.println(WL_IDLE_STATUS);
  // Serial.print("ap connected: ");
  // Serial.println(WL_AP_CONNECTED);
  // Serial.print("ap listing: ");
  // Serial.println(WL_AP_LISTENING);
  // Serial.print("no shield: ");
  // Serial.println(WL_NO_SHIELD);
  // Serial.print("no module: ");
  // Serial.println(WL_NO_MODULE);
  // Serial.print("no ssid available: ");
  // Serial.println(WL_NO_SSID_AVAIL);
  // Serial.print("scan completed: ");
  // Serial.println(WL_SCAN_COMPLETED);
  // Serial.print("connect failed: ");
  // Serial.println(WL_CONNECT_FAILED);
  // Serial.print("connection lost: ");
  // Serial.println(WL_CONNECTION_LOST);
  // Serial.print("disconnected: ");
  // Serial.println(WL_DISCONNECTED);
  // Serial.print("idle: ");
  // Serial.println(WL_IDLE_STATUS);
  // String str = String("hello") + ADAM;
  // Serial.println(str);
  // while(true);

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // status = WiFi.status();
    Serial.println(status);

    // wait 10 seconds for connection:
    delay(5000);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    // sendPost("led=on&pin=12", ADAM, VARUN);

  }
  // GETServer(VARUN, ADAM);
}

void loop() {
  if (!did) {
    GETServer(VARUN, ADAM);
    did = true;
  }
  // GETServer(VARUN, ADAM);
  // if there are incoming bytes available
  // from the server, read them and print them:
  // while (client.available()) {
  //   char c = client.read();
  //   Serial.write(c);
  // }
  if (client.available()){
    getMessageData();
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while (true);
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
        // Serial.println(String("add ") + message.charAt(msg_idx) + " to key");
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
        // Serial.println(String("add ") + message.charAt(msg_idx) + " to value");
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
}