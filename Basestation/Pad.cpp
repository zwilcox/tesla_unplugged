#include <Arduino.h>
#include "Pad.h"


ChargePad::ChargePad( 
                  uint8_t pinColorSensorSDA, 
                  uint8_t pinColorSensorSCL, 
                  uint8_t pinColorSensorLED,
                  uint8_t pinChargeEnable,
                  uint8_t pinCurrentSense,
                  uint8_t pinVoltageSense,
                  uint32_t voltageSenseResistanceR1,
                  uint32_t voltageSenseResistanceR2
                    ) : 
                  _pinPadEnable(pinChargeEnable)
{
  colorSensor = new SoftADJDS311(pinColorSensorLED,pinColorSensorSDA,pinColorSensorSCL);
  voltageSensor = new voltage_reader(pinVoltageSense,voltageSenseResistanceR1,voltageSenseResistanceR2);
  currentSensor = new ACS712(pinCurrentSense);
  pinMode(_pinPadEnable, OUTPUT);
  digitalWrite(_pinPadEnable, LOW );
  padState = false;
  ledState = false;
}


void ChargePad::calibrateColorSensor( void )
{
  colorSensor->init();
  colorSensor->ledOn();
  colorSensor->calibrate();
  //colorSensor->calibrate();
  (ledState) ? colorSensor->ledOn() : colorSensor->ledOff();
}

void ChargePad::setColorSensorLED( bool trueForOn )
{
  (trueForOn) ? colorSensor->ledOn() : colorSensor->ledOff();
  ledState = trueForOn;
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

float ChargePad::getPadVoltage( )
{
  return voltageSensor->get_voltage(10);
}

float ChargePad::getPadCurrent( )
{
  return currentSensor->get_current(10);
}

RGBC ChargePad::readColorSensor( void )
{
  return colorSensor->read();
}

