//#include "WProgram.h"
#include <Arduino.h>
#include <EEPROM.h>
#include <JsonHelper.h>
#include "ComponentAbstract.h"

//UTIL
bool isNotNull(String value){
  return value != "null" && value != "NULL";
}

//EEPROM
//This function will write a 2 byte (16bit) int to the eeprom at the specified address to address + 1.
void EEPROMWInt(int address, int value){
  //Decomposition from a int to 2 bytes by using bitshift.
  //One = Most significant -> Two = Least significant byte
  byte two = (value & 0xFF);
  byte one = ((value >> 8) & 0xFF);
  //Write the 2 bytes into the eeprom memory.
  EEPROM.write(address, two);
  EEPROM.write(address + 1, one);
}

//This function will return a 2 byte (16bit) int from the eeprom
//at the specified address to address + 2.
int EEPROMRInt(int address){
  //Read the 4 bytes from the eeprom memory.
  int two = EEPROM.read(address);
  int one = EEPROM.read(address + 1);
  //Return the recomposed int by using bitshift.
  return ((two << 0) & 0xFF) + ((one << 8) & 0xFFFF);
}

//This function will write a 4 byte (32bit) long to the eeprom at the specified address to address + 3.
void EEPROMWLong(int address, long value){
  //Decomposition from a long to 4 bytes by using bitshift.
  //One = Most significant -> Four = Least significant byte
  byte four = (value & 0xFF);
  byte three = ((value >> 8) & 0xFF);
  byte two = ((value >> 16) & 0xFF);
  byte one = ((value >> 24) & 0xFF);
  //Write the 4 bytes into the eeprom memory.
  EEPROM.write(address, four);
  EEPROM.write(address + 1, three);
  EEPROM.write(address + 2, two);
  EEPROM.write(address + 3, one);
}

long EEPROMRLong(long address){
  //Read the 4 bytes from the eeprom memory.
  long four = EEPROM.read(address);
  long three = EEPROM.read(address + 1);
  long two = EEPROM.read(address + 2);
  long one = EEPROM.read(address + 3);
  //Return the recomposed long by using bitshift.
  return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

/*template <class T> int EEPROM_writeAnything(int ee, const T& value){
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EEPROM.write(ee++, *p++);
    return i;
}
template <class T> int EEPROM_readAnything(int ee, T& value){
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    return i;
}*/

//
//BaseElement
void BaseElement::readFromEeprom(int pos){
	uint8_t val = EEPROM.read(pos++);
	if(val == 1){
		this->readSpecificFromEeprom(pos);
	}
}

void BaseElement::saveInEeprom(int pos){
  #if defined(ESP8266) || defined(ESP32)
    EEPROM.put(pos++, this->started);
  #else
	  EEPROM.update(pos++, this->started);
  #endif
	if(this->started){
    #if defined(ESP8266) || defined(ESP32)
      this->saveSpecificPartialInEeprom(pos);
    #else
      this->saveSpecificPartialInEeprom(pos);
    #endif
	}
}

//
//ActuatorAbstract
uint8_t ActuatorAbstract::getKeepValue(){
  return this->keepValue;
}
void ActuatorAbstract::setKeepValue(uint8_t keepValue){
  this->keepValue = keepValue;
}

void ActuatorAbstract::readSpecificFromEeprom(int &pos){
  this->keepValue = EEPROM.read(pos++);
}
void ActuatorAbstract::saveSpecificPartialInEeprom(int &pos){
  #if defined(ESP8266) || defined(ESP32)
    EEPROM.put(pos++, this->keepValue);
  #else
	  EEPROM.update(pos++, this->keepValue);
  #endif
}
