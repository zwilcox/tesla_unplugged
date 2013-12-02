#include "ChargeManager.h"


//Hey Ari...Zach here. Here's a good example of some documentation that would help a lot here...
/*
*	AuthorizedCar is a list of all the cars that have been registered and are authorized to charge.
*/
static LinkedList<AuthorizedCar*> AuthorizedCarList;

/*
*	The ChargeSessionList is a list of authorized cars that are currently charging on the pad.
*/

static LinkedList<ChargeSession*> ChargeSessionList;

static bool Pad1InSession;
static bool Pad2InSession;
static bool Pad3InSession;

static void CancelChargeSessions();
static AuthorizedCar * getCarFromChargeSession(ChargeSession * session);

namespace ChargeManager 
{
  void Initialize()
  {
    Pad1InSession = false;
    Pad2InSession = false;
    Pad3InSession = false;
  }

  /**
   * When PC sends vehicle authorization information, this function
   * finds the given car in the list of authorized cars and updates info,
   * or creates a new authorized car object if the given vID did not exist in the list.
   */
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
   
  /**
   * When PC sends CL command, this cancels all charge sessions and removes all authorized cars from list.
   */ 
  void ClearAuthorizedCarList()
  {
    CancelChargeSessions();
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
  
  
  /**
   * Iterates over list of current charge sessions and updates information for each one.
   * If the vehicle is no longer on the pad, the charge session is ended/deleted. 
   */ 
  void updateChargeSessionInfo()
  {
    if(ChargeSessionList.isEmpty()) return;
    
    ListIterator<ChargeSession *> iterator(&ChargeSessionList);
    
    ChargeSession * sessionToUpdate;
    while (!iterator.isEmpty() && iterator.current() != 0)
    {
      sessionToUpdate = iterator.current();
      
      AuthorizedCar * sessionCar = sessionToUpdate->getVehicleRef();
      RGBC color = PadManager::readColorSensor(sessionToUpdate->chargePad);
      bool authorized = sessionCar->isColorAuthorized(sessionToUpdate->chargePad,color);
      
      if(!authorized)
      {
        Serial.println("car no longer authorized. GTFO BITCHFACE");
        PadManager::setPadState(sessionToUpdate->chargePad, false);
        
        switch(sessionToUpdate->chargePad)
        {
          case PadManager::Pad1:
            Pad1InSession = false;
            break;
          case PadManager::Pad2:
            Pad2InSession = false;
            break;
          case PadManager::Pad3:
            Pad3InSession = false;
            break;
        }
                
        iterator.removeCurrent(); //remove it from the list..
        
        delete sessionToUpdate; //delete charge session.
       
        continue; //keep looking at list objects, if there are any
      }

      if(!sessionToUpdate->isPadInfoUpdated())
      {
        float padVoltage = PadManager::getPadVoltage(sessionToUpdate->chargePad);
        sessionToUpdate->updatePadVoltage(padVoltage);

        float padCurrent = PadManager::getPadCurrent(sessionToUpdate->chargePad);
        sessionToUpdate->updatePadCurrent(padCurrent);  
      }

      if(!iterator.moveNext())  
        return;
    }
  }

  /**
   * Reads colors from each pad and checks them against each car to detect if an authorized car is on a pad.
   * If an authorized car is on a pad, this function creates a new charge session and adds it to the list.
   */
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
      Serial.print(carToCheck->vID);
      if(carToCheck->isInChargeSession)
      {
        Serial.println("  In charge session.");
        continue;
      }
      else
      {
        Serial.print("  Checking pads for car: ");
        Serial.println(carToCheck->vID);
      }
      
      
      if (!carToCheck->isRegistrationComplete())
      {
        Serial.println("  Not yet registered");
        continue;
      }
      
      
      if (!Pad1InSession)
      {
        if (carToCheck->isColorAuthorized(PadManager::Pad1,p1ColorRead)) 
        {
          Serial.println("  Starting charge session on pad1");
          //create new charge session
          ChargeSession * newSession = new ChargeSession(PadManager::Pad1, carToCheck);
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
          Serial.println("  Starting charge session on pad2");
          ChargeSession * newSession = new ChargeSession(PadManager::Pad2, carToCheck);
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
          Serial.println("  Starting charge session on pad3");
          ChargeSession * newSession = new ChargeSession(PadManager::Pad3, carToCheck);
          ChargeSessionList.insert(newSession);
          Pad3InSession = true;
          PadManager::setPadState(PadManager::Pad3,true);
          continue;
        }
      }
      
    }while(iterator.moveNext() && (!Pad1InSession || !Pad2InSession || !Pad3InSession ));
  }
  
  /**
   * Iterates over list of charge session data, if it has been updated, it sends
   * back to PC.
   */
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

/**
 * Cancels all current charge sessions.
 */
void CancelChargeSessions()
{
  if (ChargeSessionList.isEmpty()) return;
  
  ListIterator<ChargeSession *> iterator(&ChargeSessionList);
  
  while(!ChargeSessionList.isEmpty())
  {
    ChargeSession * toDelete = iterator.current();
    iterator.removeCurrent();
    
    PadManager::setPadState(toDelete->chargePad, false);
      
    if(toDelete)
      delete (toDelete);
  }
  
  Pad1InSession = false;
  Pad2InSession = false;
  Pad3InSession = false;
}

void ChargeManager::updateVoltage(uint16_t address, float measurement)
{
	ChargeSession* car = ChargeManager::findCarByAddress(address);
	if( car != NULL)
		car->updateVehicleVoltage(measurement);
}
void ChargeManager::updateCurrent(uint16_t address, float measurement)
{
	ChargeSession* car = ChargeManager::findCarByAddress(address);
	if( car != NULL)
		car->updateVehicleCurrent(measurement);
}

ChargeSession* ChargeManager::findCarByAddress(uint16_t address)
{
	//iterate through list
	ListIterator<ChargeSession *> it(&ChargeSessionList);

	for (	; !it.isEmpty() && it.current() != 0; it.moveNext())
	{
		//if address == car_address
			//return car
		ChargeSession* temp =it.current();
		if(temp->vehicleID == address)
			return temp;
			
	}
	return NULL;
}

