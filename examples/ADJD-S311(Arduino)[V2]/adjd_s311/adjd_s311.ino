#include <SoftADJDS311.h>
#include <DigitalIO.h>

#define SENSORLED1	23
#define SENSORLED2	24 
#define SENSORLED3	25
#define SDA1 		26
#define SCL1 		27
#define SDA2 		28
#define SCL2 		29
#define SDA3 		30
#define SCL3 		31
SoftADJDS311 color_sensor1(SENSORLED1,SDA1,SCL1);
SoftADJDS311 color_sensor2(SENSORLED2,SDA2,SCL2);
SoftADJDS311 color_sensor3(SENSORLED3,SDA3,SCL3);

void setup(){
  Serial.begin(9600);

  color_sensor1.init();  
  color_sensor1.ledOn(); //turn LED on
  
  color_sensor2.init();  
  color_sensor2.ledOn(); //turn LED on
  
   color_sensor3.init();  
   color_sensor3.ledOn(); //turn LED on
 
  //Calibrate white 
  //Need to hold white card in front (1-3mm) of it to calibrate from
  Serial.print("Hold a white card above sensors then push any key to calibrate.\n");
  while(!Serial.available());
  Serial.read();
  
  
  Serial.print("Calibrate1\n");
  color_sensor1.calibrate();  
  
  Serial.print("calibrate2\n");
  color_sensor2.calibrate();  
  
  Serial.print("calibrate3\n");
  color_sensor3.calibrate();  

  color_sensor1.ledOff();
  color_sensor2.ledOff();
  color_sensor3.ledOff();

}
char on = 0;
void loop(){
  RGBC color1 = color_sensor1.read(); //read the color
  RGBC color2 = color_sensor2.read(); //read the color
  RGBC color3 = color_sensor3.read(); //read the color
  
  if (Serial.available())
  {
    if (Serial.read())
      if (!on)
      {
        color_sensor1.ledOn();
        color_sensor2.ledOn();
        color_sensor3.ledOn();
        on = 1;
      }
      else
      {
        color_sensor1.ledOff();
        color_sensor2.ledOff();
        color_sensor3.ledOff();
        on = 0;
      }
  }
  
  Serial.print("1: ");
  Serial.print((color1.red/1024.0) * 255);
  Serial.print(" | ");
  Serial.print((color1.green/1024.0) * 255);
  Serial.print(" | ");
  Serial.print((color1.blue/1024.0) * 255);
  Serial.print(" | ");
  Serial.println((color1.clear/1024.0) * 255);
 
  Serial.print("2: "); 
  Serial.print((color2.red/1024.0) * 255);
  Serial.print(" | ");
  Serial.print((color2.green/1024.0) * 255);
  Serial.print(" | ");
  Serial.print((color2.blue/1024.0) * 255);
  Serial.print(" | ");
  Serial.println((color2.clear/1024.0) * 255);
    
  Serial.print("3: ");
  Serial.print((color3.red/1024.0) * 255);
  Serial.print(" | ");
  Serial.print((color3.green/1024.0) * 255);
  Serial.print(" | ");
  Serial.print((color3.blue/1024.0) * 255);
  Serial.print(" | ");
  Serial.println((color3.clear/1024.0) * 255);
  
  Serial.println();
  delay(500); //just here to slow down the serial outputs  
}

