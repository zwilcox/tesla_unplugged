#include <Arduino.h>
#include "ChargeManager.h"
#include <LinkedList.h>
#include "ChargeSession.h"
#include "AuthorizedCar.h"

static LinkedList<AuthorizedCar*> AuthorizedCarList;
static LinkedList<ChargeSession*> ChargeSessionList;

namespace ChargeManager 
{
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
  
  void updateChargeSessions()
  {
    if(ChargeSessionList.isEmpty()) return;
    
    ListIterator<ChargeSession *> iterator(&ChargeSessionList);
    
    ChargeSession * sessionToUpdate;
    do
    {
      sessionToUpdate = iterator.current();
      //do update stuff
    }while(iterator.moveNext());
  }
}