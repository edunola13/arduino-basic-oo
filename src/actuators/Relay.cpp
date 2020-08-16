//#include "WProgram.h"
#include <Arduino.h>
#include <EEPROM.h>
#include <actuators/DigitalControl.h>
#include "Relay.h"


Relay::Relay(uint8_t pin, bool invert){
  this->begin(pin, invert);
}
void Relay::begin(uint8_t pin, bool invert){
  this->pinD = pin;
  this->invert = invert;
  this->started = true;
  pinMode(this->pinD, OUTPUT);
  this->commonlyClose();  // Always Close
  // DigitalControl::begin();  // Cant use because the invert
}
void Relay::stop(){
  this->started = false;
  this->commonlyClose();
}

uint8_t Relay::getCode(){
	return 101;
}

bool Relay::isOpen(){
  return (!this->invert && this->state == HIGH) or (this->invert && this->state == LOW);
}
void Relay::commonlyOpen() {
  if (! this->invert) {
    this->state = HIGH;
  } else {
    this->state = LOW;
  }
  digitalWrite(pinD, this->state);
}
void Relay::commonlyClose() {
  if (! this->invert) {
    this->state = LOW;
  } else {
    this->state = HIGH;
  }
  digitalWrite(pinD, this->state);
}
void Relay::changeStatus() {
  if(this->isOpen()) {
    commonlyClose();
  } else {
    commonlyOpen();
  }
}

//EEPROM
uint8_t Relay::positions(){
	return 7;
}
void Relay::readSpecificFromEeprom(int &pos){
  DigitalControl::readSpecificFromEeprom(pos);
  this->invert = EEPROM.read(pos++);
}
void Relay::saveSpecificPartialInEeprom(int &pos){
  DigitalControl::saveSpecificPartialInEeprom(pos);
  #if defined(ESP8266) || defined(ESP32)
    EEPROM.put(pos++, this->invert);
  #else
    EEPROM.update(pos++, this->invert);
  #endif
}
