#include <Arduino.h>
#include "PadManager.h"
#include "Pad.h"
#include "PacketProcessor.h"
#define AMBIENTTOLERANCE 225

//pad1 pins
#define CHARGEPADENABLE1  48
#define SENSORLED1        23
#define SDA1              26
#define SCL1              27
#define VOLTAGESENSOR1    A8 
#define CURRENTSENSOR1    A9
//voltage sense resistance
#define R1_PAD1           5850000
#define R2_PAD1           1625000

//pad2 pins
#define CHARGEPADENABLE2  50
#define SENSORLED2        24 
#define SDA2               28
#define SCL2               29
#define VOLTAGESENSOR2    A10
#define CURRENTSENSOR2    A11
//voltage sense resistance
#define R1_PAD2           11
#define R2_PAD2           2

//pad3 pins
#define CHARGEPADENABLE3  52
#define SENSORLED3        25
#define SDA3               30
#define SCL3               31
#define VOLTAGESENSOR3    A12
#define CURRENTSENSOR3    A13
//voltage sense resistance
#define R1_PAD3           11
#define R2_PAD3           2	

//file scope variables; 'singleton' class instances.
static ChargePad * pad1;
static ChargePad * pad2;
static ChargePad * pad3;

static RGBC P1Ambient;
static RGBC P2Ambient;
static RGBC P3Ambient;

namespace PadManager
{
  void Initialize()
  {
    //create new pad driver instances.
    pad1 = new ChargePad(SDA1,SCL1,SENSORLED1,           //color sensor pins
                        CHARGEPADENABLE1,                //charge pad enable pin
                        CURRENTSENSOR1,                  //current sense pin
                        VOLTAGESENSOR1,R1_PAD1,R2_PAD1); //voltage sense pins
                        
    pad2 = new ChargePad(SDA2,SCL2,SENSORLED2,
                        CHARGEPADENABLE2,
                        CURRENTSENSOR2,
                        VOLTAGESENSOR2,R1_PAD2,R2_PAD2);
                        
    pad3 = new ChargePad(SDA3,SCL3,SENSORLED3,            
                        CHARGEPADENABLE3,                 
                        CURRENTSENSOR3,                   
                        VOLTAGESENSOR3,R1_PAD3,R2_PAD3);  
  }

  /**
   * Reads the color value of the sensor on the given pad.
   */
  RGBC readColorSensor( tPadID pad )
  {
    switch(pad)
    {
      case Pad1:
        return pad1->readColorSensor();
      case Pad2:
        return pad2->readColorSensor();
      case Pad3:
        return pad3->readColorSensor();
    }
  }

  /**
   * Runs the sensor calibration method for the given pad.
   */
  void calibrateSensor( tPadID pad )
  {
    switch(pad)
    {
      case Pad1:
        pad1->calibrateColorSensor();
        do{
          P1Ambient = pad1->readColorSensor();
        }while (P1Ambient.red + P1Ambient.green + P1Ambient.blue < 100);//block while the box is still on the sensor,
        delay(1500);                                                    //then wait a few sec for shadow of hand to move
        P1Ambient = pad1->readColorSensor();                            //then take ambient light reading.
        return;
      case Pad2:
        pad2->calibrateColorSensor();
        do{
          P2Ambient = pad2->readColorSensor();
        }while (P2Ambient.red + P2Ambient.green + P2Ambient.blue < 100);//block while the box is still on the sensor,
        delay(1500);                                                    //then wait a few sec for shadow of hand to move
        P2Ambient = pad2->readColorSensor();                            //then take ambient light reading.
        return;
      case Pad3:
        pad3->calibrateColorSensor();
        do{
          P3Ambient = pad3->readColorSensor();
        }while (P3Ambient.red + P3Ambient.green + P3Ambient.blue < 100);//block while the box is still on the sensor,
        delay(1500);                                                    //then wait a few sec for shadow of hand to move
        P3Ambient = pad3->readColorSensor();                            //then take ambient light reading.
        return;
    }
  }
  
  /**
   * Turns the color sensor LED on or off on the given pad.
   */
  void setLEDState( tPadID pad, bool trueForOn )
  {
    switch(pad)
    {
      case Pad1:
        pad1->setColorSensorLED( trueForOn );
        return;
      case Pad2:
        pad2->setColorSensorLED( trueForOn );
        return;
      case Pad3:
        pad3->setColorSensorLED( trueForOn );
        return;
    }
  }
  
  /**
   * Turns the given charge pad inductive circuit on or off.
   */
  void setPadState( tPadID pad, bool trueForOn )
  {
    switch(pad)
    {
      case Pad1:
        pad1->setPadState( trueForOn );
        return;
      case Pad2:
        pad2->setPadState( trueForOn );
        return;
      case Pad3:
        pad3->setPadState( trueForOn );
        return;
    }
  }
  
  /**
   * Reads the current from the given charge pad.
   */
  float getPadCurrent( tPadID pad )
  {
    switch(pad)
    {
      case Pad1:
        return pad1->getPadCurrent();
      case Pad2:
        return pad2->getPadCurrent();
      case Pad3:
        return pad3->getPadCurrent();
    }
  }
  
  /**
   * Reads the voltage from the given charge pad.
   */
  float getPadVoltage( tPadID pad )
  {
    switch(pad)
    {
      case Pad1:
        return pad1->getPadVoltage();
      case Pad2:
        return pad2->getPadVoltage();
      case Pad3:
        return pad3->getPadVoltage();
    }
  }

  void setStrToPadID( tPadID pad , char * str )
  {
    switch(pad)
    {
      case Pad1:
        strcpy(str,"P1 ");
        return;
      case Pad2:
        strcpy(str,"P2 ");
        return;
      case Pad3:
        strcpy(str,"P3 ");
        return;
    }
  }
  
  void updateAmbientReading (tPadID pad)
  {
    switch(pad)
    {
      case Pad1:
        P1Ambient = pad1->readColorSensor();
        return;
      case Pad2:
        P2Ambient = pad2->readColorSensor();
        return;
      case Pad3:
        P3Ambient = pad3->readColorSensor();
        return;
    }
  }
  
  bool isColorAmbient(tPadID pad, RGBC color)
  { 
    RGBC ambient;
    switch(pad)
    {
      case Pad1:
        ambient = P1Ambient;
        break;
      case Pad2:
        ambient = P2Ambient;
        break;
      case Pad3:
        ambient = P3Ambient;
        break;
    }
    
    if(     color.red - ambient.red     < AMBIENTTOLERANCE 
        &&  ambient.red - color.red     < AMBIENTTOLERANCE 
        &&  color.green - ambient.green < AMBIENTTOLERANCE 
        &&  ambient.green - color.green < AMBIENTTOLERANCE
        &&  color.blue - ambient.blue   < AMBIENTTOLERANCE 
        && ambient.blue - color.blue    < AMBIENTTOLERANCE )
    {
      return true;
      Serial.println("color is ambient.");
    }
    else
    {
      return false;
    }
  }
};
