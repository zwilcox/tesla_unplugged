#include <Arduino.h>
#include "XBeeUtility.h"
#include "Utilities.h"
#include "ChargeManager.h"

static bool _isDataAvailable = false;
static XBee xbee;
  
namespace XBeeUtility
{
  /**XBEE PACKET CLASS FUNCTIONS**/
  
  //constructor from a rx16 response pkt.
  tXBeePacket::tXBeePacket( Rx16Response rx16 ) : data (NULL)
  {
    char * rsp = new char[rx16.getDataLength()+1];
    rsp[rx16.getDataLength()] = '\0';
    strncpy(rsp,(char * )rx16.getData(),rx16.getDataLength());
    remoteAddress = rx16.getRemoteAddress16();
    data = rsp;
  }
  
  //constructor from a character string
  tXBeePacket::tXBeePacket( uint16_t address = 0, char * dataStr = '\0') : data (NULL)
  {
    uint8_t length = Utilities::charArrayLength(dataStr);
    char * rsp = new char[length+1];
    rsp[length] = '\0';
    strncpy(rsp,dataStr,length);
    remoteAddress = address;
    data = rsp;
  }
  
  //destructor.
  tXBeePacket::~tXBeePacket( )
  {
    if (data)
    {
      delete(data);
    }
  }
  
  //returns xbeepacket remote address
  uint16_t tXBeePacket::getRemoteAddress()
  {
    return remoteAddress;
  }
  
  //returns xbee packet data.
  char * tXBeePacket::getData()
  {
    return data;
  }
  
  //returns length of the xbee packet payload.
  uint8_t tXBeePacket::getLength()
  {
    return Utilities::charArrayLength(data);
  }
  /**END XBEE PACKET CLASS FUNCTIONS**/
  
  /******* XBeeUtility::Initialize() ************
   * This function opens serial communication with the XBee radio. 
   * This function MUST be called before the rest of the namespace may be used.
   **********************************************/
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
    Tx16Request tx = Tx16Request(remoteAddress, (uint8_t *) dataStr, Utilities::charArrayLength(dataStr));
    xbee.send(tx);
  }
  
  void processIncommingCarMessages(uint16_t count)
  {
    tXBeePacket * pkt;
    uint16_t i = 0;
    while (isDataAvailable() && i++ < count)
    {
      pkt = getPkt();
      uint16_t address = pkt-> getRemoteAddress();
      
      char* message = pkt->getData();
      char compare[4] = {message[0], message[1], message[2], 0};
      
      //message format: SV ##.##
      //                0123
      float measurment = atof(&message[3]);  
      if(! strcmp(compare, "SV ") )
      {
        //process voltage stuff
        ChargeManager::updateVehicleVoltage(address, measurment);
      }
      else if(! strcmp(compare, "SA ") )
      {
        //process current stuff
        ChargeManager::updateVehicleCurrent(address, measurment);
      }
      else
      {
        //error. does not compute.
      }
      
     /** 
      Serial.print("XBee Receive: ");
      Serial.print(pkt->getLength());
      Serial.print(" bytes from: ");
      Serial.print(pkt->getRemoteAddress());
      Serial.println(".");
      Serial.println(pkt->getData());
      Serial.println("");
      */
      if(pkt)
        delete(pkt);
      pkt = 0;
    }
  }	
  
}