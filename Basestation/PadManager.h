#pragma once

#include <Arduino.h>
#include <SoftADJDS311.h>

/**
 * Pad manager manages instances of all chargepad drivers. 
 * Control of charge pads should be done through access functions of pad manager.
 * This ensures that there is only one driver instance created for each pad.
 */
namespace PadManager
{

  typedef enum 
  { 
    Pad1 = 1,
    Pad2 = 2,
    Pad3 = 3
  } tPadID;

  void Initialize();
  RGBC readColorSensor( tPadID pad );
  void calibrateSensor( tPadID pad );
  void setLEDState( tPadID pad, bool trueForOn );
  void setPadState( tPadID pad, bool trueForOn );
  float getPadVoltage ( tPadID pad );
  float getPadCurrent ( tPadID pad );
  void setStrToPadID(tPadID pad, char * str );
  void updateAmbientReading (tPadID pad);
  RGBC getAmbientColor(tPadID pad);
};

