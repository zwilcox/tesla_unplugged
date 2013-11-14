#include <Arduino.h>
#include "Pad.h"


ChargePad::ChargePad( 
                  uint8_t pinColorSensorSDA, 
                  uint8_t pinColorSensorSCL, 
                  uint8_t pinColorSensorLED,
                  uint8_t pinChargeEnable 
                    ) : 
                  _pinPadEnable(pinChargeEnable)
{
  colorSensor = new SoftADJDS311(pinColorSensorLED,pinColorSensorSDA,pinColorSensorSCL);
  pinMode(_pinPadEnable, OUTPUT);
  digitalWrite(_pinPadEnable, LOW );
  padState = false;
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
  digitalWrite(_pinPadEnable, (trueForOn) ? HIGH : LOW );
  padState = trueForOn;
}

bool ChargePad::getPadState( void )
{
  return padState;
}

uint16_t ChargePad::getPadVoltage( )
{

}

uint16_t ChargePad::getPadCurrent( )
{
  
}

RGBC ChargePad::readColorSensor( void )
{
  return colorSensor->read();
}

