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
#define MASTER_ADDRESS 0x5678

static bool should_broadcast;
const static String voltage_preamble = "SV ";
const static String current_preamble = "SA ";
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
    int count = 0;
    uint8_t* payload = prepare_message(voltage_preamble, v_measurement, &count);
    Tx16Request tx = Tx16Request(MASTER_ADDRESS, payload, count);
    radio->send(tx);
    //send current
    count = 0;
   payload = prepare_message(current_preamble, c_measurement, &count);
    tx = Tx16Request(MASTER_ADDRESS, payload, count);
    radio->send(tx);
    delay(500);
  }  
 
    
}

uint8_t* prepare_message(const String message, float f, int* sizeOf)
{
  //  Serial.println(f);
  char c [sizeof(f)];
  dtostrf(f, 5, 2, c);
  // SV #V  or
  // SA #A
  String temp = message + c;
 // Serial.print(temp);
  uint8_t results[temp.length()];
  temp.getBytes(results, temp.length());
  *sizeOf = temp.length();
 Serial.println((char*)results);
  return results; 
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
