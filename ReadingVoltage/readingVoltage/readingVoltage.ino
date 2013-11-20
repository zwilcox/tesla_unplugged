#include "voltage_reader.h"

voltage_reader* volts;
void setup()
{
  Serial.begin(9600);
  
  volts = new voltage_reader(A0);
  //3 for the ratio of voltage divider
 // rFactor = 1023.0 / 4;  //1023 for the resolution of the pot
  Serial.println("Starting up!");
}

void loop()
{
//  int sensorValue = analogRead(VOLTAGE_READ);
  
  //float voltage = (sensorValue / rFactor)* REFV;
  Serial.print("V is ");
  Serial.println(volts->get_voltage()); 
  delay(500);


}
