#include "AuthorizedCar.h"
#include "Utilities.h"


bool colorIsSaturated(RGBC color);

AuthorizedCar::AuthorizedCar(uint16_t vehicleID) : vID(vehicleID)
{
  _registrationComplete = false;
  p1AuthRegistered = false;
  p2AuthRegistered = false;
  p3AuthRegistered = false;
  isInChargeSession = false;
  Utilities::zeroColor(Pad1AuthorizedColor);
  Utilities::zeroColor(Pad2AuthorizedColor);
  Utilities::zeroColor(Pad3AuthorizedColor);
  magnitude = 0;
}

AuthorizedCar::~AuthorizedCar()
{

}

bool AuthorizedCar::isColorAuthorized(PadManager::tPadID chargePad, RGBC color)
{
  switch(chargePad)
  {
    case PadManager::Pad1:
      return colorIsNear(Pad1AuthorizedColor,color);
      break;
    case PadManager::Pad2:
      return colorIsNear(Pad2AuthorizedColor,color);
      break;
    case PadManager::Pad3:
      return colorIsNear(Pad3AuthorizedColor,color);
      break;
  }  
}

void AuthorizedCar::setAuthorizedColor(RGBC color, PadManager::tPadID pad)
{
  switch(pad)
  {
    case PadManager::Pad1:
      Serial.print("Registered color for vehicle ");
      Serial.print(vID);
      Serial.println(" on pad1");
      Pad1AuthorizedColor = color;
      p1AuthRegistered = true;
      
      break;
    case PadManager::Pad2:
      Serial.print("Registered color for vehicle ");
      Serial.print(vID);
      Serial.println(" on pad2");
      Pad2AuthorizedColor = color;
      p2AuthRegistered = true;  
      break;
    case PadManager::Pad3:
      Serial.print("Registered color for vehicle ");
      Serial.print(vID);
      Serial.println(" on pad3");
      Pad3AuthorizedColor = color;
      p3AuthRegistered = true;
      break;
  }

  updateRegistrationStatus();
}
    
void AuthorizedCar::updateRegistrationStatus()
{
  if ( p1AuthRegistered && p2AuthRegistered && p3AuthRegistered )
    _registrationComplete = true;
}

bool AuthorizedCar::isRegistrationComplete()
{
  return _registrationComplete;
}

bool AuthorizedCar::colorIsNear(RGBC authorizedColor, RGBC color2)
{ 
  magnitude = color2.red + color2.green + color2.blue;

  if (( magnitude ) < 300) //color not bright enough to be a car LED..
    return false;
  
  char AUTH[4];
  getAuthStr(authorizedColor,AUTH);

  char CHECK[4];
  getAuthStr(color2,CHECK);
  
  if (!strcmp(AUTH, CHECK))
    return true;
  else if (colorIsSaturated(color2) && isInChargeSession) //in charge session and sensor maxes out...
    return true;
  else
    return false;

}

bool AuthorizedCar::getAuthStr(RGBC color, char * str)
{
  uint16_t max = (color.red >= color.green) ? color.red : color.green;
  max = (max >= color.blue) ? max : color.blue;
  
  uint16_t threshold = max * 0.75;
  
  str[0] = (color.red >= threshold) ? '1' : '0';
  str[1] = (color.green >= threshold) ? '1' : '0';
  str[2] = (color.blue >= threshold) ? '1' : '0';
  str[3] = 0;
}

bool colorIsSaturated(RGBC color)
{
  if (color.red > 930 && color.green > 930 && color.blue > 930)
    return true;
   
  return false;
}
