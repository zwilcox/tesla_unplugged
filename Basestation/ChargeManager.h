#pragma once
#include <Arduino.h>
#include <LinkedList.h>
#include "ChargeSession.h"
#include "AuthorizedCar.h"
#include "PadManager.h"


#include "PadManager.h"

namespace ChargeManager 
{
  void NotifyOfNewCarInfo(uint16_t vID, PadManager::tPadID pad, RGBC color);
  void ClearAuthorizedCarList();
  void updateChargeSessionInfo();
  void checkForNewChargeSessions();
  void sendChargeSessionData();
  void updateVoltage(uint16_t address, float measurement);
  void updateCurrent(uint16_t address, float measurement);
  ChargeSession* findCarByAddress(uint16_t address);


};

