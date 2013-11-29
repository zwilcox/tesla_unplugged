#define BUFF_SIZE 64
#include "SerialCommandPacketizer.h"
#include <string.h>
#include "Utilities.h"
#include <QueueList.h>
#include "PadManager.h"
#include "PacketProcessor.h"

//forward declare file scope functions.
static void processRawInboundPacket( char * pkt );
static void setStringToCommand(SerialCommandPacketizer::tOutboundCommand cmd, char * str );

//file scope variables
static QueueList < SerialCommandPacketizer::InboundSerialPacket * > pktList;

//namespace implementation
namespace SerialCommandPacketizer
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
          PacketProcessor::commandGetColor(pkt->payload);
          break;
        case GetCurrent:
          PacketProcessor::commandGetCurrent(pkt->payload);
          break;
        case GetVoltage:
          PacketProcessor::commandGetVoltage(pkt->payload);
          break;
        case ToggleLED:
          PacketProcessor::commandToggleLED(pkt->payload);
          break;
        case TogglePad:
          PacketProcessor::commandTogglePad(pkt->payload);
          break;
        case CalColor:
          PacketProcessor::commandCalColor(pkt->payload);
          break;
        case GetRadio:
          Serial.println("Get Radio");
          break;
        case ClearList:
          PacketProcessor::commandClearList(pkt->payload);
          break;
        case InfoCar:
          PacketProcessor::commandInfoCar(pkt->payload);
          break;
        default:
          //return error packet.
          Serial.println("[INVALID_INBOUND_COMMAND]");
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
using namespace SerialCommandPacketizer;

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
