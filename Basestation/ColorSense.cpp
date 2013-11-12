#include <Arduino.h>
#include "ColorSense.h"

#define SENSORLED1	23
#define SENSORLED2	24 
#define SENSORLED3	25
#define SDA1 		26
#define SCL1 		27
#define SDA2 		28
#define SCL2 		29
#define SDA3 		30
#define SCL3 		31

static SoftADJDS311 * colorSensor1;
static SoftADJDS311 * colorSensor2;
static SoftADJDS311 * colorSensor3;

namespace ColorSense
{
  void Initialize()
  {
    colorSensor1 = new SoftADJDS311(SENSORLED1,SDA1,SCL1);
    colorSensor2 = new SoftADJDS311(SENSORLED2,SDA2,SCL2);
    colorSensor3 = new SoftADJDS311(SENSORLED3,SDA3,SCL3);
  }

  RGBC readSensor( tSensorID sensor )
  {
    switch(sensor)
    {
      case Sensor1:
        return colorSensor1->read();
      case Sensor2:
        return colorSensor2->read();
      case Sensor3:
        return colorSensor3->read();
    }
  }

  void calibrateSensor( tSensorID sensor )
  {
    switch(sensor)
    {
      case Sensor1:
        colorSensor1->calibrate();
        return;
      case Sensor2:
        colorSensor2->calibrate();
        return;
      case Sensor3:
        colorSensor3->calibrate();
        return;
    }
  }
  
  void setLEDState( tSensorID sensor, bool trueForOn )
  {
    switch(sensor)
    {
      case Sensor1:
        (trueForOn) ? colorSensor1->ledOn() : colorSensor1->ledOff() ; 
        return;
      case Sensor2:
        (trueForOn) ? colorSensor2->ledOn() : colorSensor2->ledOff() ;
        return;
      case Sensor3:
        (trueForOn) ? colorSensor3->ledOn() : colorSensor3->ledOff() ;
        return;
    }
  }
  
  
  /**
   * Creates the color string for the specified sensor.
   * ALERT: colorStr MUST BE size 18 or larger or BAD BAD things will happen.
   **/
  void getColorString( tSensorID sensor, char * colorStr )
  {      
    RGBC color = readSensor(sensor);
    sprintf(colorStr,"R%04d G%04d B%04d", color.red, color.blue, color.green);
  }
  
};
