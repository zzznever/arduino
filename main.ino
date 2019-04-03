#include <Wire.h>
#include "DHT.h"
#include "Arduino.h"
#include "SI114X.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SeeedOLED.h>

#define DHTTYPE DHT11
#define DHTPIN 2
#define ONE_WIRE_BUS 7

SI114X SI1145 = SI114X();
DHT dht(DHTPIN, DHTTYPE);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup(void) {
  Serial.begin(9600);

  // Wait for SI1145 to initialize, otherwise we can't read from it. 
  while (!SI1145.Begin()){}
  
  sensors.begin();
  dht.begin();
  Wire.begin();

  SeeedOled.init();                       //initialze SEEED OLED display
  SeeedOled.setNormalDisplay();           //Set display to normal mode (i.e non-inverse mode)
  SeeedOled.setPageMode();                //Set addressing mode to Page Mode
  SeeedOled.putString("Hello World!");    //Print the String
  SeeedOled.clearDisplay();
}

void oled_display(void) {
  //SeeedOled.clearDisplay();
  SeeedOled.setTextXY(0, 0);
  SeeedOled.putString("Visible.: ");
  SeeedOled.putNumber(SI1145.ReadVisible());
  SeeedOled.setTextXY(1, 0);
  SeeedOled.putString("IR......: ");
  SeeedOled.putNumber(SI1145.ReadIR());
  SeeedOled.setTextXY(2, 0);
  SeeedOled.putString("UV......: ");
  SeeedOled.putFloat((float)SI1145.ReadUV() / 100);
  SeeedOled.setTextXY(3, 0);
  SeeedOled.putString("Temp (C): ");
  SeeedOled.putFloat(sensors.getTempCByIndex(0));
  SeeedOled.setTextXY(4, 0);
  SeeedOled.putString("Humidity: ");
  SeeedOled.putNumber(dht.readHumidity());
}

void loop(void) {
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  //sensors.requestTemperatures();
  float h = dht.readHumidity();
  //float t = dht.readTemperature();

  //Serial.print("visual_light ");
  Serial.print(SI1145.ReadVisible());
  Serial.print(" ");

  //Serial.print("ir_light     ");
  Serial.print(SI1145.ReadIR());
  Serial.print(" ");

  //Serial.print("uv_light     ");
  Serial.print((float)SI1145.ReadUV() / 100);
  Serial.print(" ");

  //Serial.print("celcius_temp ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print(" ");
  Serial.print(h);

  Serial.println();

  oled_display();
}
