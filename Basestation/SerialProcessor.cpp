#define BUFF_SIZE 64
#include "SerialProcessor.h"
#include <string.h>
#include "Utilities.h"
#include <QueueList.h>
#include "ColorSense.h"

//forward declare file scope functions.
static void processRawInboundPacket( char * pkt );
static void setStringToCommand(SerialProcessor::tOutboundCommand cmd, char * str );
static void commandGetColor( char * pkt);
static void commandCalColor( char * pkt);
static void commandToggleLED( char * pkt);

//file scope variables
static QueueList < SerialProcessor::InboundSerialPacket * > pktList;

//namespace implementation
namespace SerialProcessor
{

  /**INBOUND SERIAL PACKET CLASS**/
  InboundSerialPacket::InboundSerialPacket( char * pkt) : 
    command( getCommandFromRawPacket( pkt ) ),
    payload( NULL )
  {
    
    if (command != INVALID_INBOUND_COMMAND)
    {
      uint8_t payloadLength = Utilities::charArrayLength(&pkt[3]);
      payload = new char[payloadLength];
      strncpy(payload, &pkt[3], payloadLength);
    }
  }
  
  InboundSerialPacket::~InboundSerialPacket()
  {
    if(payload)
    {
      delete(payload);
    }
  }
  
  tInboundCommand InboundSerialPacket::getCommandFromRawPacket( char * pkt )
  {
    char cmd[4];
    cmd[3] = '\0';
    strncpy(cmd,pkt,3);
    
    if( strcmp( cmd, "GC " ) == 0) return GetColor;
    if( strcmp( cmd, "GA " ) == 0) return GetCurrent;
    if( strcmp( cmd, "GV " ) == 0) return GetVoltage;
    if( strcmp( cmd, "TP " ) == 0) return TogglePad;
    if( strcmp( cmd, "TC " ) == 0) return ToggleLED;
    if( strcmp( cmd, "CC " ) == 0) return CalColor;
    if( strcmp( cmd, "GR " ) == 0) return GetRadio;
    if( strcmp( cmd, "CL " ) == 0) return ClearList;
    if( strcmp( cmd, "IC " ) == 0) return InfoCar;
    
    return INVALID_INBOUND_COMMAND;
  }
  
  //returns the command type of the packet.
  tInboundCommand InboundSerialPacket::getCommand()
  {
    return command;
  }
  /**END INBOUND SERIAL PACKET CLASS**/
  
  
  void getPacketsFromSerial()
  {
    static char buff[BUFF_SIZE];
    static int bIndx = 0;
    static bool readingPacket = false;
    
    if (!Serial.available()) return;

    char readChar = -1;
    
    while ((readChar = Serial.read()) != -1)
    {
     
      if( readChar == '[' )
      {
        bIndx = 0;
        readingPacket = true;
      }
      
      else if(readingPacket && readChar == ']')
      {
        readingPacket = false;
        buff[bIndx] = '\0';
        processRawInboundPacket(buff);
        bIndx = 0;
      }
      
      else if(readingPacket)
      {
        buff[bIndx++] = readChar;
      }

      if (bIndx >= BUFF_SIZE - 1)
      {
        readingPacket = false;
        bIndx = 0;
      }
    }
    
  }
  
  void processInboundPackets()
  {
    while ( !pktList.isEmpty() )
    {  
      InboundSerialPacket * pkt = pktList.pop();
    
      switch(pkt->getCommand())
      {
        case GetColor:
          commandGetColor(pkt->payload);
          break;
        case GetCurrent:
          Serial.println("Get Current");
          break;
        case GetVoltage:
          Serial.println("Get Voltage");
          break;
        case ToggleLED:
          commandToggleLED(pkt->payload);
          break;
        case TogglePad:
          Serial.println("Toggle Pad");
          break;
        case CalColor:
          commandCalColor(pkt->payload);
          break;
        case GetRadio:
          Serial.println("Get Radio");
          break;
        case ClearList:
         Serial.println("Clear List");
          break;
        case InfoCar:
          Serial.println("Info Cars");
          break;
        default:
          Serial.println("INVALID_INBOUND_COMMAND");
          break;
      }
      
      delete (pkt);
    }
  }
  
  void sendOutboundPacket(tOutboundCommand cmd, char * payload )
  {
    char cmdStr[3];
    setStringToCommand(cmd,cmdStr);  

    Serial.print('[');
    Serial.print(cmdStr);
    Serial.print(" ");
    Serial.print(payload);
    Serial.println(']'); 
  }
  
}

//file scope functions
using namespace SerialProcessor;

void processRawInboundPacket( char * pkt )
{
  pktList.push( new InboundSerialPacket(pkt) );
}

  /**
   * Creates the color string for the specified sensor.
   * ALERT: str MUST BE size 3 or larger or BAD THINGS happen.
   **/
void setStringToCommand(tOutboundCommand cmd, char * str )
{
  switch(cmd)
  {
    case ListCars:
      strcpy(str,"LC");
      return;
    case SendColor:
      strcpy(str,"SC");
      return;
    case SendVoltage:
      strcpy(str,"SV");
      return;
    case SendCurrent:
      strcpy(str,"SA");
      return;
    case SendRadio:
      strcpy(str,"SR");
      return;
    case ChargeBegin:
      strcpy(str,"CB");
      return;
    case ChargeEnd:
      strcpy(str,"CE");
      return;
    default:
      strcpy(str,"");
      return;
  } 
} 

void commandGetColor( char * pkt)
{
  using namespace ColorSense;
  char cmd[4];
  cmd[3] = '\0';
  strncpy(cmd,pkt,3);
  char colorStr[18];
  
  if( strcmp( cmd, "P1 " ) == 0)
  {
    getColorString( Sensor1 , colorStr);
    sendOutboundPacket( SendColor, colorStr );
  }
  else if( strcmp( cmd, "P2 " ) == 0)
  {
    getColorString( Sensor2 , colorStr);
    sendOutboundPacket( SendColor, colorStr );
  }
  else if( strcmp( cmd, "P3 " ) == 0)
  {
    getColorString( Sensor3 , colorStr);
    sendOutboundPacket( SendColor, colorStr );
  }
}

void commandCalColor( char * pkt)
{
  using namespace ColorSense;
  char cmd[4];
  cmd[3] = '\0';
  strncpy(cmd,pkt,3);
  
  if( strcmp( cmd, "P1 " ) == 0)
  {
    setLEDState( Sensor1, true );  
    calibrateSensor( Sensor1 );
    setLEDState( Sensor1, false );  
  }
  
  else if( strcmp( cmd, "P2 " ) == 0)
  {
    setLEDState( Sensor2, true );  
    calibrateSensor( Sensor2 );
    setLEDState( Sensor2, false );  
  }
  
  else if( strcmp( cmd, "P3 " ) == 0)
  {
    setLEDState( Sensor3, true );  
    calibrateSensor( Sensor3 );
    setLEDState( Sensor3, false );  
  }
  
}

void commandToggleLED( char * pkt)
{

  using namespace ColorSense;
  char cmd[4];
  cmd[3] = '\0';
  strncpy(cmd,pkt,3);
  
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
    return;
  }
  
  if( strcmp( cmd, "P1 " ) == 0)
  {
    setLEDState( Sensor1, turnLEDon );
  }
  
  else if( strcmp( cmd, "P2 " ) == 0)
  {
    setLEDState( Sensor2, turnLEDon );
  }
  
  else if( strcmp( cmd, "P3 " ) == 0)
  {
    setLEDState( Sensor3, turnLEDon );
  }
  
}