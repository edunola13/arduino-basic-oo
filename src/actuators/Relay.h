#ifndef Relay_h
#define Relay_h
//#include "WConstants.h"
#include <Arduino.h>
#include <actuators/DigitalControl.h>

class Relay: public DigitalControl {
  protected:
    bool invert = false;

  public:
    Relay(uint8_t pin, bool invert = false);
	  void begin(uint8_t pin, bool invert = false);
    void stop();

    uint8_t getCode();
    bool getInvert();
    void setInvert(bool invert);

    bool isOpen();
    void commonlyOpen();
    void commonlyClose();
    void changeStatus();

    //EEPROM
	  uint8_t positions();
    void readSpecificFromEeprom(int &pos);
    void saveSpecificPartialInEeprom(int &pos);
};

#endif
