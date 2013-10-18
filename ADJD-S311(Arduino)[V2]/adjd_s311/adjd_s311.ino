#include <SoftADJDS311.h>
#include <SoftI2C.h>

#define SENSORLED1 23 
#define SENSORLED2 29 
#define SDA1 24
#define SCL1 25
#define SDA2 26
#define SCL2 27
SoftADJDS311 color_sensor1(SENSORLED1,SDA1,SCL1);
SoftADJDS311 color_sensor2(SENSORLED2,SDA2,SCL2);


void setup(){
  Serial.begin(9600);
 
  color_sensor1.init();  
  color_sensor1.ledOn(); //turn LED on
 
  color_sensor2.init();  
  color_sensor2.ledOn(); //turn LED on
 
  Serial.println("Hold a wite peice of paper above sensor then press any key to calibrate...\n");
  while(!Serial.available());
  
  //Calibrate white 
  //Need to hold white card in front (1-3mm) of it to calibrate from
  color_sensor1.calibrate();  
  color_sensor1.ledOff();
  
  color_sensor2.calibrate();  
  color_sensor2.ledOff();

}

void loop(){
  RGBC color1 = color_sensor1.read(); //read the color
  RGBC color2 = color_sensor2.read(); //read the color
  
  Serial.print((color1.red/1024.0) * 255);
  Serial.print(" | ");
  Serial.print((color1.green/1024.0) * 255);
  Serial.print(" | ");
  Serial.print((color1.blue/1024.0) * 255);
  Serial.print(" | ");
  Serial.println((color1.clear/1024.0) * 255);
  
  Serial.print((color2.red/1024.0) * 255);
  Serial.print(" | ");
  Serial.print((color2.green/1024.0) * 255);
  Serial.print(" | ");
  Serial.print((color2.blue/1024.0) * 255);
  Serial.print(" | ");
  Serial.println((color2.clear/1024.0) * 255);
  
  Serial.println();
  delay(500); //just here to slow down the serial outputs  
}

