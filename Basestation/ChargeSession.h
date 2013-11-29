#pragma once
#include <Arduino.h>
#include "PadManager.h"
#include "AuthorizedCar.h"
class ChargeSession
{

  public:
    ChargeSession(PadManager::tPadID pad, AuthorizedCar * vehicle);
    ~ChargeSession();

    uint16_t vehicleID;
    PadManager::tPadID chargePad;    

    void updateVehicleVoltage(float v);
    void updateVehicleCurrent(float c);
    
    void updatePadVoltage(float v);
    void updatePadCurrent(float c);
    
    bool isPadInfoUpdated();
    bool isVehicleInfoUpdated();
    
    AuthorizedCar * getVehicleRef();

  private:
    AuthorizedCar * _vehicle;
    
    float vCurrent;
    float vVoltage;
    bool isvCurrentNew;
    bool isvVoltageNew;
    bool vehicleInfoUpdated;    
    void notifyVehicleUpdatedStatus();

    float pCurrent;
    float pVoltage;
    bool ispCurrentNew;
    bool ispVoltageNew;
    bool padInfoUpdated;
    void notifyPadUpdatedStatus();


};
