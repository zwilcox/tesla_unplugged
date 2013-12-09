#include <Arduino.h>
#include "ChargeSession.h"
#define UPDATE_FREQUENCY 250
#define AUTHORIZATION_TIMEOUT 1000

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
  prevColorAuthorized = false;
  uint32_t ms = millis();
  nextUpdateMillis = ms + UPDATE_FREQUENCY;
  nextAuthTimeout = ms + AUTHORIZATION_TIMEOUT;
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

bool ChargeSession::shouldSendInfo()
{
  uint32_t elapsed = millis();
  
  if (elapsed >= nextUpdateMillis || elapsed < (nextUpdateMillis - UPDATE_FREQUENCY))
  {
    nextUpdateMillis = elapsed + UPDATE_FREQUENCY;
    return true;
  }
  else
  {
    return false; 
  }
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

void ChargeSession::updateLastAuthorizedTime()
{
  nextAuthTimeout = millis() + AUTHORIZATION_TIMEOUT;
}

bool ChargeSession::wasAuthorizedRecently()
{
  uint32_t ms = millis();
  if (ms < nextAuthTimeout || ms < (nextAuthTimeout - AUTHORIZATION_TIMEOUT))
  {
    return true;
  }
  else
  {
    return false;
  }
}
