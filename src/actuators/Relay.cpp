//#include "WProgram.h"
#include <Arduino.h>
#include <actuators/DigitalControl.h>
#include "Relay.h"


Relay::Relay(uint8_t pin){
  this->begin(pin);
}
void Relay::begin(uint8_t pin){
  this->pinD = pin;
  DigitalControl::begin();
}
void Relay::stop(){
  this->started = false;
  this->commonlyClose();
}

uint8_t Relay::getCode(){
	return 101;
}

void Relay::commonlyOpen(){
  digitalWrite(pinD, HIGH);
  this->state = HIGH;
}
void Relay::commonlyClose(){
  digitalWrite(pinD, LOW);
  this->state = LOW;
}
void Relay::changeStatus(){
  if(this->state == HIGH){
    commonlyClose();
  }else{
    commonlyOpen();
  }
}
