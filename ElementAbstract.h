/*
Morse.h - Library for flashing Morse code.
Created by David A. Mellis, November 2, 2007. Released into the public domain.
*/
#ifndef ElementAbstract_h
#define ElementAbstract_h
//#include "WConstants.h"
#include <Arduino.h>
#include <EEPROM.h>
//#include <JsonHelper.h>
#include "JsonHelper.h"

//UTIL
bool isNotNull(String value);

//EEPROM
//Las funciones de INT guardan y devuelven los mas bien uint16_t, ya que sea hace la transformacion lo mas bien.
//This function will write a 2 byte (16bit) int to the eeprom at the specified address to address + 1.
void EEPROMWInt(int address, int value);
//This function will return a 2 byte (16bit) int from the eeprom
//at the specified address to address + 2.
int EEPROMRInt(int address);
//This function will write a 4 byte (32bit) long to the eeprom at the specified address to address + 3.
void EEPROMWLong(int address, long value);
long EEPROMRLong(long address);
//template <class T> int EEPROM_writeAnything(int ee, const T& value);
//template <class T> int EEPROM_readAnything(int ee, T& value);

class BaseElement: public JsonInterface {
  protected:
	bool started= false;
  public:
	virtual uint8_t getCode();
	bool getStarted(){
	  return this->started;
	}
	
	bool isNotNull(String value){
	  return value != "null" && value != "NULL";
	}
	
	//EEPROM
	void EEPROMWriteInt(int address, int value){
	  EEPROMWInt(address, value);
	}
	int EEPROMReadInt(int address){
      return EEPROMRInt(address);
    }
	void EEPROMWriteLong(int address, long value){
	  EEPROMWLong(address, value);
	}
	long EEPROMReadLong(long address){
	  return EEPROMRLong(address);
	}
	//EEPROM
	virtual uint8_t positions();
	virtual void readFromEeprom(int pos);
	virtual void saveInEeprom(int pos);
};

class SensorInterface: public BaseElement {
  public: 
	virtual void updateSensor();
	virtual int getLevel(uint8_t type=0);
};

#endif
