#pragma once

#include <arduino.h>

//other stuff
namespace SerialCommandPacketizer
{
  typedef enum 
  {
    GetColor        = 1,
    GetCurrent      = 2,
    GetVoltage      = 3,
    TogglePad       = 4,
    ToggleLED       = 5,
    CalColor        = 6,
    GetRadio        = 7,
    ClearList       = 8,
    InfoCar         = 9,
    INVALID_INBOUND_COMMAND = 0

  } tInboundCommand;
    
  typedef enum
  {
    ListCars    = 1,
    SendColor   = 2,
    SendVoltage = 3,
    SendCurrent = 4,
    SendRadio   = 5,
    ChargeBegin = 6,
    ChargeEnd   = 7,
    INVALID_OUTBOUND_COMMAND = 0
  
  } tOutboundCommand;
  
  class InboundSerialPacket
  {
    public:
      InboundSerialPacket( char * pkt);
      ~InboundSerialPacket( void );
      tInboundCommand getCommand();
      char * payload;
      
    private:
      tInboundCommand getCommandFromRawPacket( char * pkt );
      tInboundCommand command;
  };
  
  void getPacketsFromSerial();
  void processInboundPackets();
  void sendOutboundPacket(tOutboundCommand cmd, char * payload );
}
