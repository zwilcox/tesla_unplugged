#include <DigitalIO.h>
#include <SoftADJDS311.h>
#include "ColorSense.h"
#include "XBeeUtility.h"
#include <XBee.h>

void temporary_ColorSensorCalibrationPrompt()
{
  using namespace ColorSense;
  setLEDState(Sensor1, true);
  setLEDState(Sensor2, true);
  setLEDState(Sensor3, true);  
     
  Serial.print("Hold a white card above Sensor 1 then push any key to calibrate.\n");
  while(!Serial.available());
  while(Serial.available()) Serial.read();
  calibrateSensor(Sensor1);
  
  Serial.print("Hold a white card above Sensor 2 then push any key to calibrate.\n");
  while(!Serial.available());
  while(Serial.available()) Serial.read();
  calibrateSensor(Sensor2);
  
  Serial.print("Hold a white card above Sensor 3 then push any key to calibrate.\n");
  while(!Serial.available());
  while(Serial.available()) Serial.read();
  calibrateSensor(Sensor3);
  
  setLEDState(Sensor1, false);
  setLEDState(Sensor2, false);
  setLEDState(Sensor3, false);  
  
}

void temporary_PrintSensorData()
{
  using namespace ColorSense;
  RGBC color1 = readSensor(Sensor1); //read the color
  RGBC color2 = readSensor(Sensor2); //read the color
  RGBC color3 = readSensor(Sensor3); //read the color
  
  Serial.print("1: ");
  Serial.print((int)((color1.red/1024.0) * 255));
  Serial.print(" | ");
  Serial.print((int)((color1.green/1024.0) * 255));
  Serial.print(" | ");
  Serial.print((int)((color1.blue/1024.0) * 255));
  Serial.print(" | ");
  Serial.println((int)((color1.clear/1024.0) * 255));
 
  Serial.print("2: ");
  Serial.print((int)((color2.red/1024.0) * 255));
  Serial.print(" | ");
  Serial.print((int)((color2.green/1024.0) * 255));
  Serial.print(" | ");
  Serial.print((int)((color2.blue/1024.0) * 255));
  Serial.print(" | ");
  Serial.println((int)((color2.clear/1024.0) * 255));
    
  Serial.print("3: ");
  Serial.print((int)((color3.red/1024.0) * 255));
  Serial.print(" | ");
  Serial.print((int)((color3.green/1024.0) * 255));
  Serial.print(" | ");
  Serial.print((int)((color3.blue/1024.0) * 255));
  Serial.print(" | ");
  Serial.println((int)((color3.clear/1024.0) * 255));
  
  Serial.println("");
}


void temporary_printIfXBeeReceive()
{
  if (XBeeUtility::isDataAvailable())
  {
    XBeeUtility::tXBeePacket * pkt = XBeeUtility::getPkt();
    
    Serial.print("XBee Receive: ");
    Serial.print(pkt->getLength());
    Serial.print(" bytes from: ");
    Serial.print(pkt->getRemoteAddress());
    Serial.println(".");
    Serial.println(pkt->getData());
    Serial.println("");
    
    if(pkt)
      delete(pkt);
  }
}

void setup() 
{
  Serial.begin(9600);
  ColorSense::Initialize();
  XBeeUtility::Initialize();
  
  ColorSense::setLEDState(ColorSense::Sensor1, true);
  ColorSense::setLEDState(ColorSense::Sensor2, true);
  ColorSense::setLEDState(ColorSense::Sensor3, true);  
     
  
  
  /**temporary for testing**/
  temporary_ColorSensorCalibrationPrompt();
  /**end temporary for testing**/
}

void loop() 
{
  temporary_printIfXBeeReceive();
  temporary_PrintSensorData();
  
  delay(500); //just here to slow down the serial outputs  
}

