#include <Arduino.h>
#include <utilities.h>

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
  
};