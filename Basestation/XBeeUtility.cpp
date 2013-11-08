#include <Arduino.h>
#include "XBeeUtility.h"

static bool _isDataAvailable = false;
static XBee xbee;

uint8_t charArrayLength( char * array)
{
  uint8_t i = 0;

  for(char * c = array ; *c != '\0'; c++, i++);
  
  return i;

}
namespace XBeeUtility
{
  /**XBEE PACKET**/
  tXBeePacket::tXBeePacket( Rx16Response rx16 )
  {
    char * rsp = new char[rx16.getDataLength()+1];
    rsp[rx16.getDataLength()] = '\0';
    strncpy(rsp,(char * )rx16.getData(),rx16.getDataLength());
    remoteAddress = rx16.getRemoteAddress16();
    data = rsp;
  }

  tXBeePacket::tXBeePacket( uint16_t address = 0, char * dataStr = '\0')
  {
    uint8_t length = charArrayLength(dataStr);
    char * rsp = new char[length+1];
    rsp[length] = '\0';
    strncpy(rsp,dataStr,length);
    remoteAddress = address;
    data = rsp;
  }
  
  tXBeePacket::~tXBeePacket( )
  {
    if (data)
    {
      delete(data);
    }
  }
  
  uint16_t tXBeePacket::getRemoteAddress()
  {
    return remoteAddress;
  }
  
  char * tXBeePacket::getData()
  {
    return data;
  }
  
  uint8_t tXBeePacket::getLength()
  {
    return charArrayLength(data);
  }
  /**END XBEE PACKET**/
   
  void Initialize()
  {
    xbee.setSerial(Serial1);
    xbee.begin(9600);
  }
  
  bool isDataAvailable()
  {
    if (_isDataAvailable)
    {
      return true;
    }
    else
    {   
      xbee.readPacket();
      if (xbee.getResponse().isAvailable())
      {
        _isDataAvailable = true;
        return true;
      }
      else
      {
        _isDataAvailable = false;
        return false;
      }
    }
  }
    
  tXBeePacket * getPkt()
  {
    tXBeePacket * rxPacket;
    
    if (_isDataAvailable)
    {
      Rx16Response rx16 = Rx16Response();
      xbee.getResponse().getRx16Response(rx16);
      rxPacket = new tXBeePacket(rx16);
      _isDataAvailable = false;
    }
    else
    {
      rxPacket = NULL;
    }
    
    return rxPacket;
  }

  void sendPacket( uint16_t remoteAddress, char * dataStr )
  {
    Tx16Request tx = Tx16Request(remoteAddress, (uint8_t *) dataStr, charArrayLength(dataStr));
    xbee.send(tx);
  }
  
  
}