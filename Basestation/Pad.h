#pragma once

#include <Arduino.h>
#include <SoftADJDS311.h>
#include <voltage_reader.h>
#include <ACS712.h>

class ChargePad
{
  public:
    ChargePad( uint8_t pinColorSensorSDA, 
                      uint8_t pinColorSensorSCL, 
                      uint8_t pinColorSensorLED,
                      uint8_t pinChargeEnable,
                      uint8_t pinCurrentSense,
                      uint8_t pinVoltageSense,
                      uint16_t voltageSenseResistanceR1,
                      uint16_t voltageSenseResistanceR2);
    
    
    void calibrateColorSensor( void );
    void setColorSensorLED( bool trueForOn );
    RGBC readColorSensor( void );
    
    void setPadState( bool trueForOn );
    bool getPadState( void );
    
    float getPadVoltage( );
    float getPadCurrent( );

  
  private:
    uint8_t 			  _pinPadEnable;
      
    SoftADJDS311 	  * colorSensor;
    bool 				      padState;
    voltage_reader 	*	voltageSensor;
    ACS712			    *	currentSensor;
};