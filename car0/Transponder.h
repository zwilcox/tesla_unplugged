#include "Arduino.h"

class Transponder
{
  private:
          unsigned int led_pin;
          volatile bool is_on;
  public:
        Transponder(unsigned int led);
        bool get_is_on();
        void turn_off();
        void turn_on();
};
