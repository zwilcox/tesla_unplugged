#include <ADJDS311.h>
#include <Wire.h>

#define SENSORLED 2 //LED on the ADJDS-311
ADJDS311 color_sensor(SENSORLED);


void setup(){
  Serial.begin(9600);
  color_sensor.init();
  
  color_sensor.ledOn(); //turn LED on
  //Calibrate white 
  //Need to hold white card in front (1-3mm) of it to calibrate from
  //color_sensor.calibrate();
  color_sensor.ledOff();

}

void loop(){
  RGBC color = color_sensor.read(); //read the color
  
  Serial.print(color.red);
  Serial.print(" | ");
  Serial.print(color.green);
  Serial.print(" | ");
  Serial.print(color.blue);
  Serial.print(" | ");
  Serial.println(color.clear);
  
  delay(500); //just here to slow down the serial outputs  
}

