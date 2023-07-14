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




void setup()
{
  Serial.begin(115200);
  if (myScale.is_ready())
  {
    Serial.println();
    Serial.println("Initialize the Load Cell");
    myScale.begin(dataPin, clockPin);
    Serial.println("UNITS: gram");
    Serial.println(myScale.get_units(10));
  }
  else{
    Serial.println("Load Cell Disconnected");
  }
  calibrate();
}


void loop()
{
  Serial.print(myScale.get_units(10));
  Serial.println("(g) ");
  delay(250);
}






void calibrate()
{
  Serial.println("\n\n===========\nCALIBRATION\n===========");
  Serial.println("Remove all weight from the loadcell");
  //  flush Serial input
  while (Serial.available()) Serial.read();


  Serial.println("and press enter\n");
  while (Serial.available() == 0);


  Serial.println("Determine zero weight offset");
  myScale.tare(20);  // average 20 measurements.
  uint32_t offset = myScale.get_offset();


  Serial.print("OFFSET: ");
  Serial.println(offset);
  Serial.println();




  Serial.println("place a weight on the loadcell");
  //  flush Serial input
  while (Serial.available()) Serial.read();


  Serial.println("enter the weight in (whole) grams and press enter");
  uint32_t weight = 0;
  while (Serial.peek() != '\n')
  {
    if (Serial.available())
    {
      char ch = Serial.read();
      if (isdigit(ch))
      {
        weight *= 10;
        weight = weight + (ch - '0');
      }
    }
  }
  Serial.print("WEIGHT: ");
  Serial.println(weight);
  myScale.calibrate_scale(weight, 20);
  float scale = myScale.get_scale();


  Serial.print("SCALE:  ");
  Serial.println(scale, 6);


  Serial.print("\nuse scale.set_offset(");
  Serial.print(offset);
  Serial.print("); and scale.set_scale(");
  Serial.print(scale, 6);
  Serial.print(");\n");
  Serial.println("in the setup of your project");


  Serial.println("\n\n");
}

