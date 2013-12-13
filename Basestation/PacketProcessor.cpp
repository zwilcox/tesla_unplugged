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
  /**
   * This function is for the GC command.
   * Reads a payload of: 'P# '
   * Sends color of given sensor or error message back to PC.
   */
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
      Serial.println("[INVALID_INBOUND_COMMAND]");
      return;
    }
    
    colorToString( color, &colorStr[3] );
    SerialCommandPacketizer::sendOutboundPacket( SerialCommandPacketizer::SendColor, colorStr );
  }

  /**
   * This function is for the CC command.
   * Reads a payload of: 'P# '
   * Calls the appropriate calibration command or sends to PC error message.
   */
  void commandCalColor( char * pkt)
  {
    char cmd[4];
    cmd[3] = '\0';
    strncpy(cmd,pkt,3);
    
    if( strcmp( cmd, "P1 " ) == 0)
    {
      PadManager::calibrateSensor( PadManager::Pad1 );
    }
    
    else if( strcmp( cmd, "P2 " ) == 0)
    {
      PadManager::calibrateSensor( PadManager::Pad2 );
    }
    
    else if( strcmp( cmd, "P3 " ) == 0)
    {
      PadManager::calibrateSensor( PadManager::Pad3 );
    }
    
  }

  /**
   * This function is for the TC command.
   * Reads a payload of: 'P# 1 ' for on or 'P# 0 ' for off.
   * Turns on the LED for the given pad on or off, depending on payload.
   * sends to PC error message if packet incorrect.
   */
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
      Serial.println("[INVALID_INBOUND_COMMAND]");
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
      Serial.println("[INVALID_INBOUND_COMMAND]");
      return;
    }
    
  }
  
  /**
   * This function is for the TP command.
   * Reads a payload of: 'P# 1/0 '
   * Calls the appropriate pad on/off command or sends to PC error message.
   */
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
      Serial.println("[INVALID_INBOUND_COMMAND]");
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
      Serial.println("[INVALID_INBOUND_COMMAND]");
      return;
    }
  }
  
  /**
   * This function is for the GV command.
   * Reads a payload of: 'P# '
   * Reads voltage for given pad and sends to PC the voltage. (or error if pad packet)
   */
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
      Serial.println("[INVALID_INBOUND_COMMAND]");
      return;
    }

    Utilities::floatToStr(voltage,&voltageStr[3]);
    voltageStr[8] = 'V';
    voltageStr[9] = ' ';
    SerialCommandPacketizer::sendOutboundPacket( SerialCommandPacketizer::SendVoltage, voltageStr );
    
  }
  
  /**
   * This function is for the GA command.
   * Reads a payload of: 'P# '
   * Reads the current for the given pad and sends to PC current. (or error if pad packet)
   */
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
      Serial.println("[INVALID_INBOUND_COMMAND]");
      return;
    }
    
    Utilities::floatToStr(current,&currentStr[3]);
    currentStr[9] = ' ';
    currentStr[8] = 'A';
    SerialCommandPacketizer::sendOutboundPacket( SerialCommandPacketizer::SendCurrent, currentStr );
    
  }
  
  /**
   * This function is for the CL command.
   * Reads a payload of: ' '
   * Clears list of all authorized cars and cancels all charge sesions (or error if pad packet)
   */
  void commandClearList( char * pkt )
  {
    ChargeManager::ClearAuthorizedCarList();
  }
  
  /**
   * This function is for the IC command.
   * Reads a payload of: 'P1 2222 R0000 G0000 B0000 '
   * This function reads the pad, vehicle ID, and color, then
   * notifies charge manager of vehicle authorization information.
   * (Or sends error to PC if bad packet format)
   */
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
      Serial.println("[INVALID_INBOUND_COMMAND]");
      return;
    }

    //get the vehicle ID
    char vIDStr[6]; //"#### \0"
    vIDStr[5] = 0;
    uint16_t vID = 0;
    strncpy(vIDStr,&pkt[3],5); //read pkt[3-7], now on pkt[8]
    if(sscanf(vIDStr, "%x" , &vID) != 1 || vIDStr[4] != ' ')
    {
      Serial.println("[INVALID_INBOUND_COMMAND]");
      return;
    }
    
    //get the color.
    RGBC color;
    char colorStr[19]; //"R#### G#### B#### \0"
    colorStr[18] = 0;
    strncpy(colorStr,&pkt[8],18); //read pkt[8-25], now done.
    if(!stringToColor(colorStr,color))
    {
      Serial.println("[INVALID_INBOUND_COMMAND]");
      return;
    }

    ChargeManager::NotifyOfNewCarInfo(vID,pad,color);
  }
}

/**
 * This helper function reads string of format 'R#### G#### B#### ' and sets 
 * RGBC to the read color, with clear being 0. Returns true on success or false on parse error.
 */
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
  sprintf(colorStr,"R%04d G%04d B%04d ", color.red, color.green, color.blue);
}