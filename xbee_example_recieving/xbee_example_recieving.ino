#include <XBee.h>


XBee xbee; 
void setup()
{
  XBee xbee = XBee();
  xbee.begin(9600);

  Serial.println("starting up");
  
}

void loop()
{
  
  xbee.readPacket();
 if (xbee.getResponse().isAvailable())
 {
    Rx16Response rx16 = Rx16Response();
    xbee.getResponse().getRx16Response(rx16);
    uint8_t length = rx16.getDataLength();
    Serial.println(length);
    Serial.print("The remote address is: ");
    Serial.println(rx16.getRemoteAddress16());
    uint8_t* data = rx16.getData();
    for(int i = 0; i < length; i++)
    {
      Serial.print((char)data[i]);
    }
    Serial.println("");
 }
}
