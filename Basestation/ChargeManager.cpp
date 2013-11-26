#include <Arduino.h>
#include "ChargeManager.h"
#include <LinkedList.h>
#include "ChargeSession.h"
#include "AuthorizedCar.h"
#include "PadManager.h"

static LinkedList<AuthorizedCar*> AuthorizedCarList;
static LinkedList<ChargeSession*> ChargeSessionList;
static bool Pad1InSession;
static bool Pad2InSession;
static bool Pad3InSession;

static AuthorizedCar * getCarFromChargeSession(ChargeSession * session);

namespace ChargeManager 
{
  void Initialize()
  {
    Pad1InSession = false;
    Pad2InSession = false;
    Pad3InSession = false;
  }

  void NotifyOfNewCarInfo(uint16_t vID, PadManager::tPadID pad, RGBC color)
  {
    ListIterator<AuthorizedCar *> iterator(&AuthorizedCarList);
    
    if (AuthorizedCarList.isEmpty())
    {
      AuthorizedCar * car = new AuthorizedCar(vID);
      car->setAuthorizedColor(color,pad);
      AuthorizedCarList.insert(car);
      return;
    }
    
    AuthorizedCar * carToUpdate;
    do
    {
      carToUpdate = iterator.current();
      if (carToUpdate->vID == vID)
      {
        carToUpdate->setAuthorizedColor(color,pad);
        return;
      }
    }while(iterator.moveNext());
    
    AuthorizedCar * car = new AuthorizedCar(vID);
    car->setAuthorizedColor(color,pad);
    AuthorizedCarList.insert(car);
    return;
  }

  void ClearAuthorizedCarList()
  {
    //CancelChargeSessions();
    if (AuthorizedCarList.isEmpty()) return;
    
    ListIterator<AuthorizedCar *> iterator(&AuthorizedCarList);
    
    while(!AuthorizedCarList.isEmpty())
    {
      AuthorizedCar * toDelete = iterator.current();
      iterator.removeCurrent();
      
      if(toDelete)
        delete (toDelete);
    }
    
  }
  
  void updateChargeSessionInfo()
  {
    if(ChargeSessionList.isEmpty()) return;
    
    ListIterator<ChargeSession *> iterator(&ChargeSessionList);
    
    ChargeSession * sessionToUpdate;
    do
    {
      sessionToUpdate = iterator.current();
      AuthorizedCar * sessionCar = getCarFromChargeSession(sessionToUpdate);
      RGBC color = PadManager::readColorSensor(sessionToUpdate->chargePad);
      bool authorized = false;
      authorized = sessionCar->isColorAuthorized(sessionToUpdate->chargePad,color);
      
      if(!authorized)
      {
        PadManager::setPadState(sessionToUpdate->chargePad, false);
        if (sessionToUpdate)
          delete sessionToUpdate;
        
        if (iterator.hasNext())
        {
          iterator.removeCurrent();
        }
        else
        {
          return; //reached end of list... just exit, don't keep checking list.
        }
        sessionToUpdate = iterator.current();
      }

      if(!sessionToUpdate->isPadInfoUpdated())
      {
        float padVoltage = PadManager::getPadVoltage(sessionToUpdate->chargePad);
        sessionToUpdate->updatePadVoltage(padVoltage);

        float padCurrent = PadManager::getPadCurrent(sessionToUpdate->chargePad);
        sessionToUpdate->updatePadCurrent(padCurrent);
      }
    }while(iterator.moveNext());
  }

  void checkForNewChargeSessions()
  {
    if (AuthorizedCarList.isEmpty()) return;
   
    RGBC p1ColorRead = PadManager::readColorSensor(PadManager::Pad1);
    RGBC p2ColorRead = PadManager::readColorSensor(PadManager::Pad2);
    RGBC p3ColorRead = PadManager::readColorSensor(PadManager::Pad3);

    ListIterator<AuthorizedCar *> iterator(&AuthorizedCarList);
    
    AuthorizedCar * carToCheck;
    do
    {
      carToCheck = iterator.current();
      if (!carToCheck->isRegistrationComplete())
      {
        Serial.print("Car not yet registered");
        continue;
      }
      
      
      if (!Pad1InSession)
      {
        if (carToCheck->isColorAuthorized(PadManager::Pad1,p1ColorRead)) 
        {
          //create new charge session
          ChargeSession * newSession = new ChargeSession(PadManager::Pad1, carToCheck->vID);
          ChargeSessionList.insert(newSession);
          Pad1InSession = true;
          PadManager::setPadState(PadManager::Pad1,true);
          continue;
        }
      }
      if (!Pad2InSession)
      {  
        if (carToCheck->isColorAuthorized(PadManager::Pad2,p2ColorRead)) 
        {
          ChargeSession * newSession = new ChargeSession(PadManager::Pad2, carToCheck->vID);
          ChargeSessionList.insert(newSession);
          Pad2InSession = true;
          PadManager::setPadState(PadManager::Pad2,true);
          continue;
        }
      }
      if (!Pad3InSession)
      {
        if (carToCheck->isColorAuthorized(PadManager::Pad3,p3ColorRead)) 
        {
          ChargeSession * newSession = new ChargeSession(PadManager::Pad3, carToCheck->vID);
          ChargeSessionList.insert(newSession);
          Pad3InSession = true;
          PadManager::setPadState(PadManager::Pad3,true);
          continue;
        }
      }
    }while(iterator.moveNext() && (Pad1InSession || Pad2InSession || Pad3InSession ));
  }
  
  void sendChargeSessionData()
  {
    if (ChargeSessionList.isEmpty()) return;
   
    RGBC p1ColorRead = PadManager::readColorSensor(PadManager::Pad1);
    RGBC p2ColorRead = PadManager::readColorSensor(PadManager::Pad2);
    RGBC p3ColorRead = PadManager::readColorSensor(PadManager::Pad3);

    ListIterator<ChargeSession * > iterator(&ChargeSessionList);
    
    ChargeSession * sessionToSend;
    do
    {
      sessionToSend = iterator.current();
      
      if (sessionToSend->isPadInfoUpdated())
      {
        Serial.print("fake voltage/current send for");
        Serial.println(sessionToSend->vehicleID);
      }
    }while(iterator.moveNext());
  }
}
AuthorizedCar * getCarFromChargeSession(ChargeSession * session)
{
    ListIterator<AuthorizedCar *> iterator(&AuthorizedCarList);
    
    AuthorizedCar * carToCheck;
    do
    {
      if (carToCheck->vID == session->vehicleID)
        return carToCheck;
    }while(iterator.moveNext());
}
