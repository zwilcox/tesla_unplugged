#include <Arduino.h>
#include <SoftADJDS311.h>

namespace ColorSense
{
  typedef enum 
  { 
    Sensor1 = 1,
    Sensor2 = 2,
    Sensor3 = 3
  } tSensorID;

  void Initialize();
  RGBC readSensor( tSensorID sensor );
  void calibrateSensor( tSensorID sensor );
  void setLEDState( tSensorID sensor, bool trueForOn );
  void getColorString( tSensorID sensor, char * colorStr );
};