#include <XBee.h>
#include <voltage_reader.h>
#include <ACS712.h>
#include "Transponder.h"
#include <avr/interrupt.h>

#define CAR_NUMBER 0
#define CURRENT_PORT 0  
#define VOLTAGE_PORT 1
#define LED 7
#define BUTTON 2

static bool should_broadcast;

static ACS712* current;
static XBee* radio;
static voltage_reader* volts;
static Transponder* trans;

void setup()
{

  should_broadcast = false;

  //set up current
  current = new ACS712(CURRENT_PORT);
  //set up radio
  radio = new XBee();
  //set up voltage
  volts = new voltage_reader(VOLTAGE_PORT);
  //set up transponder
  trans = new Transponder(  LED);  //
 
     
  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, HIGH);    // Enable pullup resistor

  //set up interrupt 
  // enable global interrupts
 attachInterrupt(0, pin2ISR, FALLING);

//set up button
  Serial.begin(9600);
 
}

void loop()
{

  //check voltage
  float v_measurement = volts->get_voltage(50);
  
  //if voltage high enough
  //step down converter doesn't come on until 4v
  if(v_measurement >= 4.0f)
  {
    //check current
    float c_measurement = current->get_current();
    //send voltage
    //send current
  }
  Serial.println(volts->get_voltage(50));
   delay(500); 
}

void pin2ISR()
{
  
   static unsigned long last_interrupt_time = 0;
   unsigned long interrupt_time = millis();
    // If interrupts come faster than 200ms, assume it's a bounce and ignore
    if (interrupt_time - last_interrupt_time > 200) 
    {
      if(trans->get_is_on())
        trans->turn_off();
      else
        trans->turn_on();
      
      
    }
  last_interrupt_time = interrupt_time;

}
