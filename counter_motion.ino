/*************************************************** 
  This is a library for our I2C LED Backpacks & FeatherWings

  Designed specifically to work with the Adafruit 16x8 LED Matrix FeatherWing

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_8x16minimatrix matrix = Adafruit_8x16minimatrix();

int inputPin = 12; // the input pin for the PIR sensor
int counter = 0;
int currentState = 0;
int previousState = 0;  
int pirState = LOW;     // we start assuming no motion has been detected.
int val = 0; //   variable for reading the pin state

void setup() {
  matrix.begin(0x70); 
  matrix.clear();
  pinMode(inputPin, INPUT);   // declare sensor as input
  Serial.begin(9600);
  delay(100);

}


void loop() {

  delay(100);
  currentState = digitalRead(inputPin);
    if ( currentState != previousState) {
      pirState = LOW;}

  //motion has been detected

   else { 
      for (int i = 0; < currentState; i++)
      counter = counter+1;
      Serial.println(counter);
      pirState = HIGH;
    }
    
    else {
      if (pirState == HIGH){
   
    previousState = currentState;
    delay(0);
    matrix.drawPixel(0, 0, LED_ON);
    pirState = LOW;
      }



{
  matrix.clear();
  matrix.setTextSize(1);
  matrix.setTextWrap(false); // makes it so the text doesn't wrap
  matrix.setTextColor(LED_ON);
  matrix.setRotation(1);
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
}
}
}


