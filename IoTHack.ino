/*

 *  Simple HTTP get webclient test

 */

 

#include &lt;ESP8266WiFi.h&gt;
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x16minimatrix matrix = Adafruit_8x16minimatrix();

const char* ssid     = &quot;Puppet Guest&quot;;

const char* password = &quot;argon4949&quot;;

 

const char* host = &quot;wifitest.adafruit.com&quot;;

String URI = &quot;hackathonweb.php&quot;;

String server = &quot;https://motionsensorsurvey.000webhostapp.com&quot;;

String data = &quot;motiondata=100&quot;;

const char* motion_count = &quot;0&quot;;

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

  Serial.print(&quot;Connecting to &quot;);

  Serial.println(ssid);

  

  WiFi.begin(ssid, password);

  

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(&quot;.&quot;);

  }

 

  Serial.println(&quot;&quot;);

  Serial.println(&quot;WiFi connected&quot;);  

  Serial.println(&quot;IP address: &quot;);

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
 

  Serial.print(&quot;connecting to &quot;);

  Serial.println(host);

  

  // Use WiFiClient class to create TCP connections

  WiFiClient client;

  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {

    Serial.println(&quot;connection failed&quot;);

    return;

  }

  

  // We now create a URI for the request

  String url = &quot;/testwifi/index.html&quot;;

  Serial.print(&quot;Requesting URL: &quot;);

  Serial.println(url);

  

  // This will send the request to the server

  client.print(String(&quot;GET &quot;) + url + &quot; HTTP/1.1\r\n&quot; +

               &quot;Host: &quot; + host + &quot;\r\n&quot; + 

               &quot;Connection: close\r\n\r\n&quot;);

  delay(500);

  motion_count = &quot;100&quot;;

  client.print(

    String(&quot;POST &quot;) + URI + &quot; HTTP/1.0\r\n&quot; +

  

    &quot;Host: &quot; + server + &quot;\r\n&quot; +

  

    &quot;Accept: *&quot; + &quot;/&quot; + &quot;*\r\n&quot; +

  

    &quot;Content-Length: &quot; + data.length() + &quot;\r\n&quot; +

  

    &quot;Content-Type: application/x-www-form-urlencoded\r\n&quot; +

  

    &quot;\r\n&quot; + data);

delay(1000);

  

  // Read all the lines of the reply from server and print them to Serial

  while(client.available()){

    String line = client.readStringUntil(&#39;\r&#39;);

    Serial.print(line);

  }

  

  Serial.println();

  Serial.println(&quot;closing connection&quot;);

}


