#pragma once
#include <Arduino.h>

#include "PadManager.h"

namespace ChargeManager 
{
  void NotifyOfNewCarInfo(uint16_t vID, PadManager::tPadID pad, RGBC color);
  void ClearAuthorizedCarList();
  void updateChargeSessions();
};

