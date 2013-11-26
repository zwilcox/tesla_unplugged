#include "PacketProcessor.h"
#include <Arduino.h>
#include "PadManager.h"
#include "SerialCommandPacketizer.h"
#include "Utilities.h"
#include "ChargeManager.h"
//forward declare local scope function
static void colorToString(RGBC color , char * colorStr );
static bool stringToColor(char * colorStr, RGBC &color);

  
namespace PacketProcessor
{

  void commandGetColor( char * pkt)
  {
    char pID[4]; 
    pID[3] = '\0';
    strncpy(pID,pkt,3);
    char colorStr[22];
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
    
    colorToString( color, &colorStr[3] );
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
    voltageStr[8] = 'V';
    voltageStr[9] = ' ';
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
    currentStr[9] = ' ';
    currentStr[8] = 'A';
    SerialCommandPacketizer::sendOutboundPacket( SerialCommandPacketizer::SendCurrent, currentStr );
    
  }
  
  void commandClearList( char * pkt )
  {
    ChargeManager::ClearAuthorizedCarList();
  }
  
  void commandInfoCar( char * pkt )
  {
    //get the pad ID
    char pID[4]; //for "P# \0"
    pID[3] = '\0';
    strncpy(pID,pkt,3);  //read pkt[0-2], now on &pkt[3]
    PadManager::tPadID pad;
    if( strcmp( pID, "P1 " ) == 0)
    {
      pad = PadManager::Pad1;
    }
    else if( strcmp( pID, "P2 " ) == 0)
    {
      pad = PadManager::Pad2;
    }
    else if( strcmp( pID, "P3 " ) == 0)
    {
      pad = PadManager::Pad3;
    }
    else
    {
      //silently ignore or send error packet
                      Serial.println("error during pID read");
      return;
    }

    //get the vehicle ID
    char vIDStr[6]; //"#### \0"
    vIDStr[5] = 0;
    uint16_t vID = 0;
    strncpy(vIDStr,&pkt[3],5); //read pkt[3-7], now on pkt[8]
    if(sscanf(vIDStr, "%x" , &vID) != 1 || vIDStr[4] != ' ')
    {
      //silently ignore or send error packet
                Serial.println("error during vID read");
      return;
    }
    
    //get the color.
    RGBC color;
    char colorStr[19]; //"R#### G#### B#### \0"
    colorStr[18] = 0;
    strncpy(colorStr,&pkt[8],18); //read pkt[8-25], now done.
    if(!stringToColor(colorStr,color))
    {
      //silently ignore or send error packet.
          Serial.println("error during color read");
      return;
    }
    
    char parsedColorStr[19];
    parsedColorStr[18] = 0;
    
    colorToString(color,parsedColorStr);
    Serial.print("Read color str: ");
    Serial.println(parsedColorStr);
 
    ChargeManager::NotifyOfNewCarInfo(vID,pad,color);
  }
}


bool stringToColor(char * colorStr, RGBC &color)
{
  //read red;
  char redStr[7];
  redStr[6] = 0;
  uint16_t red;
  strncpy(redStr,colorStr,6); //read  colorstr[0-5], now on colorstr[6]
  if (redStr[0] != 'R' || redStr[5] != ' ')
  {
    //error!
    return false;
  }
  red = atoi(&redStr[1]);
  if ( red == 0 && strcmp( &redStr[1], "0000 " ) != 0 )
  {
    //error!
    return false;
  }
  
  //read green;
  char greenStr[7];
  greenStr[6] = 0;
  uint16_t green;
  strncpy(greenStr,&colorStr[6],6); //read  colorstr[6-11], now on colorstr[12]
  if (greenStr[0] != 'G' || greenStr[5] != ' ')
  {
    //error!
    return false;
  }
  green = atoi(&greenStr[1]);
  if ( green == 0 && strcmp( &greenStr[1], "0000 " ) != 0 )
  {
    //error!
    return false;
  }
  
  //read blue;
  char blueStr[7];
  blueStr[6] = 0;
  uint16_t blue;
  strncpy(blueStr,&colorStr[12],6); //read  colorstr[12-18], done
  if (blueStr[0] != 'B' || blueStr[5] != ' ')
  {
    //error!
    return false;
  }
  blue = atoi(&blueStr[1]);
  if ( blue == 0 && strcmp( &blueStr[1], "0000 " ) != 0 )
  {
    //error!
    return false;
  }
  
  color.red = red;
  color.green = green;
  color.blue = blue;
  color.clear = 0;
  
  return true;
}

/**
 * Creates the color string for the color sensor reading.
 * ALERT: colorStr MUST BE size 19 or larger or BAD BAD things will happen.
 **/
void colorToString(RGBC color, char * colorStr )
{
  sprintf(colorStr,"R%04d G%04d B%04d ", color.red, color.blue, color.green);
}