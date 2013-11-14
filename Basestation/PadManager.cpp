#include <Arduino.h>
#include "PadManager.h"
#include "Pad.h"

//pad1 pins
#define CHARGEPADENABLE1 48
#define SENSORLED1	23
#define SDA1 		26
#define SCL1 		27

//pad2 pins
#define CHARGEPADENABLE2 50
#define SENSORLED2	24 
#define SDA2 		28
#define SCL2 		29

//pad3 pins
#define CHARGEPADENABLE3 52
#define SENSORLED3	25
#define SDA3 		30
#define SCL3 		31

//file scope variables; 'singleton' class instances.
static ChargePad * pad1;
static ChargePad * pad2;
static ChargePad * pad3;


namespace PadManager
{
  void Initialize()
  {
    pad1 = new ChargePad(SDA1,SCL1,SENSORLED1,CHARGEPADENABLE1);
    pad2 = new ChargePad(SDA2,SCL2,SENSORLED2,CHARGEPADENABLE2);
    pad3 = new ChargePad(SDA3,SCL3,SENSORLED3,CHARGEPADENABLE3);
  }

  RGBC readColorSensor( tPadID pad )
  {
    switch(pad)
    {
      case Pad1:
        return pad1->readColorSensor();
      case Pad2:
        return pad2->readColorSensor();
      case Pad3:
        return pad3->readColorSensor();
    }
  }

  void calibrateSensor( tPadID pad )
  {
    switch(pad)
    {
      case Pad1:
        pad1->calibrateColorSensor();
        return;
      case Pad2:
        pad2->calibrateColorSensor();
        return;
      case Pad3:
        pad3->calibrateColorSensor();
        return;
    }
  }
  
  void setLEDState( tPadID pad, bool trueForOn )
  {
    switch(pad)
    {
      case Pad1:
        pad1->setColorSensorLED( trueForOn );
        return;
      case Pad2:
        pad2->setColorSensorLED( trueForOn );
        return;
      case Pad3:
        pad3->setColorSensorLED( trueForOn );
        return;
    }
  }
  
  void setPadState( tPadID pad, bool trueForOn )
  {
    switch(pad)
    {
      case Pad1:
        pad1->setPadState( trueForOn );
        return;
      case Pad2:
        pad2->setPadState( trueForOn );
        return;
      case Pad3:
        pad3->setPadState( trueForOn );
        return;
    }
  }

};
