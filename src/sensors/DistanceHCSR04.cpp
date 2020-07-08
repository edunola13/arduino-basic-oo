//#include "WProgram.h"
#include <Arduino.h>
#include <EEPROM.h>
#include <ComponentAbstract.h>
#include "DistanceHCSR04.h"

DistanceHCSR04::DistanceHCSR04() {
}
DistanceHCSR04::DistanceHCSR04(uint8_t pinEcho, uint8_t pinTrig, uint8_t type) {
  this->begin(pinEcho, pinTrig, type);
}
void DistanceHCSR04::begin(uint8_t pinEcho, uint8_t pinTrig, uint8_t type) {
  this->pinEcho = pinEcho;
  this->pinTrig = pinTrig;
  this->type = type;
  this->begin();
}
void DistanceHCSR04::begin() {
  pinMode(this->pinTrig, OUTPUT);
  pinMode(this->pinEcho, INPUT);
  this->started = true;
}
void DistanceHCSR04::stop() {
  this->started = false;
}

uint8_t DistanceHCSR04::getCode(){
	return 4;
}

uint8_t DistanceHCSR04::getPinEcho(){
  return pinEcho;
}
void DistanceHCSR04::setPinEcho(uint8_t pinEcho){
  this->pinEcho = pinEcho;
  this->begin();
}
uint8_t DistanceHCSR04::getPinTrig(){
  return pinTrig;
}
void DistanceHCSR04::setPinTrig(uint8_t pinTrig){
  this->pinTrig = pinTrig;
  this->begin();
}

//Sensor Interface
void DistanceHCSR04::updateSensor(){
  digitalWrite(this->pinTrig, LOW);     // Nos aseguramos de que el trigger está desactivado
  delayMicroseconds(2);     // Para estar seguros de que el trigger ya está LOW
  digitalWrite(this->pinTrig, HIGH);    // Activamos el pulso de salida
  delayMicroseconds(10);    // Esperamos 10µs. El pulso sigue active este tiempo
  digitalWrite(this->pinTrig, LOW);     // Cortamos el pulso y a esperar el echo
  long duration;
  duration = pulseIn(this->pinEcho, HIGH);
  this->distance = duration / 2 / 29.1  ;
}
int DistanceHCSR04::getLevel(uint8_t type){
  return this->distance;
}

//EEPROM
uint8_t DistanceHCSR04::positions(){
	return 10;
}
void DistanceHCSR04::readSpecificFromEeprom(int &pos){
  this->pinEcho = EEPROM.read(pos++);
  this->pinTrig = EEPROM.read(pos++);
  this->type = EEPROM.read(pos++);
  this->begin();
}
void DistanceHCSR04::saveSpecificPartialInEeprom(int &pos){
  #if defined(ESP8266) || defined(ESP32)
    // ESP
    EEPROM.put(pos++, this->pinEcho);
    EEPROM.put(pos++, this->pinTrig);
    EEPROM.put(pos++, this->type);
  #else
    // ARDUINO
    EEPROM.update(pos++, this->pinEcho);
    EEPROM.update(pos++, this->pinTrig);
    EEPROM.update(pos++, this->type);
  #endif
}
