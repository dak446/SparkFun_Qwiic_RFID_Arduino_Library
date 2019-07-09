/*
	This example reads the scanned RFID tag when the interrupt indicates that an
  RFID tag has been scanned by the Qwiic RFID Reader. This is not a 
  "pure" Qwiic example as you'll need a wire attached to pin 3 on your Arduino. 
  There is the ability to get the RFID tag ID's associated "scan" time in
  seconds with getReqTime() or getPrecReqTime(). This however is not when the
  RFID tag was scanned, but rather the time between when the tag was scanned and when you
  the user requested the tag from the Qwiic RFID Reader. Since we're using an
  interrupt to get a single tag ID, that time will be the time between when the
  interrupt fired (tag was scanned) and when you requested it (called
  getTag()). So some fraction of a second i.e. useless data. 

	By: Elias Santistevan
	Sparkfun Electronics
	Date: July, 2019
	License: This code is public domain but if you use this and we meet someday, get me a beer! 

	Feel like supporting our work? Buy a board from Sparkfun!
	https://www.sparkfun.com/products/15191

*/

#include <Wire.h> 
#include "SparkFun_Qwiic_Rfid.h"

#define RFID_ADDR 0x7D // Default I2C address 

// Interrupt Pin on pin 3. 
const int intPin = 3; 
String tag; 

Qwiic_Rfid myRfid(RFID_ADDR);

void setup()
{
  // Begin I-squared-C
	Wire.begin(); 
	Serial.begin(115200); 

  if(myRfid.begin())
    Serial.println("Ready to scan some tags!"); 
  else
    Serial.println("Could not communicate with the Qwiic RFID Reader!!!"); 

  // Put the interrupt pin in a known HIGH state. 
  pinMode(intPin, INPUT_PULLUP); 
}

void loop()
{

  // If the pin goes low, then a card has been scanned. 
  if(digitalRead(intPin) == LOW){
    tag = myRfid.getTag();
    Serial.println(tag);
  }

  delay(500); // Geeze, woah! Slow it down mate.

}
