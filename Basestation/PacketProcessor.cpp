#include "PacketProcessor.h"
#include <Arduino.h>
#include "PadManager.h"
#include "SerialCommandPacketizer.h"
#include "Utilities.h"

//forward declare local scope function
static void colorSensorToString(RGBC color , char * colorStr );
  
namespace PacketProcessor
{

  void commandGetColor( char * pkt)
  {
    char pID[4]; 
    pID[3] = '\0';
    strncpy(pID,pkt,3);
    char colorStr[21];
    RGBC color;
    strncpy(colorStr,pID,3);  
    
    if( strcmp( pID, "P1 " ) == 0)
    {
      color = PadManager::readColorSensor( PadManager::Pad1 );
    }
    else if( strcmp( pID, "P2 " ) == 0)
    {
      color = PadManager::readColorSensor( PadManager::Pad2);
    }
    else if( strcmp( pID, "P3 " ) == 0)
    {
      color = PadManager::readColorSensor( PadManager::Pad3 );
    }
    else
    {
      //silently ignore OR return error packet???
      return;
    }
    
    colorSensorToString( color, &colorStr[3] );
    SerialCommandPacketizer::sendOutboundPacket( SerialCommandPacketizer::SendColor, colorStr );
  }

  void commandCalColor( char * pkt)
  {
    char cmd[4];
    cmd[3] = '\0';
    strncpy(cmd,pkt,3);
    
    if( strcmp( cmd, "P1 " ) == 0)
    {
      PadManager::setLEDState( PadManager::Pad1, true );  
      PadManager::calibrateSensor( PadManager::Pad1 );
      PadManager::setLEDState( PadManager::Pad1, false );  
    }
    
    else if( strcmp( cmd, "P2 " ) == 0)
    {
      PadManager::setLEDState( PadManager::Pad2, true );  
      PadManager::calibrateSensor( PadManager::Pad2 );
      PadManager::setLEDState( PadManager::Pad2, false );  
    }
    
    else if( strcmp( cmd, "P3 " ) == 0)
    {
      PadManager::setLEDState( PadManager::Pad3, true );  
      PadManager::calibrateSensor( PadManager::Pad3 );
      PadManager::setLEDState( PadManager::Pad3, false );  
    }
    
  }

  void commandToggleLED( char * pkt)
  {
    char pID[4];
    pID[3] = '\0';
    strncpy(pID,pkt,3);
    
    bool turnLEDon = false;
    char onOff[3];
    onOff[2] = '\0';
    strncpy(onOff,&pkt[3],2);
    
    if( strcmp (onOff, "1 ") == 0)
    {
      turnLEDon = true;
    }
    else if( strcmp (onOff, "0 ") == 0)
    {
      turnLEDon = false;
    }
    else
    {
      //ignore silently, or send error packet.
      return;
    }
    
    if( strcmp( pID, "P1 " ) == 0)
    {
      PadManager::setLEDState( PadManager::Pad1, turnLEDon );
    }
    
    else if( strcmp( pID, "P2 " ) == 0)
    {
      PadManager::setLEDState( PadManager::Pad2, turnLEDon );
    }
    
    else if( strcmp( pID, "P3 " ) == 0)
    {
      PadManager::setLEDState( PadManager::Pad3, turnLEDon );
    }
    else
    {
      //ignore silently or send error packet
      return;
    }
    
  }
  
  void commandTogglePad(char * pkt )
  {
    char pID[4];
    pID[3] = '\0';
    strncpy(pID,pkt,3);
    
    bool turnPadOn = false;
    char onOff[3];
    onOff[2] = '\0';
    strncpy(onOff,&pkt[3],2);
    
    if( strcmp (onOff, "1 ") == 0)
    {
      turnPadOn = true;
    }
    else if( strcmp (onOff, "0 ") == 0)
    {
      turnPadOn = false;
    }
    else
    {
      //ignore silently, or send error packet.
      return;
    }
    
    if( strcmp( pID, "P1 " ) == 0)
    {
      PadManager::setPadState( PadManager::Pad1, turnPadOn );
    }
    
    else if( strcmp( pID, "P2 " ) == 0)
    {
      PadManager::setPadState( PadManager::Pad2, turnPadOn );
    }
    
    else if( strcmp( pID, "P3 " ) == 0)
    {
      PadManager::setPadState( PadManager::Pad3, turnPadOn );
    }
    else
    {
      //ignore silently or send error packet
      return;
    }
  }
  
  void commandGetVoltage( char * pkt)
  {
    char pID[4];
    pID[3] = '\0';
    strncpy(pID,pkt,3);
    float voltage = 0.0f;
    char voltageStr[11];
    voltageStr[10] = '\0';
    strncpy(voltageStr,pID,3);
    
    if( strcmp( pID, "P1 " ) == 0)
    {
      voltage = PadManager::getPadVoltage( PadManager::Pad1 );
    }
    
    else if( strcmp( pID, "P2 " ) == 0)
    {
      voltage = PadManager::getPadVoltage( PadManager::Pad2 );
    }
    
    else if( strcmp( pID, "P3 " ) == 0)
    {
      voltage = PadManager::getPadVoltage( PadManager::Pad3 );
    }
    
    else
    {
      //silently ignore or send error packet
      return;
    }

    Utilities::floatToStr(voltage,&voltageStr[3]);
    voltageStr[9] = 'V';
    SerialCommandPacketizer::sendOutboundPacket( SerialCommandPacketizer::SendVoltage, voltageStr );
    
  }
  
  void commandGetCurrent( char * pkt)
  {
    char pID[4];
    pID[3] = '\0';
    strncpy(pID,pkt,3);
    float current = 0.0f;
    char currentStr[11];
    currentStr[10] = '\0';
    strncpy(currentStr,pID,3);
    
    if( strcmp( pID, "P1 " ) == 0)
    {
      current = PadManager::getPadCurrent( PadManager::Pad1 );
    }
    
    else if( strcmp( pID, "P2 " ) == 0)
    {
      current = PadManager::getPadCurrent( PadManager::Pad2 );
    }
    
    else if( strcmp( pID, "P3 " ) == 0)
    {
      current = PadManager::getPadCurrent( PadManager::Pad3 );
    }
    
    else
    {
      //silently ignore or send error packet
      return;
    }
    
    Utilities::floatToStr(current,&currentStr[3]);
    currentStr[9] = 'A';
    SerialCommandPacketizer::sendOutboundPacket( SerialCommandPacketizer::SendCurrent, currentStr );
    
  }
}



/**
 * Creates the color string for the color sensor reading.
 * ALERT: colorStr MUST BE size 18 or larger or BAD BAD things will happen.
 **/
void colorSensorToString(RGBC color, char * colorStr )
{
  sprintf(colorStr,"R%04d G%04d B%04d", color.red, color.blue, color.green);
}