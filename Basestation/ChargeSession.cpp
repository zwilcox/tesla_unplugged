#include <Arduino.h>
#include "ChargeSession.h"


ChargeSession::ChargeSession(PadManager::tPadID pad, AuthorizedCar * vehicle) : 
                            chargePad(pad), vehicleID(vehicle->vID), _vehicle(vehicle)
{
  isvCurrentNew = false;
  isvVoltageNew = false;
  ispCurrentNew = false;
  ispVoltageNew = false;
  padInfoUpdated = false;
  vehicleInfoUpdated = false;
  _vehicle->isInChargeSession = true;
}

ChargeSession::~ChargeSession()
{
  _vehicle->isInChargeSession = false;
}

AuthorizedCar * ChargeSession::getVehicleRef()
{
  return _vehicle;
}

void ChargeSession::updateVehicleVoltage(float v)
{
  vVoltage = v;
  isvVoltageNew = true;
}

void ChargeSession::updateVehicleCurrent(float c)
{
  vCurrent = c;
  isvCurrentNew = true;
}
  
void ChargeSession::updatePadVoltage(float v)
{
  pVoltage = v;
  ispVoltageNew = true;
}

void ChargeSession::updatePadCurrent(float c)
{
  pCurrent = c;
  ispCurrentNew = true;
}

float ChargeSession::getPadCurrent()
{
  ispCurrentNew = false;
  return pCurrent;
}

float ChargeSession::getVehicleCurrent()
{
  isvCurrentNew = false;
  return vCurrent;
}

float ChargeSession::getPadVoltage()
{
  ispVoltageNew = false;
  return pVoltage;
}

float ChargeSession::getVehicleVoltage()
{
  isvVoltageNew = false;
  return vVoltage;
}

bool ChargeSession::isPadInfoUpdated()
{
  return (ispVoltageNew && ispCurrentNew);
}

bool ChargeSession::isVehicleInfoUpdated()
{
  return (isvVoltageNew && isvCurrentNew);
}