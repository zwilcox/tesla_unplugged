#include <Arduino.h>
#include "ChargeSession.h"


ChargeSession::ChargeSession(PadManager::tPadID pad, uint16_t vID) : 
                            chargePad(pad), vehicleID(vID)
{
  isvCurrentNew = false;
  isvVoltageNew = false;
  ispCurrentNew = false;
  ispVoltageNew = false;
}

ChargeSession::~ChargeSession()
{

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