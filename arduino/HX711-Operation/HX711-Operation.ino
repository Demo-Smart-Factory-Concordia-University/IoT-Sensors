// ----------------------------------------------------------------
// HX711 Load Cell Mesurement
//
// (c) Zhaohan Zheng
//     2023 Concordia University
//
// author:  Zhaohan Zheng
// email:   zhaohan.zheng@mail.concordia.ca
//
// This software is copyright under the BSD license
// ---------------------------------------------------------------
// history:
// ---------------------------------------------------------------
// Date         Modification                     Author
// ---------------------------------------------------------------
// 13.07.2023   Creation                         Z. Zheng
// ---------------------------------------------------------------




//Fine tune is needed for correct unit calculation


#define VERSION "V1.0"
//https://docs.espressif.com/projects/esp-idf/en/latest/esp32/
//https://github.com/RobTillaart/HX711
#include "HX711.h"


// initialize HX711 library
HX711 myScale;


uint8_t dataPin = 18;
uint8_t clockPin = 5;
uint32_t offset = 10;
uint32_t factor = 400;


void setup()
{
  Serial.begin(115200);
  if (myScale.is_ready())
  {
    Serial.println();
    Serial.println("Initialize the Load Cell");
    myScale.begin(dataPin, clockPin);
    Serial.println("UNITS: gram");
    Serial.print("Scale Factor: ");
    Serial.print(factor);
    Serial.print("Scale offset");
    Serial.println(offset);
  }
  else{
    Serial.println("Load Cell Disconnected");
  }
}


void loop()
{
  uint32_t Readings = myScale.read_average(10) *offset + factor;
  Serial.print(Readings);
  Serial.println(" (g) ");
  delay(250);                       //Change for the scale refresh time
}

