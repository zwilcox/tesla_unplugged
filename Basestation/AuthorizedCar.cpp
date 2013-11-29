#include "AuthorizedCar.h"
#define TOLERANCE 100

static void zeroColor(RGBC &color);
static bool colorIsNear(RGBC color1, RGBC color2);

AuthorizedCar::AuthorizedCar(uint16_t vehicleID) : vID(vehicleID)
{
  _registrationComplete = false;
  p1AuthRegistered = false;
  p2AuthRegistered = false;
  p3AuthRegistered = false;
  isInChargeSession = false;
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

static void zeroColor(RGBC &color)
{
  color.red = 0;
  color.blue = 0;
  color.green = 0;
  color.clear = 0;
}

static bool colorIsNear(RGBC color1, RGBC color2)
{
  Serial.print("Red diff is:   ");
  Serial.println(color1.red - color2.red);
  Serial.print("Green diff is: ");
  Serial.println(color1.green - color2.green);
  Serial.print("Blue diff is:  ");
  Serial.println(color1.blue - color2.blue);
  
  if ((int)(color1.red - color2.red) > TOLERANCE || (int)(color2.red - color1.red) > TOLERANCE)
    return false;
  if ((int)(color1.green - color2.green) > TOLERANCE || (int)(color2.green - color1.green) > TOLERANCE)
    return false;   
  if ((int)(color1.blue - color2.blue) > TOLERANCE || (int)(color2.blue - color1.blue) > TOLERANCE)
    return false;
    
  return true;
}