#pragma once

#include <Arduino.h>
#include <SoftADJDS311.h>

namespace Utilities
{

  uint8_t charArrayLength( char * array );
  int get_free_memory( void );
  
  void floatToStr( float val, char * str );
  void zeroColor(RGBC &color);
};

