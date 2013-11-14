#pragma once

#include <Arduino.h>
#include <XBee.h>


namespace XBeeUtility
{
  class tXBeePacket
  {
    public:    
      tXBeePacket( Rx16Response );
      tXBeePacket( uint16_t remoteAddress, char * dataStr);
      ~tXBeePacket();
      
      uint16_t getRemoteAddress();
      char * getData();
      uint8_t getLength();
 
    private:
      uint16_t remoteAddress;
      char * data;
      
  };
  
  void Initialize( void );
  bool isDataAvailable( void );
  tXBeePacket * getPkt( void );
  //void queuePacketForSend( tXBeePacket pkt );
  void sendPacket( uint16_t remoteAddress, char * dataStr );
  
}
