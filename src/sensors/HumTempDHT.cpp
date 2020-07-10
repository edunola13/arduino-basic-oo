#include <Arduino.h>
#include <EEPROM.h>
#include <ComponentAbstract.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "HumTempDHT.h"

HumTempDHT::HumTempDHT(){}
HumTempDHT::HumTempDHT(uint8_t pin, uint8_t type){
  this->begin(pin, type);
}
void HumTempDHT::begin(){
  pinMode(pin, INPUT_PULLUP);
  this->started = true;
}
void HumTempDHT::begin(uint8_t pin, uint8_t type){
  this->type = type;
  this->pin = pin;
  this->begin();
}
void HumTempDHT::stop(){
  this->started = false;
}

uint8_t HumTempDHT::getCode(){
	return 2;
}

uint8_t HumTempDHT::getPin(){
  return this->pin;
}
void HumTempDHT::setPin(uint8_t pin){
  this->pin = pin;
  this->begin();
}
float HumTempDHT::getHumedad(){
  return this->hum;
}
float HumTempDHT::getTemperatura(){
  return this->temp;
}
bool HumTempDHT::getErrorRead(){
  return this->errorRead;
}

//Sensor Interface
void HumTempDHT::updateSensor(){
  DHT dht(pin, type);
  dht.begin();
  float h = dht.readHumidity();
  //Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    this->errorRead = true;
  }else{
    this->errorRead = false;
    this->hum = h;
    this->temp = t;
  }
}
int HumTempDHT::getLevel(uint8_t type){
  if(type == 0){
	   return this->hum;
  }else{
	   return this->temp;
  }
}

//EEPROM
uint8_t HumTempDHT::positions(){
	return 5;
}
void HumTempDHT::readSpecificFromEeprom(int &pos){
  this->pin= EEPROM.read(pos++);
  this->type= EEPROM.read(pos++);
  this->begin();
}
void HumTempDHT::saveSpecificPartialInEeprom(int &pos){
  #if defined(ESP8266) || defined(ESP32)
    // ESP
    EEPROM.put(pos++, this->pin);
    EEPROM.put(pos++, this->type);
  #else
    // ARDUINO
    EEPROM.update(pos++, this->pin);
    EEPROM.update(pos++, this->type);
  #endif
}
