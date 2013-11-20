#include "ACS712.h"


static ACS712* amp_read; 
void setup()
{
  amp_read = new ACS712(A0);
  Serial.begin(9600);  // sets the serial port to 9600
}

void loop()
{
 
  Serial.println(amp_read->get_current());
  delay(500);                        // wait 100ms for next reading
   Serial.println(amp_read->get_current(100));
  delay(500);
}
