#ifndef DigitalControl_h
#define DigitalControl_h
//#include "WConstants.h"
#include <Arduino.h>
#include <ComponentAbstract.h>

class DigitalControl: public ActuatorAbstract {
  protected:
    uint8_t pinD, state;

  public:
	   //1 = Digital, 2 = PWM
    uint8_t type = 1;

    DigitalControl();
    DigitalControl(uint8_t pinD, uint8_t type=1);
    void begin();
    void begin(uint8_t pinD, uint8_t type=1);
    void stop();

	  uint8_t getCode();

    void set(uint8_t value);

    uint8_t getPinD();
    void setPinD(uint8_t pinD);
    uint8_t getState();

	  //EEPROM
	  uint8_t positions();
    void readSpecificFromEeprom(int &pos);
    void saveSpecificPartialInEeprom(int &pos);
};

#endif
