#include "ACS712.h"

ACS712::ACS712(int pin)
{
	this->pin = pin;
}
void ACS712::set_analog(int anal)
{
	this->pin = anal;
}
float ACS712::get_current()
{
	return get_current(50);
}
float ACS712::get_current(int iterations)
{
	float average = 0.0f;
	for(int i = 0; i < iterations; i++) 
		//values calculated from data sheet
		average += (.0264 * analogRead(this->pin) -13.51) / iterations;
		
	return average;
}
