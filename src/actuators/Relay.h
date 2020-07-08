#ifndef Relay_h
#define Relay_h
//#include "WConstants.h"
#include <Arduino.h>
#include <actuators/DigitalControl.h>

class Relay: public DigitalControl {
  public:
    Relay(uint8_t pin);
	  void begin(uint8_t pin);
    void stop();

    uint8_t getCode();

    void commonlyOpen();
    void commonlyClose();
    void changeStatus();
};

#endif
