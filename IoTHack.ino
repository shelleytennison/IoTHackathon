/*

 *  Simple HTTP get webclient test

 */

 
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x16minimatrix matrix = Adafruit_8x16minimatrix();

const char* ssid     = "Puppet Guest";

const char* password = "argon4949";

 

const char* host = "wifitest.adafruit.com";

String URI = "hackathonweb.php";

String server = "https://motionsensorsurvey.000webhostapp.com";

String data = "motiondata=100";

const char* motion_count = "0";

int ledPin = 12; // the pin for the LED 
int inputPin = 12; // th input pin for the PIR sensor
int pirState = LOW; // we start, assuming no motion has been detected. 
int val = 0; // variable for reading the pin status
int counter = 0;
int currentState = 0;
int previousState = 0;


void setup() {

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); // declare LED as output
  pinMode(ledPin, INPUT); // declare the motion sensor data as input.
  delay(100);

 

  // We start by connecting to a WiFi network

 

  Serial.println();

  Serial.println();

  Serial.print("Connecting to ");

  Serial.println(ssid);

  

  WiFi.begin(ssid, password);

  

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

 

  Serial.println("");

  Serial.println("WiFi connected");  

  Serial.println("IP address: ");

  Serial.println(WiFi.localIP());

}

 

int value = 0;

 

void loop() {

  delay(1000);

  

  val = digitalRead(inputPin); // read input value
  if (val == HIGH) { // check if the input is HIGH
  digitalWrite(ledPin, HIGH); // turn LED ON
  if (pirState == LOW) {
  // we have just turned on
  currentState = 1;
  // We only want to print on the output change, not state
  pirState = HIGH;
  delay(1000);
}
}  else {
  digitalWrite(ledPin, LOW); // turn LED OFF
  if (pirState == HIGH){
  // we have just turned of
  currentState = 0;
  // We only want to print on the output change, not state
  pirState = LOW;
  }
  }
  if(currentState != previousState){
  if(currentState == 1){
  counter = counter + 1;
  Serial.println(counter);
 }
}
 

  Serial.print("connecting to ");

  Serial.println(host);

  

  // Use WiFiClient class to create TCP connections

  WiFiClient client;

  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {

    Serial.println("connection failed");

    return;

  }

  

  // We now create a URI for the request

  String url = "/testwifi/index.html";

  Serial.print("Requesting URL: ");

  Serial.println(url);

  

  // This will send the request to the server

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +

               "Host: " + host + "\r\n" + 

               "Connection: close\r\n\r\n");

  delay(500);

  motion_count = "100";

  client.print(

    String("POST ") + URI + " HTTP/1.0\r\n" +

  

    "Host: " + server + "\r\n" +

  

    "Accept: *" + "/" + "*\r\n" +

  

    "Content-Length: " + data.length() + "\r\n" +

  

    "Content-Type: application/x-www-form-urlencoded\r\n" +

  

    "\r\n" + data);

delay(1000);

  

  // Read all the lines of the reply from server and print them to Serial

  while(client.available()){

    String line = client.readStringUntil('\r');

    Serial.print(line);

  }

  

  Serial.println();

  Serial.println("closing connection");

}

