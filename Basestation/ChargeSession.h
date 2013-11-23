#pragma once
#include <Arduino.h>
#include "PadManager.h"

class ChargeSession
{

  public:
    ChargeSession(PadManager::tPadID pad, uint16_t vID);
    ~ChargeSession();
    
    void updateVehicleVoltage(float v);
    void updateVehicleCurrent(float c);
    
    void updatePadVoltage(float v);
    void updatePadCurrent(float c);
    
  private:
    float vCurrent;
    float vVoltage;
    bool isvCurrentNew;
    bool isvVoltageNew;
    
    float pCurrent;
    float pVoltage;
    bool ispCurrentNew;
    bool ispVoltageNew;
    
    uint16_t vehicleID;
    PadManager::tPadID chargePad;

};