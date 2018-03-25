/*
 * PIR sensor tester
 */
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "config.h"
#include "Adafruit_MQTT.h"
#include "ArduinoHttpClient.h"



Adafruit_8x16minimatrix matrix = Adafruit_8x16minimatrix();
AdafruitIO_Feed *ioFeed = io.feed("Motion Sensor Count Tracker");


int ledPin = LED_BUILTIN;       // choose the pin for the LED
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
                    // variable for reading the pin status
int counter = 0;
int currentState = 0;
int previousState = 0;
 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT); // declare the motion sensor data as input.
  
  matrix.begin(0x70); 
  matrix.clear();
  
  Serial.begin(9600); 
   while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  delay(100);
}
 
void loop(){
  delay(2000);//every 10 second
  
  int currentState = digitalRead(inputPin);//getting the current state from input pin
  Serial.println("Current State Value: ");
  Serial.print(currentState);
  
  if (currentState == HIGH){
    //motion has been detected
    counter = counter+1;// increment counter to 1
    Serial.println("Value of Counter (inside if condition): ");
    Serial.print(counter);
      io.run();

  // save count to the 'counter' feed on Adafruit IO
  Serial.print("sending -> ");
  Serial.println(counter);
  ioFeed->save(counter);
    }


//Show it on    LED 
      matrix.clear();
      matrix.setTextSize(1);
      matrix.setTextWrap(false); // makes it so the text doesn't wrap
      matrix.setTextColor(LED_ON);
      matrix.setRotation(1);
      Serial.println("Value of Counter (when showing on LED): ");
      Serial.print(counter);
      for (int8_t x=7; x>=-36; x--)
    {
      matrix.clear();
      matrix.setCursor(x,0);
      matrix.writeDisplay();
      
      matrix.print(counter);
      matrix.writeDisplay();
      delay(100);
    }
  }
  /*
   int val = digitalRead(inputPin);  // read input value
  if(val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
  */

