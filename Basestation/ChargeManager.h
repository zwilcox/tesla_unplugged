#pragma once
#include <Arduino.h>
#include "PadManager.h"

namespace ChargeManager 
{
  void NotifyOfNewCarInfo(uint16_t vID, PadManager::tPadID pad, RGBC color);
  void ClearAuthorizedCarList();
  void updateChargeSessionInfo();
  void checkForNewChargeSessions();
  void sendChargeSessionData();
  void updateVehicleVoltage(uint16_t address, float measurement);
  void updateVehicleCurrent(uint16_t address, float measurement);
};

