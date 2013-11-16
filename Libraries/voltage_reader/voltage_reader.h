#ifndef voltage
#define voltage
#include "Arduino.h"
class voltage_reader
{
	private:
    	        int pin;
    	        float r_factor;
    	        float reference_v;
	
	public:
        	/*
        	*	Sets up the ADC to read voltage measurements
        	*	Defaults the reference voltage to be 5 V
        	* 	Defaults the dividing factor to be 4.
        	*	
        	*	@param pin - the ADC pin to read voltage
        	*/ 
        	voltage_reader(int pin);
        	/*
        	*	Sets up the ADC to read voltage measurements
        	*	Defaults the reference voltage to be 5 V
        	* 	The divining factor is calculated at (r2 / (r2 + r1))
        	*	
        	*	@param pin - the ADC pin to read voltage
        	*	@param r1  - resistor connected to voltage being measured
        	*	@param r2  - resistor connected to ground
        	*/ 
        	voltage_reader(int pin, int r1, int r2);
        	/*
        	*	Set changes the ADC pin used to measure voltage
        	*	Uses builder method to so caller can keep setting values;
        	*	@param pin - the ADC pin to read voltage
        	*/ 
        	voltage_reader set_pin(int pin);
        	/*
        	*	Set changes the reference voltage.
        	*	Uses builder method so caller can keep setting values;
        	*	@param voltage - changes the reference voltage used in calculations
        	*/
        	voltage_reader set_reference_v(float voltage);
        	/*
        	*	Set resistors in voltage dividers
        	*	Uses builder method so caller can keep setting values;
        	*	@param r1  - resistor connected to voltage being measured
        	*	@param r2  - resistor connected to ground
        	*/
        	voltage_reader set_resistance(int r1, int r2);
        	/*
        	*	Reads the ADC once and returns the voltage reading;
        	*/
        	float get_voltage();
        	/*
        	*	Reads the ADC iteration times and finds the average voltage
        	* 	@param iterations - number of times adc is read to find average voltage
        	*/
        	float get_voltage(int iterations);
};
#endif