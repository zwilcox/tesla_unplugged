#pragma once

#include <Arduino.h>
#include <SoftADJDS311.h>
#include "PadManager.h"

class AuthorizedCar
{
  public:
    AuthorizedCar(uint16_t vehicleID);
    ~AuthorizedCar();
    uint16_t vID;
    
    bool isColorAuthorized(PadManager::tPadID chargePad, RGBC color);
    
    void setAuthorizedColor(RGBC color, PadManager::tPadID pad);

    bool isRegistrationComplete();
    bool isInChargeSession;
  
  private:
    void updateRegistrationStatus();
    
    RGBC Pad1AuthorizedColor;
    bool p1AuthRegistered;
    
    RGBC Pad2AuthorizedColor;
    bool p2AuthRegistered;
    
    RGBC Pad3AuthorizedColor;
    bool p3AuthRegistered;
    
    bool _registrationComplete;
    
};
