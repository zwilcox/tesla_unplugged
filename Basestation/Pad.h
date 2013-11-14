#pragma once

#include <Arduino.h>
#include <SoftADJDS311.h>

class ChargePad
{
  public:
    ChargePad( uint8_t pinColorSensorSDA, 
                      uint8_t pinColorSensorSCL, 
                      uint8_t pinColorSensorLED,
                      uint8_t pinChargeEnable );
    
    
    void calibrateColorSensor( void );
    void setColorSensorLED( bool trueForOn );
    RGBC readColorSensor( void );
    
    void setPadState( bool trueForOn );
    bool getPadState( void );
    
    uint16_t getPadVoltage( );
    uint16_t getPadCurrent( );

  
  private:
    SoftADJDS311 * colorSensor;
    bool padState;
    uint8_t _pinPadEnable;
};