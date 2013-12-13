#include "ChargeManager.h"
#include "SerialCommandPacketizer.h"
#include <LinkedList.h>
#include "ChargeSession.h"
#include "AuthorizedCar.h"
#include "Utilities.h"

/**
 *  AuthorizedCar is a list of all the cars that have been registered and are authorized to charge.
 */
static LinkedList<AuthorizedCar*> AuthorizedCarList;

/**
 *  The ChargeSessionList is a list of authorized cars that are currently charging on the pad.
 */
static LinkedList<ChargeSession*> ChargeSessionList;

static bool isPad1InSession;
static bool isPad2InSession;
static bool isPad3InSession;

static bool pad1WasAmbient;
static bool pad2WasAmbient;
static bool pad3WasAmbient;

static void CancelChargeSessions();
static void EndChargeSession(ChargeSession * sessionToEnd );
static AuthorizedCar * getCarFromChargeSession(ChargeSession * session);
static ChargeSession * findChargeSessionByAddress(uint16_t address);

namespace ChargeManager 
{
  void Initialize()
  {
    isPad1InSession = false;
    isPad2InSession = false;
    isPad3InSession = false;
    pad1WasAmbient = true;
    pad2WasAmbient = true;
    pad3WasAmbient = true;
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
      bool newAuth = sessionCar->isColorAuthorized(sessionToUpdate->chargePad,color);
      bool isColorAmbient = PadManager::isColorAmbient(sessionToUpdate->chargePad, color);
      
      if (newAuth)
          sessionToUpdate->updateLastAuthorizedTime();
            
      if((!sessionToUpdate->prevColorAuthorized && isColorAmbient) || !sessionToUpdate->wasAuthorizedRecently()) //if previous color was invalid and then the light returns to ambient, remove session.
      {
        EndChargeSession(sessionToUpdate);
                
        iterator.removeCurrent(); //remove it from the list..
        
        delete sessionToUpdate; //delete charge session.
       
        continue; //keep looking at list objects, if there are any
      }
      else
      {
        sessionToUpdate->prevColorAuthorized = newAuth;
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
   * This function only handles creating new charge sessions.
   */
  void checkForNewChargeSessions()
  {
    if (AuthorizedCarList.isEmpty()) return;
   
    RGBC p1ColorRead = PadManager::readColorSensor(PadManager::Pad1);
    RGBC p2ColorRead = PadManager::readColorSensor(PadManager::Pad2);
    RGBC p3ColorRead = PadManager::readColorSensor(PadManager::Pad3);

    bool shouldCheckP1 = false;
    bool shouldCheckP2 = false;
    bool shouldCheckP3 = false;
    
    if (PadManager::isColorAmbient(PadManager::Pad1,p1ColorRead))
    {
      pad1WasAmbient = true;
      shouldCheckP1 = false;
    }
    else
    {
      shouldCheckP1 = true;
    }
    
    if (PadManager::isColorAmbient(PadManager::Pad2,p2ColorRead))
    {
      pad2WasAmbient = true;
      shouldCheckP2 = false;
    }
    else
    {
      shouldCheckP2 = true;
    }
    
    if (PadManager::isColorAmbient(PadManager::Pad3,p3ColorRead))
    {
      pad3WasAmbient = true;
      shouldCheckP3 = false;
    }
    else
    {
      shouldCheckP3 = true;
    }
    
    ListIterator<AuthorizedCar *> iterator(&AuthorizedCarList);
    
    AuthorizedCar * carToCheck;
    do
    {
      char payload[10];
      payload[9] = 0;
      carToCheck = iterator.current();

      if(carToCheck->isInChargeSession || !carToCheck->isRegistrationComplete())
      {
        continue;
      }      
      
      if (!isPad1InSession && pad1WasAmbient && shouldCheckP1)
      {
        if (carToCheck->isColorAuthorized(PadManager::Pad1, p1ColorRead)) 
        { 
          //create new charge session
          ChargeSession * newSession = new ChargeSession(PadManager::Pad1, carToCheck);
          ChargeSessionList.insert(newSession);
          newSession->prevColorAuthorized = true;
          isPad1InSession = true;
          PadManager::setPadState(PadManager::Pad1,true);
          
          PadManager::setStrToPadID(newSession->chargePad,payload);
          sprintf(&payload[3],"%04X ", carToCheck->vID);
          SerialCommandPacketizer::sendOutboundPacket(SerialCommandPacketizer::ChargeBegin, payload);
                    
          pad1WasAmbient = false;
                    
          continue;
        }
      }
      if (!isPad2InSession && pad2WasAmbient && shouldCheckP2)
      {  
        if (carToCheck->isColorAuthorized(PadManager::Pad2, p2ColorRead)) 
        {
          ChargeSession * newSession = new ChargeSession(PadManager::Pad2, carToCheck);
          ChargeSessionList.insert(newSession);
          newSession->prevColorAuthorized = true;
          isPad2InSession = true;
          PadManager::setPadState(PadManager::Pad2,true);
          
          PadManager::setStrToPadID(newSession->chargePad,payload);
          sprintf(&payload[3],"%04X ", carToCheck->vID);
          SerialCommandPacketizer::sendOutboundPacket(SerialCommandPacketizer::ChargeBegin, payload);
                  
          pad2WasAmbient = false;
                  
          continue;
        }
      }
      if (!isPad3InSession && pad3WasAmbient && shouldCheckP3)
      {
        if (carToCheck->isColorAuthorized(PadManager::Pad3, p3ColorRead)) 
        {
          
          ChargeSession * newSession = new ChargeSession(PadManager::Pad3, carToCheck);
          ChargeSessionList.insert(newSession);
          newSession->prevColorAuthorized = true;
          isPad3InSession = true;
          PadManager::setPadState(PadManager::Pad3,true);
          
          PadManager::setStrToPadID(newSession->chargePad,payload);
          sprintf(&payload[3],"%04X ", carToCheck->vID);
          SerialCommandPacketizer::sendOutboundPacket(SerialCommandPacketizer::ChargeBegin, payload);
          
          pad3WasAmbient = false;
          
          continue;
        }
      }
    }while(iterator.moveNext() && (!isPad1InSession || !isPad2InSession || !isPad3InSession )); //while lis is not empty and any pad is not in a session.
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
      if (sessionToSend->isPadInfoUpdated() && sessionToSend->isVehicleInfoUpdated() && sessionToSend->shouldSendInfo())
      {
        float vCurrent = sessionToSend->getVehicleCurrent();
        float pCurrent = sessionToSend->getPadCurrent();
        float vVoltage = sessionToSend->getVehicleVoltage();
        float pVoltage = sessionToSend->getPadVoltage(); 
        
        char vCurrentStr[13]; //'2222 01.23A \0'
        char pCurrentStr[11]; //'P2 01.23A \0'
        char pVoltageStr[11]; //'P2 01.23V \0'
        char vVoltageStr[13]; //'2222 01.23V \0'

        //add the pad ID to payload strings
        PadManager::setStrToPadID(sessionToSend->chargePad,pCurrentStr);
        PadManager::setStrToPadID(sessionToSend->chargePad,pVoltageStr);
        
        //add the vehicle ID to payload strings
        sprintf(vVoltageStr,"%04X ",sessionToSend->vehicleID); //'2222 \0'
        sprintf(vCurrentStr,"%04X ",sessionToSend->vehicleID);
        
        //copy the data to the strings
        Utilities::floatToStr( vCurrent, &vCurrentStr[5]);
        Utilities::floatToStr( vVoltage, &vVoltageStr[5]);
        Utilities::floatToStr( pCurrent, &pCurrentStr[3]);
        Utilities::floatToStr( pVoltage, &pVoltageStr[3]);
        
        //label the data
        sprintf(&vCurrentStr[10],"A ");
        sprintf(&pCurrentStr[8],"A ");
        sprintf(&vVoltageStr[10],"V ");
        sprintf(&pVoltageStr[8],"V ");
        
        //send the data
        SerialCommandPacketizer::sendOutboundPacket( SerialCommandPacketizer::SendCurrent , vCurrentStr );
        SerialCommandPacketizer::sendOutboundPacket( SerialCommandPacketizer::SendCurrent , pCurrentStr );
        SerialCommandPacketizer::sendOutboundPacket( SerialCommandPacketizer::SendVoltage , vVoltageStr );
        SerialCommandPacketizer::sendOutboundPacket( SerialCommandPacketizer::SendVoltage , pVoltageStr );
      }
    }while(iterator.moveNext());
  }
  
  void updateVehicleVoltage(uint16_t address, float measurement)
  {
    ChargeSession * sessionToUpdate = findChargeSessionByAddress(address);
    if( sessionToUpdate != NULL)
      sessionToUpdate->updateVehicleVoltage(measurement);
  }
  
  void updateVehicleCurrent(uint16_t address, float measurement)
  {
    ChargeSession * sessionToUpdate = findChargeSessionByAddress(address);
    if( sessionToUpdate != NULL)
      sessionToUpdate->updateVehicleCurrent(measurement);
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
    
    EndChargeSession(toDelete);
      
    if(toDelete)
      delete (toDelete);
  }
  
  isPad1InSession = false;
  isPad2InSession = false;
  isPad3InSession = false;
}

void EndChargeSession(ChargeSession * sessionToEnd )
{
  if (!sessionToEnd) return;
  
  char payload[10];
  payload[9] = 0;

  PadManager::setPadState(sessionToEnd->chargePad, false);
  
  switch(sessionToEnd->chargePad)
  {
    case PadManager::Pad1:
      isPad1InSession = false;
      break;
    case PadManager::Pad2:
      isPad2InSession = false;
      break;
    case PadManager::Pad3:
      isPad3InSession = false;
      break;
  }
  
  setStrToPadID(sessionToEnd->chargePad,payload);
  sprintf(&payload[3],"%04X ", sessionToEnd->vehicleID);
  SerialCommandPacketizer::sendOutboundPacket(SerialCommandPacketizer::ChargeEnd, payload);
}

/**
 * Given a vehicle ID, iterates the list of authorized cars and returns the charge session object.
 */
ChargeSession * findChargeSessionByAddress(uint16_t address)
{
  //iterate through list
  ListIterator<ChargeSession *> it(&ChargeSessionList);

  do
  {
    //if address == car_address
    ChargeSession* temp =it.current();
    if(temp->vehicleID == address)
      return temp;
      
  }while(it.moveNext());
  
  return NULL;
}