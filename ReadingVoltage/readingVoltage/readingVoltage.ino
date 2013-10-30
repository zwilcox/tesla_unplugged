#define VOLTAGE_READ A0
#define V_IN_R 97.7f
#define GND_R 98.1f
#define REFV 5

float rFactor;
void setup()
{
  Serial.begin(9600);
  rFactor = 1023.0 * (GND_R)/ (GND_R + V_IN_R);
  Serial.println("Starting up!");
}

void loop()
{
  int sensorValue = analogRead(VOLTAGE_READ);
  float voltage = (sensorValue / rFactor)* REFV;
  Serial.print("V is ");
  Serial.println(voltage); 
  delay(500);


}
