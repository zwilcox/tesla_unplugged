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
    
    float getVehicleCurrent( void );
    float getPadCurrent( void );
    float getVehicleVoltage( void );
    float getPadVoltage( void );
    
    bool isPadInfoUpdated();
    bool isVehicleInfoUpdated();
    
    AuthorizedCar * getVehicleRef();

    bool shouldSendInfo();
    
  private:
    AuthorizedCar * _vehicle;
    
    float vCurrent;
    float vVoltage;
    bool isvCurrentNew;
    bool isvVoltageNew;
    bool vehicleInfoUpdated;    

    float pCurrent;
    float pVoltage;
    bool ispCurrentNew;
    bool ispVoltageNew;
    bool padInfoUpdated;
    
    uint32_t nextUpdateMillis;
};
