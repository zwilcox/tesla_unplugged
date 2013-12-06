#include <Arduino.h>
#include "Utilities.h"

extern int __bss_end;  
extern void *__brkval;

namespace Utilities
{
  
  /***** get_free_memory() ******
   * Returns the amount of free memory remaining, in bytes.
   * The space remaining is the space between the bottom of the stack and the top of the heap.
   ******************************/
  int get_free_memory()
  {
    int free_memory;

    if((int)__brkval == 0)
      free_memory = ((int)&free_memory) - ((int)&__bss_end);
    else
      free_memory = ((int)&free_memory) - ((int)__brkval);

    return free_memory;
  }

  /***** charArrayLength( char * array ) ******
   * Returns the length of a NULL-TERMINATED array of characters.
   * Important: array MUST BE NULL-TERMINATED else function will return incorrectly.
   ********************************************/
  uint8_t charArrayLength( char * array)
  {
    uint8_t i = 0;

    for(char * c = array ; *c != '\0'; c++, i++);
    
    return i;

  }
  
  /***** floatToStr( float val, char * str) ******
   * Reads the float val and prints 5 characters into the char * array str.
   * Important: array size 6 or greater or BAD things happen.
   ********************************************/
  void floatToStr( float val, char * str)
  {
    sprintf(str,"%02d",(int) val);
    sprintf(&str[2],".");
    
    uint8_t printIndx = 3;
    unsigned int precision = 100;
    unsigned int frac;
    if(val >= 0)
      frac = (val - int(val)) * precision;
    else
       frac = (int(val)- val ) * precision;
    int frac1 = frac;
    while( frac1 /= 10 )
        precision /= 10;
    precision /= 10;
    while(  precision /= 10)
        sprintf(&str[printIndx++],"0");

    sprintf(&str[printIndx],"%d",frac);
  }
  
  
  void zeroColor(RGBC &color)
  {
    color.red = 0;
    color.blue = 0;
    color.green = 0;
    color.clear = 0;
  }
  
};