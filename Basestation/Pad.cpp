#include <Arduino.h>
#include "Pad.h"


ChargePad::ChargePad( uint8_t pinColorSensorSDA, 
                  uint8_t pinColorSensorSCL, 
                  uint8_t pinColorSensorLED )
{
  colorSensor = new SoftADJDS311(pinColorSensorLED,pinColorSensorSDA,pinColorSensorSCL);
  
}


void ChargePad::calibrateColorSensor( void )
{
  colorSensor->calibrate();
}

void ChargePad::setColorSensorLED( bool trueForOn )
{
  (trueForOn) ? colorSensor->ledOn() : colorSensor->ledOff();
}

void ChargePad::setPadState( bool trueForOn )
{
  
}

bool ChargePad::getPadState( void )
{

}

uint16_t ChargePad::getPadVoltage( )
{

}

uint16_t ChargePad::getPadCurrent( )
{

}

void ChargePad::padVoltagetToString( char * str )
{

}

void ChargePad::padCurrentToString( char * str )
{

}
  /**
   * Creates the color string for the color sensor reading.
   * ALERT: colorStr MUST BE size 18 or larger or BAD BAD things will happen.
   **/
void ChargePad::colorSensorToString( char * colorStr )
{
  RGBC color = colorSensor->read();
  sprintf(colorStr,"R%04d G%04d B%04d", color.red, color.blue, color.green);
}




RGBC readColorSensor( void )
{

}

