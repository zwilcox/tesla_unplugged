#ifndef acs
#define acs
#include "Arduino.h"
class ACS712
{

	private:
		int pin;
		
	public:
	/*
	* 	Set's up the current sensor
	* 	@param pin - set the analog pin that ACS712 is connected to
	*/
	ACS712(int pin);
	/*
	*	reset the analog port
	* 	@param anal - the desired analog port
	*/
	void set_analog(int anal);
	/*
	*	get_current reads the analog port the number of iterations and finds the average
	* 	Iterations is defaulted to be 50.  If this is the value of iterations, get_currents will
	*	read the analog port 50 times and return the average reading.
	*	
	*/
	float get_current();
	
	/*
	*	get_current reads the analog port the number of iterations and finds the average
	* 	Iterations is defaulted to be 50.  If this is the value of iterations, get_currents will
	*	read the analog port 50 times and return the average reading.
	*	
	*/
	float get_current(int iterations);
};
#endif
