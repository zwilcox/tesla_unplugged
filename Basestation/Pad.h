#include <Arduino.h>
#include <SoftADJDS311.h>

class ChargePad
{
  public:
    ChargePad( uint8_t pinColorSensorSDA, 
                      uint8_t pinColorSensorSCL, 
                      uint8_t pinColorSensorLED );
    
    
    void calibrateColorSensor( void );
    void setColorSensorLED( bool trueForOn );

    void setPadState( bool trueForOn );
    bool getPadState( void );
    
    uint16_t getPadVoltage( );
    uint16_t getPadCurrent( );
    
    void padVoltagetToString( char * str );
    void padCurrentToString( char * str );
    void colorSensorToString( char * str );
    
    RGBC readColorSensor( void );
  
  private:
    SoftADJDS311 * colorSensor;

};

