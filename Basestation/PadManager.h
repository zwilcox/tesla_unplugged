#include <Arduino.h>
#include <SoftADJDS311.h>

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
  void getColorString( tPadID pad, char * colorStr );
};