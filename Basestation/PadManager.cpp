#include <Arduino.h>
#include "PadManager.h"
#include "Pad.h"

//pad1 pins
#define CHARGEPADENABLE1  48
#define SENSORLED1	      23
#define SDA1 		          26
#define SCL1 		          27
#define VOLTAGESENSOR1    A8 
#define CURRENTSENSOR1    A9

#define R1_PAD1           5850000
#define R2_PAD1           1625000

//pad2 pins
#define CHARGEPADENABLE2  50
#define SENSORLED2	      24 
#define SDA2 		          28
#define SCL2 		          29
#define VOLTAGESENSOR2    A10
#define CURRENTSENSOR2    A11

#define R1_PAD2           5850000
#define R2_PAD2           1373000

//pad3 pins
#define CHARGEPADENABLE3  52
#define SENSORLED3	      25
#define SDA3 		          30
#define SCL3 		          31
#define VOLTAGESENSOR3    A12
#define CURRENTSENSOR3    A13

#define R1_PAD3           5820000
#define R2_PAD3           1473000
//file scope variables; 'singleton' class instances.
static ChargePad * pad1;
static ChargePad * pad2;
static ChargePad * pad3;


namespace PadManager
{
  void Initialize()
  {
    pad1 = new ChargePad(SDA1,SCL1,SENSORLED1,
                        CHARGEPADENABLE1,
                        CURRENTSENSOR1,
                        VOLTAGESENSOR1,R1_PAD1,R2_PAD1);
                        
    pad2 = new ChargePad(SDA2,SCL2,SENSORLED2,
                        CHARGEPADENABLE2,
                        CURRENTSENSOR2,
                        VOLTAGESENSOR2,R1_PAD2,R2_PAD2);
                        
    pad3 = new ChargePad(SDA3,SCL3,SENSORLED3,
                        CHARGEPADENABLE3,
                        CURRENTSENSOR3,
                        VOLTAGESENSOR3,R1_PAD3,R2_PAD3);
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
  
  float getPadCurrent( tPadID pad )
  {
    switch(pad)
    {
      case Pad1:
        return pad1->getPadCurrent();
      case Pad2:
        return pad2->getPadCurrent();
      case Pad3:
        return pad3->getPadCurrent();
    }
  }
  
  float getPadVoltage( tPadID pad )
  {
    switch(pad)
    {
      case Pad1:
        return pad1->getPadVoltage();
      case Pad2:
        return pad2->getPadVoltage();
      case Pad3:
        return pad3->getPadVoltage();
    }
  }

};
