//#include "WProgram.h"
#include <Arduino.h>
#include <EEPROM.h>
#include <ComponentAbstract.h>
#include "TempBase.h"

TempBase::TempBase(){}
TempBase::TempBase(uint8_t pinA, uint8_t type) {
  this->begin(pinA, type);
}
void TempBase::begin(uint8_t pinA, uint8_t type) {
  this->pinA = pinA;
  this->type = type;
  this->begin();
}
void TempBase::begin() {
  this->started = true;
}
void TempBase::stop() {
  this->started = false;
}

uint8_t TempBase::getCode(){
	return 3;
}

uint8_t TempBase::getPinA(){
  return pinA;
}
void TempBase::setPinA(uint8_t pinA){
  this->pinA = pinA;
}
float TempBase::getTemperatura(){
  return temp;
}

//Sensor Interface
void TempBase::updateSensor(){
  int lectura = analogRead(this->pinA);
  float voltaje = 5.0 /1024 * lectura ;
  if(this->type == 1){
    //LM35DZ
    temp= voltaje * 100 ;
  }else{
    //TMP36
    temp= voltaje * 100 - 50;
  }
}
int TempBase::getLevel(uint8_t type){
  return this->temp;
}

//EEPROM
uint8_t TempBase::positions(){
	return 10;
}
void TempBase::readSpecificFromEeprom(int &pos){
  this->pinA = EEPROM.read(pos++);
  this->type = EEPROM.read(pos++);
  this->begin();
}
void TempBase::saveSpecificPartialInEeprom(int &pos){
  #if defined(ESP8266) || defined(ESP32)
    // ESP
    EEPROM.put(pos++, this->pinA);
    EEPROM.put(pos++, this->type);
  #else
    // ARDUINO
    EEPROM.update(pos++, this->pinA);
    EEPROM.update(pos++, this->type);
  #endif
}
