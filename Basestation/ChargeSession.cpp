#include <Arduino.h>
#include "ChargeSession.h"


ChargeSession::ChargeSession(PadManager::tPadID pad, uint16_t vID) : 
                            chargePad(pad), vehicleID(vID)
{
  isvCurrentNew = false;
  isvVoltageNew = false;
  ispCurrentNew = false;
  ispVoltageNew = false;
  padInfoUpdated = false;
  vehicleInfoUpdated = false;
}

ChargeSession::~ChargeSession()
{

}
  
void ChargeSession::updateVehicleVoltage(float v)
{
  vVoltage = v;
  isvVoltageNew = true;
  notifyVehicleUpdatedStatus();
}

void ChargeSession::updateVehicleCurrent(float c)
{
  vCurrent = c;
  isvCurrentNew = true;
  notifyVehicleUpdatedStatus();
}
  
void ChargeSession::updatePadVoltage(float v)
{
  pVoltage = v;
  ispVoltageNew = true;
  notifyPadUpdatedStatus();
}

void ChargeSession::updatePadCurrent(float c)
{
  pCurrent = c;
  ispCurrentNew = true;
  notifyPadUpdatedStatus();
}

bool ChargeSession::isPadInfoUpdated()
{
  return padInfoUpdated;
}

bool ChargeSession::isVehicleInfoUpdated()
{
  return vehicleInfoUpdated;
}

void ChargeSession::notifyVehicleUpdatedStatus()
{
  vehicleInfoUpdated == (isvVoltageNew && isvCurrentNew);
}

void ChargeSession::notifyPadUpdatedStatus()
{
  padInfoUpdated == (ispVoltageNew && ispCurrentNew);
}
