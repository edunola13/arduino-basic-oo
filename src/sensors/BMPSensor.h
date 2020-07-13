#ifndef BMPSensor_h
#define BMPSensor_h
//#include "WConstants.h"
#include <Arduino.h>
#include <ComponentAbstract.h>
#include <Adafruit_BMP085.h>

class BMPSensor: public SensorInterface{
  protected:
    int altitude;
    float temp;
    int32_t pressure;

  public:
    /*DBMP180 = 0, */
	  uint8_t type;
    Adafruit_BMP085 bmp;

    BMPSensor(int altitude=0, uint8_t type=0);
    void begin(int altitude=0, uint8_t type=0);
    void stop();

	  uint8_t getCode();

    int getAltitude();
    void setAltitude(int altitude);
    int32_t getPressurePa();
    int32_t getPressureHPa();
    float getTemperatura();

    //SensorInterface
  	void updateSensor();
  	int getLevel(uint8_t type=0);

  	//EEPROM
  	uint8_t positions();
    void readSpecificFromEeprom(int &pos);
    void saveSpecificPartialInEeprom(int &pos);
};

#endif
