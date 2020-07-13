#include <ComponentAbstract.h>
#include <JsonHelper.h>

#include <sensors/AnalogSensor.h>
#include <sensors/DigitalSensor.h>
#include <sensors/DistanceHCSR04.h>
#include <sensors/HumTempDHT.h>
#include <sensors/TempBase.h>
#include <sensors/BMPSensor.h>

#include <actuators/DigitalControl.h>
#include <actuators/Relay.h>

AnalogSensor sen1(0);
DigitalSensor dig(2);
DistanceHCSR04 dis(3, 4);
HumTempDHT sen(5, 11);
TempBase tmp(2, 1);
BMPSensor bmp(25, 0);

DigitalControl digC(3,1);
Relay rel(3);

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
