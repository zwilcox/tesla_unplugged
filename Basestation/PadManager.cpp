#include <Arduino.h>
#include "PadManager.h"
#include "Pad.h"

#define SENSORLED1	23
#define SENSORLED2	24 
#define SENSORLED3	25
#define SDA1 		26
#define SCL1 		27
#define SDA2 		28
#define SCL2 		29
#define SDA3 		30
#define SCL3 		31

static ChargePad * pad1;
static ChargePad * pad2;
static ChargePad * pad3;

//todo: Make generic for n pads.


namespace PadManager
{
  void Initialize()
  {
    pad1 = new ChargePad(SDA1,SCL1,SENSORLED1);
    pad2 = new ChargePad(SDA2,SCL2,SENSORLED2);
    pad3 = new ChargePad(SDA3,SCL3,SENSORLED3);
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
  
  void setLEDState( tPadID sensor, bool trueForOn )
  {
    switch(sensor)
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
  
  
  /**
   * Creates the color string for the specified pad..
   * ALERT: colorStr MUST BE size 21 or larger or BAD BAD things will happen.
   **/
  void getColorString( tPadID pad, char * colorStr )
  {      
    switch(pad)
    {
      case Pad1:
        strncpy(colorStr,"P1 ",3);                  //set the first part of str to padID, 
        pad1->colorSensorToString( &colorStr[3] );  //then get rest of color str from pad itself.
        return;
      case Pad2:
        strncpy(colorStr,"P2 ",3);
        pad2->colorSensorToString( &colorStr[3] );
        return;
      case Pad3:
        strncpy(colorStr,"P3 ",3);
        pad3->colorSensorToString( &colorStr[3] );
        return;
    }
  }
  
};
