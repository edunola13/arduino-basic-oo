//#include "WProgram.h"
#include <Arduino.h>
#include <EEPROM.h>
#include <ComponentAbstract.h>
#include "DigitalControl.h"

DigitalControl::DigitalControl(){}
DigitalControl::DigitalControl(uint8_t pinD, uint8_t type){
  this->begin(pinD, type);
}
void DigitalControl::begin(uint8_t pinD, uint8_t type) {
  this->pinD= pinD;
  this->type= type;
  this->begin();
}
void DigitalControl::begin() {
  pinMode(this->pinD, OUTPUT);
  this->started = true;
  this->set(0);
}
void DigitalControl::stop() {
  this->started = false;
}

uint8_t DigitalControl::getCode(){
	return 105;
}

void DigitalControl::set(uint8_t value){
  if(this->type == 1){
	  digitalWrite(this->pinD, value);
  }else{
    analogWrite(this->pinD, value);
  }
  this->state = value;
}

uint8_t DigitalControl::getPinD(){
  return this->pinD;
}
void DigitalControl::setPinD(uint8_t pinD){
  this->pinD = pinD;
  this->begin();
}
uint8_t DigitalControl::getState(){
  return this->state;
}

//EEPROM
uint8_t DigitalControl::positions(){
	return 5;
}
void DigitalControl::readSpecificFromEeprom(int &pos){
  ActuatorAbstract::readSpecificFromEeprom(pos);
  this->pinD = EEPROM.read(pos++);
  this->type = EEPROM.read(pos++);
  this->begin();
  if(this->keepValue){
    // Leo el valor que tenia y lo seteo
    this->state = EEPROM.read(pos++);
    this->set(this->state);
  }
}
void DigitalControl::saveSpecificPartialInEeprom(int &pos){
  ActuatorAbstract::saveSpecificPartialInEeprom(pos);
  #if defined(ESP8266) || defined(ESP32)
    EEPROM.put(pos++, this->pinD);
    EEPROM.put(pos++, this->type);
    // Guardo siempre aunque despues no lo tenga que usar
    EEPROM.put(pos++, this->state);
  #else
    EEPROM.update(pos++, this->pinD);
    EEPROM.update(pos++, this->type);
    // Guardo siempre aunque despues no lo tenga que usar
    EEPROM.update(pos++, this->state);
  #endif
}
