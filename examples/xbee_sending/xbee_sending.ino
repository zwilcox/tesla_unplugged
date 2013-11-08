#include <XBee.h>


XBee xbee; 
void setup()
{
  XBee xbee = XBee();
  Serial.begin(9600); // used for printing;  
  Serial.println("starting up");
}

void loop()
{
  uint8_t payload[] = "hello world";
  Tx16Request tx = Tx16Request(0x5678, payload, sizeof(payload));
  xbee.send(tx);
  
  delay(1000);
  
}
