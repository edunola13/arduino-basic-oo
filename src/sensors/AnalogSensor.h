#ifndef AnalogSensor_h
#define AnalogSensor_h
//#include "WConstants.h"
#include <Arduino.h>
#include <ComponentAbstract.h>

//PhotoResistance
//FlameSensor
//WaterLevelSensor
class AnalogSensor: public SensorInterface{
  protected:
    uint8_t pinA;
	  uint8_t	pinD = -1;
    int in;

  public:
	  uint8_t type = 0;

	  AnalogSensor();
    AnalogSensor(uint8_t pinA);
	  AnalogSensor(uint8_t pinA, uint8_t pinD, uint8_t type=0);
	  void begin();
	  void begin(uint8_t pinA);
	  void begin(uint8_t pinA, uint8_t pinD, uint8_t type=0);
	  void stop();

	  uint8_t getCode();

	  bool getStarted();
	  uint8_t getPinA();
	  void setPinA(uint8_t pinA);
	  uint8_t getPinD();
	  void setPinD(uint8_t pinD);
    int getIn();

	  //SensorInterface
	  void updateSensor();
	  int getLevel(uint8_t type=0);

	  //JsonInterface
	  // virtual void jsonProperties(String &value);
    // virtual void parseJson(String* json);

	  //EEPROM
	  uint8_t positions();
    void readSpecificFromEeprom(int &pos);
    void saveSpecificPartialInEeprom(int &pos);
};


class RainSensor: public AnalogSensor {
  public:
    RainSensor();
    RainSensor(uint8_t pinA);
	  RainSensor(uint8_t pinA, uint8_t pinD, uint8_t type=0);

    int getLevel(uint8_t type=0);
};

class LdrsSensor: public AnalogSensor {
  public:
    LdrsSensor();
    LdrsSensor(uint8_t pinA);
	  LdrsSensor(uint8_t pinA, uint8_t pinD, uint8_t type=0);

    int getLevel(uint8_t type=0);
};

class MQSensor: public AnalogSensor {
  public:
    MQSensor();
    MQSensor(uint8_t pinA);
	  MQSensor(uint8_t pinA, uint8_t pinD, uint8_t type=0);

    int getLevel(uint8_t type=0);
};

#endif
