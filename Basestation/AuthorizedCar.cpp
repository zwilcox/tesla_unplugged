#include "AuthorizedCar.h"
#define TOLERANCE 50

static void zeroColor(RGBC &color);
static bool colorIsNear(RGBC color1, RGBC color2, uint16_t tolerance);

AuthorizedCar::AuthorizedCar(uint16_t vehicleID) : vID(vehicleID)
{
  _registrationComplete = false;
  p1AuthRegistered = false;
  p2AuthRegistered = false;
  p3AuthRegistered = false;
  zeroColor(Pad1AuthorizedColor);
  zeroColor(Pad2AuthorizedColor);
  zeroColor(Pad3AuthorizedColor);
}

AuthorizedCar::~AuthorizedCar()
{

}

bool AuthorizedCar::isColorAuthorized(PadManager::tPadID chargePad, RGBC color)
{
      switch(chargePad)
      {
        case PadManager::Pad1:
          return colorIsNear(Pad1AuthorizedColor,color,TOLERANCE);
          break;
        case PadManager::Pad2:
          return colorIsNear(Pad2AuthorizedColor,color,TOLERANCE);
          break;
        case PadManager::Pad3:
          return colorIsNear(Pad3AuthorizedColor,color,TOLERANCE);
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

static void zeroColor(RGBC &color)
{
  color.red = 0;
  color.blue = 0;
  color.green = 0;
  color.clear = 0;
}

static bool colorIsNear(RGBC color1, RGBC color2, uint16_t tolerance)
{
  if (color1.red - color2.red > tolerance || color2.red -color1.red > tolerance)
    return false;
  if (color1.green - color2.green > tolerance || color2.green -color1.green > tolerance)
    return false;   
  if (color1.blue - color2.blue > tolerance || color2.blue -color1.blue > tolerance)
    return false;
    
  return true;
}