#pragma once

#include <Arduino.h>
#include "SerialCommandPacketizer.h"
#include <SoftADJDS311.h>

namespace PacketProcessor
{
  void commandGetColor( char * pkt );
  void commandCalColor( char * pkt );
  void commandToggleLED( char * pkt );
  void commandTogglePad( char * pkt );
  void commandGetVoltage( char * pkt );
  void commandGetCurrent( char * pkt );
}