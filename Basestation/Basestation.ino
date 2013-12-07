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

#define MEM_PRINT_INTERVAL 5000
static uint32_t nextMemPrint;

void printMemLeft()
{  
  if(millis() >= nextMemPrint)
  { 
    Serial.print("[MEM LEFT: ~");
    Serial.print(Utilities::get_free_memory());
    Serial.print(" bytes ]");
    nextMemPrint = millis() + MEM_PRINT_INTERVAL;
  }
}

void setup() 
{
  Serial.begin(9600);
  PadManager::Initialize();
  XBeeUtility::Initialize();
  Serial.println("[BT ]");
  
  nextMemPrint = millis() + MEM_PRINT_INTERVAL;
}

void loop() 
{
  //get incomming commands from PC.
  SerialCommandPacketizer::getPacketsFromSerial();
  
  printMemLeft();
  
  //print incomming commands from PC.
  SerialCommandPacketizer::processInboundPackets();
  
  //look for new cars on pads...
  ChargeManager::checkForNewChargeSessions();
  
  //get & process information on pad side.
  ChargeManager::updateChargeSessionInfo();

  //get & process information from cars, including charging cars
  XBeeUtility::processIncommingCarMessages(5);
  
  //send all charge information to PC database
  ChargeManager::sendChargeSessionData();
}

