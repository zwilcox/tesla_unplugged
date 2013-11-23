#include <XBee.h>
#define PIN 2

XBee* radio;
uint8_t payload[] = "test1";
Tx16Request tx;

void setup()
{
  radio = new XBee();
  tx = Tx16Request(0x5678, payload, sizeof(payload));

  pinMode(PIN, INPUT);
  digitalWrite(PIN, HIGH);
  Serial.println("Staring up");  
  attachInterrupt(0, pin2ISR, FALLING);

}

void loop()
{

 
  
}

void pin2ISR()
{
   static unsigned long last_interrupt_time = 0;
   unsigned long interrupt_time = millis();
    // If interrupts come faster than 200ms, assume it's a bounce and ignore
    if (interrupt_time - last_interrupt_time > 200) 
    {
      
       radio->send(tx);
       Serial.println("message sent");
       delay(5000);
      
      
    }
  last_interrupt_time = interrupt_time;
  
}
