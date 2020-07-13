#include <Arduino.h>
#include <EEPROM.h>
#include <ComponentAbstract.h>
#include <Adafruit_BMP085.h>
#include "BMPSensor.h"

BMPSensor::BMPSensor(int altitude, uint8_t type){
  this->begin(altitude, type);
}
void BMPSensor::begin(int altitude, uint8_t type){
  this->type = type;
  this->altitude = altitude;
  this->bmp.begin();
  this->started = true;
}
void BMPSensor::stop(){
  this->started = false;
}

uint8_t BMPSensor::getCode(){
	return 6;
}

int BMPSensor::getAltitude(){
  return this->altitude;
}
void BMPSensor::setAltitude(int altitude){
  this->altitude = altitude;
}
int32_t BMPSensor::getPressurePa(){
  return this->pressure;
}
int32_t BMPSensor::getPressureHPa(){
  return this->pressure / 100;
}
float BMPSensor::getTemperatura(){
  return this->temp;
}

//Sensor Interface
void BMPSensor::updateSensor(){
  this->temp = this->bmp.readTemperature();
  this->pressure = this->bmp.readSealevelPressure(this->altitude);
}
int BMPSensor::getLevel(uint8_t type){
  if(type == 0){
	   return this->temp;
  }else{
	   return this->pressure;
  }
}

//EEPROM
uint8_t BMPSensor::positions(){
	return 5;
}
void BMPSensor::readSpecificFromEeprom(int &pos){
  this->altitude = EEPROM.read(pos++);
  this->type = EEPROM.read(pos++);
  this->begin();
}
void BMPSensor::saveSpecificPartialInEeprom(int &pos){
  #if defined(ESP8266) || defined(ESP32)
    // ESP
    EEPROM.put(pos++, this->altitude);
    EEPROM.put(pos++, this->type);
  #else
    // ARDUINO
    EEPROM.update(pos++, this->altitude);
    EEPROM.update(pos++, this->type);
  #endif
}
