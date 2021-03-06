#include "voltage_reader.h"
voltage_reader::voltage_reader(int pin)
{
	this->pin = pin;
	r_factor = 1023.0f / 6.5f;
	reference_v = 5.0f;
}

voltage_reader::voltage_reader(int pin, uint32_t r1, uint32_t r2)
{
	this->pin = pin;
	r_factor = (r2 + 0.0f) / (r2 + r1 + 0.0f);
	r_factor = 1023.0 * r_factor;
  reference_v = 5.0f;
}
voltage_reader voltage_reader::set_pin(int pin)
{
	this->pin = pin;
	return *this;
}
voltage_reader voltage_reader::set_reference_v(float v)
{
  reference_v = v;
  return *this;
}

voltage_reader voltage_reader::set_resistance(uint32_t r1, uint32_t r2)
{
	r_factor = (r2 + 0.0f) / (r2 + r1 + 0.0f);
	r_factor = 1023.0 * r_factor;

	return *this;
}

float voltage_reader::get_voltage()
{
	return get_voltage(1);
}

float voltage_reader::get_voltage(int iterations)
{
	float average = 0.0f;
	for(int i = 0; i < iterations; i++)
	{        
    average += (analogRead(pin) / r_factor) * reference_v;
	}

	return average / iterations;
}