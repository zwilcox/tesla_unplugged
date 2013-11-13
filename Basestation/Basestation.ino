#include <DigitalIO.h>
#include <SoftADJDS311.h>
#include "PadManager.h"
#include "XBeeUtility.h"
#include "SerialProcessor.h"
#include "Utilities.h"
#include <XBee.h>
#include <QueueList.h>
#include "Pad.h"

void temporary_printIfXBeeReceive()
{
  if (XBeeUtility::isDataAvailable())
  {
    XBeeUtility::tXBeePacket * pkt = XBeeUtility::getPkt();
    
    Serial.print("XBee Receive: ");
    Serial.print(pkt->getLength());
    Serial.print(" bytes from: ");
    Serial.print(pkt->getRemoteAddress());
    Serial.println(".");
    Serial.println(pkt->getData());
    Serial.println("");
    
    if(pkt)
      delete(pkt);
  }
}

void setup() 
{
  Serial.begin(9600);
  PadManager::Initialize();
  XBeeUtility::Initialize();
}

void loop() 
{
  temporary_printIfXBeeReceive();
  
  SerialProcessor::getPacketsFromSerial();
  SerialProcessor::processInboundPackets();
  
  Serial.println(Utilities::get_free_memory());
  delay(500);
}

