/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
  Based on the Dallas Temperature Library example
*********/
#include <Wire.h>
#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 2
#include "Arduino.h"
#include "SI114X.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SeeedOLED.h>
SI114X SI1145 = SI114X();
// Data wire is conntec to the Arduino digital pin 2
#define ONE_WIRE_BUS 7
DHT dht(DHTPIN, DHTTYPE);
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

void setup(void)
{
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library
  sensors.begin();

  while (!SI1145.Begin()) {
    Serial.println("Si1145 is not ready!");
    delay(1000);
  }
  //Serial.println("Si1145 is ready!");
  //Serial.println("DHTxx test!");

  /*if using WIO link,must pull up the power pin.*/
  // pinMode(PIN_GROVE_POWER, OUTPUT);
  // digitalWrite(PIN_GROVE_POWER, 1);

  dht.begin();

  Wire.begin();
  SeeedOled.init();  //initialze SEEED OLED display

  SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
  SeeedOled.setPageMode();           //Set addressing mode to Page Mode
  SeeedOled.setTextXY(0, 0);         //Set the cursor to Xth Page, Yth Column
  SeeedOled.putString("Hello World!"); //Print the String
}

void oled_display(void) {
  SeeedOled.clearDisplay();
  SeeedOled.setTextXY(0, 0);
  SeeedOled.putNumber(SI1145.ReadVisible());
  SeeedOled.setTextXY(1, 0);
  SeeedOled.putNumber(SI1145.ReadIR());
  SeeedOled.setTextXY(2, 0);
  SeeedOled.putNumber((float)SI1145.ReadUV() / 100);
  SeeedOled.setTextXY(3, 0);
  SeeedOled.putNumber(sensors.getTempCByIndex(0));
  SeeedOled.setTextXY(4, 0);
  SeeedOled.putNumber(dht.readHumidity());
}

void loop(void) {
  delay(1000);
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  //Serial.print("//--------------------------------------//\r\n");
  //Serial.print("visual_light ");
  Serial.print(SI1145.ReadVisible());
  Serial.print(" ");
  //Serial.print("ir_light     ");
  Serial.print(SI1145.ReadIR());
  Serial.print(" ");
  //the real UV value must be div 100 from the reg value , datasheet for more information.
  //Serial.print("uv_light     ");
  Serial.print((float)SI1145.ReadUV() / 100);
  Serial.print(" ");
  //Serial.print("celcius_temp ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print(" ");
  //Serial.print(" - Fahrenheit temperature: ");
  //Serial.println(sensors.getTempFByIndex(0));

  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }
  else
  {
    //Serial.print("humidity     ");
    Serial.println(h);

    //Serial.println(" %\t");
    //Serial.print("Temperature: ");
    //Serial.print(t);
    //Serial.println(" *C");
  }

  oled_display();
  delay(1000);
}
