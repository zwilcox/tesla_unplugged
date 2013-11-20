#include <XBee.h>
#include <voltage_reader.h>
#include <ACS712.h>

#define CURRENT_PORT A0  
#define VOLTAGE_PORT A1
#define LED A7
#define R1 97500
#define R2 10000

static car_number = 0;

static ACS712* current;
static XBee* radio;
static voltage_reader* volts;

void setup()
{
//set up current
current = new ACS712(CURRENT_PORT);
//set up radio
radio = new XBee();
//set up voltage
volts = new voltage_reader(VOLTAGE_PORT11);
//set up led

//set up button
  Serial.begin(9600);
}

void loop()
{
  //check button for led
  //check button
  //check voltage
  //if voltage high enough
    //check current
    //send voltage
    //send current
  Serial.println(volts->get_voltage());
   delay(500); 
}
