#include "Transponder.h"


Transponder::Transponder(unsigned int led)
{
  
    Serial.begin(9600);

    led_pin = led;
    //set up button

    //set up led
    pinMode(led_pin, OUTPUT);
    //start turned off;
    turn_off();
   
}

bool Transponder::get_is_on()
{
   return  is_on; 
}
void Transponder::turn_off()
{
    digitalWrite(led_pin, LOW); 
    is_on = false;
}
void Transponder::turn_on()
{
    digitalWrite(led_pin, HIGH ); 
    is_on = true;
}

