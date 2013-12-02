#include <DigitalIO.h>
#include <SoftADJDS311.h>
#include "PadManager.h"
#include "XBeeUtility.h"
#include "SerialCommandPacketizer.h"
#include "Utilities.h"
#include <XBee.h>
#include <QueueList.h>
#include <ACS712.h>
#include <voltage_reader.h>
#include "ChargeSession.h"
#include <LinkedList.h>
#include "AuthorizedCar.h"
#include "ChargeManager.h"


void process_car_message()
{
  
    XBeeUtility::tXBeePacket * pkt = XBeeUtility::getPkt();
	uint16_t address = pkt-> getRemoteAddress();
	char* message = pkt->getData();
	char compare[3] = {message[0], message[1], 0};
	//message format: SV ##.##
	//                0123
	float measurment = atof(&message[3]);  
	if(! strcmp(compare, "SV") )
	{
		//process voltage stuff
		ChargeManager::updateVoltage(address, measurment);
	}
	else if(! strcmp(compare, "SA") )
	{
		//process current stuff
		ChargeManager::updateCurrent(address, measurment);
	}
   /* 
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
	
}	

void setup() 
{
	Serial.begin(9600);
	PadManager::Initialize();
	XBeeUtility::Initialize();
}

void loop() 
{
  
	SerialCommandPacketizer::getPacketsFromSerial();
	Serial.println(Utilities::get_free_memory());
	SerialCommandPacketizer::processInboundPackets();
  
	ChargeManager::checkForNewChargeSessions();
	ChargeManager::updateChargeSessionInfo();
	
	//ChargeManager::sendChargeSessionData();
    if (XBeeUtility::isDataAvailable())
	{
		process_car_message();
    }
	
  delay(500);
}

